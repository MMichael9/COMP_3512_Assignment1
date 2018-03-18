#include "GooglePageRank.hpp"

using namespace std;


GooglePageRank::GooglePageRank(std::string file, int s) {

	matrix = new int[s];
	size = { s };
	sizeSqrt = (sqrt(size));

	istringstream iss{ file };

	for (int i = 0; i < size; ++i) {

		int a;

		iss >> a;

		matrix[i] = a;

	}

	/*
	//IN DEGREE OF CONNECTIVITY MATRIX
	for (int i = 0; i < sizeSqrt; ++i) {
		int rowSum = 0;

		for (int j = 0; j < sizeSqrt; ++j) {

			int val = matrix[i * sizeSqrt + j];
			rowSum += val;
			cout << val << " ";

		}
		cout << "Row Sum = " << rowSum << endl << endl;
	}

	cout << "-----------------------------------------------\n" << endl;

	for (int i = 0; i < sizeSqrt; ++i) {

		int colSum = 0;

		for (int j = 0; j < sizeSqrt; ++j) {

			int val = matrix[i + (sizeSqrt * j)];
			colSum += val;
			cout << val << " ";

		}
		cout << "Col Sum = " << colSum << endl << endl;
	}

	*/


}

GooglePageRank::GooglePageRank(const GooglePageRank& gpr) {

	matrix = new (nothrow) int[gpr.size]();
	size = { gpr.size };
	sizeSqrt = { gpr.sizeSqrt };

	for (int i = 0; i < size; ++i) {

		matrix[i] = gpr.matrix[i];

	}
}

void GooglePageRank::set_value(int row, int col, int val) {

	int plc = (sizeSqrt * row) + col;

	matrix[plc] = val;


}

int GooglePageRank::get_value(int row, int col) {

	int plc = (sizeSqrt * row) + col;

	return (matrix[plc]);

}


std::ostream & operator<<(std::ostream & out, const GooglePageRank & gpr)
{
	for (int i = 0; i < gpr.sizeSqrt; ++i) {
		for (int j = 0; j < gpr.sizeSqrt; ++j) {
			out << gpr.matrix[i * gpr.sizeSqrt + j] << "  ";
		}
		out << "\n";
	}
	return out;
}