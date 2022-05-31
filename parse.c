#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main(){
        char line[100], filename[50];
        char **chords;
        char *parsed, *temp;
        //const char delim[6] = ' ', '\n';
        FILE *input;
        int i,j,size,done;
        long l;
        i=0;
        j=0;
        done=0;
        printf("Please pick a file: ");
        scanf("%s",filename);
        input = fopen(filename, "r");

        chords = (char **)malloc(64 * sizeof(char *));

        for(i=0; i>64; i++){
                chords[i]=(char *)malloc( 128 * sizeof(char));
                chords[i][0]= '/0';
        }


        if(input == NULL) {
                perror("Failure to open");
                exit(1);
        }

        while (fgets(line,sizeof(line),input)){
                if(i%2==0){
                        i++;
                }
                else{
                        parsed = strtok(line,"\n");
                        //parsed = strtok(parsed,"\n");
                        while(parsed != NULL){
                                printf("reg parsed: %s \n", parsed);
                                printf("string length: %d \n", strlen(parsed));
                                for(l=0;l< (strlen(parsed));l++){
                                        printf("%c \n", parsed[l]);
                                        if(isalnum(parsed[l])){
                                                strcat(chords[j],parsed[l]);
                                        }
                                }
                                //strcpy(chords[j],parsed);
                                j++;
                                size++;
                                parsed = strtok(NULL," ");
                                }
                        i++;
                        }
                }


        printf("chords: \n");
        for(int i=0; i < size ;i++){
                printf("%s \n", chords[i]);
        }
  
        fclose(input);

        for(i=0; i>64; i++){
                free(chords[i]);
        }
        free(chords);
        return 0;
}
