#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

//#include "main.h"

using namespace std;

//extern vector<vector<string>> content;

class Block
{
	public:
		int start, end;
		vector<vector<string>> bContent;
		string parentBlock;

};

class Routine: public Block
{
	public:
		string name;
		vector<string> parameters;
		void defineContent(vector<vector<string>> tempContent);
};

class If: public Block
{
	public:
		vector<string>* expression;
		/*
		void defineContent(void)
		{
		
		};
		*/
};

void Routine::defineContent(vector<vector<string>> tempContent)
{
	for ( int i = start + 1; i < end; i++ )
	{
		bContent.push_back(tempContent[i]);
	}
};

