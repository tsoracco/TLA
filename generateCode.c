#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "generateCode.h"

static definedVar vars[MAX_VARS];

typedef char *(*reductor)(Node *);

reductor reductors[] = {
    reduceStringNode,
    reduceConstNode,
    reduceVarNode,
    reduceOpNode,
    reduceCondNode,
    reduceBlockNode,
    reduceEmptyNode,
    reduceIfNode,
    reduceWhileNode,
    reduceForNode,
    reduceRetNode,
    reduceInstrListNode,
    reduceInstrNode,
    reduceNotNode,
    reducePrintNode};

char *reduceStringNode(Node *node)
{
  char *value = ((StringNode *)node)->str;

  const size_t bufferLen = strlen(value) + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "%s", value);

  return buffer;
}

char *reduceConstNode(Node *node)
{
  char *value = ((ConstNode *)node)->cons;
  return value;
}

char *reduceVarNode(Node *node)
{
  char *name = ((VarNode *)node)->name;
  char *prefix = "_";
  char *newVar = calloc(strlen(name) + strlen(prefix) + 1, sizeof(char));

  strcpy(newVar, name);
  strcat(newVar, "_");

  return newVar;
}

definedVar *varFind(char *varName)
{
  int i;
  int found;

  for (i = 0, found = 0; vars[i].name[0] != '0' && i < MAX_VARS && !found; i++)
  {
    if (strcmp(vars[i].name, varName) == 0)
    {
      found = 1;
      vars[i--].defined = 1;
    }
  }

  if (!found)
  {
    strcpy(vars[i].name, varName);
    vars[i].defined = 0;
  }

  return &vars[i];
}

char *reduceOpNode(Node *node)
{
  OpNode *nodeValue = (OpNode *)node;

  char *first = eval(nodeValue->first);
  char *sec = eval(nodeValue->sec);
  char *op = nodeValue->operator;
  char *buffer;

  if (nodeValue->first->type == VAR_NODE && strcmp(nodeValue->operator, "=") == 0
     || strcmp(nodeValue->operator, "+=") == 0 || strcmp(nodeValue->operator, "-=") == 0
     || strcmp(nodeValue->operator, "/=") == 0 || strcmp(nodeValue->operator, "*=") == 0)
  {
    definedVar *var = varFind(((VarNode *)nodeValue->first)->name);

    VarNode *firstNode = (VarNode *)nodeValue->first;
    VarNode *secNode = (VarNode *)nodeValue->sec;

    if ((nodeValue->sec->type == STRING_NODE || (nodeValue->sec->type == VAR_NODE && secNode->stored != NULL && secNode->stored->type == STRING_NODE)))
    {
      const size_t typeLen = strlen("char* ");
      const size_t bufferLen = strlen(first) + strlen(op) + strlen(sec) + typeLen + 4;
      buffer = malloc(bufferLen);
      if (var->defined == 0)
      {
        snprintf(buffer, bufferLen, "char* ");
      }
      var->type = STRING_NODE;
    }
    else
    {
      const size_t typeLen = strlen("int ");
      const size_t bufferLen = strlen(first) + strlen(op) + strlen(sec) + typeLen + 4; //el "_", " " y ";"
      buffer = malloc(bufferLen);
      if (var->defined == 0)
      {
        snprintf(buffer, bufferLen, "int ");
      }
      var->type = CONST_NODE;
    }

    strcat(buffer, first);
    strcat(buffer, " ");
    strcat(buffer, op);
    strcat(buffer, " ");
    strcat(buffer, sec);
    strcat(buffer, ";");

    return buffer;
  }
  else
  {
    const size_t tokenLen = strlen("()");
    const size_t bufferLen = strlen(first) + strlen(op) + strlen(sec) + tokenLen + 1;
    buffer = malloc(bufferLen);
    snprintf(buffer, bufferLen, "(%s%s%s)", first, op, sec);
    return buffer;
  }
}

char *reduceCondNode(Node *node)
{
  CondNode *nodeValue = (CondNode *)node;

  char *first = eval(nodeValue->first);
  char *sec = eval(nodeValue->sec);
  char *third = eval(nodeValue->third);

  const size_t tokenLen = 2 + 3 + 3; // "()", " ? ", " : "
  const size_t bufferLen = strlen(first) + strlen(sec) + strlen(third) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "(%s ? %s : %s)", first, sec, third);

  return buffer;
}

char *reduceBlockNode(Node *node)
{
  return eval(node);
}

char *reduceEmptyNode(Node *node)
{
  const char *delimiter = "\n";

  const size_t bufferLen = strlen(delimiter) + 1;
  char *buffer = malloc(bufferLen);
  strcpy(buffer, delimiter);

  return buffer;
}

