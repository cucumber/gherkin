package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import org.junit.jupiter.api.Test;

import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.*;

class LocationsTest {

    @Test
    void atLine() {
        // random integer conversion that is far after the cache upper bound works
        Location location = Locations.atLine(12000);
        assertEquals(Long.valueOf(12000L), location.getLine());
        // sequential integer conversion works (the cache has no hole)
        for (int i = 0; i < 12000; i++) {
            Long expectedLine = (long) i;
            Location actual = Locations.atLine(i);
            assertEquals(expectedLine, actual.getLine());
        }
    }

    @Test
    void atLine_negative_number_not_supported() {
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> Locations.atLine(-1));
    }

    @Test
    void atLine_multithreaded_does_not_raise_exception() {
        // Given
        AtomicInteger successCounter = new AtomicInteger(0);
        int numberOfThreads = 1000;
        int numberOfIterations = 20000;
        Thread[] threads = new Thread[numberOfThreads];
        for (int i = 0; i < numberOfThreads; i++) {
            threads[i] = new Thread(() -> {
                for (int j = 500; j < numberOfIterations; j *= 2) {
                    Long expectedLine = (long) j;
                    Location actual = Locations.atLine(j);
                    assertEquals(expectedLine, actual.getLine());
                }
                successCounter.incrementAndGet();
            });
        }

        // When
        for (Thread thread : threads) {
            thread.start();
        }

        // Then
        for (Thread thread : threads) {
            assertDoesNotThrow(() -> thread.join());
        }
        assertEquals(numberOfThreads, successCounter.get());
    }

}
