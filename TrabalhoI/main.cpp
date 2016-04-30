#include <iostream>
#include "ast.h"

extern AST::Block* programRoot; //set on Bison file
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();                  //parses whole data
    programRoot->printTree();   //prints the ASTs
    return 0;
}
