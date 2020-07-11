#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>


class Block
{
	public:
		int start, end;
		std::vector<std::vector<std::string>> bContent;
		std::vector<std::string> parentBlock;
		void defineContent(std::vector<std::vector<std::string>> tempContent);
		
};

class Routine: public Block
{
	public:
		std::string name;
		std::vector<std::string> parameters;
};

class If: public Block
{
	public:
		std::vector<std::string> expression;
};



#endif
