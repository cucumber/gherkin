package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.*;

class LocationsTest {

    @Test
    void getLong() {
        // random integer conversion that is far after the cache upper bound works
        assertEquals(Long.valueOf(12000L), Locations.getLong(12000));

        // sequential integer conversion works (the cache has no hole)
        for (int i=0; i<12000; i++) {
            Long expectedLong = (long)i;
            assertEquals(expectedLong, Locations.getLong(i));
        }
    }

    @Test
    void getLong_negative_number_not_supported() {
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> Locations.getLong(-12000));
    }

    @Test
    void getLong_multithread_does_not_raise_exception() {
        // Given
        AtomicInteger successCounter = new AtomicInteger(0);
        int numberOfThreads = 1000;
        int numberOfIterations = 20000;
        Thread[] threads = new Thread[numberOfThreads];
        for (int i = 0; i < numberOfThreads; i++) {
            threads[i] = new Thread(() -> {
                for (int j = 500; j < numberOfIterations; j *= 2) {
                    Long expectedLong = (long)j;
                    assertEquals(expectedLong, Locations.getLong(j));
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
