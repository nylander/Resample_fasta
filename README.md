# Resample FASTA alignments

- Last modified: fre mar 28, 2025  05:24
- Sign: Johan Nylander

## Description

Sample random columns from a set of aligned fasta formatted sequences.
That is, sample positions in first sequence, then make sure to
sample the same positions in all consecutive sequences as well.

Written with low memory requirements and speed in mind.

## Install

See file [INSTALL](INSTALL)

## Run

    $ refast data/infile > outfile.fas

## Help and options

    $ refast -h
    Usage: refast [options] <infile>
    Options:
      -x fraction  Set the fraction to sample (default: 0.50)
      -w wrap      Set the line wrap length (default: 60)
      -h           Show this help message
      -v           Show version information
      infile is an alignment in fasta format

## Scripts

The file [`scripts/resample_fasta.pl`](scripts/resample_fasta.pl) is the first
implementation.  Still works, but too slow on very large data.

## License and copyright

[MIT License](LICENSE)

