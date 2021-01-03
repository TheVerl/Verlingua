#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;


class Block
{
	public:
		int start, end, index;
		vector<vector<string>> bContent;
		vector<string> parentBlock;
		void defineContent(vector<vector<string>> tempContent);
};

class Routine: public Block
{
	public:
		string name;
		vector<string> parameters;
};

class If: public Block
{
	public:
		vector<string> expression;
};

void Block::defineContent(vector<vector<string>> tempContent)
{
	for ( int i = start + 1; i < end; i++ )
	{
		bContent.push_back(tempContent[i]);
	}
};
