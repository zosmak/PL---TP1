#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// word def.
typedef struct _def {
    char *desc;
    struct _def *next;
} Def;

// word
typedef struct _word {
    char *name;
    struct _def *def;
    struct _word *next;
    struct _word *previous;
} Word;

// globally initialize our dictionary
struct Word *Dictionary;

void InsertOrderedWord(char* name, char* def){
 if(Dictionary == NULL){
     InsertWord(NULL, NULL, name, def);
    } else {
        Word *cell = GetTheAlphabethicalPosisiton(word, Dictionary);
        InsertWord(cell->next, cell->previous, name, def);
    }
}

// insert a word in our dictionary
void InsertWord(Word* nextWord, Word* lastWord, char* name, char* def) {
    Word *cell = (Word*) malloc(sizeof(Word));
    cell->name = strdup(name);
    cell->def = InsertDescription(def);
    cell->next = nextWord;
    cell->previous = lastWord;
    return cell;
}

// insert a word in our dictionary
Def* InsertDescription(Def* lastDef, char* desc) {
    Def *cell = (Def*) malloc(sizeof(Def));
    cell->desc = strdup(desc);
    cell->next = lastDef;
    return cell;
}

// get the alphabethical position to insert the new word
Word* GetTheAlphabethicalPosisiton(name, Word* dictionaryWord) {
    // validate the alphabethical 10 chars from 2 words
    if(strncmp(name, dictionaryWord->name, 10) < 0){
        // the word procceed the dictionary word
        return dictionaryWord;
    } else {
        return GetTheAlphabethicalPosisiton(name, dictionaryWord->next);
    }
}


void ListWordDefinition(Def* def) {
    if (def != NULL) {
        printf("%s; ", def->desc);
        ListWordDefinition(def->next);
    }
}

void ListDictionary(Word* word) {
    if (word != NULL) {
        printf("%s => Definições\n", word->name);
        ListWordDefinition(word->def);
        ListDictionary(word->next);
    }
}

int main() {
    InsertOrderedWord("batatas", "Batatinhas do LIDL");
    InsertOrderedWord("cenouras", "Cenourinhas do LIDL");
    InsertOrderedWord("abacate", "Abacatinho do LIDL");
    ListDictionary(Dictionary);

    return 0;
}