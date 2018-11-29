#ifndef _NODE_CREATOR_H
#define _NODE_CREATOR_H

#include "nodes.h"

#define TRUE 1
#define FALSE 0

StringNode *toString(const char *str);
ConstNode *valConstant(const char *cons);
VarNode *valVariable(const char *var);
OpNode *valOp(const Node *first, const Node *sec, const char *op);
CondNode *toCond(const Node *first, const Node *sec, const Node *third);
IfNode *toIf(const Node *cond, const Node *then, const Node *ifnot);
WhileNode *toWhile(const Node *cond, const Node *block);
NodeList *instrList(const Node *node);
NodeList *addInstr(const NodeList *lista, const Node *node);
RetNode *ret(const Node *exp);
BlockNode *block(const NodeList *ins);
Node *empty();
InstrNode *instr(Node *ins);
NotNode *toNot(Node *exp);
PrintNode *print(Node *exp);

#endif
