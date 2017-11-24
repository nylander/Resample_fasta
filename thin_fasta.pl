#!/usr/bin/perl 
#===============================================================================
=pod

=head2

         FILE:  thin_fasta.pl

        USAGE:  ./thin_fasta.pl --every=1000 [--help] infile | fold > outfile.fas


  DESCRIPTION:  Thin fasta alignment by printing every Nth position
  
                Input: file fasta alignment (i.e., sequences of the same length!)

                output: prints to stdout.

      OPTIONS:  
                --every=1000    print every Nth position. Default=1000
                --help          show this help

 REQUIREMENTS:  ---
         BUGS:  ---
        NOTES:  ---
       AUTHOR:  Johan A. A. Nylander (JN), <johan.nylander\@nrm.se>
      COMPANY:  SU
      VERSION:  1.0
      CREATED:  09/23/2010 12:48:40 PM CEST
     REVISION:  11/23/2017 04:38:16 PM

=cut
#===============================================================================

use strict;
use warnings;
use Getopt::Long;

$| = 1; # Do not buffer stdout

my $every = 1000;
my $help  = q{};

GetOptions (
    "help"   => sub { exec("perldoc", $0); exit(0); },
    "every=i" => \$every,
);

my $nargs = scalar(@ARGV);
if ($nargs < 1) {
    die "Usage: $0 infile\nfor options see $ --help\n";
}

my $infile = shift(@ARGV);
open my $IN, "<", $infile or die "open failed: $! \n";

my $i=0;
my $nl=0;
my @print;
while (<$IN>) {
    chomp;
    next if (/^\s*$/);
    if (/^>/) {
        print STDOUT "\n", $_, "\n";
        $i=0;
        $nl=0;
        @print = ();
        next;
    }
    my (@a) = split //;
    foreach my $p (@a) {
        $i++;
        if ($i == $every) {
            print STDOUT $p;
            $i=0;
            $nl++;
            if ($nl == 80) {
                print "\n";
                $nl = 0;
            }
        }
    }
}
print STDOUT "\n";
close($IN);

