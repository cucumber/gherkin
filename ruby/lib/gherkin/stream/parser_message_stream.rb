# frozen_string_literal: true

require 'cucumber/messages'
require_relative '../parser'
require_relative '../token_matcher'
require_relative '../pickles/compiler'

module Gherkin
  module Stream
    class ParserMessageStream
      def initialize(paths, sources, options)
        @paths = paths
        @sources = sources
        @options = options

        id_generator = options[:id_generator] || Cucumber::Messages::Helpers::IdGenerator::UUID.new
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
              media_type: 'text/x.cucumber.gherkin+plain'
            )
            yielder.yield(source)
          end
          @sources.each do |source|
            yielder.yield(source)
          end
        end
      end

      def build_gherkin_document(source)
        if @options[:default_dialect]
          token_matcher = TokenMatcher.new(@options[:default_dialect])
          gd = @parser.parse(source.data, token_matcher)
        else
          gd = @parser.parse(source.data)
        end
        Cucumber::Messages::GherkinDocument.new(
          uri: source.uri,
          feature: gd.feature,
          comments: gd.comments
        )
      end
    end
  end
end
