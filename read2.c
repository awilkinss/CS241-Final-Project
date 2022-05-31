/* program to read in a corpus sheet file
   and return an array of chords used
   in the file */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#define NOTES_SIZE 7
#define CHORD_SIZE 7

void skip_space(char ch, FILE *fp) {
  while (isspace(ch)) {
    ch = fgetc(fp);
  }
  return;
}

void next_line(char ch, FILE *fp) {
  while (ch != '\n') {
    ch = fgetc(fp);
  }
  ch = fgetc(fp);
  return;
}

char **read(char *filename){

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error: ");
    exit(1);
  }

  //char notes_arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char **chord_arr = NULL;
  chord_arr = (char **) malloc(sizeof(char *) * CHORD_SIZE);

  int line = 1;
  int count = 0;

  char *chord = NULL;
  chord = malloc(sizeof(char *) * CHORD_SIZE);

  char ch = fgetc(fp);
  skip_space(ch, fp);
  while(ch != EOF) {
    if (line % 2 == 0) {
      char ch = fgetc(fp);
      skip_space(ch, fp);

      while (isspace(ch) == 0) {
	strncat(chord, &ch, 1);
	ch = fgetc(fp);
      }
      chord_arr[count] = chord;
    }
    next_line(ch, fp);
    line++;
  }

  return chord_arr;

}

int main(int argc, char *argv[]) {
  char **chord_arr = read(argv[1]);
  int i = 0;
  while(chord_arr[i] != NULL) {
    printf("%s ", chord_arr[i]);
    i++;
  }
  printf("\n");
}
  
		   
