#include <iostream>
#include "ast.h"
#include "st.h"
#include "data.h"
#include "interpreter.h"
#include "itree.h"


extern AST::Block* programRoot; //set on Bison file
extern int yyparse();
extern int yydebug;

int main( int argc, char **argv ) {
	//yydebug = 1;              //remove comment to have verbose debug messages
	// yyparse();                  //parses whole data
	// programRoot->printTree();   //prints the ASTs
	std::string a = "teste";
	Data* dt = new Data(a);
	// std::cout<<"Substring:"<<std::endl;
	// dt->subString(1,2);
	// dt->tamanho();
	std::cout<<"ITNode:"<<std::endl;
	ITNode* tr = new ITNode();
	tr = tr->createVar(a);
	tr->updateData(dt);
	std::cout<<tr->getId()<<" :: "<<tr->getData().toString()<<std::endl;
	std::cout<<"Interpreter:"<<std::endl;
	Interpreter * it =  new Interpreter();
	it->addId(a,tr);
	std::cout<<it->processNode(tr)<<std::endl;
	return 0;
}
