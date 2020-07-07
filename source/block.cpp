#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef struct 
{
	int start;
	int end;
	string parentBlock;
	int tableNumber;
	string** content;
	
} Block;