char *reduceIfNode(Node *node)
{
  IfNode *nodeValue = (IfNode *)node;

  char *cond = eval(nodeValue->cond);
  char *then = eval(nodeValue->then);
  char *ifnot = eval(nodeValue->ifnot);

  const size_t tokenLen = strlen("if %s {%s} else {%s}");
  const size_t bufferLen = strlen(cond) + strlen(then) + strlen(ifnot) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "if %s {%s} else {%s}", cond, then, ifnot);

  return buffer;
}

char *reduceWhileNode(Node *node)
{
  WhileNode *nodeValue = (WhileNode *)node;

  char *cond = eval(nodeValue->cond);
  char *block = eval(nodeValue->block);

  const size_t tokenLen = strlen("while %s {%s}");
  const size_t bufferLen = strlen(cond) + strlen(block) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "while %s {%s}", cond, block);

  return buffer;
}

char *reduceForNode(Node *node)
{
  ForNode *nodeValue = (ForNode *)node;

  char *var = nodeValue->var;
  int min = nodeValue->min;
  int max=nodeValue->max;
  char *block = eval(nodeValue->block);

  const size_t tokenLen = strlen("for(int %s = %d; %s <= %d; %s++) {%s}");
  const size_t bufferLen = strlen(var) + countDigits(min) + countDigits(max) + strlen(block) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "for(int %s = %d; %s <= %d; %s++) {%s}", var, min, var, max, var, block);

  return buffer;
}

char *reduceRetNode(Node *node)
{
  RetNode *nodeValue = (RetNode *)node;

  char *exp = eval(nodeValue->exp);

  const size_t tokenLen = strlen("return ;");
  const size_t bufferLen = strlen(exp) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "return %s;\n", exp);

  return buffer;
}

char *reduceInstrListNode(Node *node)
{
  NodeList *list = (NodeList *)node;

  char *buffer = malloc(1);
  buffer[0] = '\0';
  size_t tokenLen = 0;

  if (list == NULL)
    return buffer;

  do
  {
    Node *actual = (Node *)list->node;
    if (actual == NULL)
      break;

    char *aux = eval(actual);
    buffer = realloc(buffer, strlen(aux) + strlen(buffer) + tokenLen + 1);
    strcat(buffer, aux);

  } while ((list = list->next) != NULL);

  return buffer;
}

char *reduceInstrNode(Node *node)
{
  InstrNode *nodeValue = (InstrNode *)node;

  char *instr = eval(nodeValue->instr);

  const size_t tokenLen = strlen(";");
  const size_t bufferLen = strlen(instr) + tokenLen + 1;
  char *buffer = malloc(bufferLen);
  snprintf(buffer, bufferLen, "%s\n", instr);

  return buffer;
}

char *reduceNotNode(Node *node)
{
  NotNode *nodeValue = (NotNode *)node;
  char *exp = eval(nodeValue->exp);

  const size_t tokenLen = strlen("(!)");
  const size_t bufferLen = strlen(exp) + tokenLen + 1;
  char *buffer = calloc(bufferLen, sizeof(char));
  snprintf(buffer, bufferLen, "(!%s)", exp);

  return buffer;
}
//chequear
char *reducePrintNode(Node *node)
{
  PrintNode *nodeValue = (PrintNode *)node;
  char *exp = eval(nodeValue->exp);
  char *param;

  char *p = malloc(strlen(exp) * sizeof(char));
  strcpy(p, exp);
  p[strlen(p) - 1] = 0;

  definedVar *var = varFind(p);

  if (var->type == STRING_NODE)
    param = "%s";
  else
    param = "%d";

  const size_t tokenLen = strlen("printf('', );\n") + 2; //2 de %s o %d
  const size_t bufferLen = strlen(exp) + tokenLen + 1;
  char *buffer = calloc(bufferLen, sizeof(char));
  snprintf(buffer, bufferLen, "printf(\"%s\", %s);\n", param, exp);

  return buffer;
}

//Toma el node y llama al reductor correspondiente al type

static char *eval(Node *node)
{
  if (node == NULL || reductors[node->type] == NULL)
  {
    char *nullString = "";
    return nullString;
  }

  return reductors[node->type](node);
}

int countDigits(int n) {
  int count = 0;

  while(n != 0)
  {
      n /= 10;
      ++count;
  }

  return count;
}

// Genera el code C

char *generateCode(Node *node)
{
  for (int i = 0; i < MAX_VARS; i++)
  {
    memset(vars[i].name, '0', MAX_VAR_LEN);
  }

  char *code = eval(node);

  return code;
}
