#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE

typedef struct WordNode {
  char word[100];
  int counter;
  struct WordNode* nextWord;
} WordNode;

WordNode* hashTable[TABLE_SIZE];

unsigned int hash(const char *word);

int main(int argc, char const *argv[])
{
  printf("TYPE YOUR TEXT: \n\n");
  printf("RESULTS: \n");
  printf("TOTAL NUMBER OF WORDS: ");

  return 0;
}

unsigned int hash(const char *word) {
    unsigned int hashValue = 0;
    while (*word) {
        hashValue = (hashValue << 5) + *word++;
    }
    return hashValue % TABLE_SIZE;
}