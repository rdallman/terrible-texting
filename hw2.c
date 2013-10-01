/*
 * Reed Allman
 * reed@auburn.edu
 * man and stackoverflow are my only friends :(
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* readFile(char* name);
char* decryptMsg(char* emsg);

typedef struct Node {
  struct Node* next;
  char c;
} Node;

//place the node at <pos> at head of list, then return it
Node* popIt(Node** list, int pos) {
  Node *curr, *prev;
  prev = NULL;

  int i = 0;
  for ( curr = *list;
        curr != NULL;
        i++, prev = curr, curr = curr->next) {
    //this is the node we are looking for
    if (i == pos) {
      if (prev == NULL) {
      } else {
        prev->next = curr->next;
        curr->next = *list;
        *list = curr;
      }
      return *list;
    }
  }
}

void insert(Node** list, char c) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->c = c;
  n->next = *list;
  *list = n;
}

char* decryptMsg(char *emsg) {
  char *dmsg = malloc(sizeof(emsg));
  Node* list = malloc(sizeof(Node));

  size_t n = 0;
  size_t m = 0;
  size_t l = 0;

  while (emsg[n]) {
    if (isdigit(emsg[n])) {
      //just getting an int from a char[], nothing to see here
      char* num;
      num = malloc(1024);
      size_t z = 0;
      while(isdigit(emsg[n])) {
        num[z++] = emsg[n++];
      }
      dmsg[m++] = popIt(&list, atoi(num))->c;
    } else {
      //just put the letter
      dmsg[m++] = emsg[n];
      insert(&list, emsg[n++]);
    }
    n++;
  }
  dmsg[m] = '\0';
  return dmsg;
}

//reads file <name> char by char
char* readFile(char* name) {
  FILE *file = fopen(name, "rt");
  char *msg;
  msg = malloc(1000 * sizeof(char));
  size_t n = 0;
  int c;

  if (file == NULL) {
    fprintf(stderr, "bad file: %s", name);
    exit(1);
  }

  while ((c = fgetc(file)) != EOF) {
    msg[n++] = (char) c;
  }
  msg[n] = '\0';

  return msg;
}

//let the magic happen
int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file.txt", argv[0]);
    exit(1);
  }

  char* emsg = readFile(argv[1]);
  printf("Encrypted Message:\n%s\n", emsg);

  char* dmsg = decryptMsg(emsg);
  printf("Decrypted Message:\n%s\n", dmsg);

  return 1;
}
