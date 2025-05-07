package Gherkin::MarkdownTokenMatcher;

use strict;
use warnings;

my $DEFAULT_DOC_STRING_SEPARATOR = q/^(```[`]*)(.*)/;
my $KEYWORD_PREFIX_BULLET        = q/^(\\s*[*+-]\\s*)/;
my $KEYWORD_PREFIX_HEADER        = q/^(#{1,6}\\s)/;

use Class::XSAccessor accessors => [
    qw/dialect _default_dialect_name _indent_to_remove _active_doc_string_separator _keyword_types
      _matched_FeatureLine _non_star_step_keywords/,
];

use Cucumber::Messages;
use Gherkin::Dialect;

sub new {
    my ( $class, $options ) = @_;
    $options->{'dialect'} ||= Gherkin::Dialect->new( { dialect => 'en' } );
    my $self = bless $options, $class;
    $self->_default_dialect_name( $self->dialect_name );
    my @non_star_step_keywords = map {
        grep { $_ ne '* ' }
          @{ $self->dialect->$_ }
    } qw/Given When Then And But/;
    $self->_non_star_step_keywords( \@non_star_step_keywords );
    $self->reset();
    return $self;
}

sub _add_keyword_type_mappings {
    my ( $keyword_types, $keywords, $type ) = @_;

    for my $keyword ( @{$keywords} ) {
        if ( not exists $keyword_types->{$keyword} ) {
            $keyword_types->{$keyword} = [];
        }
        push( @{ $keyword_types->{$keyword} }, $type );
    }
}

sub dialect_name { $_[0]->dialect->dialect }

sub change_dialect {
    my $self = shift;
    $self->dialect->change_dialect(@_);

    my $keyword_types = {};
    _add_keyword_type_mappings( $keyword_types, $self->dialect->Given,
        Cucumber::Messages::Step::KEYWORDTYPE_CONTEXT );
    _add_keyword_type_mappings( $keyword_types, $self->dialect->When,
        Cucumber::Messages::Step::KEYWORDTYPE_ACTION );
    _add_keyword_type_mappings( $keyword_types, $self->dialect->Then,
        Cucumber::Messages::Step::KEYWORDTYPE_OUTCOME );
    _add_keyword_type_mappings( $keyword_types, [ @{ $self->dialect->And }, @{ $self->dialect->But } ],
        Cucumber::Messages::Step::KEYWORDTYPE_CONJUNCTION );
    $self->_keyword_types($keyword_types);
}

sub reset {
    my $self = shift;
    $self->change_dialect( $self->_default_dialect_name );
    $self->_indent_to_remove(0);
    $self->_active_doc_string_separator($DEFAULT_DOC_STRING_SEPARATOR);
}

sub match_FeatureLine {
    my ( $self, $token ) = @_;
    return if $self->_matched_FeatureLine;

    # We first try to match "# Feature: blah"
    my $result = $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        FeatureLine => $self->dialect->Feature );
    # If we didn't match "# Feature: blah", we still match this line
    # as a FeatureLine.
    # The reason for this is that users may not want to be constrained by having this as their fist line.
    unless ($result) {
        $self->_set_token_matched( $token,
            FeatureLine => { text => $token->line->_trimmed_line_text } );
    }
    $self->_matched_FeatureLine(1);
}

sub match_RuleLine {
    my ( $self, $token ) = @_;
    $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        RuleLine => $self->dialect->Rule );
}

sub match_ScenarioLine {
    my ( $self, $token ) = @_;
    $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        ScenarioLine => $self->dialect->Scenario )
      or $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        ScenarioLine => $self->dialect->ScenarioOutline );
}

sub match_BackgroundLine {
    my ( $self, $token ) = @_;
    $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        BackgroundLine => $self->dialect->Background );
}

sub match_ExamplesLine {
    my ( $self, $token ) = @_;
    $self->_match_title_line( $KEYWORD_PREFIX_HEADER, ':', $token,
        ExamplesLine => $self->dialect->Examples );
}

sub match_Language {
    my ( $self, $token ) = @_;
    # We've made a deliberate choice not to support `# language: [ISO 639-1]` headers or similar
    # in Markdown. Users should specify a language globally.
    return '';
}

sub match_TagLine {
    my ( $self, $token ) = @_;
    my @tags = ();
    while ( $token->line->line_text =~ m/`(@[^`]+)`/g ) {
        push(
            @tags,
            {
                column => 2 + length($`),
                text   => $1,
            }
        );
    }
    return unless scalar(@tags);
    $self->_set_token_matched( $token, TagLine => { items => \@tags } );
}

sub _match_title_line {
    my ( $self, $prefix, $keyword_suffix, $token, $token_type, $keywords ) = @_;
    my $regex = $prefix . '(' . join( '|', @{$keywords} ) . ')' . $keyword_suffix . '\s*(.*)';
    if ( $token->line->_trimmed_line_text =~ qr/$regex/ ) {
        my $indent  = $token->line->indent + ( length($1) || 0 );
        my $keyword = $2;
        my $text    = $3;
        $text =~ s/\s+$//;
        my $keyword_type;
        if ( exists $self->_keyword_types->{$keyword} ) {
            # only set the keyword type if this is a step keyword
            $keyword_type =
              ( scalar( @{ $self->_keyword_types->{$keyword} } ) > 1 )
              ? Cucumber::Messages::Step::KEYWORDTYPE_UNKNOWN
              : $self->_keyword_types->{$keyword}->[0];
        }
        $self->_set_token_matched( $token, $token_type,
            { indent => $indent, keyword => $keyword, text => $text, keyword_type => $keyword_type } );
    }
}

