#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* readFile(char* n);

typedef struct Node {
  struct Node* next;
  char c;
} Node;

typedef struct List {
  Node* head;

  Node* (*popAtAndPush) (struct List* l, int pos);
  void (*insert) (struct List* l, char c);
} List;

Node* popAtAndPush(List* l, int pos) {
  int i = 0;
  Node* pn = l->head;
  Node* n = pn;
  while (i++ < pos) {
    /*printf("%c", n->c);*/
    pn = n;
    n = n->next;
  }
  /*printf("%c", n->c);*/
  pn->next = n->next;
  n->next = l->head;
  l->head = n;
  return n;
}

void insert(List* l, char c) {
  Node* n = malloc(sizeof(Node));
  n->c = c;
  n->next = l->head;
  l->head = n;
  /*printf("\nhead:%c", l->head->c);*/
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file.txt", argv[0]);
    exit(1);
  }

  char* emsg = readFile(argv[1]);
  printf("Encrypted Message:\n%s\n", emsg);

  char* dmsg;
  dmsg = malloc(sizeof(emsg));

  List list;
  list.head = NULL;
  list.popAtAndPush = &popAtAndPush;
  list.insert = &insert;

  size_t n = 0;
  size_t m = 0;
  size_t l = 0;

  while (emsg[n]) {
    if (isdigit(emsg[n])) {
      char* num;
      num = malloc(1024);
      size_t z = 0;
      while(isdigit(emsg[n])) {
        num[z++] = emsg[n++];
      }
      dmsg[m++] = list.popAtAndPush(&list, atoi(num))->c;
      printf("%c", dmsg[m-1]);
    } else {
      /*printf("%c", emsg[n]);*/
      dmsg[m++] = emsg[n];
      list.insert(&list, emsg[n++]);
      /*printf("%c", emsg[n]);*/
    }
    n++;
  }
  dmsg[m] = '\0';
  /*printf("%s", dmsg);*/
}

char* readFile(char* name) {
  FILE *file = fopen(name, "rt");
  char *msg;
  size_t n = 0;
  int c;

  if (file == NULL) {
    fprintf(stderr, "bad file: %s", name);
    exit(1);
  }

  msg = malloc(1000 * sizeof(char));

  while ((c = fgetc(file)) != EOF) {
    msg[n++] = (char) c;
  }
  msg[n] = '\0';

  return msg;
}
