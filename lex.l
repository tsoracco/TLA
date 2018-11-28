%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%option noyywrap

digit       [0-9]
number      -?[0-9]+(\.[0-9]+)?
/*Esto significa que un string podria ser "asdasd' o 'asdas' o 'asdasd" o 'asdasd"*/
string			[\"'][^\"]*[\"']
/*Las variables pueden contener _ o - y cualquier caracter*/
var  [a-zA-Z_]+
newLine     \n
exit        ("exit")

%%
"yes"			{ return(YES); }
"else"			{ return(ELSE);	}
"return"		{ return(RETURN); }
"while"			{ return(WHILE); }
"print"			{ return(PRINT); }
"="				{ return(ASIGN); }
"+="			{ return(SUM_ASIGN); }
"-="			{ return(SUB_ASIGN); }
"*="			{ return(MULT_ASIGN); }
"/="			{ return(DIV_ASIGNACION); }
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
":"				{ return(DOUBLE_DOT); }
"!"				{ return(NOT); }
"-"				{ return(SUB); }
"+"				{ return(ADD); }
"/"				{ return(DIV); }
"*"				{ return(MULT); }
"%"				{ return(REMAINDER); }
"?"				{ return(THEN); }
{number}        { strcpy(yylval.cadena, yytext); return NUMBER; }	
{var}    		{ strcpy(yylval.cadena, yytext); return VAR; }		
{string}		{ strcpy(yylval.cadena, yytext); return STRING; }
{newLine}    	{ yylineno++; return NEWLINE; }
.				{ /* ignorar los demas caracteres */ }
%%

/*AGREGAR TOKENS PARA STACK, QUEUE, LINKEDLIST*/