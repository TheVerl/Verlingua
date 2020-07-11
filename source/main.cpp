// Include global libraries.
#include <iostream> 
#include <string>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
#include <array>
#include <iterator>

// Include local libraries.
#include "lib.h"
#include "block.h"

using namespace std;

// Define global variables.
const std::string suffix = ".verl";
vector<vector<string>> content;
bool debug = false;
int tempStart = 0;
int lineNumber = 0;
vector<If> ifIndex;
vector<Routine> routineIndex;
bool readingRoutine = false;
bool readingIf = false;

// Error handling.
int error ( int code, char* x[] )
{
	switch ( code )
	{
		case ( 1 ):
			cout << "ERROR! Inadequate ammount of arguments!\nUsage: " << x[0] << " FILE\nError Code 1\r";
			return 1;
			break;
		case ( 2 ):
			cout << "ERROR! Not enough memory!\nError Code 2\r";
			return 1;
			break;
		case ( 3 ):
			cout << "ERROR! No expression for if block at subvector " << tempStart << "!\nError Code 3\r";
			return 1;
			break;
		case ( 4 ):
			cout << "ERROR! Unsupported block type for parentBlock of block!\nErro Code 4\r";
			return 1;
			break;
	};
	return 1;
};

/*
 * FILE
 * STUFF
 */

// Chops up the line string into a vector and returns said vector.
vector<string> chopUpLine ( string line )
{
	stringstream ss( line );
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vstrings(begin, end);
	return vstrings;
}


// Reads the file into the file vector.
void readFileIntoFileVector ( string filename )
{

	// Initialise our variables.
	string line;
	ifstream file(filename);
	int numberOfLines = 0;
	vector<string> vec;

	// First it counts the number of lines in the file.
	while ( getline( file, line ) )
	{
		numberOfLines++;
	}
	
	// If we are in debug mode, tell the user how many lines there are in the file.
	if ( debug )
	{
		cout << "The number of lines in this file is: " << numberOfLines << endl;
	}
	string lineB;
	ifstream fileB(filename);
	
	// Going through each line, we chop the line up by each space and then put that into the new subvector of the file vector. If the line is just whitespace, then we don't put it into the file
	// vector. For some reason it gives -19 instead of 0 if we're correct with the comparison.
	while ( numberOfLines-- )
	{
		getline( fileB, lineB );
		if ( debug )
		{
			cout << "lineB.compare(" ")" << lineB.compare(" ") << endl;
		};
		if ( lineB.compare(" ") == -19 )
		{
			numberOfLines--;
			continue;
		}
		else
		{
		content.push_back(chopUpLine(lineB));
		}
	}

}


// Prints out the file vector along with information about the subvector and element being read. Only works in debug mode.
void printFileVector ()
{
	for ( int i = 0; i < content.size(); i++ )
	{	
		for ( int j = 0; j < content[i].size(); j++ )
		{
			cout << "Printing element " << j << " of vector " << i << " of supervector content." << endl;
			cout << content[i][j] <<  " ::: ";
		}
	}

	cout << endl;
}

// Declare functions below main.
void initBlocks ( int subvec, bool debug );

// Main function.
int main ( int argc, char* argv[])
{
	// Checks if the user passed a filename, creates an error if he did not.
	if ( argc < 2 )
	{
		error( 1, argv );
	}
	else
	{
		// Checks if we are assigned to debug mode.
		if ( argc >= 3 )
		{	
			if ( strcmp( argv[2], "-debug" ) == 0 )
			{
				debug = true;
			}
		}
		// Checks if the file is compatible by checking it's extension.
		bool checkCorrectExtension = hasSuffix( argv[1], suffix );
		switch ( checkCorrectExtension )
		{
			case true:
				// Tells the user that the file is compatible, reads the file into the file vector and if the programme is in debug mode, prints it out along with some other info. If not,
				// then we just move along.
				printf("This file is compatible.\n");
				readFileIntoFileVector(argv[1]);
				if ( debug )
				{	
					printFileVector();
				}
				break;
			case false:
				// Tells the user that the file is not compatible and closes the programme.
				printf("This file is not compatible.\n");
				break;
			default:
				printf("Uhhh... How is your file neither compatible nor not compatible?\n");
		};
		// Now we read through the file vector and assign the blocks.
		for ( int i = 0; i < content.size(); i++ )
		{
			initBlocks( i, debug );
			//lineNumber++; 
		};
		cout << "--------PRINTING WHOLE FILE VECTOR--------" << endl;
		//cout << 0 << " ::: ";
		for ( int i = 0; i < content.size(); i++)
		{
			cout << endl;
			cout << i << " ::: ";
			for ( int j = 0; j < content[i].size(); j++ )
			{
				cout << content[i][j] << " ";
			}
		}
		
		return 0;
	};
}; 

