<?php

declare(strict_types=1);

namespace Cucumber\Gherkin;

use Cucumber\Messages\Envelope;
use Cucumber\Messages\Source;
use Cucumber\Messages\Streams\NdJson\NdJsonStreamWriter;
use PHPUnit\Framework\TestCase;

final class TestDataTest extends TestCase
{
    /**
     * @dataProvider provideGoodFeatureFiles
     */
    public function testTokensAreSameAsTestData(string $fullPath): void
    {
        $result = (new Parser(new TokenFormatterBuilder()))->parse(
            $fullPath,
            new StringTokenScanner(file_get_contents($fullPath)),
            new TokenMatcher(),
        );

        self::assertStringEqualsFile($fullPath . '.tokens', $result);
    }

    /**
     * @dataProvider provideGoodFeatureFiles
     */
    public function testAstsAreSameAsTestData(string $fullPath, Source $source): void
    {
        $envelopes = (new GherkinParser(
            predictableIds: true,
            includeSource: false,
            includeGherkinDocument: true,
            includePickles: false,
        ))->parse([$source]);

        self::assertEnvelopesMatchNdJsonFile($envelopes, $fullPath . '.ast.ndjson');
    }

    /**
     * @dataProvider provideGoodFeatureFiles
     */
    public function testSourcesAreSameAsTestData(string $fullPath, Source $source): void
    {
        $envelopes = (new GherkinParser(
            predictableIds: true,
            includeSource: true,
            includeGherkinDocument: false,
            includePickles: false,
        ))->parse([$source]);

        self::assertEnvelopesMatchNdJsonFile($envelopes, $fullPath . '.source.ndjson');
    }

    /**
     * @dataProvider provideGoodFeatureFiles
     */
    public function testPicklesAreSameAsTestData(string $fullPath, Source $source): void
    {
        $envelopes = (new GherkinParser(
            predictableIds: true,
            includeSource: false,
            includeGherkinDocument: false,
            includePickles: true,
        ))->parse([$source]);

        self::assertEnvelopesMatchNdJsonFile($envelopes, $fullPath . '.pickles.ndjson');
    }

    /**
     * @dataProvider provideBadFeatureFiles
     */
    public function testErrorsAreSameAsTestData(string $fullPath, Source $source): void
    {
        $envelopes = (new GherkinParser(
            predictableIds: true,
            includeSource: false,
            includeGherkinDocument: false,
            includePickles: true,
        ))->parse([$source]);

        self::assertEnvelopesMatchNdJsonFile($envelopes, $fullPath . '.errors.ndjson');
    }

    /**
     * @return iterable<string, array{0: string, 1: Source}>
     */
    public function provideGoodFeatureFiles(): iterable
    {
        return $this->provideFeatureFiles("good");
    }

    /**
     * @return iterable<string, array{0: string, 1: Source}>
     */
    public function provideBadFeatureFiles(): iterable
    {
        return $this->provideFeatureFiles("bad");
    }

    /**
     * @param 'good'|'bad' $subDir
     *
     * @return iterable<string, array{0: string, 1: Source}>
     */
    private function provideFeatureFiles(string $subDir): iterable
    {
        foreach (glob(__DIR__ . "/../../../testdata/$subDir/*.feature") as $fullPath) {
            $shortPath = substr($fullPath, strlen(__DIR__ . '/../../'));

            yield $shortPath => [$fullPath, new Source($shortPath, file_get_contents($fullPath))];
        }
    }

    /**
     * @param iterable<Envelope> $envelopes
     */
    private static function assertEnvelopesMatchNdJsonFile(iterable $envelopes, string $expectedfile): void
    {
        $output = fopen('php://memory', 'w');
        NdJsonStreamWriter::fromFileHandle($output)->writeEnvelopes($envelopes);
        rewind($output);

        $actual = stream_get_contents($output);
        $expected = file_get_contents($expectedfile);

        // rather than compare the full file, compare line by line to get better JSON diffs on error
        $actualLines = explode("\n", $actual);
        $expectedLines = explode("\n", $expected);

        self::assertSame(count($actualLines), count($expectedLines));

        foreach ($actualLines as $i => $actualLine) {
            if ($actualLine !== '') {
                self::assertJsonStringEqualsJsonString($expectedLines[$i], $actualLine);
            } else {
                self::assertEquals($expectedLines[$i], '');
            }
        }
    }
}
