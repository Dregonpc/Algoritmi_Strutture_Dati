#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include "hash_table.h"

/**
 * @brief Read words with a minimun lenght from a file and insert them into a hash table with 
 * @param file_path path of the file to read\
 * @param min_length minimum length of the words to insert into the hash table
 * @param table hash table to insert the words into
 * @return void
*/
void read_words_from_file(const char* file_path, int min_length, HashTable* table);

/**
 * @brief Find the word with the maximum frequency in the hash table
 * @param table hash table to search the word in
 * @param min_length minimum length of the words to consider
 */
void find_max_frequency_word(HashTable* table, int min_length);

/**
 * @brief Free the memory of the hash table, including the keys and the values
 * @param table hash table to free
 */
void free_hash_table_with_values(HashTable* table);

/**
 * @brief Find the most frequent word in a file
 * @param file_path path of the file to read
 * @param min_length minimum length of the words to consider
 */
void find_most_frequent_word(const char* file_path, int min_length);

#endif // WORD_COUNT_H
