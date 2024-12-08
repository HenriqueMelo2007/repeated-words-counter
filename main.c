#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1000

typedef struct WordNode
{
    char word[100];
    int counter;
    struct WordNode *nextWord;
} WordNode;

WordNode* hashTable[TABLE_SIZE];

void initializeHashPointers();
unsigned int hash(const char *word);
void insertWord(const char *word);
void displayWordsByQuantity();
void processText(char *text);

int main(void)
{
    initializeHashPointers();

    printf("TYPE YOUR TEXT: \n\n");
    char text[10000];
    fgets(text, sizeof(text), stdin);

    processText(text);

    printf("\nTOTAL NUMBER OF WORDS: ");
    int totalWords = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        WordNode *current = hashTable[i];
        while (current)
        {
            totalWords += current->counter;
            current = current->nextWord;
        }
    }
    printf("%d\n", totalWords);

    printf("\nTOTAL NUMBERS OF EACH WORD (sorted): \n");
    displayWordsByQuantity();

    return 0;
}

void initializeHashPointers()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }
}

unsigned int hash(const char *word)
{
    unsigned int hashValue = 0;
    while (*word)
    {
        hashValue = (hashValue << 5) + tolower(*word++);
    }
    return hashValue % TABLE_SIZE;
}

void insertWord(const char *word)
{
    unsigned int index = hash(word);
    WordNode *current = hashTable[index];
    while (current)
    {
        if (strcmp(current->word, word) == 0)
        {
            current->counter++;
            return;
        }
        current = current->nextWord;
    }

    WordNode *newNode = (WordNode *)malloc(sizeof(WordNode));
    strcpy(newNode->word, word);
    newNode->counter = 1;
    newNode->nextWord = hashTable[index];
    hashTable[index] = newNode;
}

void processText(char *text)
{
    char *token = strtok(text, " ,.!?\n");
    while (token)
    {
        insertWord(token);
        token = strtok(NULL, " ,.!?\n");
    }
}

void displayWordsByQuantity()
{
    WordNode* words[TABLE_SIZE];
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        WordNode* current = hashTable[i];
        while (current)
        {
            words[count++] = current;
            current = current->nextWord;
        }
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (words[i]->counter < words[j]->counter)
            {
                WordNode *temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        printf("%s: %d\n", words[i]->word, words[i]->counter);
    }
}