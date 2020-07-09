#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class Block
{
	public:
		int start, end, tableNumber;
		vector<vector<string>>* content;
		string parentBlock;
};

class Routine: public Block
{

};

class If: public Block
{

};

