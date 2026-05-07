<?php

declare(strict_types=1);

namespace Cucumber\Gherkin\Parser;

use Generator;
use PHPUnit\Framework\TestCase;

final class RuleTypeTest extends TestCase
{
    public function testItCanCastFromTokens(): void
    {
        foreach (TokenType::cases() as $tokenType) {
            self::assertInstanceOf(RuleType::class, RuleType::cast($tokenType));
        }
    }
}
