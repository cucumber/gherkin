#ifndef CUCUMBER_GHERKIN_AST_BUILDER_HPP
#define CUCUMBER_GHERKIN_AST_BUILDER_HPP

#include "cucumber/gherkin/AstNode.hpp"
#include "cucumber/gherkin/IdGenerator.hpp"
#include "cucumber/gherkin/MsgTypes.hpp"
#include "cucumber/gherkin/RuleType.hpp"
#include "cucumber/gherkin/Token.hpp"
#include "cucumber/messages/All.hpp"
#include <memory>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

namespace cucumber::gherkin
{
    using TableRows = std::vector<std::shared_ptr<messages::TableRow>>;
    using Tags = std::vector<std::shared_ptr<messages::Tag>>;
    using Comments = std::vector<std::shared_ptr<messages::Comment>>;

    class AstBuilder
    {
    public:
        using ResultType = messages::GherkinDocument;

        AstBuilder();
        AstBuilder(IdGeneratorPtr idp);

        virtual ~AstBuilder() = default;
        AstBuilder(const AstBuilder&) = delete;
        AstBuilder& operator=(const AstBuilder&) = delete;
        AstBuilder(AstBuilder&&) = delete;
        AstBuilder& operator=(AstBuilder&&) = delete;

        void Reset(std::string_view uri);

        void StartRule(RuleType ruleType);
        void EndRule(RuleType ruleType);
        void Build(const Token& token);

        [[nodiscard]] const ResultType& GetResult() const;

    private:
        using AstNodeStack = std::stack<AstNode>;

        std::string NextId();

        void TransformNode(AstNode& from, AstNode& destination);

        messages::Step MakeStep(AstNode& node);
        messages::DataTable MakeDataTable(AstNode& node);
        messages::Background MakeBackground(AstNode& node);
        messages::Scenario MakeScenarioDefinition(AstNode& node);
        messages::Examples MakeExamplesDefinition(AstNode& node);
        TableRows MakeExamplesTable(AstNode& node);
        messages::Feature MakeFeature(AstNode& node);
        messages::Rule MakeRule(AstNode& node);
        ResultType MakeGherkinDocument(AstNode& node);

        TableRows GetTableRows(const AstNode& node);
        Tags GetTags(const AstNode& node);

        AstNode PopNode();
        AstNode& CurrentNode();
        [[nodiscard]] const AstNode& CurrentNode() const;

        IdGeneratorPtr idp;
        AstNodeStack stack;
        std::string_view uri;
        Comments comments;
        ResultType doc;
    };

    using AstBuilderPtr = std::unique_ptr<AstBuilder>;

    template<typename... Args>
    AstBuilderPtr NewAstBuilder(Args&&... args)
    {
        return std::make_unique<AstBuilder>(std::forward<Args>(args)...);
    }

}

#endif
