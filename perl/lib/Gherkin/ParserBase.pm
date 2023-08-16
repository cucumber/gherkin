package Gherkin::ParserBase;

use strict;
use warnings;

use Class::XSAccessor accessors =>
  [ qw/ast_builder token_matcher stop_at_first_error max_errors/, ];

use Gherkin::ParserContext;
use Gherkin::Exceptions;
use Gherkin::AstBuilder;

use Gherkin::TokenMatcher;
use Gherkin::TokenScanner;

sub new {
    my ( $class, $ast_builder, $token_matcher ) = @_;
    bless {
        ast_builder         => $ast_builder || Gherkin::AstBuilder->new(),
        token_matcher       => $token_matcher || Gherkin::TokenMatcher->new(),
        stop_at_first_error => 0,
        max_errors          => 10,
      },
      $class;
}

sub get_result { return $_[0]->ast_builder->get_result }

sub add_error {
    my ( $self, $context, $error ) = @_;

    die $error if not ref $error; # rethrow if unstructured; not ours
    die $error if $self->stop_at_first_error;
    if ( ref $error eq 'Gherkin::Exceptions::CompositeParser' ) {
        $context->add_errors( @{ $error->errors } );
    } else {
        $context->add_errors( $error );
    }

    my @errors = $context->errors;
    Gherkin::Exceptions::CompositeParser->throw(@errors)
      if @errors > $self->max_errors;
}

sub _start_rule {
    my ( $self, $context, $ruleType ) = @_;

    if (not eval { $self->ast_builder->start_rule( $ruleType ); 1 }) {
        $self->add_error( $context, $@ );
    }
}

sub _end_rule {
    my ( $self, $context, $ruleType ) = @_;
    if (not eval { $self->ast_builder->end_rule( $ruleType ); 1 }) {
        $self->add_error( $context, $@ );
    }
}

sub _build {
    my ( $self, $context, $token ) = @_;
    if (not eval { $self->ast_builder->build( $token ); 1 }) {
        $self->add_error( $context, $@ );
    }
}

1;
