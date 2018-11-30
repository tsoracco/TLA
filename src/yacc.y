%{
	#include "./nodeCreator.h"
	#include "./generateCode.h"
	#define NULL 0
	extern int yylineno;
	void yyerror(NodeList **, char *);
%}

%union {
 	int num;
 	char string[1000];
 	struct Node * node;
	struct NodeList * list;
}

%token VAR NUMBER STRING
%token NEWLINE
%token GEQ_OP LEQ_OP EQUAL_OP NOT_EQUAL_OP
%token AND_OP OR_OP MULT_ASSIGN DIV_ASSIGN SUM_ASSIGN SUB_ASSIGN
%token LESS GREATER OPEN_BRACE CLOSE_BRACE
%token PARENTH_OPEN PARENTH_CLOSE
%token COMMA COLON NOT SUB SUM DIV MULT MOD THEN
%token IF ELSE RETURN WHILE FOR IN DOT
%token PRINT ASSIGN DO END TWO_DOTS

%type <node> primary_exp r_exp mult_op
%type <node> sum_op rel_op eq_op
%type <node> and_op or_op cond_op
%type <node> assign_op exp block cond_block
%type <node> cycle_block ret_block print_block
%type <node> basic_exp const var_exp
%type <node> queue stack /*no se si es correcto este type*/

%type <string> assign_operator rel_operator ASSIGN MULT_ASSIGN DIV_ASSIGN SUM_ASSIGN SUB_ASSIGN
%type <string> VAR STRING NUMBER

%type <list> braces instructions

%parse-param {NodeList ** prog}

%start instructions

%%

primary_exp:
	  const { $$ = $1; }
	| STRING { $$ = toString($1); }
	| PARENTH_OPEN exp PARENTH_CLOSE { $$ = $2; }
	;

queue:
	LESS const GREATER { $$ = toQueue($2); }
	;

stack:
	OPEN_BRACE const CLOSE_BRACE { $$ = toStack($2); }
	;

const:
	NUMBER { $$ = valConstant($1); }
	;

var_exp:
	VAR { $$ = valVariable($1); }
	;

r_exp:
	  primary_exp { $$ = $1; }
	| var_exp { $$ = $1; }
	;

basic_exp:
	  r_exp { $$ = $1; }
	| NOT r_exp { $$ = toNot($2); }
	;

mult_op:
	  basic_exp { $$ = $1; }
	| mult_op MULT basic_exp { $$ = valOp($1, $3, "*"); }
	| mult_op DIV basic_exp { $$ = valOp($1, $3, "/"); }
	| mult_op MOD basic_exp { $$ = valOp($1, $3, "%"); }
	;

sum_op:
	  mult_op { $$ = $1; }
	| sum_op SUM mult_op { $$ = valOp($1, $3, "+"); }
	| sum_op SUB mult_op { $$ = valOp($1, $3, "-"); }
	;

rel_op:
	  sum_op { $$ = $1; }
	| rel_op rel_operator rel_op { $$ = valOp($1, $3, $2); }
	;

rel_operator:
	  LESS { strcpy($$, "<"); }
	| GREATER { strcpy($$, ">"); }
	| LEQ_OP { strcpy($$, "<="); }
	| GEQ_OP { strcpy($$, ">="); }
	;

eq_op:
	  rel_op { $$ = $1; }
	| eq_op EQUAL_OP rel_op { $$ = valOp($1, $3, "=="); }
	| eq_op NOT_EQUAL_OP rel_op { $$ = valOp($1, $3, "!="); }
	;

and_op:
	  eq_op { $$ = $1; }
	| and_op AND_OP eq_op { $$ = valOp($1, $3, "&&"); }
	;

or_op:
	  and_op { $$ = $1; }
	| or_op OR_OP and_op { $$ = valOp($1, $3, "||"); }
	;

cond_op:
	  or_op { $$ = $1; }
	| or_op THEN exp COLON cond_op { $$ = toCond($1, $3, $5); }
	;

assign_op:
	  cond_op { $$ = $1; }
	| var_exp assign_operator queue { $$ = valOp($1, $3, $2); }
	| var_exp assign_operator stack { $$ = valOp($1, $3, $2); }
	| var_exp assign_operator assign_op { $$ = valOp($1, $3, $2); }
	;

assign_operator:
	  ASSIGN { strcpy($$, "="); }
	| MULT_ASSIGN { strcpy($$, "*="); }
	| DIV_ASSIGN { strcpy($$, "/="); }
	| SUM_ASSIGN { strcpy($$, "+="); }
	| SUB_ASSIGN { strcpy($$, "-="); }
	;

exp:
	assign_op { $$ = $1; }
	;

block:
	  braces { $$ = block($1); }
	| cond_block { $$ = $1; }
	| cycle_block { $$ = $1; }
	| ret_block { $$ = $1; }
	| print_block { $$ = $1; }
	| exp  { $$ = toInstr($1); }
	| NEWLINE { $$ = empty(); }
	;

braces:
	 DO END { $$ = instrList(NULL); }
	| DO instructions END { $$ = $2; }
	;

instructions:
	  block { $$ = (*prog = instrList($1)); }
	| instructions block { $$ = (*prog = addInstr($1, $2)); }
	;

cond_block:
	  IF PARENTH_OPEN exp PARENTH_CLOSE braces { $$ = toIf($3, $5, NULL); }
	| IF PARENTH_OPEN exp PARENTH_CLOSE braces ELSE braces { $$ = toIf($3, $5, $7); }
	;

cycle_block:
	  WHILE PARENTH_OPEN exp PARENTH_CLOSE braces { $$ = toWhile($3, $5); }
	| FOR PARENTH_OPEN VAR IN NUMBER TWO_DOTS NUMBER PARENTH_CLOSE braces { $$ = toFor($3, $5, $8, $10); }
	;

ret_block:
	RETURN PARENTH_OPEN exp PARENTH_CLOSE { $$ = ret($3); }
	;

print_block:
	PRINT PARENTH_OPEN exp PARENTH_CLOSE { $$ = print($3); }
	;

%%
void yyerror(NodeList ** prog, char *msg) {
  printf("%s in line %d\n\n", msg, yylineno);
  exit(1);
}
int main() {

	NodeList * prog;
  int ret = yyparse(&prog);
	if (ret == 1) {
		printf("%s", "There was an error in parsing");
		return 1;
	} else if (ret == 2) {
		printf("%s", "Not enough memory available");
	}
	
	printf("#include <stdio.h>\n");
	printf("#include <stdlib.h>\n\n");
	printf("int main(int argc, char const *argv[])\n{\n");
	printf("%s\n", generateCode(prog));
	printf("\nreturn 0;\n}");
	return 0;
}