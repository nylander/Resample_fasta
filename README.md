# Resample FASTA alignments

- Thu 15 Feb 2018 10:42:24 AM CET 
- Johan.Nylander@{nrm|nbis}.se

## Description

Sample random columns from a set of aligned fasta formatted sequences.
That is, sample positions in first sequence, then make sure to
sample the same positions in all consecutive sequences as well.

Written with low memory requirements and speed in mind.

## Compile

    cd src
    make
    make test

## Run

    ./refas infile > outfile.fas

## Note

This is work in progress ("proof of concept").
Currently the resampling fraction is set to 50%. To change this, edit
the file `resample_fasta.c`, and set a new value for the constant `XFRAC`,
then recompile.

