
/*
*
* g++ main.cpp firebird.cpp ibpp/core/all_in_one.cpp -o fire -lfbclient -lcrypt -lm -ldl -lpthread
*
*/

#include <iostream>
#include <string>

#include "C++/firebird.h"

int main( int argc, char** argv )
{
	std::cout << "Hello, firebird!\n";

	Firebird fb;
	
	std::vector<int> intVec;

	const char* statement = "SELECT duration FROM track";

	if ( fb.query( statement, &intVec ) ) {
		std::cout << "int query successful\n";
	} else {
		std::cout << "ERROR: int query unsuccessful\n";
	}

	//for ( int i = 0; i < intVec.size(); i++ )
	//	std::cout << intVec[i] << "\n";

	std::vector<std::string> stringVec;

	const char* statement2 = "SELECT vktrack.artist,vktrack.title FROM vktrack INNER JOIN track ON track.vktrack_id = vktrack.id WHERE track.album_id = 5";

	if ( fb.query( statement2, &stringVec ) ) {
		std::cout << "string query successful\n";
	} else {
		std::cout << "ERROR: string query unsuccessful\n";
	}

	//for ( int i = 0; i < stringVec.size(); i++ )
	//	std::cout << stringVec[i] << "\n";

	std::vector< std::vector<std::string> > arrayStringVec;

	const char* statement3 = "SELECT vktrack.artist,vktrack.title FROM vktrack INNER JOIN track ON track.vktrack_id = vktrack.id WHERE track.album_id = 3";

	if ( fb.query( statement3, &arrayStringVec ) ) {
		std::cout << "array string query successful\n";
	} else {
		std::cout << "ERROR: array string query unsuccessful\n";
	}

	for ( int i = 0; i < arrayStringVec.size(); i++ )
		for ( int j = 0; j < arrayStringVec[i].size(); j++ )
			std::cout << arrayStringVec[i][j] << "\n";

	return 0;
}
