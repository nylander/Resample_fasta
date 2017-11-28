//source https://raw.githubusercontent.com/IGBB/reservoir_sample/master/reservoir_sample.c
//Quickly sample fast[qa] files using the reservoir sample algorithm
//gcc -o reservoir_sample reservoir_sample.c -lz to complie.
//reservoir_sample --help prints help message

#include <stdlib.h>
#include <zlib.h>  
#include <stdio.h>  
#include <stdint.h>
#include <limits.h>
#include <argp.h>
#include <time.h>

#include "kseq.h" 

#define parse_args(args) argp_parse (&argp, argc, argv, 0, 0, args);

#define RAND()                                                          \
  ((((uint64_t) rand() <<  0) & 0x000000000000FFFFull) |                \
   (((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) |                \
   (((uint64_t) rand() << 32) & 0x0000FFFF00000000ull) |                \
   (((uint64_t) rand() << 48) & 0xFFFF000000000000ull))

struct arguments {
  int size, crop;
  char* name; 
  char* files[64];
  int file_count;
};


const char *argp_program_version = "reservoir_sample 0.0a";
const char *argp_program_bug_address = "<maa146@igbb.msstate.edu>";
const char doc[] = "Sample fast[aq].gz files using reservoir sampling and output them in fasta format";
const char args_doc[] = "FILE ...";
const struct arguments ARG_DEFAULTS = {0, 85, "TEST"};
const struct argp_option options[] =
  {
    {"reservoir_size",    's', "SIZE",   0, "Number of reads to output" },
    {"read_length",       'l', "LENGTH", 0, "Read length to crop to"    },
    {"name",              'n', "NAME",   0, "Header name in output"     },
    {0}
  };

int parse_opt (int key, char *arg, struct argp_state *state) { 
  struct arguments *args = state->input;
  switch (key) { 

  case 's':
    args->size = atoi(arg);
    break;
  case 'l':
    args->crop = atoi(arg);
    break;
  case 'n':
    args->name = arg;
    break;

    /* assume bare arguments are file */
  case ARGP_KEY_ARG:
    args->files[state->arg_num] = arg;
    
    break;
  case ARGP_KEY_END:
    args->file_count = state->arg_num;
    break;
  }
  return 0; 
}

const struct argp argp = { options, parse_opt, args_doc, doc };

KSEQ_INIT(gzFile, gzread)


int main (int argc, char** argv){
  struct arguments args = ARG_DEFAULTS;
  uint64_t index, count;
  gzFile fp;
  int i;
  kseq_t *seq;
  char **reservoir;

  parse_args(&args);
  
  reservoir = calloc(args.size, sizeof(char*));

  count = 0;

  srand ( time(NULL) );
  
  for( i = 0; i < args.file_count; i++){
    fprintf(stderr, "   files[%d]:      %s\n", i, args.files[i]);
    
    fp = gzopen(args.files[i], "r");
    seq = kseq_init(fp);

    while (kseq_read(seq) >= 0) {
      index = count;
      count++;
      
      if(index > args.size)
        index = RAND() % count;

      if(index < args.size){
        reservoir[index] = realloc(reservoir[index], seq->seq.l+1);
        memcpy(reservoir[index], seq->seq.s, seq->seq.l);
        reservoir[index][args.crop] = 0;
      }
    }
    
    kseq_destroy(seq);
    gzclose(fp);
  }

  for( i = 0; i < args.size; i++)
    printf(">%s_%d\n%s\n", args.name, i, reservoir[i]);
    
  return 0;
}
