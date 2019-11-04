#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// word definition struct
typedef struct _def {
    char *desc;
    struct _def *next;
} Def;

// word struct
typedef struct _word {
    char *name;
    struct _def *def;
    struct _word *next;
    struct _word *previous;
} Word;


// insert a word description in our dictionary
Def* InsertDescription(Def* lastDef, char* desc) {
    Def *cell = (Def*) malloc(sizeof(Def));
    cell->desc = strdup(desc);
    if(lastDef != NULL){
		cell->next = lastDef;
	} else {
		cell->next = NULL;
	}
    return cell;
}

// insert a word in our dictionary
Word* InsertWord(Word* previous, Word* next, char* name, char* def) {
    Word *cell = (Word*) malloc(sizeof(Word));
    cell->name = strdup(name);
    cell->def = InsertDescription(NULL, def);
    cell->previous = previous;
    cell->next = next;

    return cell;
}

// get the alphabethical position to insert the new word
Word* GetTheAlphabethicalPosition(char* name, Word* dictionary) {
	char *newname = dictionary->name;
    // validate the alphabethical 10 chars from the 2 words
	if(strncmp(name, dictionary->name, 15) < 0){
        if(dictionary->previous == NULL){
        	return NULL;	
		} 
		
		// has previous and the word is higher than the word that's in the dictionary
		char *lastName = dictionary->previous->name;
        return dictionary->previous;
	} else {
		//it's the last word
		if(dictionary->next == NULL){
    		return dictionary;
		}
	}
 
 	// repeat everything with the next word
	return GetTheAlphabethicalPosition(name, dictionary->next);
}

// sets the dictionary at the first word.
Word* GetDictionaryFirstPosition(Word* dictionary){
	if (dictionary->previous != NULL) {
		return GetDictionaryFirstPosition(dictionary->previous);
 	} else {
 		return dictionary;
	}
 
}

// insert a word alphabetically
Word* InsertOrderedWord(char* name, char* def, Word* dictionary){
 if(dictionary == NULL){
     return InsertWord(NULL, NULL, name, def);
    } else {
    	dictionary = GetDictionaryFirstPosition(dictionary);
        Word *cell = GetTheAlphabethicalPosition(name, dictionary);
        if(cell != NULL){
        	Word *nextWord = NULL;
        	if(cell->next != NULL){
        		nextWord = cell->next;
			}
        	char *asd = cell->name;
        	dictionary = InsertWord(cell, nextWord, name, def);
        	dictionary->previous->next = dictionary;
        	if(nextWord != NULL){
        		dictionary->next->previous = dictionary;
			}
			return dictionary;
		} else {
			// no previous cell, place it at first place
			dictionary = InsertWord(NULL, dictionary, name, def);
			dictionary->next->previous = dictionary;
			return dictionary;

		}
    }
}

// list the word definition
void ListWordDefinition(Def* def) {
    if (def != NULL) {
        printf("%s; ", def->desc);
        if (def->next != NULL) {
        ListWordDefinition(def->next);
	    } else {
	    	printf("\n");
		}
	}
}

// list all the dictionary words
void ListDictionary(Word* word) {
	Word *Dictionary = GetDictionaryFirstPosition(Dictionary);
	
    while(Dictionary != NULL) {
        printf("Definicoes de %s:\n", Dictionary->name);
        ListWordDefinition(Dictionary->def);
        Dictionary = Dictionary->next;
    }
}

int main() {
	
	// initialize our dictionary
    Word *Dictionary = NULL;
    Dictionary = InsertOrderedWord("batatas", "Batatinhas do LIDL", Dictionary);
    Dictionary = InsertOrderedWord("cenourasa", "Cenourinhas do LIDL", Dictionary);
    Dictionary = InsertOrderedWord("gageasdsad", "gage do gage", Dictionary);
    Dictionary = InsertOrderedWord("cenourasb", "Cenourinhas do LIDL", Dictionary);
    Dictionary = InsertOrderedWord("abacate", "Abacatinho do LIDL", Dictionary);
	Dictionary = InsertOrderedWord("cenourasc", "Cenourinhas do LIDL", Dictionary);
    Dictionary = InsertOrderedWord("cenourasaaa", "Cenourinhas do LIDL", Dictionary);
    
    /*s
	EM FALTA:
	- SE A PALAVRA EXISTE, ADICIONADA ÀS DEFINIÇÔES.
	- ADICIONAR AS USABILIDADES TAMBÉM
	*/

	
	// list all the dictionary words
    ListDictionary(Dictionary);
    
	getchar();
    return 0;
}
