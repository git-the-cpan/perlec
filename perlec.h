/* ----------------------------------------------------------------------------
 * perlec.h - Perl Easy Call.
 * ----------------------------------------------------------------------------
 * Mastering programmed by YAMASHINA Hio
 *
 * Copyright 2007 YAMASHINA Hio
 * ----------------------------------------------------------------------------
 * $Id: /mirror/erlang/perlre/perlec/perlec.h 477 2007-06-11T08:12:13.810924Z hio  $
 * ------------------------------------------------------------------------- */
#ifndef PERLEC_H
#define PERLEC_H

#ifndef NO_PERL
#include <EXTERN.h>
#include <perl.h>
#endif

struct perlec_s;
typedef struct perlec_s perlec_t;
struct perlec_s
{
#ifndef NO_PERL
	PerlInterpreter* my_perl;
	SV* cv_match;
	SV* cv_gsub;
	SV* cv_eval;
	SV* cv_regcheck;
#endif
	void* (*array_new)(perlec_t* perlec, int len, int guessed_size);
	void  (*array_store)(void* array, int idx, const void* value, int len);
	void  (*array_delete)(void* array);
	void* (*scalar_new)(perlec_t* perlec, const void* value, int len);
	void  (*scalar_delete)(void* scalar);
};

typedef void* perlec_rx_t;
typedef void* perlec_array_t;
typedef void* perlec_scalar_t;

#define PERLEC_ROPT_NONE        0
#define PERLEC_ROPT_MULTILINE   1
#define PERLEC_ROPT_SINGLELINE  2
#define PERLEC_ROPT_IGNORECASE  4
#define PERLEC_ROPT_EXTENDED    8
#define PERLEC_ROPT_UTF8        16

/* ----------------------------------------------------------------------------
 * perlec_init(&perlec_buf);
 *  initialize.
 * ------------------------------------------------------------------------- */
extern void perlec_init(perlec_t* perlec);

/* ----------------------------------------------------------------------------
 * perlec_discard(&perlec_buf);
 *  discard.
 * ------------------------------------------------------------------------- */
extern void perlec_discard(perlec_t* perlec);

/* ----------------------------------------------------------------------------
 * ret = perlec_match(perlec, "s1", s1_len, "re", re_len, rxflags);
 * ret :: perlec_array | NULL
 *  NULL when compiling regexp is failed or does not match.
 *  if fail, perlec_errmsg returns scalar, and otherwise return NULL.
 * ------------------------------------------------------------------------- */
extern void* perlec_match(perlec_t* perlec, const char* s1, int s1_len, const char* re, int re_len, int rx_flags);

/* ----------------------------------------------------------------------------
 * ret = perlec_replacement(perlec, "s1", s1_len, "re", re_len, "repl", repl_len);
 * ret :: perlec_scalar | NULL
 *  NULL when compiling regexp is failed.
 * ------------------------------------------------------------------------- */
extern void* perlec_replacement(perlec_t* perlec, const char* s1, int s1_len, const char* re, int re_len, const char* repl, int repl_len);

/* ----------------------------------------------------------------------------
 * ret = perlec_compile(perlec, "re", re_len, int rx_flags);
 * ret :: perlec_rx | NULL
 *  NULL when compiling regexp is failed.
 * ------------------------------------------------------------------------- */
extern void* perlec_compile(perlec_t* perlec, const char* re, int re_len, int rx_flags);

/* ----------------------------------------------------------------------------
 * ret = perlec_match_rx(perlec, "s1", s1_len, rx, rx_flags);
 * ret :: perlec_array | NULL
 *  NULL on no matches.
 * ------------------------------------------------------------------------- */
extern void* perlec_match_rx(perlec_t* perlec, const char* str, int str_len, void* re_obj, int rx_flags);

/* ----------------------------------------------------------------------------
 * ret = perlec_errmsg(perlec);
 * ret :: perlec_scalar
 * ------------------------------------------------------------------------- */
