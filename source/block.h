#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

class Block
{
	public:
		int start, end, tableNumber;
		std::vector<std::vector<std::string>>* content;
		std::string parentBlock;
		
};

class Routine: public Block
{

};

class If: public Block
{

};
		

#endif
