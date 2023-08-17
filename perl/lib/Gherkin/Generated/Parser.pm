package Gherkin::Generated::Parser;

# This file is generated. Do not edit! Edit gherkin-perl.razor instead.
use strict;
use warnings;

use base 'Gherkin::ParserBase';

our %states_to_match_names = (
    0 => "match_token_at_0",
    1 => "match_token_at_1",
    2 => "match_token_at_2",
    3 => "match_token_at_3",
    4 => "match_token_at_4",
    5 => "match_token_at_5",
    6 => "match_token_at_6",
    7 => "match_token_at_7",
    8 => "match_token_at_8",
    9 => "match_token_at_9",
    10 => "match_token_at_10",
    11 => "match_token_at_11",
    12 => "match_token_at_12",
    13 => "match_token_at_13",
    14 => "match_token_at_14",
    15 => "match_token_at_15",
    16 => "match_token_at_16",
    17 => "match_token_at_17",
    18 => "match_token_at_18",
    19 => "match_token_at_19",
    20 => "match_token_at_20",
    21 => "match_token_at_21",
    22 => "match_token_at_22",
    23 => "match_token_at_23",
    24 => "match_token_at_24",
    25 => "match_token_at_25",
    26 => "match_token_at_26",
    27 => "match_token_at_27",
    28 => "match_token_at_28",
    29 => "match_token_at_29",
    30 => "match_token_at_30",
    31 => "match_token_at_31",
    32 => "match_token_at_32",
    33 => "match_token_at_33",
    34 => "match_token_at_34",
    35 => "match_token_at_35",
    36 => "match_token_at_36",
    37 => "match_token_at_37",
    38 => "match_token_at_38",
    39 => "match_token_at_39",
    40 => "match_token_at_40",
    41 => "match_token_at_41",
    43 => "match_token_at_43",
    44 => "match_token_at_44",
    45 => "match_token_at_45",
    46 => "match_token_at_46",
    47 => "match_token_at_47",
    48 => "match_token_at_48",
    49 => "match_token_at_49",
    50 => "match_token_at_50",
);

sub parse {
    my ( $self, $token_scanner, $uri ) = @_;

    $token_scanner = Gherkin::TokenScanner->new($token_scanner)
      unless ref $token_scanner && (ref $token_scanner ne 'SCALAR');

    $self->ast_builder->reset($uri);
    $self->token_matcher->reset();

    my $context = Gherkin::ParserContext->new(
        {
            token_scanner => $token_scanner,
            token_matcher => $self->token_matcher,
        }
    );

    $self->_start_rule( $context, 'GherkinDocument' );

    my $state = 0;
    my $token;

    while (1) {
        $token = $context->read_token($context);
        $state = $self->match_token( $state, $token, $context );

        last if $token->is_eof();
    }

    $self->_end_rule( $context, 'GherkinDocument' );

    if ( my @errors = $context->errors ) {
        Gherkin::Exceptions::CompositeParser->throw(@errors);
    }

    return $self->get_result();
}

sub match_token {
    my ( $self, $state, $token, $context ) = @_;
    my $method_name = $states_to_match_names{ $state } ||
        die "Unknown state: $state";
    $self->$method_name( $token, $context );
}

sub _construct_parser_error {
    my ($self, $token, @args) = @_;
    my $error_class = "Gherkin::Exceptions::" . (
        $token->is_eof ? 'UnexpectedEOF' : 'UnexpectedToken' );

    return $error_class->new( $token, @args );
}


# Start
sub match_token_at_0 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Language($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Feature');
        $self->_start_rule($context, 'FeatureHeader');
        $self->_build($context, $token);
        return 1;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Feature');
        $self->_start_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 2;
    }
    ($ok, $err) = $context->token_matcher->match_FeatureLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Feature');
        $self->_start_rule($context, 'FeatureHeader');
        $self->_build($context, $token);
        return 3;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 0;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 0;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Language", "#TagLine", "#FeatureLine", "#Comment", "#Empty"],
        "State: 0 - Start",
    );
    $self->add_error( $context, $err );

    return 0;
}

# GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
sub match_token_at_1 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 2;
    }
    ($ok, $err) = $context->token_matcher->match_FeatureLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 3;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 1;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 1;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#FeatureLine", "#Comment", "#Empty"],
        "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0",
    );
    $self->add_error( $context, $err );

    return 1;
}

# GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
sub match_token_at_2 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 2;
    }
    ($ok, $err) = $context->token_matcher->match_FeatureLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_build($context, $token);
        return 3;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 2;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 2;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#FeatureLine", "#Comment", "#Empty"],
        "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 2;
}

# GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
sub match_token_at_3 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 3;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 5;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 6;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 4;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0",
    );
    $self->add_error( $context, $err );

    return 3;
}

# GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_4 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 5;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 6;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 4;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 4;
}

# GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0
sub match_token_at_5 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 5;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 6;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'FeatureHeader');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 5;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 5 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 5;
}

# GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
sub match_token_at_6 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 6;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 8;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 7;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 6 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0",
    );
    $self->add_error( $context, $err );

    return 6;
}

# GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_7 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 8;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 7;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 7 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 7;
}

# GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0
sub match_token_at_8 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 8;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 8;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 8 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 8;
}

# GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
sub match_token_at_9 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DataTable');
        $self->_build($context, $token);
        return 10;
    }
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DocString');
        $self->_build($context, $token);
        return 49;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 9;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#DocStringSeparator", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0",
    );
    $self->add_error( $context, $err );

    return 9;
}

# GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
sub match_token_at_10 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 10;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 10;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 10;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 10;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
sub match_token_at_11 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 11;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 11;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 11;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#ScenarioLine", "#Comment", "#Empty"],
        "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 11;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
sub match_token_at_12 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 14;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 13;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0",
    );
    $self->add_error( $context, $err );

    return 12;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_13 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 14;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 13;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 13;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
sub match_token_at_14 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 14;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 14;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 14;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
sub match_token_at_15 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DataTable');
        $self->_build($context, $token);
        return 16;
    }
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DocString');
        $self->_build($context, $token);
        return 47;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 15;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#DocStringSeparator", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0",
    );
    $self->add_error( $context, $err );

    return 15;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
sub match_token_at_16 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 16;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 16;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 16;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 16;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
sub match_token_at_17 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 17;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 17;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 17;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#ExamplesLine", "#Comment", "#Empty"],
        "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 17;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
sub match_token_at_18 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 20;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 21;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 19;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0",
    );
    $self->add_error( $context, $err );

    return 18;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_19 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 20;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 21;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 19;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 19;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
sub match_token_at_20 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 20;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 21;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 20;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 20;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
sub match_token_at_21 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 21;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 21;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 21;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 21;
}

# GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
sub match_token_at_22 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 22;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 22;
}

# GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
sub match_token_at_23 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 25;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 26;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 24;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0",
    );
    $self->add_error( $context, $err );

    return 23;
}

# GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_24 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 25;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 26;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 24;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 24;
}

# GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0
sub match_token_at_25 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 25;
    }
    ($ok, $err) = $context->token_matcher->match_BackgroundLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Background');
        $self->_build($context, $token);
        return 26;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'RuleHeader');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 25;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#BackgroundLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 25 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 25;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
sub match_token_at_26 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 26;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 28;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 27;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0",
    );
    $self->add_error( $context, $err );

    return 26;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_27 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 28;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 27;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 27;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0
sub match_token_at_28 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 28;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 28;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 28;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
sub match_token_at_29 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DataTable');
        $self->_build($context, $token);
        return 30;
    }
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DocString');
        $self->_build($context, $token);
        return 45;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 29;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#DocStringSeparator", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0",
    );
    $self->add_error( $context, $err );

    return 29;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
sub match_token_at_30 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 30;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 30;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 30;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 30;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
sub match_token_at_31 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 31;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 31;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 31;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#ScenarioLine", "#Comment", "#Empty"],
        "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 31;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
sub match_token_at_32 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 34;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 33;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0",
    );
    $self->add_error( $context, $err );

    return 32;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_33 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 34;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 33;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 33;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
sub match_token_at_34 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 34;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 34;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 34;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
sub match_token_at_35 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DataTable');
        $self->_build($context, $token);
        return 36;
    }
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'DocString');
        $self->_build($context, $token);
        return 43;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 35;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#DocStringSeparator", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0",
    );
    $self->add_error( $context, $err );

    return 35;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
sub match_token_at_36 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 36;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DataTable');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 36;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 36;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 36;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
sub match_token_at_37 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 37;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Tags');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 37;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 37;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#TagLine", "#ExamplesLine", "#Comment", "#Empty"],
        "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0",
    );
    $self->add_error( $context, $err );

    return 37;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
sub match_token_at_38 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 40;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 41;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'Description');
        $self->_build($context, $token);
        return 39;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Empty", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0",
    );
    $self->add_error( $context, $err );

    return 38;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
sub match_token_at_39 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_build($context, $token);
        return 40;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 41;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Description');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 39;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Other"],
        "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0",
    );
    $self->add_error( $context, $err );

    return 39;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
sub match_token_at_40 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 40;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_start_rule($context, 'ExamplesTable');
        $self->_build($context, $token);
        return 41;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 40;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#Comment", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Empty"],
        "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0",
    );
    $self->add_error( $context, $err );

    return 40;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
