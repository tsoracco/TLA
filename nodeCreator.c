#include <stdlib.h>
#include <string.h>
#include "nodeCreator.h"

StringNode *toString(const char *str)
{
  StringNode *node = malloc(sizeof(StringNode));
  node->type = STRING_NODE;
  node->str = calloc(strlen(str) + 1, sizeof(char));
  strcpy(node->str, str);
  return node;
}

ConstNode *valConstant(const char *cons)
{
  ConstNode *node = malloc(sizeof(ConstNode));
  node->type = CONST_NODE;
  node->cons = calloc(strlen(cons) + 1, sizeof(char));
  strcpy(node->cons, cons);
  return node;
}

VarNode *valVariable(const char *var)
{
  VarNode *node = malloc(sizeof(VarNode));
  node->type = VAR_NODE;
  node->stored = NULL;
  node->defined = FALSE;
  node->name = calloc(strlen(var) + 1, sizeof(char));
  strcpy(node->name, var);
  return node;
}

OpNode *valOp(const Node *first, const Node *sec, const char *op)
{
  OpNode *node = malloc(sizeof(OpNode));
  node->type = OP_NODE;
  node->first = (Node *)first;
  node->sec = (Node *)sec;
  node->operator = calloc(strlen(op) + 1, sizeof(char));
  strcpy(node->operator, op);
  return node;
}

CondNode *toCond(const Node *first, const Node *sec, const Node *third)
{
  CondNode *node = malloc(sizeof(CondNode));
  node->type = COND_NODE;
  node->first = (Node *)first;
  node->sec = (Node *)sec;
  node->third = (Node *)third;
  return node;
}

IfNode *toIf(const Node *cond, const Node *then, const Node *ifnot)
{
  IfNode *node = malloc(sizeof(IfNode));
  node->type = IF_NODE;
  node->cond = (Node *)cond;
  node->then = (Node *)then;
  node->ifnot = (Node *)ifnot;
  return node;
}

WhileNode *toWhile(const Node *cond, const Node *block)
{
  WhileNode *node = malloc(sizeof(WhileNode));
  node->type = WHILE_NODE;
  node->cond = (Node *)cond;
  node->block = (Node *)block;
  return node;
}

ForNode *toFor(const char *var, const int min, const int max, const Node *block)
{
  ForNode *node = malloc(sizeof(ForNode));
  node->type = FOR_NODE;
  node->var = var;
  node->min = min;
  node->max = max;
  node->block = (Node *)block;
  return node;
}

NodeList *instrList(const Node *node)
{
  NodeList *list = malloc(sizeof(NodeList));
  list->type = INSTR_LIST_NODE;
  list->node = (Node *)node;
  list->next = NULL;
  return list;
}

NodeList *addInstr(const NodeList *list, const Node *node)
{
  NodeList *actual = (NodeList *)list;
  while (actual->next != NULL)
    actual = actual->next;
  actual->next = listaInstrucciones(node);

  return (NodeList *)list;
}

RetNode *ret(const Node *exp)
{
  RetNode *node = malloc(sizeof(RetNode));
  node->type = RET_NODE;
  node->exp = (Node *)exp;
  return node;
}

BlockNode *block(const NodeList *instr)
{
  BlockNode *node = malloc(sizeof(BlockNode));
  node->type = BLOCK_NODE;
  node->instr = (NodeList *)instr;
  return node;
}

Node *empty()
{
  Node *node = malloc(sizeof(Node));
  node->type = EMPTY_NODE;
  return node;
}

InstrNode *instruccion(Node *instruccion)
{
  InstrNode *node = malloc(sizeof(InstrNode));
  node->type = INSTR_NODE;
  node->instr = instr;
  return node;
}

NotNode *toNot(Node *exp)
{
  NotNode *node = malloc(sizeof(NotNode));
  node->type = NOT_NODE;
  node->exp = exp;
  return node;
}

PrintNode *print(Node *exp)
{
  PrintNode *node = malloc(sizeof(PrintNode));
  node->type = PRINT_NODE;
  node->exp = exp;
  return node;
}
