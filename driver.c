/* Toby, Alim, Jesse - driver file for final
   project */

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "read.h"
#include "music.h"

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char **orig_chords = read(argv[i]);

    /* process to generate new_chords */
  }

  /* print output as new corpus sheet */




  return 0;
}
