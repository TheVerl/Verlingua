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

using namespace std;

// Define global variables.
const std::string suffix = ".verl";
vector<vector<string>> content;
bool debug = false;

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
	
	// Going through each line, we chop the line up by each space and then put that into the new subvector of the file vector.
	while ( numberOfLines-- )
	{
		getline( fileB, lineB );
		//cout << lineB << endl;
		content.push_back(chopUpLine(lineB));
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
			cout << content[i][j] << endl;
		}
	}
}

// Main function.
int main ( int argc, char* argv[])
{
	// Checks if the user passed a filename, creates an error if he did not.
	if ( argc < 2 )
	{
		error( 2, argv );
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
	};
};  	
