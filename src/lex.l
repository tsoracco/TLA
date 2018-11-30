%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "nodeCreator.h"
	#include "y.tab.h" 
%}

%option noyywrap

digit       [0-9]
number      -?[0-9]+(\.[0-9]+)?
/*Esto significa que un string podria ser "asdasd' o 'asdas' o 'asdasd" o 'asdasd"*/
string			[\"'][^\"]*[\"']
/*Las variables pueden contener _ y cualquier caracter*/
var  [a-zA-Z_]+
newLine     \n
exit        ("exit")

%%
"if"			{ return(IF); }
"else"			{ return(ELSE);	}
"return"		{ return(RETURN); }
"while"			{ return(WHILE); }
"for"			{ return(FOR); }
"in"			{ return(IN); }
"."				{ return(DOT); }
"print"			{ return(PRINT); }
"="				{ return(ASSIGN); }
"+="			{ return(SUM_ASSIGN); }
"-="			{ return(SUB_ASSIGN); }
"*="			{ return(MULT_ASSIGN); }
"/="			{ return(DIV_ASSIGN); }
"<="			{ return(LEQ_OP); }
">="			{ return(GEQ_OP); }
"=="			{ return(EQUAL_OP); }
"!="			{ return(NOT_EQUAL_OP); }
"<"				{ return(LESS); }
">"				{ return(GREATER); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
("{")			{ return(OPEN_BRACE); }
("}")			{ return(CLOSE_BRACE); }
"("				{ return(PARENTH_OPEN); }
")"				{ return(PARENTH_CLOSE); }
","				{ return(COMMA); }
":"				{ return(COLON); }
"!"				{ return(NOT); }
"-"				{ return(SUB); }
"+"				{ return(SUM); }
"/"				{ return(DIV); }
"*"				{ return(MULT); }
"%"				{ return(MOD); }
"?"				{ return(THEN); }
{number}        { strcpy(yylval.string, yytext); return NUMBER; }	
{var}    		{ strcpy(yylval.string, yytext); return VAR; }		
{string}		{ strcpy(yylval.string, yytext); return STRING; }
{newLine}    	{ yylineno++; return NEWLINE; }

\/\*[^\*\/]*\*\/    ; /* comentarios */
\/\/[^\n]*  ; /* whitespaces */
[ \t]  ;


.				{ /* ignorar los demas caracteres */ }
%%
