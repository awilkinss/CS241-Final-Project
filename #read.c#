/* program to read in a corpus sheet file
   and return an array of chords used
   in the file */

#include <stdlib.h>
#include <ctype.h>

char **read(char *filename){
  /*
  char line[100], filename[50], chords[64][128];
  char *parsed;
  FILE *input;
  int i,j,l,size;
  
  i=0;
  j=0;
  printf("Please pick a file: ");
  scanf("%s",filename);
  */
  
        FILE *input = fopen(filename, "r");
        if(input == NULL) {
                perror("Failure to open");
                exit(1);
        }

	char *chord = scaf("%s", input);

        while (fgets(line,sizeof(line),input)){
                if(i%2==0){
                        i++;
                }
                else{
                        parsed = trim(strtok(line," "));
                        while(parsed != NULL){
                                strcpy(chords[j],parsed);
                                j++;
                                size++;
                                parsed = strtok(NULL," ");
                        }
                        i++;
                }
        }
        for(int i=0; i < size ;i++){
                printf("%s \n", chords[i]);
        }

        return 0;
}

char *trim(char *s){
        int l = strlen(s);


        while(isspace(s[l-1])) --l;
        while(*s && isspace(*s)) ++s, --l;

        return strndup(s,l);
}
