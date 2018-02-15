# Resample FASTA alignments

- Thu 15 Feb 2018 10:42:24 AM CET 
- Johan.Nylander@{nrm|nbis}.se

## Description

Sample random columns from a set of aligned fasta formatted sequences.
That is, sample positions in first sequence, then make sure to
sample the same positions in all consecutive sequences as well.

## Compile

    cd src
    make
    make test
