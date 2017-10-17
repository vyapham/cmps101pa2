/*********
 * Name: VY PHAM
 * ID: vyapham
 * Student ID #: 1593394
 * Assignment name: pa2
 ********/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include<string.h>

#define MAX_LEN 2048

List insertion(char* s[], int length) {
  List L = newList();

  append(L, 0);
  
  for (int i = 1; i <= length; i++) {
    if (strcmp(s[i], s[front(L)]) < 0) {
      prepend(L, i);
      continue;
    }
    if (strcmp(s[i], s[back(L)]) > 0) {
      append(L, i);
      continue;
    } 
    moveFront(L);
    while (index(L) != -1) {
      if (strcmp(s[i], s[get(L)]) >= 0) {
	moveNext(L);
      }
      else {
	insertBefore(L, i);
	break;
      }
    }
  }
 
  return L;
}

int main(int argc, char* argv[]) {
  int lineNumber = 0;
  FILE *in, *out;
  char line[MAX_LEN];

  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  
  in = fopen(argv[1], "r");
  if(in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  
  while(fgets(line, MAX_LEN, in) != NULL)  {
    lineNumber++;      
  }

  char* s[MAX_LEN];

  for(int i = 0;  i <= lineNumber; i++){
    s[i] = calloc(1, sizeof(char* [MAX_LEN]) );
  }
  // char* s[lineNumber];
  //fclose(in);
  rewind(in);
  //  in = fopen(argv[1], "r");

  int n = 0;
  while(fgets(line, MAX_LEN, in) != NULL) {
    strcpy(s[n], line);
    //    printf("%s ", s[n]);
    n++;
  }
  
  fclose(in);

  List L = insertion(s, lineNumber);

  out = fopen(argv[2], "w");

  if(out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  moveFront(L);
  while (index(L) != -1) {
    fprintf(out, "%s", s[get(L)]);
    moveNext(L);
  }

  fclose(out);
    
  n = 0;
  while (n <= lineNumber) {
    free(s[n]);
    n++;
  }
  freeList(&L);
   
  return 0;
}
