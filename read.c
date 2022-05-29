#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main(){
        char line[100], filename[50], chords[64][128];
        char *parsed;
        FILE *input;
        int i,j,size;
        const char delim[2] = " ";

        i=0;
        j=0;
        printf("Please pick a file: ");
        scanf("%s",filename);
        input = fopen("chords.txt", "r");

        if(input == NULL) {
                perror("Failure to open");
                exit(1);
        }

        while (fgets(line,sizeof(line),input)){
                if(i%2==0){
                        i++;
                }
                else{
                        parsed = strtok(line, delim);
                        while(parsed != NULL){
                                strcpy(chords[j],parsed);
                                parsed = strtok(NULL,delim);
                                j++;
                                size++;
                        }
                        i++;
                         }
        }
        for(int i=0; i < size ;i++){
                printf("%s \n", chords[i]);
        }

        return 0;
}
