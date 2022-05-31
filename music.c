#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

struct node{
  char key[10];
  int freq;
  struct node *next;
  struct node *prev;
};
struct list{
  int size;
  struct node *head;
  struct node *tail;
};
struct dictionary{
  char key[10];
  struct list *chords;
  struct list *freq;
  struct dictionary *next;
  struct dictionary *prev;
};
struct dictList{
  struct dictionary *head;
  struct dictionary *tail;
};
struct node *createNode(char *c){
  struct node *newNode = malloc(sizeof(struct node));
  if(newNode == NULL){
    perror("Error!");
    exit(1);
  }
  strcpy(newNode->key,c);
  newNode->freq = 0;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}
struct list *createList(){
  struct list *newList = malloc(sizeof(struct list));
  struct node *head = createNode("s");
  struct node *tail = createNode("s");
  if(newList == NULL){
    perror("Error!");
    exit(1);
  }
  newList->size = 0;
  newList->head = head;
  newList->tail = tail;
  newList->head->next = newList->tail;
  newList->tail->prev = newList->head;
  return newList;
}
struct dictionary *createDict(char *c){
  struct dictionary *newDictionary = malloc(sizeof(struct dictionary));
  if(newDictionary == NULL){
    perror("Error: ");
    exit(1);
  }
  strcpy(newDictionary->key,c);
  newDictionary->chords = createList();
  newDictionary->freq = createList();
  newDictionary->next = NULL;
  newDictionary->prev = NULL;
  return newDictionary;
}
struct dictList *createDictList(){
  struct dictList *newDictList = malloc(sizeof(struct dictList));
  if(newDictList == NULL){
    perror("Error!");
    exit(1);
  }
  struct dictionary *head = createDict("s");
  struct dictionary *tail = createDict("s");
  newDictList->head = head;
  newDictList->tail = tail;
  newDictList->head->next = newDictList->tail;
  newDictList->tail->prev = newDictList->head;
  return newDictList;
}
struct dictionary *fetchDictionary(char *key, struct dictList *song){
  struct dictionary *temp = song->head->next;
  while(temp != song->tail){
    if(strcmp(temp->key,key) == 0){
      return temp;
    }
    temp= temp->next;
  }
  return temp;
}
struct node *fetchChord(char *chord, struct list *chordList){
  struct node *temp = chordList->head->next;
  while(temp != chordList->tail){
    if(strcmp(temp->key,chord) == 0){
      return temp;
    }
    temp = temp->next;
  }
  return temp;
}
void insertNode(struct node *chord, struct list *chords){
  struct node *head = chords->head;
  struct node *tail = chords->tail;
  struct node *temp = head->next;
  if(head->next != tail){
    chord->next = temp;
    head->next = chord;
    temp->prev = chord;
    chord->prev = head;
    chords->size = chords->size + 1;
  }
  else{
    head->next = chord;
    chord->next = tail;
    tail->prev = chord;
    chord->prev = head;
    chords->size = chords->size + 1;
  }
}
void insertDictionary(struct dictionary *newDict, struct dictList *song){
  struct dictionary *head = song->head;
  struct dictionary *tail = song->tail;
  struct dictionary *temp = head->next;
  if(head->next != tail){
    newDict->next = temp;
    head->next = newDict;
    temp->prev = newDict;
    newDict->prev = head;
  }
  else{
    head->next = newDict;
    newDict->next = tail;
    tail->prev = newDict;
    newDict->prev = head;
  }
}

void updateDictionary(char *chord, struct dictionary *dict){
  struct list *chordListTemp = dict->chords;
  struct node *tempChord = fetchChord(chord, chordListTemp);
  if(strcmp(tempChord->key, "s") == 0){
    struct node *tempChord2 = createNode(chord);
    tempChord2->freq = tempChord2->freq +1;
    insertNode(tempChord2, chordListTemp);
  }else{
    tempChord->freq = tempChord->freq +1;
  }
}

void updateDictionaryList(char *dictionaryKey,char *chord, struct dictList *song){
  struct dictionary *dict = fetchDictionary(dictionaryKey,song);
  if(strcmp(dict->key,"s") == 0){
    struct dictionary *newDict = createDict(dictionaryKey);
    updateDictionary(chord, newDict);
    insertDictionary(newDict,song);
  }else{
    updateDictionary(chord,dict);
  }
}

//chord picker related stuff
int * frequencyArrayMaker(char *c, struct dictList *dictListSong){
  struct dictionary *chord = fetchDictionary(c,dictListSong);
  struct list *chords = chord->chords;
  struct node *temp = chords->head->next;
  int n = chords->size;
  int array[n];
  int i = 0;
  while(temp != chords->tail){
    array[i] = temp->freq;
    temp = temp->next;
    i++;
  }
  return array;
}

char ** chordArrayMaker(char *c, struct dictList *song){
  struct dictionary *chord = fetchDictionary(c,song);
  struct list *chords = chord->chords;
  struct node *temp = chords->head->next;
  char **array = NULL;
  array = malloc(sizeof(char *) * chords->size);
  for(int k = 0; k < chords->size; k++){
    array[k] = malloc((chords->size+1)*sizeof(char));
  }
  int i = 0;
  while(temp != chords->tail){
    strcpy(array[i], temp->key);
    temp = temp->next;
    i++;
  }
  return array;
}

int findCeil(int arr[], int r, int l, int h){
  int mid;
  while(l < h){
    mid = l + ((h-l) >> 1);
    (r > arr[mid]) ? (l = mid +1) : (h = mid);
  }
  return (arr[l] >= r) ? l : -1;
}

char * chooseChord(char **chords,int *frequency, int n){
  int freq[n];
  for(int m =0; m < n; m++){
    freq[m] = *(frequency+m);
  }
  int prefix[n], i;
  prefix[0] = freq[0];
  for (i = 1; i < n; ++i)
    prefix[i] = prefix[i - 1] + freq[i]; 
  int r = (rand() % prefix[n - 1]) + 1;
  int indexc = findCeil(prefix, r, 0, n - 1);
  return chords[indexc];
}

int main(){

  struct dictList *song = createDictList();
  char newChord[24][10];
  char chosen[10] = "C";
  updateDictionaryList("C","F",song);
  updateDictionaryList("F","D",song);
  updateDictionaryList("D","C",song);
  updateDictionaryList("C","B",song);
  updateDictionaryList("B","C",song);
  updateDictionaryList("C","G",song);
  struct dictionary *dict = fetchDictionary(chosen,song);
  int n = dict->chords->size;
  printf("%d",n);
  for(int j = 1; j < 24; j++){  
    strcpy(chosen,chooseChord(chordArrayMaker(chosen,song),frequencyArrayMaker(chosen,song),n));
    strcpy(newChord[j], chosen);
    printf("%s",newChord[j]);
  }
  /*printf("%s\n",song->head->key);
  printf("%s\n",song->head->chords->head->key);
  updateDictionaryList("Cmaj","Fmin", song);
  printf("%s\n",song->head->next->key);
  printf("%s\n",song->head->next->chords->head->next->key);
  printf("%d\n",song->head->next->chords->head->next->freq);
  updateDictionaryList("Cmaj","Fmin",song);
  printf("This should be Cmaj:%s\n",song->head->next->key);
  printf("This should be s:%s\n",song->head->next->next->key);
  printf("This should be Fmin:%s\n",song->head->next->chords->head->next->key);
  printf("This shoudl be s:%s\n",song->head->next->chords->head->next->next->key);
  printf("This should be Fmin Freq 2:%d\n",song->head->next->chords->head->next->freq);*/
  

  return 1;
  
}
