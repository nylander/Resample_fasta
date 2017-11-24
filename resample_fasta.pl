#!/usr/bin/perl 
#===============================================================================
=pod

=header2

             FILE:  resample_fasta.pl

            USAGE:  ./resample_fasta.pl [--nreps=1] [--jack=50] [--percent=100] [--split] [--help] infile(s)


      DESCRIPTION:  Input: fasta alignment (i.e., sequences of the same length!)

          OPTIONS:  --nreps=1
                    --jack=50
                    --percent=100
                    --split
                    --help
                    --man
                    --version
                    --verbose

     REQUIREMENTS:  ---
             BUGS:  This script will not work on very long (many GB) of sequences
            NOTES:  ---
           AUTHOR:  Johan A. A. Nylander (JN), <jnylander @ users.sourceforge.net>
          COMPANY:  SU
          VERSION:  1.0
          CREATED:  09/23/2010 12:48:40 PM CEST
         REVISION:  fre 24 nov 2017 11:14:04
=cut

#===============================================================================

use strict;
use warnings;
use Getopt::Long;
use Data::Dumper;
use Pod::Usage;
use List::Util qw(shuffle);


## Globals
my $nreps    = 1;
my $jack     = 0;
my $boot     = 1;
my $percent  = 100;
my $split    = 0;
my $term     = $/;
my $verbose  = 0;
my $help     = q{};
my $VERSION  = "0.1"; # Change in POD as well as here!
my $CHANGES  = "09/23/2010 06:10:47 PM CEST";
my $PRINT_FH;

## Read args
my $res = GetOptions (
                      "help"        => sub { pod2usage(1); },
                      "version"     => sub { print STDOUT "  $0 version $VERSION\n  Last changes $CHANGES\n"; exit(0) },
                      "man"         => sub { pod2usage(-exitstatus => 0, -verbose => 2); },
                      "jack=f"      => \$jack,
                      "nreps=i"     => \$nreps,
                      "split"       => \$split,
                      "percent=i"   => \$percent,
                      "verbose"     => \$verbose,
                    );

my $nargs = scalar(@ARGV);
if ($nargs < 1) {
    die "Usage: $0 infile\nfor options see $ --help\n";
}
if ($jack) {
    $boot = 0;
}
if (!$split) {
    $PRINT_FH = *STDOUT; # Using the typeglob notation in order to use STDOUT as a variable
}


#===  FUNCTION  ================================================================
#         NAME:  get_random_nrs
#      VERSION:  fre 24 nov 2017 11:07:04
#  DESCRIPTION:  GEt an array of random numbers
#   PARAMETERS:  $inchar, $outchar  = number of input and output characters
#      RETURNS:  ???
#         TODO:  ???
#===============================================================================
sub get_random_nrs {
    my ($inchar, $outchar) = (@_);
    my @nums = ();
    srand;
	for (my $i = 0 ; $i < $outchar ; $i++) {
        #my $r = $from + int(rand($to - $from));
		my $nr = int(rand($inchar));
		push @nums, $nrs;
	}
	return(\@nums);
} # end of get_random_nrs



#===  FUNCTION  ================================================================
#         NAME:  "main"
#      VERSION:  09/23/2010 01:40:07 PM CEST
#  DESCRIPTION:  ???
#   PARAMETERS:  ???
#      RETURNS:  ???
#         TODO:  ???
#===============================================================================

