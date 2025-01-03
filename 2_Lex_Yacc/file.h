
#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "file.tab.h"

extern YYSTYPE yylval;  


void yyerror(const char* s);

#endif 
