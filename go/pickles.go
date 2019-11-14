package gherkin

import (
	"fmt"
	"github.com/cucumber/cucumber-messages-go/v7"
	"strings"
)

func Pickles(gherkinDocument messages.GherkinDocument, uri string, newId func() string) []*messages.Pickle {
	pickles := make([]*messages.Pickle, 0)
	if gherkinDocument.Feature == nil {
		return pickles
	}
	language := gherkinDocument.Feature.Language

	pickles = compileFeature(pickles, *gherkinDocument.Feature, uri, language, newId)
	return pickles
}

func compileFeature(pickles []*messages.Pickle, feature messages.GherkinDocument_Feature, uri string, language string, newId func() string) []*messages.Pickle {
	backgroundSteps := make([]*messages.Pickle_PickleStep, 0)
	featureTags := feature.Tags
	for _, child := range feature.Children {
		switch t := child.Value.(type) {
		case *messages.GherkinDocument_Feature_FeatureChild_Background:
			backgroundSteps = append(backgroundSteps, pickleSteps(t.Background.Steps, newId)...)
		case *messages.GherkinDocument_Feature_FeatureChild_Rule_:
			pickles = compileRule(pickles, child.GetRule(), featureTags, backgroundSteps, uri, language, newId)
		case *messages.GherkinDocument_Feature_FeatureChild_Scenario:
			scenario := t.Scenario
			if len(scenario.GetExamples()) == 0 {
				pickles = compileScenario(pickles, backgroundSteps, scenario, featureTags, uri, language, newId)
			} else {
				pickles = compileScenarioOutline(pickles, scenario, featureTags, backgroundSteps, uri, language, newId)
			}
		default:
			panic(fmt.Sprintf("unexpected %T feature child", child))
		}
	}
	return pickles
}

func compileRule(pickles []*messages.Pickle, rule *messages.GherkinDocument_Feature_FeatureChild_Rule, tags []*messages.GherkinDocument_Feature_Tag, steps []*messages.Pickle_PickleStep, uri string, language string, newId func() string) []*messages.Pickle {
	backgroundSteps := make([]*messages.Pickle_PickleStep, 0)
	backgroundSteps = append(backgroundSteps, steps...)

	for _, child := range rule.Children {
		switch t := child.Value.(type) {
		case *messages.GherkinDocument_Feature_FeatureChild_RuleChild_Background:
			backgroundSteps = append(backgroundSteps, pickleSteps(t.Background.Steps, newId)...)
		case *messages.GherkinDocument_Feature_FeatureChild_RuleChild_Scenario:
			scenario := t.Scenario
			if len(scenario.GetExamples()) == 0 {
				pickles = compileScenario(pickles, backgroundSteps, scenario, tags, uri, language, newId)
			} else {
				pickles = compileScenarioOutline(pickles, scenario, tags, backgroundSteps, uri, language, newId)
			}
		default:
			panic(fmt.Sprintf("unexpected %T feature child", child))
		}
	}
	return pickles

}

func compileScenarioOutline(
	pickles []*messages.Pickle,
	scenario *messages.GherkinDocument_Feature_Scenario,
	featureTags []*messages.GherkinDocument_Feature_Tag,
	backgroundSteps []*messages.Pickle_PickleStep,
	uri string,
	language string,
	newId func() string,
) []*messages.Pickle {
	for _, examples := range scenario.Examples {
		if examples.TableHeader == nil {
			continue
		}
		variableCells := examples.TableHeader.Cells
		for _, valuesRow := range examples.TableBody {
			valueCells := valuesRow.Cells
			tags := pickleTags(append(featureTags, append(scenario.Tags, examples.Tags...)...))

			pickleSteps := make([]*messages.Pickle_PickleStep, 0)

			// translate pickleSteps based on valuesRow
			for _, step := range scenario.Steps {
				text := step.Text
				for i, variableCell := range variableCells {
					text = strings.Replace(text, "<"+variableCell.Value+">", valueCells[i].Value, -1)
				}

				pickleStep := pickleStep(step, variableCells, valuesRow, newId)
				pickleSteps = append(pickleSteps, pickleStep)
			}

			// translate pickle name
			name := scenario.Name
			for i, key := range variableCells {
				name = strings.Replace(name, "<"+key.Value+">", valueCells[i].Value, -1)
			}

			if len(pickleSteps) > 0 {
				pickleSteps = append(backgroundSteps, pickleSteps...)
			}

			pickles = append(pickles, &messages.Pickle{
				Id:        newId(),
				Uri:       uri,
				Steps:     pickleSteps,
				Tags:      tags,
				Name:      name,
				Language:  language,
				SourceIds: []string{scenario.Id, valuesRow.Id},
			})
		}
	}
	return pickles
}

