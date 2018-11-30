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
  FOR_NODE,
  RET_NODE,
  INSTR_LIST_NODE,
  INSTR_NODE,
  NOT_NODE,
  PRINT_NODE
} NodeType;

typedef struct Node
{
  NodeType type;
} Node;

typedef struct NodeList
{
  NodeType type;
  Node *node;
  struct nodeList *next;
} NodeList;

typedef struct StringNode
{
  NodeType type;
  char *str;
} StringNode;

typedef struct ConstNode
{
  NodeType type;
  char *cons;
} ConstNode;

typedef struct VarNode
{
  NodeType type;
  int defined;
  char *name;
  Node *stored;
  char *var;
} VarNode;

typedef struct OpNode
{
  NodeType type;
  Node *first;
  Node *sec;
  char *operator;
} OpNode;

typedef struct CondNode
{
  NodeType type;
  Node *first;
  Node *sec;
  Node *third;
} CondNode;

typedef struct IfNode
{
  NodeType type;
  Node *cond;
  Node *then;
  Node *ifnot;
} IfNode;

typedef struct WhileNode
{
  NodeType type;
  Node *cond;
  Node *block;
} WhileNode;

typedef struct ForNode
{
  NodeType type;
  char *var;
  int min;
  int max;
  Node *block;
} ForNode;

typedef struct RetNode
{
  NodeType type;
  Node *exp;
} RetNode;

typedef struct BlockNode
{
  NodeType type;
  NodeList *instr;
} BlockNode;

typedef struct InstrNode
{
  NodeType type;
  Node *instr;
} InstrNode;

typedef struct NotNode
{
  NodeType type;
  Node *exp;
} NotNode;

typedef struct PrintNode
{
  NodeType type;
  Node *exp;
} PrintNode;

#endif
