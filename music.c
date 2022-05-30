/* Jesse, Toby, Alim - functions used in
   Markov model chord generation */

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

/* node struct */
struct node{
  char key;
  int freq;
  struct node *next;
  struct node *prev;
};

/* list struct */
struct list{
  struct node *head;
  struct node *tail;
};

/* dictionary struct */
struct dictionary{
  char key;
  struct list *chords;
  struct list *freq;
  struct dictionary *next;
  struct dictionary *prev;
};

/* dictionary list struct */
struct dictList{
  struct dictionary *head;
  struct dictionary *tail;
};

/* func for creating a node */
struct node *createNode(char c){
  struct node *newNode = malloc(sizeof(struct node));
  if(newNode == NULL){
    perror("Error!");
    exit(1);
  }
  newNode->key = c;
  newNode->freq = 0;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

/* func for creating a list */
struct list *createList(){
  struct list *newList = malloc(sizeof(struct list));
  struct node *head = createNode('s');
  struct node *tail = createNode('s');
  if(newList == NULL){
    perror("Error!");
    exit(1);
  }
  newList->head = head;
  newList->tail = tail;
  newList->head->next = newList->tail;
  newList->tail->prev = newList->head;
  return newList;
}

/* func for creating a dictionary */
struct dictionary *createDict(char c){
  struct dictionary *newDictionary = malloc(sizeof(struct dictionary));
  if(newDictionary == NULL){
    perror("Error: ");
    exit(1);
  }
  newDictionary->key = c;
  newDictionary->chords = createList();
  newDictionary->freq = createList();
  newDictionary->next = NULL;
  newDictionary->prev = NULL;
  return newDictionary;
}

/* func for creating a dictionary list */
struct dictList *createDictList(){
  struct dictList *newDictList = malloc(sizeof(struct dictList));
  if(newDictList == NULL){
    perror("Error!");
    exit(1);
  }
  struct dictionary *head = createDict('s');
  struct dictionary *tail = createDict('s');
  newDictList->head = head;
  newDictList->tail = tail;
  newDictList->head->next = newDictList->tail;
  newDictList->tail->prev = newDictList->head;
  return newDictList;
}

/* func that fetches a certain dictionary based 
   on an inputed key and dictionary list */
struct dictionary *fetchDictionary(char key, struct dictList *song){
  struct dictionary *temp = song->head->next;
  while(temp != song->tail){
    if(temp->key == key){
      return temp;
    }
    temp= temp->next;
  }
  return temp;
}

/* func that fetches a chord node from a chord list */ 
struct node *fetchChord(char chord, struct list *chordList){
  struct node *temp = chordList->head->next;
  while(temp != chordList->tail){
    if(temp->key == chord){
      return temp;
    }
    temp = temp->next;
  }
  return temp;
}

/* func to insert a node in a list */
void insertNode(struct node *chord, struct list *chords){
  struct node *head = chords->head;
  struct node *tail = chords->tail;
  struct node *temp = head->next;
  if(head->next != tail){
    chord->next = temp;
    head->next = chord;
    temp->prev = chord;
    chord->prev = head;
  }
  else{
    head->next = chord;
    chord->next = tail;
    tail->prev = chord;
    chord->prev = head;
  }
}

/* inserts a dictionary into a dictionary
   list */
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

void updateDictionary(char chord, struct dictionary *dict){
  struct list *chordListTemp = dict->chords;
  struct node *tempChord = fetchChord(chord, chordListTemp);
  if(tempChord->key == 's'){
    struct node *tempChord2 = createNode(chord);
    tempChord2->freq = tempChord2->freq +1;
    insertNode(tempChord2, chordListTemp);
  }else{
    tempChord->freq = tempChord->freq +1;
  }
}

void updateDictionaryList(char dictionaryKey,char chord, struct dictList *song){
  struct dictionary *dict = fetchDictionary(dictionaryKey,song);
  if(dict->key == 's'){
    struct dictionary *newDict = createDict(dictionaryKey);
    updateDictionary(chord, newDict);
    insertDictionary(newDict,song);
  }else{
    updateDictionary(chord,dict);
  }
}
    

int main(){

  struct dictList *song = createDictList();
  printf("%c\n",song->head->key);
  printf("%c\n",song->head->chords->head->key);
  updateDictionaryList('C','F', song);
  printf("%c\n",song->head->next->key);
  printf("%c\n",song->head->next->chords->head->next->key);
  printf("%d\n",song->head->next->chords->head->next->freq);
  return 1;
  
}
