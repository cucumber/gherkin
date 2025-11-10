package io.cucumber.gherkin;

import io.cucumber.messages.IdGenerator;
import io.cucumber.messages.types.DataTable;
import io.cucumber.messages.types.DocString;
import io.cucumber.messages.types.Examples;
import io.cucumber.messages.types.Feature;
import io.cucumber.messages.types.FeatureChild;
import io.cucumber.messages.types.GherkinDocument;
import io.cucumber.messages.types.Pickle;
import io.cucumber.messages.types.PickleDocString;
import io.cucumber.messages.types.PickleStep;
import io.cucumber.messages.types.PickleStepArgument;
import io.cucumber.messages.types.PickleStepType;
import io.cucumber.messages.types.PickleTable;
import io.cucumber.messages.types.PickleTableCell;
import io.cucumber.messages.types.PickleTableRow;
import io.cucumber.messages.types.PickleTag;
import io.cucumber.messages.types.Rule;
import io.cucumber.messages.types.RuleChild;
import io.cucumber.messages.types.Scenario;
import io.cucumber.messages.types.Step;
import io.cucumber.messages.types.StepKeywordType;
import io.cucumber.messages.types.TableCell;
import io.cucumber.messages.types.TableRow;
import io.cucumber.messages.types.Tag;
import org.jspecify.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static io.cucumber.messages.types.StepKeywordType.CONJUNCTION;
import static io.cucumber.messages.types.StepKeywordType.UNKNOWN;
import static java.util.Collections.emptyList;
import static java.util.Collections.singletonList;

final class PickleCompiler {

    private final IdGenerator idGenerator;

    PickleCompiler(IdGenerator idGenerator) {
        this.idGenerator = idGenerator;
    }

    List<Pickle> compile(GherkinDocument gherkinDocument, String uri) {
        List<Pickle> pickles = new ArrayList<>(GherkinParser.FEATURE_FILE_AVERAGE_LINE_COUNT);
        if (!gherkinDocument.getFeature().isPresent()) {
            return pickles;
        }
        Feature feature = gherkinDocument.getFeature().get();

        String language = feature.getLanguage();

        compileFeature(pickles, feature, language, uri);
        return pickles;
    }

    private void compileFeature(List<Pickle> pickles, Feature feature, String language, String uri) {
        List<Tag> tags = feature.getTags();
        List<Step> featureBackgroundSteps = new ArrayList<>();
        for (FeatureChild featureChild : feature.getChildren()) {
            if (featureChild.getBackground().isPresent()) {
                featureBackgroundSteps.addAll(featureChild.getBackground().get().getSteps());
            } else if (featureChild.getRule().isPresent()) {
                compileRule(pickles, featureChild.getRule().get(), tags, featureBackgroundSteps, language, uri);
            } else if (featureChild.getScenario().isPresent()) {
                Scenario scenario = featureChild.getScenario().get();
                if (scenario.getExamples().isEmpty()) {
                    compileScenario(pickles, scenario, tags, featureBackgroundSteps, language, uri);
                } else {
                    compileScenarioOutline(pickles, scenario, tags, featureBackgroundSteps, language, uri);
                }
            }
        }
    }

    private void compileRule(List<Pickle> pickles, Rule rule, List<Tag> parentTags, List<Step> featureBackgroundSteps, String language, String uri) {
        List<Step> ruleBackgroundSteps = new ArrayList<>(featureBackgroundSteps);

        List<Tag> ruleTags = compileTags(parentTags, rule.getTags());

        for (RuleChild ruleChild : rule.getChildren()) {
            if (ruleChild.getBackground().isPresent()) {
                ruleBackgroundSteps.addAll(ruleChild.getBackground().get().getSteps());
            } else if (ruleChild.getScenario().isPresent()) {
                Scenario scenario = ruleChild.getScenario().get();
                if (scenario.getExamples().isEmpty()) {
                    compileScenario(pickles, scenario, ruleTags, ruleBackgroundSteps, language, uri);
                } else {
                    compileScenarioOutline(pickles, scenario, ruleTags, ruleBackgroundSteps, language, uri);
                }
            }
        }
    }

    private void compileScenario(List<Pickle> pickles, Scenario scenario, List<Tag> parentTags, List<Step> backgroundSteps, String language, String uri) {
        List<PickleStep> steps = compilePickleSteps(backgroundSteps, scenario.getSteps(), emptyList(), null);
        List<Tag> scenarioTags = compileTags(parentTags, scenario.getTags());
        List<String> sourceIds = singletonList(scenario.getId());

        Pickle pickle = new Pickle(
                idGenerator.newId(),
                uri,
                scenario.getLocation(),
                scenario.getName(),
                language,
                steps,
                pickleTags(scenarioTags),
                sourceIds
        );
        pickles.add(pickle);
    }

    private List<Tag> compileTags(List<Tag> parentTags, List<Tag> scenarioTags) {
        if (parentTags.isEmpty()) {
            // Avoid array creation
            return scenarioTags;
        }
        if (scenarioTags.isEmpty()) {
            // Avoid array creation
            return parentTags;
        }
        List<Tag> tags = new ArrayList<>(parentTags.size() + scenarioTags.size());
        tags.addAll(parentTags);
        tags.addAll(scenarioTags);
        return tags;
    }

