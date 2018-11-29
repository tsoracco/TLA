#ifndef _GENERATE_CODE_H
#define _GENERATE_CODE_H

#include "nodeCreator.h"

#define MAX_VARS 20
#define MAX_VAR_LEN 20

typedef struct definedVar
{
  NodeType type;
  char name[MAX_VAR_LEN];
  int defined;
} definedVar;

definedVar *varFind(char *name);
char *reduceStringNode(Node *node);
char *reduceConstNode(Node *node);
char *reduceVarNode(Node *node);
char *reduceOpNode(Node *node);
char *reduceCondNode(Node *node);
char *reduceBlockNode(Node *node);
char *reduceEmptyNode(Node *node);
char *reduceIfNode(Node *node);
char *reduceWhileNode(Node *node);
char *reduceRetNode(Node *node);
char *reduceInstrListNode(Node *node);
char *reduceInstNode(Node *node);
char *reduceNotNode(Node *node);
char *reducePrintNode(Node *node);

static char *eval(Node *node);
char *generateCode(Node *node);

#endif
