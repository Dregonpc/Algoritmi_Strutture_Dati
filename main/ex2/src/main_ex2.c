#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/distance.h"

#define MAX_LEN 50

typedef struct{
    char word[MAX_LEN];
} Words;

Words* read_dictionary(const char *filename, size_t* num_words_dictionary) {
  FILE *file;
  size_t capacity = 1;
  size_t count = 0;

  Words* dictionary = malloc(capacity * sizeof(dictionary));
  if (dictionary == NULL) {
    printf("Allocation memory error.\n");
    return NULL;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file (Dictionary file).\n");
    free(dictionary);
    exit(EXIT_FAILURE);
  }

  while (fgets(dictionary[count].word, MAX_LEN, file) != NULL) {
    int len = strlen(dictionary[count].word);
    if (len > 0 && dictionary[count].word[len - 1] == '\n') {
      dictionary[count].word[len - 1] = '\0';
    }

    count++;

    if (count >= capacity) {
      capacity *= 2;
      dictionary = realloc(dictionary, capacity * sizeof(Words));
      if (dictionary == NULL) {
        printf("Reallocation memory error.\n");
        free(dictionary);
        fclose(file);
        exit(EXIT_FAILURE);
      }
    }
  }

  // printf("Parole lette dal file '%s':\n", filename);
  // for (size_t i = 0; i < count; i++) {
  //     printf("%s\n", dictionary[i].word);
  // }

  fclose(file);
  (*num_words_dictionary) = count;
  return dictionary;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Error, to start:\nmain_ex2.c (Path of the dictionary file) (Path of the file to correct)");
    exit(EXIT_FAILURE);
  }

  size_t* num_words_dictionary = 0;
    
  read_dictionary(argv[1], &num_words_dictionary);
  return 0;
}
