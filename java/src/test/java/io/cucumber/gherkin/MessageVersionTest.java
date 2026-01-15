package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

// This tests that the message library exposes its version. This test is hard to do in the
// library itself since it requires running against a packaged version (jar).
class MessageVersionTest {
    @Test
    void message_library_has_version() {
        var version = Envelope.class.getModule().getDescriptor().version();
        assertThat(version).isNotEmpty();
    }
}
