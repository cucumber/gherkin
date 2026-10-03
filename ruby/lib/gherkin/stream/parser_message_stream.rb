# frozen_string_literal: true

require 'cucumber/messages'

require_relative '../parser'
require_relative '../token_matcher'
require_relative '../token_matcher_markdown'
require_relative '../pickles/compiler'

module Gherkin
  module Stream
    class ParserMessageStream
      PLAIN_MEDIA_TYPE = 'text/x.cucumber.gherkin+plain'
      MARKDOWN_MEDIA_TYPE = 'text/x.cucumber.gherkin+markdown'

      def self.markdown_uri?(uri)
        uri.to_s.end_with?('.feature.md')
      end

      def self.media_type_for_uri(uri)
        markdown_uri?(uri) ? MARKDOWN_MEDIA_TYPE : PLAIN_MEDIA_TYPE
      end

      def self.markdown_source?(source)
        source.media_type == MARKDOWN_MEDIA_TYPE || markdown_uri?(source.uri)
      end

      def initialize(paths: [], sources: [], options: {})
        @paths = paths
        @sources = sources
        @options = options

        id_generator = options.fetch(:id_generator, Cucumber::Messages::Helpers::IdGenerator::UUID.new)
        @parser = Parser.new(AstBuilder.new(id_generator))
        @compiler = Pickles::Compiler.new(id_generator)
      end

      def messages
        enumerated = false
        Enumerator.new do |yielder|
          raise DoubleIterationException, "Messages have already been enumerated" if enumerated

          enumerated = true

          sources.each do |source|
            yielder.yield(Cucumber::Messages::Envelope.new(source: source)) if @options[:include_source]
            begin
              gherkin_document = nil

              if @options[:include_gherkin_document]
                gherkin_document = build_gherkin_document(source)
                yielder.yield(Cucumber::Messages::Envelope.new(gherkin_document: gherkin_document))
              end
              if @options[:include_pickles]
                gherkin_document ||= build_gherkin_document(source)
                pickles = @compiler.compile(gherkin_document, source)
                pickles.each do |pickle|
                  yielder.yield(Cucumber::Messages::Envelope.new(pickle: pickle))
                end
              end
            rescue CompositeParserException => e
              yield_parse_errors(yielder, e.errors, source.uri)
            rescue ParserException => e
              yield_parse_errors(yielder, [e], source.uri)
            end
          end
        end
      end

      private

      def yield_parse_errors(yielder, errors, uri)
        errors.each do |err|
          parse_error = Cucumber::Messages::ParseError.new(
            source: Cucumber::Messages::SourceReference.new(
              uri: uri,
              location: Cucumber::Messages::Location.new(
                line: err.location[:line],
                column: err.location[:column]
              )
            ),
            message: err.message
          )
          yielder.yield(Cucumber::Messages::Envelope.new(parse_error: parse_error))
        end
      end

      def sources
        Enumerator.new do |yielder|
          @paths.each do |path|
            source = Cucumber::Messages::Source.new(
              uri: path,
              data: File.open(path, 'r:UTF-8', &:read),
              media_type: self.class.media_type_for_uri(path)
            )
            yielder.yield(source_with_markdown_media_type(source))
          end
          @sources.each do |source|
            yielder.yield(source_with_markdown_media_type(source))
          end
        end
      end

      def source_with_markdown_media_type(source)
        return source unless self.class.markdown_uri?(source.uri)
        return source if source.media_type == MARKDOWN_MEDIA_TYPE

        Cucumber::Messages::Source.new(
          uri: source.uri,
          data: source.data,
          media_type: MARKDOWN_MEDIA_TYPE
        )
      end

      def build_gherkin_document(source)
        dialect_name = @options[:default_dialect] || 'en'
        token_matcher = if self.class.markdown_source?(source)
                          GherkinInMarkdownTokenMatcher.new(dialect_name)
                        else
                          TokenMatcher.new(dialect_name)
                        end
        gherkin_document = @parser.parse(source.data, token_matcher)
        Cucumber::Messages::GherkinDocument.new(
          uri: source.uri,
          feature: gherkin_document.feature,
          comments: gherkin_document.comments
        )
      end
    end
  end
end
