#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// word definition struct
typedef struct _def
{
	char *desc;
	struct _def *next;
} Def;

// word struct
typedef struct _word
{
	char *name;
	struct _def *def;
	struct _word *next;
	struct _word *previous;
} Word;

// usage struct
typedef struct _usage
{
	char *name;
	struct _word *word;
	struct _usage *next;
	struct _usage *previous;
} Usage;

// insert a word description in our dictionary
Def *InsertDescription(Def *lastDef, char *desc)
{
	Def *cell = (Def *)malloc(sizeof(Def));
	cell->desc = strdup(desc);
	if (lastDef != NULL)
	{
		cell->next = lastDef;
	}
	else
	{
		cell->next = NULL;
	}
	return cell;
}

// insert a word in our usage
Word *InsertWord(Word *previous, Word *next, char *name, char *def)
{
	Word *cell = (Word *)malloc(sizeof(Word));
	cell->name = strdup(name);
	cell->def = InsertDescription(NULL, def);
	cell->previous = previous;
	cell->next = next;

	return cell;
}


// sets the words at first position.
Word *GetAndSetWordFirstPosition(Word *words)
{
	if (words->previous != NULL)
	{
		return GetAndSetWordFirstPosition(words->previous);
	}
	else
	{
		return words;
	}
}


// get the alphabethical position to insert the new word
Word *GetAndSetWordAlphabethicalPosition(char *name, Word *words)
{
	char *newname = words->name;
	// validate the alphabethical 10 chars from the 2 words
	if (strncmp(name, words->name, 15) == 0)
	{
		//it's the same word
		return words;
	}

	if (strncmp(name, words->name, 15) < 0)
	{
		if (words->previous == NULL)
		{
			return NULL;
		}

		// has previous and the word is higher than the word that's in the words
		char *lastName = words->previous->name;
		return words->previous;
	}
	else
	{
		//it's the last word
		if (words->next == NULL)
		{
			return words;
		}
	}

	// repeat everything with the next word
	return GetAndSetWordAlphabethicalPosition(name, words->next);
}


Word *InsertOrderedWord(char *name, char *def, Word *words)
{
	if (words == NULL)
	{
		return InsertWord(NULL, NULL, name, def);
	}
	else
	{
		
		words = GetAndSetWordFirstPosition(words);
		Word *cell = GetAndSetWordAlphabethicalPosition(name, words);
		if (cell != NULL)
		{
			//if it's the same word
			if (strcmp(cell->name, name) == 0)
			{
				cell->def = InsertDescription(cell->def, def);
				return words;
			}
			
			Word *nextWord = NULL;
			if (cell->next != NULL)
			{
				nextWord = cell->next;
			}
			char *asd = cell->name;
			words = InsertWord(cell, nextWord, name, def);
			words->previous->next = words;
			if (nextWord != NULL)
			{
				words->next->previous = words;
			}
			return words;
		}
		else
		{
			// no previous cell, place it at first place
			words = InsertWord(NULL, words, name, def);
			words->next->previous = words;
			return words;
		}
	}
}

// insert a usage in our dictionary
Usage *InsertUsage(Usage *previous, Usage *next, char *name, char *wordName, char *wordDef)
{
	Usage *cell = (Usage *)malloc(sizeof(Usage));
	cell->name = strdup(name);
	cell->word = InsertOrderedWord(wordName, wordDef, NULL);
	cell->previous = previous;
	cell->next = next;

	return cell;
}


// sets the dictionary at the first word.
Usage *GetAndSetDictionaryFirstPosition(Usage *dictionary)
{
	if (dictionary->previous != NULL)
	{
		return GetAndSetDictionaryFirstPosition(dictionary->previous);
	}
	else
	{
		return dictionary;
	}
}