    private List<PickleStep> compilePickleSteps(List<Step> backgroundSteps, List<Step> scenarioSteps, List<TableCell> variableCells, @Nullable TableRow valuesRow) {
        if (scenarioSteps.isEmpty()) {
            // usually, a scenario has at least one step, but that's not mandatory
            return new ArrayList<>(0);
        }
        List<PickleStep> steps = new ArrayList<>(backgroundSteps.size() + scenarioSteps.size());
        StepKeywordType lastKeywordType = UNKNOWN;
        for (Step step : backgroundSteps) {
            StepKeywordType stepKeywordType = step.getKeywordType().orElse(UNKNOWN);
            if (stepKeywordType != CONJUNCTION) {
                lastKeywordType = stepKeywordType;
            }
            steps.add(pickleBackgroundStep(step, lastKeywordType));
        }
        for (Step scenarioStep : scenarioSteps) {
            StepKeywordType stepKeywordType = scenarioStep.getKeywordType().orElse(UNKNOWN);
            if (stepKeywordType != CONJUNCTION) {
                lastKeywordType = stepKeywordType;
            }
            steps.add(pickleStep(scenarioStep, variableCells, valuesRow, lastKeywordType));
        }
        return steps;
    }

    private void compileScenarioOutline(List<Pickle> pickles, Scenario scenario, List<Tag> parentTags, List<Step> backgroundSteps, String language, String uri) {
        List<Tag> scenarioTags = compileTags(parentTags, scenario.getTags());
        for (final Examples examples : scenario.getExamples()) {
            if (!examples.getTableHeader().isPresent()) continue;
            List<TableCell> variableCells = examples.getTableHeader().get().getCells();
            for (final TableRow valuesRow : examples.getTableBody()) {
                List<PickleStep> steps = compilePickleSteps(backgroundSteps, scenario.getSteps(), variableCells, valuesRow);
                List<Tag> tags = compileTags(scenarioTags, examples.getTags());
                List<String> sourceIds = List.of(scenario.getId(), valuesRow.getId());
                Pickle pickle = new Pickle(
                        idGenerator.newId(),
                        uri,
                        valuesRow.getLocation(),
                        interpolate(scenario.getName(), variableCells, valuesRow.getCells()),
                        language,
                        steps,
                        pickleTags(tags),
                        sourceIds
                );

                pickles.add(pickle);
            }
        }
    }

    @SuppressWarnings("ForLoopReplaceableByForEach") // classic 'for' loop is ~2x faster than 'for-each'
    private PickleTable pickleDataTable(DataTable dataTable, List<TableCell> variableCells, List<TableCell> valueCells) {
        List<TableRow> rows = dataTable.getRows();
        int rowCount = rows.size();
        List<PickleTableRow> newRows = new ArrayList<>(rowCount);
        for (int i = 0; i < rowCount; i++) {
            TableRow row = rows.get(i);
            List<TableCell> cells = row.getCells();
            int cellCount = cells.size();
            List<PickleTableCell> newCells = new ArrayList<>(cellCount);
            for (int j = 0; j < cellCount; j++) {
                TableCell cell = cells.get(j);
                newCells.add(new PickleTableCell(interpolate(cell.getValue(), variableCells, valueCells)));
            }
            newRows.add(new PickleTableRow(newCells));
        }
        return new PickleTable(newRows);
    }

    private PickleDocString pickleDocString(DocString docString, List<TableCell> variableCells, List<TableCell> valueCells) {
        return new PickleDocString(
                docString.getMediaType().isPresent() ? interpolate(docString.getMediaType().get(), variableCells, valueCells) : null,
                interpolate(docString.getContent(), variableCells, valueCells)
        );
    }

    private PickleStep pickleStep(Step step, List<TableCell> variableCells, @Nullable TableRow valuesRow, StepKeywordType keywordType) {
        List<TableCell> valueCells = valuesRow == null ? emptyList() : valuesRow.getCells();
        String stepText = interpolate(step.getText(), variableCells, valueCells);

        PickleStepArgument argument = null;
        Optional<DataTable> dataTable = step.getDataTable();
        if (dataTable.isPresent()) {
            argument = new PickleStepArgument(null, pickleDataTable(dataTable.get(), variableCells, valueCells));
        }
        Optional<DocString> docString = step.getDocString();
        if (docString.isPresent()) {
            argument = new PickleStepArgument(pickleDocString(docString.get(), variableCells, valueCells), null);
        }

        List<String> astNodeIds;
        if (valuesRow != null) {
            astNodeIds = List.of(step.getId(), valuesRow.getId());

        } else {
            astNodeIds = List.of(step.getId());
        }

        return new PickleStep(
                argument,
                astNodeIds,
                idGenerator.newId(),
                pickleStepType(keywordType),
                stepText
        );
    }

    private static PickleStepType pickleStepType(StepKeywordType keywordType) {
        return switch (keywordType) {
            case CONTEXT -> PickleStepType.CONTEXT;
            case ACTION -> PickleStepType.ACTION;
            case OUTCOME -> PickleStepType.OUTCOME;
            default -> PickleStepType.UNKNOWN;
        };
    }

    private PickleStep pickleBackgroundStep(Step step, StepKeywordType keywordType) {
        // Background steps are not interpolated
        return pickleStep(step, emptyList(), null, keywordType);
    }

    private String interpolate(String name, List<TableCell> variableCells, List<TableCell> valueCells) {
        for (int i = 0, variableCellsSize = variableCells.size(); i < variableCellsSize; i++) {
            TableCell variableCell = variableCells.get(i);
            TableCell valueCell = valueCells.get(i);
            String header = variableCell.getValue();
            String value = valueCell.getValue();
            name = name.replace("<" + header + ">", value);
        }
        return name;
    }

    private List<PickleTag> pickleTags(List<Tag> tags) {
        if (tags.isEmpty()) {
            return new ArrayList<>(0);
        }
        List<PickleTag> result = new ArrayList<>();
        for (Tag tag : tags) {
            result.add(pickleTag(tag));
        }
        return result;
    }

    private PickleTag pickleTag(Tag tag) {
        return new PickleTag(tag.getName(), tag.getId());
    }

}
