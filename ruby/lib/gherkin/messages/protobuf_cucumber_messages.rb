require 'cucumber/messages'

module Gherkin
  module Messages
    class ProtobufCucumberMessages
      def initialize(io)
        @io = io
      end

      def messages
        Enumerator.new do |y|
          while !@io.eof?
            envelope = Cucumber::Messages::Envelope.parse_delimited_from(@io)
            y.yield envelope
          end
        end
      end
    end
  end
end
