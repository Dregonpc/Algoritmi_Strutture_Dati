#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/distance.h"

#define MAX_LEN 50

typedef struct{
  char word[MAX_LEN];
} Words;

void trim(char *str) {
  char *start = str;

  while (*start && isspace((unsigned char)*start)) 
    start++;

  char *end = start + strlen(start) - 1;

  while (end > start && isspace((unsigned char)*end)) 
    end--;

  *(end + 1) = '\0';

  memmove(str, start, end - start + 2);
}

void remove_punctuation(char *str) {
  char *src = str;
  char *dest = str;

  while (*src) {
    if (isalnum((unsigned char)*src)) {
      *dest = *src;
      dest++;
    }
    src++;
  }

  *dest = '\0';
}

Words* read_dictionary(const char *filename, size_t* num_words_dictionary) {
  FILE *file;
  size_t capacity = 1;
  size_t count = 0;

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file (Dictionary file).\n");
    exit(EXIT_FAILURE);
  }
  
  Words* dictionary = malloc(capacity * sizeof(Words));
  if (dictionary == NULL) {
    printf("Allocation memory error.\n");
    return NULL;
  }

  while (fgets(dictionary[count].word, MAX_LEN, file) != NULL) {
    int len = strlen(dictionary[count].word);
    if (len > 0 && dictionary[count].word[len - 1] == '\n') {
      dictionary[count].word[len - 1] = '\0';
    }

    for (size_t i = 0; dictionary[count].word[i] != '\0'; i++) {
      dictionary[count].word[i] = tolower((unsigned char)dictionary[count].word[i]);
    }

    count++;

    if (count >= capacity) {
      capacity *= 1.5;
      dictionary = realloc(dictionary, capacity * sizeof(Words));
      if (dictionary == NULL) {
        printf("Reallocation memory error.\n");
        free(dictionary);
        fclose(file);
        exit(EXIT_FAILURE);
      }
    }
  }
  
  fclose(file);
  (*num_words_dictionary) = count;
  return dictionary;
}

Words* read_text(const char *filename, size_t* num_words_text) {
  FILE *file;
  size_t capacity = 1;
  size_t count = 0;

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file (Text file to correct).\n");
    exit(EXIT_FAILURE);
  }

  char line[1024];
  if (!fgets(line, sizeof(line), file)) {
    printf("Error reading file (Text file to correct).\n");
    fclose(file);
    return NULL;
  }
  
  Words* text = malloc(capacity * sizeof(Words));
  if (text == NULL) {
    printf("Allocation memory error.\n");
    return NULL;
  }

  char *token = strtok(line, " ");
  while (token != NULL) {
    trim(token);
    remove_punctuation(token);

    for (size_t i = 0; token[i] != '\0'; i++) {
      token[i] = tolower((unsigned char)token[i]);
    }

    if (count >= capacity) {
      capacity *= 1.5;
      text = realloc(text, capacity * sizeof(Words));
      if (text == NULL) {
        printf("Reallocation memory error.\n");
        free(text);
        fclose(file);
        exit(EXIT_FAILURE);
      }
    }

    strncpy(text[count].word, token, MAX_LEN - 1);
    text[count].word[MAX_LEN - 1] = '\0';
    count++;
    token = strtok(NULL, " ");
  }
  
  fclose(file);
  (*num_words_text) = count;
  return text;
}

void find_min_edit_distance(Words *dictionary, Words *text, size_t num_words_dictionary, size_t num_words_text) {
  for (size_t i = 0; i < num_words_text; i++) {
    int min_distances[5];
    Words closest_words[5];

    for (size_t k = 0; k < 5; k++) {
      min_distances[k] = __INT_MAX__;
      strcpy(closest_words[k].word, "");
    }

    for (size_t j = 0; j < num_words_dictionary; j++) {
      int distance = edit_distance_dyn(text[i].word, dictionary[j].word);

      for (size_t k = 0; k < 5; k++) {
        if (distance < min_distances[k]) {
          for (size_t l = 4; l > k; l--) {
            min_distances[l] = min_distances[l - 1];
            strcpy(closest_words[l].word, closest_words[l - 1].word);
          }
          
          min_distances[k] = distance;
          strcpy(closest_words[k].word, dictionary[j].word);
          break;
        }
      }
    }

    printf("Word: %s\n", text[i].word);
    printf("Closest words:\n");
    for (size_t k = 0; k < 5 && min_distances[k] < __INT_MAX__; k++) {
      printf("  %s (Distance: %d)\n", closest_words[k].word, min_distances[k]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Error, to start:\nmain_ex2.c (Path of the dictionary file) (Path of the file to correct)");
    exit(EXIT_FAILURE);
  }

  size_t num_words_dictionary = 0;
  Words *dictionary = read_dictionary(argv[1], &num_words_dictionary);

  size_t num_words_text = 0;
  Words *text = read_text(argv[2], &num_words_text);

  find_min_edit_distance(dictionary, text, num_words_dictionary, num_words_text);

  free(dictionary);
  free(text);

  return (EXIT_SUCCESS);
}