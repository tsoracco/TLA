#!/bin/bash

# access src folder
cd src

# create yacc and lex files
yacc yacc.y -d
lex lex.l

# make the binary
make all

# remove unused files
rm *.o *.yy.c *.tab.c *.tab.h

#return to root folder
cd ../..