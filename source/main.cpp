// Include global libraries.
#include <iostream> 
#include <string>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
#include <array>

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
		
		return 0;
	};
}; 

/*
 * PARSING
 * STUFF
 */
// Parses through the file vector to find blocks and define them.
void initBlocks ( int subvec, bool debug )
{
	string element = content[subvec][0];
	//cout << element << endl;
	
	// Debugging.
	if ( debug )
	{
		cout << "Accesing first element of subvector " << subvec << " of file vector.\n" << "the element is " << element << "." << endl;
	};

	// Start tags.
	if ( element.compare("routine") == 0 ) 
	{
		if ( debug )
		{
			cout << "Found routine decleration at (ignoring newlines) line " << subvec+1 << "." << endl;
		};
		// Sets the tempStart variable to the current subvector. tempStart will be used to define the start member of the block object.
		tempStart = subvec;
		
	}
	else if ( element.compare("if") == 0 )
	{
		if ( debug )
		{
			cout << "Found if decleration at (ignoring new lines) line " << subvec+1 << "." << endl;
		};
		tempStart = subvec;	
	};

	// End tags.
	if ( element.compare("endr") == 0 )
	{
		if ( debug )
		{
			cout << "Found new block of routine from (ignoring newlines) line " << tempStart+1 << " to " << subvec+1 << "." << endl;
		};
		// Defines the members of the routine block object.
		routineIndex.push_back(Routine());
		routineIndex.back().name = content[tempStart][1];
		routineIndex.back().start = tempStart;
		routineIndex.back().end = subvec;
		routineIndex.back().defineContent(content);
		// Parameter handling.
		/*
		bool areThereParameters = false	;
		if ( content[tempStart].size() > 1 )
		{	
			areThereParameters = true;
			for ( int i = 2; i <= content[tempStart].size(); i++ )
			{
				string line = content[tempStart][i];
				routineIndex.back().parameters.push_back(line);
			};
		};
		*/
		// If in debug mode, we will display just more verbose info about the block.
		if ( debug )
		{
			//cout << "The new routine is of element" << routineIndex.back << "." << endl;
			cout << "There is a new routine whose name is " << routineIndex.back().name << "." << endl;
			cout << "It's start and end subvectors are " << routineIndex.back().start << " and " << routineIndex.back().end << "." << endl;
			/*
			if ( areThereParameters )
			{
				vector<string> param = routineIndex.back().parameters;
				for ( int i = 0; i <= param.size(); i++ )
				{
					cout << param[i] << " ";
				}
				cout << endl;
			}
			*/
			cout << "Finally, it's content is:" << endl;
			vector<vector<string>> blockContent = routineIndex.back().bContent;
			for ( int i = 0; i < blockContent.size(); i++ )
			{
			
				for ( int j = 0; j < blockContent[i].size(); j++ )
				{
					cout << blockContent[i][j] << " ";
				};
				cout << endl;
			};
		};
		
	}
	else if ( element.compare("endi") == 0 )
	{
		if ( debug )
		{
			cout << "Found new block of if from (ignoring newlines) line " << tempStart+1 << " to " << subvec+1 << "." << endl;
		};
	}
};