sub _set_token_matched {
    my ( $self, $token, $matched_type, $options ) = @_;
    $options->{'items'} ||= [];
    $token->matched_type($matched_type);

    if ( defined $options->{'text'} ) {
        chomp( $options->{'text'} );
        $token->matched_text( $options->{'text'} );
    }

    $token->matched_keyword( $options->{'keyword'} )
      if defined $options->{'keyword'};
    $token->matched_keyword_type( $options->{'keyword_type'} )
      if defined $options->{'keyword_type'};

    if ( defined $options->{'indent'} ) {
        $token->matched_indent( $options->{'indent'} );
    } else {
        $token->matched_indent( $token->line ? $token->line->indent : 0 );
    }

    $token->matched_items( $options->{'items'} )
      if defined $options->{'items'};

    $token->location->{'column'} = $token->matched_indent + 1;
    $token->matched_gherkin_dialect( $self->dialect_name );
}

sub match_EOF {
    my ( $self, $token ) = @_;
    return unless $token->is_eof;
    $self->_set_token_matched( $token, 'EOF' );
}

sub match_Empty {
    my ( $self, $token ) = @_;
    if (
        $token->line->is_empty
        || (   !$self->match_TagLine($token)
            && !$self->match_FeatureLine($token)
            && !$self->match_ScenarioLine($token)
            && !$self->match_BackgroundLine($token)
            && !$self->match_ExamplesLine($token)
            && !$self->match_RuleLine($token)
            && !$self->match_TableRow($token)
            && !$self->match_Comment($token)
            && !$self->match_Language($token)
            && !$self->match_DocStringSeparator($token)
            && !$self->match_EOF($token)
            && !$self->match_StepLine($token) )
      )
    {
        $self->_set_token_matched( $token, Empty => { indent => 0 } );
    }
}

sub match_Comment {
    my ( $self, $token ) = @_;
    if (   $token->line->startswith('|')
        && $self->_is_gfm_table_separator( $token->line->table_cells ) )
    {
        $self->_set_token_matched( $token,
            Comment => { text => $token->line->line_text, indent => 0 } );
    }
}

sub match_Other {
    my ( $self, $token ) = @_;
    # take the entire line, except removing DocString indents
    my $text = $token->line->get_line_text( $self->_indent_to_remove );
    $self->_set_token_matched( $token,
        Other => { indent => 0, text => $text } );
}

sub match_StepLine {
    my ( $self, $token ) = @_;
    $self->_match_title_line( $KEYWORD_PREFIX_BULLET, '', $token,
        StepLine => $self->_non_star_step_keywords );
}

sub match_DocStringSeparator {
    my ( $self, $token ) = @_;
    my $active_doc_string_separator = $self->_active_doc_string_separator;
    if ( $token->line->line_text =~ qr/$active_doc_string_separator/ ) {
        if ( $self->_active_doc_string_separator eq $DEFAULT_DOC_STRING_SEPARATOR ) {
            $self->_active_doc_string_separator( '^(' . $1 . ')$' );
            $self->_indent_to_remove( $token->line->indent );
        } else {
            $self->_active_doc_string_separator($DEFAULT_DOC_STRING_SEPARATOR);
        }
        $self->_set_token_matched( $token,
            DocStringSeparator => { keyword => $1, text => '' } );
    }
}

sub match_TableRow {
    my ( $self, $token ) = @_;
    # Gherkin tables must be indented 2-5 spaces in order to be distinguidedn from non-Gherkin tables
    if ( $token->line->line_text =~ m/^\s\s\s?\s?\s?\|/ ) {
        my $table_cells = $token->line->table_cells;
        return if ( $self->_is_gfm_table_separator($table_cells) );
        $self->_set_token_matched( $token,
            TableRow => { items => $table_cells } );
    }
}

sub _is_gfm_table_separator {
    my ( $self, $table_cells ) = @_;
    my @separator_values = grep { $_->{'text'} =~ m/^:?-+:?$/ } @{$table_cells};
    return scalar(@separator_values) > 0;
}

1;

__END__


=head1 NAME

Gherkin::MarkdownTokenMatcher - Line token matching for the Gherkin parser

=head1 SYNOPSIS

  use Gherkin::MarkdownTokenMatcher;
  use Gherkin::Dialect;

  # Instantiate a token matcher with the default language 'Emoji'
  my $matcher = Gherkin::MarkdownTokenMatcher->new( {
        dialect => Gherkin::Dialect->new( { dialect => 'em'} )
  } );

=head1 DESCRIPTION

This is an alternate token matcher for Markdown with Gherkin (MDG).

The Gherkin language has a line-based structure. The parser knows about state,
but defers identifying the type of line tokens to the token matcher. The
matcher knows how to identify line tokens based on the grammar's keywords.
Although the matcher knows how to identify line tokens based on the keywords,
it depends on L<Gherkin::Dialect> to provide the actual keyword texts.

=head1 METHODS

=head2 new( [$options] )

Constructor.

C<$options> is a hashref with the following keys:

=over

=item C<dialect>

An instance of L<Gherkin::Dialect> to provide the keyword texts used to identify
the type of line-token being matched.

=back

=head2 dialect_name

Returns the name of the current dialect selected from the C<dialect> instance.

=head2 change_dialect

Changes the selected dialect on the C<dialect> instance. Dialects are groups of
keywords belonging together; this is how keyword translations are being handled.

=head2 reset

Changes the token scanner's state back to its initial state; used to restart
scanning a document. Multiple documents may be parsed using a single token
scanner with a C<reset> call in-between.

=head1 SEE ALSO

=over 8

=item * L<Gherkin>

=item * L<Gherkin::Dialect>

=item * L<Gherkin::Parser>

=item * L<Gherkin::TokenMatcher>

=back

=head1 LICENSE

See L<Gherkin>.

=cut
