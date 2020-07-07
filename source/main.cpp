#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <iostream>

// Include local libraries
#include "lib.h"

using namespace std;

// Define global variables

const std::string suffix = ".verl";
string **source;

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
};

// Initialises the file 2D Array.
void fuckStallman()
{

	/*
	 * Put Code in Here *
	                    */
		
};


// Reads the file into the 2D Array 'source'.
void readFile ( string filename )
{
	string line;
	ifstream file( filename );
	int k = 0;

	// Iterates line by line through the file, checking the size of the line and then divides the line by spaces into words and puts them into
	// the 2D array. 
	while ( getline( file, line ) )
	{
		istringstream first( line );
		int i = 0;

		// Gets the size of the line.
		do
		{

			string wordA;
			first >> wordA;
			cout << wordA;
			printf("\n");
			i++;
			
		} while ( first );

		// Defines an array to put the line with the size equal to the amount of words in the line.
		string temp[i];
		i = 0;

		// Puts the words into the array.
		istringstream second( line );
		do
		{
			string wordB;
			second >> wordB;
			temp[i] = wordB;
			i++;

		} while ( second );

		int sourceSize = (sizeof(source)/sizeof(*source));
		int tempSize = (sizeof(temp)/sizeof(*temp));
		//cout << sourceSize << "\n";
		//cout << sourceSize << "\n";
		
		// Puts the words in the array into the 2D Array.
		//int j = 0;
		
		for ( int j = 0; j < tempSize; j++ )
		{
			source[k][j] = temp[j];
		}
		
		k++;
	};

	int rows = (sizeof(source)/sizeof(source[0]));
	int cols = (sizeof(source[0])/sizeof(int));
	cout << rows << "\n";
	cout << cols << "\n";

	for ( int i = 0; i < rows; i++ ) 
	{
		for ( int j = 0; j < cols; j++)
		{
			cout << source[i][j] << "\r";
		};
	};

	/*
	do 
	{
		do
		{
			for ( string l; string != endDetect; mama++; )
			{
				l = source[joe][mama];
				cout << l;
				joe++;
			}
		} mama++;
	} while ( source[joe][0] != endDetect );
	*/	
};

int main ( int argc, char* argv[])
{

	// Checks if the user passed a filename, creates an error if he did not.
	if ( argc < 2 )
	{
		error( 2, argv );
	}
	else
	{
		// Checks if the file is compatible by checking it's extension.
		bool checkCorrectExtension = hasSuffix( argv[1], suffix );
		switch ( checkCorrectExtension )
		{
			case true:
				printf("This file is compatible.\n");
				readFile(argv[1]);
				break;
			case false:
				printf("This file is not compatible.\n");
				break;
			default:
				printf("Uhhh... How is your file neither compatible nor not compatible?\n");
		};
	};
};