sub match_token_at_41 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_TableRow($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 41;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'ExamplesTable');
        $self->_end_rule($context, 'Examples');
        $self->_end_rule($context, 'ExamplesDefinition');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 41;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 41;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#TableRow", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0",
    );
    $self->add_error( $context, $err );

    return 41;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
sub match_token_at_43 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 44;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 43;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#DocStringSeparator", "#Other"],
        "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 43;
}

# GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
sub match_token_at_44 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 35;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 37;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 38;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 44;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 44;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 44;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
sub match_token_at_45 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 46;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 45;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#DocStringSeparator", "#Other"],
        "State: 45 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 45;
}

# GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
sub match_token_at_46 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 29;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 31;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 32;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Rule');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 46;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 46;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 46;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
sub match_token_at_47 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 48;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 47;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#DocStringSeparator", "#Other"],
        "State: 47 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 47;
}

# GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
sub match_token_at_48 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 15;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_1($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 17;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ExamplesLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'ExamplesDefinition');
        $self->_start_rule($context, 'Examples');
        $self->_build($context, $token);
        return 18;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Scenario');
        $self->_end_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 48;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 48;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#StepLine", "#TagLine", "#ExamplesLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 48 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 48;
}

# GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
sub match_token_at_49 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_DocStringSeparator($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 50;
    }
    ($ok, $err) = $context->token_matcher->match_Other($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 49;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#DocStringSeparator", "#Other"],
        "State: 49 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 49;
}

# GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
sub match_token_at_50 {
    my ( $self, $token, $context ) = @_;
    my ( $ok, $err );
    ($ok, $err) = $context->token_matcher->match_EOF($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_end_rule($context, 'Feature');
        $self->_build($context, $token);
        return 42;
    }
    ($ok, $err) = $context->token_matcher->match_StepLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_start_rule($context, 'Step');
        $self->_build($context, $token);
        return 9;
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        if ($self->lookahead_0($context, $token)) {
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 11;
        }
    }
    ($ok, $err) = $context->token_matcher->match_TagLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_start_rule($context, 'Tags');
        $self->_build($context, $token);
        return 22;
    }
    ($ok, $err) = $context->token_matcher->match_ScenarioLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'ScenarioDefinition');
        $self->_start_rule($context, 'Scenario');
        $self->_build($context, $token);
        return 12;
    }
    ($ok, $err) = $context->token_matcher->match_RuleLine($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_end_rule($context, 'DocString');
        $self->_end_rule($context, 'Step');
        $self->_end_rule($context, 'Background');
        $self->_start_rule($context, 'Rule');
        $self->_start_rule($context, 'RuleHeader');
        $self->_build($context, $token);
        return 23;
    }
    ($ok, $err) = $context->token_matcher->match_Comment($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 50;
    }
    ($ok, $err) = $context->token_matcher->match_Empty($token);
    if ($ok) {
        $self->add_error( $context, $err ) if $err;
        $self->_build($context, $token);
        return 50;
    }

    $token->detach;
    $err = $self->_construct_parser_error(
        $token,
        ["#EOF", "#StepLine", "#TagLine", "#ScenarioLine", "#RuleLine", "#Comment", "#Empty"],
        "State: 50 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0",
    );
    $self->add_error( $context, $err );

    return 50;
}


sub lookahead_0 {
    my ($self, $context, $current_token) = @_;

    $current_token->detach();

    my $token;
    my @queue;
    my $match = 0;

    my $ok;
    while (1) {
        $token = $context->read_token();
        $token->detach;
        push( @queue, $token );


        ($match) = $context->token_matcher->match_ScenarioLine($token);
        last if $match;

        ($ok) = $context->token_matcher->match_Empty($token);
        next if $ok;
        ($ok) = $context->token_matcher->match_Comment($token);
        next if $ok;
        ($ok) = $context->token_matcher->match_TagLine($token);
        next if $ok;
        last;
    }

    $context->add_tokens( @queue );
    return $match;
}
sub lookahead_1 {
    my ($self, $context, $current_token) = @_;

    $current_token->detach();

    my $token;
    my @queue;
    my $match = 0;

    my $ok;
    while (1) {
        $token = $context->read_token();
        $token->detach;
        push( @queue, $token );


        ($match) = $context->token_matcher->match_ExamplesLine($token);
        last if $match;

        ($ok) = $context->token_matcher->match_Empty($token);
        next if $ok;
        ($ok) = $context->token_matcher->match_Comment($token);
        next if $ok;
        ($ok) = $context->token_matcher->match_TagLine($token);
        next if $ok;
        last;
    }

    $context->add_tokens( @queue );
    return $match;
}
1;