/*
 * PARSING
 * STUFF
 */

void parseIf ( int start, int end, string parentBlockID[2] )
{
	// Define members of the if block object.
	ifIndex.push_back(If());
	ifIndex.back().start = start;
	ifIndex.back().end = end;
	ifIndex.back().parentBlock.push_back(parentBlockID[0]);
	ifIndex.back().parentBlock.push_back(parentBlockID[1]);
	if ( parentBlockID[0].compare("ROUTINE") == 0)
	{
		string parentBlockType = "routine";
		int parentBlockProperID = stoi(parentBlockID[1]);
		string parentBlockName = routineIndex[parentBlockProperID].name;
		cout << "Found new block of if from subvector " << start << " to " << end << " and is a subblock of block type " << parentBlockType << " with the name of " << parentBlockName << "." << endl;

	}
	
	else if ( parentBlockID[0].compare("IF") == 0)
	{
		string parentBlockType = "if statement";
		int parentBlockProperID = stoi(parentBlockID[1]);
		cout << "Found new block of if from subvector " << start << " to " << end << " and is a subblock of block type " << parentBlockType << " with the expression of" << endl;
		for ( int i = 0; i < ifIndex[parentBlockProperID].expression.size(); i++ )
		{
			cout << ifIndex[parentBlockProperID].expression[i] << " ";
		}
		cout << endl;
			
	}
	else
	{
		error(4, NULL);
	};
	

	// Define the expression.
	if ( content[start].size() >= 1)
	{
		for ( int i = 0; i < content[start].size(); i++ )
		{
			string line = content[start][i];
			ifIndex.back().expression.push_back(line);	
		};
	}
	else
	{
		error( 3, NULL );
	};
	tempStart = 0;

	// Read through the ifBlock to find any subblocks.
	for ( int i = start+1; i <= end; i++ )
	{
		string word = content[i][0];

		if ( word.compare("if") == 0)
		{
			tempStart = i;
		};

		if ( word.compare("endi") == 0)
		{
			int index = ifIndex.begin() - ifIndex.begin();
			string id[2] = {"IF", to_string(index)};
			parseIf( tempStart, i, id );	
		};
	}
}


void parseRoutine ( int start, int end )
{
	bool done = false;
	// Define members of the routine block object.
	routineIndex.push_back(Routine());
	routineIndex.back().name = content[start][1];
	routineIndex.back().start = start;
	routineIndex.back().end = end;
	routineIndex.back().defineContent(content);

	// Define the parameters, if there are any.
	bool areThereParameters = false;
	if ( content [tempStart].size() >= 2)
	{
		areThereParameters = true;
		for ( int i = 2; i < content[tempStart].size(); i++ )
		{
			string line = content[tempStart][i];
			routineIndex.back().parameters.push_back(line);
		};
	};
	tempStart = 0;

	// Read through the routineBlock to find any subblocks.
	for ( int i = start; i <= end; i++ )
	{
		string line = content[i][0];
		
		if ( done == true )
		{
			break;
		}
		else if ( line.compare("if") == 0)
		{
			tempStart = i;
		}
		else if ( line.compare("endi") == 0)
		{
			int index = routineIndex.begin() - routineIndex.begin();
			string id[2] = {"ROUTINE", to_string(index)};
			parseIf( tempStart, i, id);
		};
	};
}

// Parses through the file vector to find blocks and define them.
void initBlocks ( int subvec, bool debug )
{
	string element = content[subvec][0];
	
	// Debugging.
	if ( debug )
	{
		cout << "Accesing first element of subvector " << subvec << " of file vector.\n" << "the element is " << element << "." << endl;
	};

	// Start tags.
	if ( element.compare("#") == 0)
	{
		content.erase(content.begin()+(subvec));
	}

	else if ( element.compare("routine") == 0 ) 
	{
		if ( debug )
		{
			cout << "Found routine decleration at subvector " << subvec << "." << endl;
		};
		// Sets the tempStart variable to the current subvector. tempStart will be used to define the start member of the block object.
		tempStart = subvec;
		readingRoutine = true;		
	};

	// End tags.
	if ( element.compare("endr") == 0 )
	{
		if ( debug )
		{
			cout << "Found new block of routine from subvector " << tempStart << " to " << subvec << "." << endl;
		};
		parseRoutine( tempStart, subvec );	
	}
};

