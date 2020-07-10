#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

//extern std::vector<std::vector<std::string>> content;

class Block
{
	public:
		int start, end;
		std::vector<std::vector<std::string>> bContent;
		std::string parentBlock;
		
};

class Routine: public Block
{
	public:
		std::string name;
		std::vector<std::string> parameters;
		void defineContent(std::vector<std::vector<std::string>> tempContent);
};

class If: public Block
{
	public:
		std::vector<std::string>* expression;
};



#endif
