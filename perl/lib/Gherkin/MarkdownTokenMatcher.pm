package Gherkin::MarkdownTokenMatcher;

use strict;
use warnings;

use base 'Gherkin::TokenMatcher';

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