## Read infiles from STDIN
while (my $infile = shift(@ARGV)) {

    my %seq_hash = ();
    my $outnr    = q{};

    ## Read infile
    open my $INFILE, "<", $infile or die "open failed: $! \n";
    $/ = ">";
    while (<$INFILE>) {
        chomp;
        next if($_ eq '');
        my ($id, @sequencelines) = split /\n/;
        my $sequence = '';
        foreach my $line (@sequencelines) {
            $sequence .= $line;
        }
        my (@bases) = split //, $sequence;
        foreach my $base (@bases) {
            push @{$seq_hash{$id}}, $base;
        }
    }
    $/ = $term;
    close($INFILE);

    ## Get the length of the sequences
    my $seq_length;
    my $lname;
    foreach my $name (keys %seq_hash) {
        my $l = scalar(@{$seq_hash{$name}});
        if ( defined $seq_length ) {
            die "Sequences not all same length in $infile ($lname is $seq_length, $name is $l)"
              unless $seq_length == $l;
        }
        else {
            $seq_length = scalar(@{$seq_hash{$name}});
            $lname  = $name;
        }
    }


    ## Bootstrap or jackknife
    if ($boot) {
        print STDERR "Doing $nreps bootstrapping ($percent%).\n" if ($verbose > 0);
        
        ## Set the length of the output seq, allowing boot to sample more than 100%
        $outnr = int($seq_length * ($percent/100));
        if ($outnr < 1) {
            print STDERR "Warning: adjusted output seq length to 1 when using --percent=$percent\n";
            $outnr = 1;
        }

        ## Do the printing
        for (my $i=0; $i < $nreps; $i++) {
            if ($split) {
                my $rep_file = $infile . "." . $i . ".fas";
                open $PRINT_FH, ">", $rep_file or die "could not open $rep_file for printing : $! \n";
            }

            #my (@random_numbers) = get_random_nrs($seq_length, $outnr);
            my $random_numbers = get_random_nrs($seq_length, $outnr);

            foreach my $taxon (sort keys %seq_hash) {
                print $PRINT_FH ">$taxon\n";
                print $PRINT_FH @{$seq_hash{$taxon}}[@{$random_numbers}]; # array slice
                print $PRINT_FH "\n";
            }
            if ($split) {
                close($PRINT_FH);
            }
            elsif ($nreps > 1) {
                print $PRINT_FH "\n";
            }
        }
    }
    else { # Jackknife
        print STDERR "Doing $nreps jackknifing ($percent%).\n" if ($verbose > 0);

        ## Set the length of the output seq 
        $outnr = int($seq_length * ($jack/100));
        if ($outnr < 1) {
            print STDERR "Warning: adjusted output seq length to 1 when using --percent=$percent\n";
            $outnr = 1;
        }

        ## Do the printing
        for (my $i=0; $i < $nreps; $i++) {
            if ($split) {
                my $rep_file = $infile . "." . $i . ".fas";
                open $PRINT_FH, ">", $rep_file or die "could not open $rep_file for printing : $! \n";
            }
            ## fre 24 nov 2017 11:21:20: Too expensive way of generating the array on numbers
            my (@numbers) = shuffle 0..$seq_length-1; # list needs to include 0
            my (@jacks) = @numbers[0..$outnr-1]; # list needs to include 0

            foreach my $taxon (sort keys %seq_hash) {
                print $PRINT_FH ">$taxon\n", @{$seq_hash{$taxon}}[@jacks], "\n";
            }
            if ($split) {
                close($PRINT_FH);
            }
            elsif ($nreps > 1) {
                print $PRINT_FH "\n";
            }
        }
    }

    if ($nargs > 1) {
        print $PRINT_FH "\n\n";
    }
}

print STDERR "\nDone.\n" if ($verbose > 0);

exit(1);

__END__

#===  POD DOCUMENTATION  =======================================================
#      VERSION:  fre 24 nov 2017 11:22:36
#  DESCRIPTION:  Documentation
#         TODO:  ?
#===============================================================================
=pod

=head1 NAME

resample_fasta.pl


=head1 VERSION

Documentation for resample_fasta version 0.1


=head1 SYNOPSIS

resample_fasta.pl [--nreps=1] [--jack=50] [--percent=100] [--split] [--help] INFILE(S) > OUTPUT


=head1 DESCRIPTION

Script for resampling fasta formatted alignments (i.e., sequences need to be of same length).

Bootstrapping (sampling with replacement) or jackknifing (w.o. replacement) can be applied.

Different deletion percentages can be applied in jackknifing.

Warning, script will not work on very long (GB) sequences.


=head1 OPTIONS

=over 8

=item B<--nreps=>I<number>

Create I<number> of new matrices from the input data.


=item B<--jack=>I<number>

Do Jackknifing, i.e., sampling without replacement instead of bootstrapping (the default).

I<number> will decide the fraction (as percentage) of the characters sampled. 
Popular values is either I<50.0>%, or 1/e = I<36.78794410>%.


=item B<--precentage=>I<number>

Resample I<number> percent, for example I<50>, of the data. Default is I<100>.


=item B<--split>

If used together with B<--nreps>, allows printing of individual matrices to separate files.


=item B<--help>

Prints help message and exits.


=item B<--man>

Displays the manual page.


=item B<--version>

Prints version message and exits.


=item B<--verbose>

Be verbose.


=item B<FILE>

FASTA formatted alignment file(s)


=item B<OUTPUT>

Prints to B<STDOUT> unless B<--split> is used.


=back


=head1 USAGE

Examples:

    resample_fasta.pl infile > out
    resample_fasta.pl --jack=37 infile > out
    resample_fasta.pl --nreps=10 --split infile


=head1 AUTHOR

Written by Johan A. A. Nylander


=head1 REPORTING BUGS

Please report any bugs to I<jnylander @ users.sourceforge.net>.


=head1 DEPENDENCIES

Uses Perl modules Getopt::Long and Pod::Usage


=head1 LICENSE AND COPYRIGHT

Copyright (c) 2010-2017 Johan Nylander.
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. 
http://www.gnu.org/copyleft/gpl.html 


=cut

