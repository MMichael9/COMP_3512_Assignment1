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
	double * matrix;
	double p = { 0.85 };

public:

	GooglePageRank(std::string file, int s);
	GooglePageRank(int s);
	GooglePageRank(const GooglePageRank& gpr);

	~GooglePageRank() { delete[] matrix;  std::cout << std::endl << "Destoryed" << std::endl; }

	void set_value(int row, int col, double val);
	void set_value(int index, double val);
	double get_value(int row, int col);
	double get_value(int index);
	int getSize();

	void changeCol(GooglePageRank gpr);

	void testFunction(GooglePageRank& gpr, int colNum, double colSum);

	void randomWalkCalc();

	void addMatrix(GooglePageRank gpr);

	double * initializeRank();
	void markovProcess(double * rank);
	bool compareRank(double * rank, double * tmp);

	void calcRank(double * rank);

	void streamResults(double * rank);

	friend std::ostream& operator<<(std::ostream& out, const GooglePageRank& gpr);


};