# frozen_string_literal: true

require_relative 'token_matcher'

module Gherkin
  class GherkinInMarkdownTokenMatcher < TokenMatcher
    HEADER_PREFIX = /\A([#]{1,6}\s)/
    BULLET_PREFIX = /\A(\s*[*+-]\s*)/
    DOC_STRING_SEPARATOR = /\A(`{3,})(.*)\z/
    TAG = /`(@[^`]+)`/

    def initialize(dialect_name = 'en')
      super
      @non_star_step_keywords = @sorted_step_keywords.reject { |keyword| keyword == '* ' }
    end

    def reset
      super
      @matched_feature_line = false
    end

    def match_FeatureLine(token)
      return false if @matched_feature_line

      matched = match_markdown_title_line(token, :FeatureLine, @dialect.feature_keywords)
      unless matched
        set_token_matched(token, :FeatureLine, token.line.trimmed_line_text)
        matched = true
      end
      @matched_feature_line = matched
      matched
    end

    def match_RuleLine(token)
      match_markdown_title_line(token, :RuleLine, @dialect.rule_keywords)
    end

    def match_ScenarioLine(token)
      match_markdown_title_line(token, :ScenarioLine, @dialect.scenario_keywords) ||
        match_markdown_title_line(token, :ScenarioLine, @dialect.scenario_outline_keywords)
    end

    def match_BackgroundLine(token)
      match_markdown_title_line(token, :BackgroundLine, @dialect.background_keywords)
    end

    def match_ExamplesLine(token)
      match_markdown_title_line(token, :ExamplesLine, @dialect.examples_keywords)
    end

    def match_StepLine(token)
      match_markdown_title_line(token, :StepLine, @non_star_step_keywords, '')
    end

    def match_TableRow(token)
      return false unless token.line.get_line_text(0).match?(/\A\s{2,5}\|/)

      table_cells = token.line.table_cells
      return false if gfm_table_separator?(table_cells)

      set_token_matched(token, :TableRow, nil, '|', token.line.indent, nil, table_cells)
      true
    end

    def match_Comment(token)
      return false unless token.line.start_with?('|')
      return false unless gfm_table_separator?(token.line.table_cells)

      set_token_matched(token, :Empty, nil, nil, 0)
      true
    end

    def match_Empty(token)
      return false if token.eof?

      result = token.line.empty?
      unless match_TagLine(token) ||
             match_FeatureLine(token) ||
             match_ScenarioLine(token) ||
             match_BackgroundLine(token) ||
             match_ExamplesLine(token) ||
             match_RuleLine(token) ||
             match_TableRow(token) ||
             match_Comment(token) ||
             match_Language(token) ||
             match_DocStringSeparator(token) ||
             match_EOF(token) ||
             match_StepLine(token)
        result = true
      end

      set_token_matched(token, :Empty, nil, nil, 0) if result
      result
    end

    def match_Language(_token)
      false
    end

    def match_TagLine(token)
      tags = []
      token.line.trimmed_line_text.to_enum(:scan, TAG).each do
        match = Regexp.last_match
        tags << GherkinLine::Span.new(token.line.indent + match.begin(0) + 2, match[1])
      end
      return false if tags.empty?

      set_token_matched(token, :TagLine, nil, nil, nil, nil, tags)
      true
    end

    def match_DocStringSeparator(token)
      if @active_doc_string_separator.nil?
        match = markdown_line_text(token).match(DOC_STRING_SEPARATOR)
        return false unless match

        @active_doc_string_separator = match[1]
        @indent_to_remove = token.line.indent
        set_token_matched(token, :DocStringSeparator, match[2], match[1])
      else
        return false unless markdown_line_text(token) == @active_doc_string_separator

        separator = @active_doc_string_separator
        @active_doc_string_separator = nil
        @indent_to_remove = 0
        set_token_matched(token, :DocStringSeparator, '', separator)
      end
      true
    end

    def match_Other(token)
      text = token.line.get_line_text(@indent_to_remove)
      set_token_matched(token, :Other, text, nil, 0)
      true
    end

    private

    def match_markdown_title_line(token, token_type, keywords, suffix = ':')
      text = token.line.trimmed_line_text
      prefix = suffix.empty? ? BULLET_PREFIX : HEADER_PREFIX
      prefix_match = text.match(prefix)
      return false unless prefix_match

      rest = text[prefix_match[0].length..]
      keyword = keywords.detect do |candidate|
        rest.start_with?(candidate) && (suffix.empty? || rest[candidate.length..].start_with?(suffix))
      end
      return false unless keyword

      title = rest[(keyword.length + suffix.length)..].to_s.strip
      keyword_types = @keyword_types[keyword]
      keyword_type = if keyword_types
                       keyword_types.length > 1 ? Cucumber::Messages::StepKeywordType::UNKNOWN : keyword_types[0]
                     end
      indent = token.line.indent + prefix_match[0].length
      set_token_matched(token, token_type, title, keyword, indent, keyword_type)
      true
    end

    def markdown_line_text(token)
      token.line.trimmed_line_text.sub(/[\r\n]+\z/, '')
    end

    def gfm_table_separator?(table_cells)
      table_cells.any? { |cell| cell.text.match?(/\A:?-+:?\z/) }
    end
  end
end
