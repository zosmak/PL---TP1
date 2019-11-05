  #include <stdio.h>
  #include "dicAberto.c"

  FILE *yyin;
  Usage *Dictionary = NULL;
  char* etiqueta;
  char* tipo;
  char* definicao;


%x ORTH USG DEF
%%

\<orth> { BEGIN(ORTH); }

<ORTH>[A-Z][a-z]+.[a-z]+  {	etiqueta = strdup(yytext); printf("\nEtiqueta: %s", etiqueta); }

<ORTH>\<\/orth> { BEGIN(INITIAL); }

\<usg\ type=\"style\">|dom\">|geo\"> { BEGIN(USG); }

<USG>[A-Z]?[a-z]+\.? { tipo = strdup(yytext); printf("\nUsage: %s", tipo);	}

<USG>\<\/usg> { BEGIN(INITIAL); }

\<def>\n { BEGIN(DEF); }

<DEF>[^\<]+ { definicao =strdup(yytext); printf("\nDef: %s", definicao); Dictionary = InsertInDictionary(tipo, etiqueta, definicao, Dictionary); }
											
<DEF>\<\/def> { BEGIN(INITIAL); }

	
%%

int main() {
            yyin = fopen("dicAberto.xml","r");
            yyparse();
            ListDictionary(Dictionary);
            fclose(yyin);
            return 0;
}