// get the alphabethical position to insert the new dictionary
Usage *GetAndSetDictionaryAlphabethicalPosition(char *name, Usage *dictionary)
{
	char *newname = dictionary->name;
	// validate the alphabethical 10 chars from the 2 dictionary
	if (strncmp(name, dictionary->name, 15) == 0)
	{
		//it's the same word
		return dictionary;
	}

	if (strncmp(name, dictionary->name, 15) < 0)
	{
		if (dictionary->previous == NULL)
		{
			return NULL;
		}

		// has previous and the word is higher than the word that's in the dictionary
		char *lastName = dictionary->previous->name;
		return dictionary->previous;
	}
	else
	{
		//it's the last word
		if (dictionary->next == NULL)
		{
			return dictionary;
		}
	}

	// repeat everything with the next word
	return GetAndSetDictionaryAlphabethicalPosition(name, dictionary->next);
}

// insert a word alphabetically
Usage *InsertOrderedUsage(char *name, char *wordName, char *defName, Usage *dictionary)
{
	// our dictionary is empty
	if (dictionary == NULL)
	{
		return InsertUsage(NULL, NULL, name, wordName, defName);
	}
	else
	{
		dictionary = GetAndSetDictionaryFirstPosition(dictionary);
		Usage *cell = GetAndSetDictionaryAlphabethicalPosition(name, dictionary);
		if (cell != NULL)
		{
			//if it's the same word
			if (strcmp(cell->name, name) == 0)
			{
				cell->word = InsertOrderedWord(wordName, defName, cell->word);
				return dictionary;
			}
			// 
			Usage *nextUsage = NULL;
			if (cell->next != NULL)
			{
				nextUsage = cell->next;
			}
			dictionary = InsertUsage(cell, nextUsage, name, wordName, defName);
			dictionary->previous->next = dictionary;
			if (nextUsage != NULL)
			{
				dictionary->next->previous = dictionary;
			}
			return dictionary;
		}
		else
		{
			// no previous cell, place it at first place
			dictionary = InsertUsage(NULL, dictionary, name, wordName, defName);
			dictionary->next->previous = dictionary;
			return dictionary;
		}
	}
}

// list the word definition
void ListWordDefinition(Def *def)
{
	if (def != NULL)
	{
		printf("%s, ", def->desc);
		if (def->next != NULL)
		{
			ListWordDefinition(def->next);
		}
		else
		{
			printf("\n");
		}
	}
}


// list all the dictionary words
void ListUsageWords(Word *word)
{
	Word *WordDictionary = GetAndSetWordFirstPosition(word);

	while (WordDictionary != NULL)
	{
		printf("- %s: ", WordDictionary->name);
		ListWordDefinition(WordDictionary->def);
		WordDictionary = WordDictionary->next;
	}
}

// list all the dictionary words
void ListDictionary(Usage *usage)
{
	Usage *Dictionary = GetAndSetDictionaryFirstPosition(usage);

	while (Dictionary != NULL)
	{
		printf("%s:\n", Dictionary->name);
		ListUsageWords(Dictionary->word);
		Dictionary = Dictionary->next;
	}
}

int main()
{
	// initialize our dictionary
	Usage *Dictionary = NULL;

	//Insert word, (usage, orth, definition, currentDictionary)
	Dictionary = InsertOrderedUsage("batatas", "batatas2", "Batatinhas do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("cenourasa", "batatas2", "Cenourinhas do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("gageasdsad", "batatas2", "gage do gage", Dictionary);
	Dictionary = InsertOrderedUsage("cenourasb", "batatas2", "Cenourinhas do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("abacate", "batatas2", "Abacatinho do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("cenourasc", "batatas2", "Cenourinhas do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("cenourasaaa", "batatas2", "Cenourinhas do LIDL", Dictionary);
	Dictionary = InsertOrderedUsage("cenourasaaa", "batatas3", "Cenourinhas do LIDL 2", Dictionary);

	// list all the dictionary words
	ListDictionary(Dictionary);

	getchar();
	return 0;
}
