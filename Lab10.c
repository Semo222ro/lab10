#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
// Trie structure
struct Trie
{	
    int count;      
    struct Trie *character[ALPHABET_SIZE];

};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if (!current -> character[index]) 
        {
            current -> character[index] = (struct Trie *)malloc(sizeof(struct Trie));
            for (int j = 0; j < ALPHABET_SIZE; j++)
                current -> character[index] -> character[j] = NULL;
            current -> character[index] -> count = 0;
        }
        current = current -> character[index];
    }
    current -> count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if (!current -> character)
            return 0;
        current = current -> character[index];
    }
    return current -> count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL) 
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (pTrie -> character[i] != NULL)
            {
                deallocateTrie(pTrie -> character[i]);
            }
        }
            
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    for (int i = 0; i < ALPHABET_SIZE; i++)
        trie -> character[i] = NULL;
    trie -> count = 0;
    
    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **WordList)
{
    FILE *file = fopen(filename, "r");
    
    int count = 0;
    char word[256]; 

    while (fscanf(file, "%s", word) != EOF) 
    {
        WordList[count] = strdup(word); 
        count++;
    }

    fclose(file);
    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