func compileScenario(pickles []*messages.Pickle, backgroundSteps []*messages.Pickle_PickleStep, scenario *messages.GherkinDocument_Feature_Scenario, featureTags []*messages.GherkinDocument_Feature_Tag, uri string, language string, newId func() string) []*messages.Pickle {
	steps := make([]*messages.Pickle_PickleStep, 0)
	if len(scenario.Steps) > 0 {
		steps = append(backgroundSteps, pickleSteps(scenario.Steps, newId)...)
	}
	tags := pickleTags(append(featureTags, scenario.Tags...))
	pickles = append(pickles, &messages.Pickle{
		Id:        newId(),
		Uri:       uri,
		Steps:     steps,
		Tags:      tags,
		Name:      scenario.Name,
		Language:  language,
		SourceIds: []string{scenario.Id},
	})
	return pickles
}

func pickleDataTable(table *messages.GherkinDocument_Feature_Step_DataTable, variableCells []*messages.GherkinDocument_Feature_TableRow_TableCell, valueCells []*messages.GherkinDocument_Feature_TableRow_TableCell) *messages.PickleStepArgument_PickleTable {
	pickleTableRows := make([]*messages.PickleStepArgument_PickleTable_PickleTableRow, len(table.Rows))
	for i, row := range table.Rows {
		pickleTableCells := make([]*messages.PickleStepArgument_PickleTable_PickleTableRow_PickleTableCell, len(row.Cells))
		for j, cell := range row.Cells {
			pickleTableCells[j] = &messages.PickleStepArgument_PickleTable_PickleTableRow_PickleTableCell{
				Value: interpolate(cell.Value, variableCells, valueCells),
			}
		}
		pickleTableRows[i] = &messages.PickleStepArgument_PickleTable_PickleTableRow{Cells: pickleTableCells}
	}
	return &messages.PickleStepArgument_PickleTable{Rows: pickleTableRows}
}

func pickleDocString(docString *messages.GherkinDocument_Feature_Step_DocString, variableCells []*messages.GherkinDocument_Feature_TableRow_TableCell, valueCells []*messages.GherkinDocument_Feature_TableRow_TableCell) *messages.PickleStepArgument_PickleDocString {
	return &messages.PickleStepArgument_PickleDocString{
		ContentType: interpolate(docString.ContentType, variableCells, valueCells),
		Content:     interpolate(docString.Content, variableCells, valueCells),
	}
}

func pickleTags(tags []*messages.GherkinDocument_Feature_Tag) []*messages.Pickle_PickleTag {
	ptags := make([]*messages.Pickle_PickleTag, len(tags))
	for i, tag := range tags {
		ptags[i] = &messages.Pickle_PickleTag{
			Name:     tag.Name,
			SourceId: tag.Id,
		}
	}
	return ptags
}

func pickleSteps(steps []*messages.GherkinDocument_Feature_Step, newId func() string) []*messages.Pickle_PickleStep {
	pickleSteps := make([]*messages.Pickle_PickleStep, len(steps))
	for i, step := range steps {
		pickleStep := pickleStep(step, nil, nil, newId)
		pickleSteps[i] = pickleStep
	}
	return pickleSteps
}

func pickleStep(
	step *messages.GherkinDocument_Feature_Step,
	variableCells []*messages.GherkinDocument_Feature_TableRow_TableCell,
	valuesRow *messages.GherkinDocument_Feature_TableRow,
	newId func() string) *messages.Pickle_PickleStep {

	var valueCells []*messages.GherkinDocument_Feature_TableRow_TableCell
	if valuesRow != nil {
		valueCells = valuesRow.Cells
	}

	pickleStep := &messages.Pickle_PickleStep{
		Id:        newId(),
		Text:      interpolate(step.Text, variableCells, valueCells),
		SourceIds: []string{step.Id},
	}
	if valuesRow != nil {
		pickleStep.SourceIds = append(pickleStep.SourceIds, valuesRow.Id)
	}
	if step.GetDataTable() != nil {
		pickleStep.Argument = &messages.PickleStepArgument{
			Message: &messages.PickleStepArgument_DataTable{
				DataTable: pickleDataTable(step.GetDataTable(), variableCells, valueCells),
			},
		}
	}
	if step.GetDocString() != nil {
		pickleStep.Argument = &messages.PickleStepArgument{
			Message: &messages.PickleStepArgument_DocString{
				DocString: pickleDocString(step.GetDocString(), variableCells, valueCells),
			},
		}
	}
	return pickleStep
}

func interpolate(s string, variableCells []*messages.GherkinDocument_Feature_TableRow_TableCell, valueCells []*messages.GherkinDocument_Feature_TableRow_TableCell) string {
	if variableCells == nil || valueCells == nil {
		return s
	}

	for i, variableCell := range variableCells {
		s = strings.Replace(s, "<"+variableCell.Value+">", valueCells[i].Value, -1)
	}

	return s
}
