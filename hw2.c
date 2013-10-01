#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* readFile(char* n);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file.txt", argv[0]);
    exit(1);
  }

  char* emsg = readFile(argv[1]);
  printf("Encrypted Message:\n%s\n", emsg);

  char* dmsg;
  dmsg = malloc(sizeof(emsg));

  char* list;
  list = malloc(50 * sizeof(char));

  size_t n, m, l;
  n=m=l=0;
  int c;
  while (emsg[n]) {
    c = emsg[n++];
    printf("%d", c);
    if (isdigit(c)) {
      dmsg[m++] = list[l-c];
    } else {
      dmsg[m++] = c;
      list[l++] = c;
    }
    n++;
  }
  dmsg[m] = '\0';
  printf("%s", dmsg);
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
