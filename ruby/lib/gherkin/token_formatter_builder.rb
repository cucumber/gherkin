# frozen_string_literal: true

module Gherkin
  class TokenFormatterBuilder
    def initialize
      reset
    end

    def reset
      @tokens = []
    end

    def build(token)
      tokens << token
    end

    def start_rule(_rule_type); end

    def end_rule(_rule_type); end

    def get_result
      tokens.map { |token| "#{format_token(token)}\n" }.join
    end

    private

    def tokens
      @tokens ||= []
    end

    def format_token(token)
      return 'EOF' if token.eof?

      sprintf(
        "(%s:%s)%s:%s/%s/%s",
        token.location[:line],
        token.location[:column],
        token.matched_type,
        token.matched_keyword ? sprintf("(%s)%s", token.matched_keyword_type, token.matched_keyword) : "",
        token.matched_text,
        Array(token.matched_items).map { |i| "#{i.column}:#{i.text}" }.join(',')
      )
    end
  end
end
