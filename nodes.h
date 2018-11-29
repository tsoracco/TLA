#ifndef _NODES_H
#define _NODES_H

typedef enum
{
  STRING_NODE = 0,
  CONST_NODE,
  VAR_NODE,
  OP_NODE,
  COND_NODE,
  BLOCK_NODE,
  EMPTY_NODE,
  IF_NODE,
  WHILE_NODE,
  RET_NODE,
  INSTR_LIST_NODE,
  INSTR_NODE,
  NOT_NODE,
  PRINT_NODE
} nodeType;

typedef struct Node
{
  nodeType type;
} Node;

typedef struct nodeList
{
  nodeType type;
  Node *node;
  struct nodeList *next;
} nodeList;

typedef struct StringNode
{
  nodeType type;
  char *str;
} StringNode;

typedef struct ConstNode
{
  nodeType type;
  char *cons;
} ConstNode;

typedef struct VarNode
{
  nodeType type;
  int defined;
  char *name;
  Node *stored;
  char *var;
} VarNode;

typedef struct OpNode
{
  nodeType type;
  Node *first;
  Node *sec;
  char *operador;
} OpNode;

typedef struct CondNode
{
  nodeType type;
  Node *first;
  Node *sec;
  Node *third;
} CondNode;

typedef struct IfNode
{
  nodeType type;
  Node *cond;
  Node *then;
  Node *ifnot;
} IfNode;

typedef struct WhileNode
{
  nodeType type;
  Node *cond;
  Node *block;
} WhileNode;

typedef struct RetNode
{
  nodeType type;
  Node *exp;
} RetNode;

typedef struct BlockNode
{
  nodeType type;
  nodeList *instr;
} BlockNode;

typedef struct InstrNode
{
  nodeType type;
  Node *instr;
} InstrNode;

typedef struct NotNode
{
  nodeType type;
  Node *exp;
} NotNode;

typedef struct PrintNode
{
  nodeType type;
  Node *exp;
} PrintNode;

#endif