extern void* perlec_errmsg(perlec_t* perlec);

/* ----------------------------------------------------------------------------
 * ret = perlec_eval(perlec, "str", str_len);
 * ret :: perlec_scalar
 * ------------------------------------------------------------------------- */
extern void* perlec_eval(perlec_t* perlec, const char* str, int str_len);

/*

$VERSION = '0.08';

=head1 NAME

perlec - Perl Easy Call Interface

=head1 VERSION

Version 0.08

=head1 SYNOPSIS

 perlec_t perlec;
 perlec_init(&perlec);
 
 str = "abc";
 re = "(\\w+)";
 matches = perlec_match(str, strlen(str), re, strlen(re), PERLEC_ROPT_NONE);
 
 result = perlec_eval("1+2");
 
 perlec_discard(&perlec);

=head1 DESCRIPTION

perlec is a C library which enables embedding perl 
interpretor to your program simply.

=head1 FUNCTIONS

=head2 perlec_init()

 void perlec_init(perlec_t* perlec);

Initializes perlec instance.

=head2 perlec_discard()

 void perlec_discard(perlec_t* perlec);

Discards perlec instance.

=head2 perlec_match()

 perlec_array_t* ret = perlec_match(perlec, str, str_len, re_len, flags);

NULL when compiling regexp is failed or does not match.
if fail, perlec_errmsg returns scalar, and otherwise return NULL.

flags is bitwise-or of followings:

 PERLEC_ROPT_NONE
 PERLEC_ROPT_MULTILINE
 PERLEC_ROPT_SINGLELINE
 PERLEC_ROPT_IGNORECASE
 PERLEC_ROPT_EXTENDED
 PERLEC_ROPT_UTF8

=head2 perlec_replacement()

 perlec_scalar_t* ret = perlec_replacement(perlec, str, str_len, re, re_len, replacement, replacement_len, flags);

like C<STR =~ s/PATTERN/REPLACEMENT/g>.

=head2 perlec_compile()

 perlec_rx_t* ret = perlec_compile(perlec, re, re_len, flags);

compile regexp pattern.

=head2 perlec_match_rx()

 perlec_array_t* ret = perlec_match_rx(perlec, str, str_len, rx, flags);

=head2 perlec_errmsg()

 perlec_scalar_t* ret = perlec_errmsg(perlec);

get C<$@> string.

=head2 perlec_eval()

 perlec_scalar_t* ret = perlec_eval(perlec, str, str_len);

eval string.

=head1 AUTHOR

YAMASHINA Hio, C<< <hio at cpan.org> >>

=head1 BUGS

Please report any bugs or feature requests to
C<bug-perlec at rt.cpan.org>, or through the web interface at
L<http://rt.cpan.org/NoAuth/ReportBug.html?Queue=perlec>.
I will be notified, and then you'll automatically be notified of progress on
your bug as I make changes.

=head1 SUPPORT

You can find documentation for this module with the perldoc command.

    perldoc perlec

You can also look for information at:

=over 4

=item * AnnoCPAN: Annotated CPAN documentation

L<http://annocpan.org/dist/perlec>

=item * CPAN Ratings

L<http://cpanratings.perl.org/d/perlec>

=item * RT: CPAN's request tracker

L<http://rt.cpan.org/NoAuth/Bugs.html?Dist=perlec>

=item * Search CPAN

L<http://search.cpan.org/dist/perlec>

=back

=head1 ACKNOWLEDGEMENTS

=head1 COPYRIGHT & LICENSE

Copyright 2007 YAMASHINA Hio, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut

*/

#endif
/* ----------------------------------------------------------------------------
 * Copyright (C) 2007 YAMASHINA Hio
 * This program is free software; you can redistribute it and/or modify it
 * under the same terms as Perl itself.
 * ----------------------------------------------------------------------------
 * End of File.
 * ------------------------------------------------------------------------- */
