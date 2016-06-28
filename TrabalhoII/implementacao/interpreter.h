
#ifndef INTERPRETER_H
#define INTERPRETER_H
//Global Includes
#include <map>
//Local Includes
#include "data.h"
#include "itree.h"
#include "st.h"

class intepreter {

public:
	bool isDefined ( std::string id );
	ITNode::NodeType getType ( std::string id );
	Data processNode ( ITNode * node );
	ls
private:
	std::map<std::string, ITNode *> idTable;
	ST::SymbolTable * currentSyntab;

};

bool intepreter::isDefined ( std::string id ) {
	currentSyntab->checkId ( id );
}

#endif
