#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// Checks if the string has a suffix akin to the passed one.
bool hasSuffix ( const std::string &str, const std::string &suffix ) 
{

    if ( str.size() >= suffix.size() && str.compare( str.size() - suffix.size(), suffix.size(), suffix ) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
