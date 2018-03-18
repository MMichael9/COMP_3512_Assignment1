#pragma once

#include <iostream>
#include <string>
#include <new>
#include <iomanip>
#include <cmath>
#include <iterator>
#include <fstream>
#include <sstream>

class GooglePageRank {

	int size;
	int sizeSqrt;
	int * matrix;

public:

	GooglePageRank(std::string file, int s);

	~GooglePageRank() { delete[] matrix;  std::cout << std::endl << "Destoryed" << std::endl; }

	friend std::ostream& operator<<(std::ostream& out, const GooglePageRank& gpr);

};