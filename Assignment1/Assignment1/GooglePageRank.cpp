#include "GooglePageRank.hpp"

using namespace std;


GooglePageRank::GooglePageRank(std::string file, int s) {

	matrix = new double[s];
	size = { s };
	sizeSqrt = (sqrt(size));

	istringstream iss{ file };

	for (int i = 0; i < size; ++i) {

		double a;

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

	matrix = new (nothrow) double[gpr.size]();
	size = { gpr.size };
	sizeSqrt = { gpr.sizeSqrt };

	for (int i = 0; i < size; ++i) {

		matrix[i] = gpr.matrix[i];

	}
}

void GooglePageRank::set_value(int row, int col, double val) {

	int plc = (sizeSqrt * row) + col;

	matrix[plc] = val;


}

int GooglePageRank::get_value(int row, int col) {

	int plc = (sizeSqrt * row) + col;

	return (matrix[plc]);

}

void GooglePageRank::changeCol(GooglePageRank gpr) {

	for (int i = 0; i < sizeSqrt; ++i) {

		int colSum = 0;

		for (int j = 0; j < sizeSqrt; ++j) {

			int val = matrix[i + (sizeSqrt * j)];
			colSum += val;
			cout << val << " ";

		}
		cout << "Col Sum = " << colSum << endl << endl;

		testFunction(*this, i, colSum);

	}


	for (int i = 0; i < this->sizeSqrt; ++i) {
		for (int j = 0; j < this->sizeSqrt; ++j) {
			cout << this->matrix[i * this->sizeSqrt + j] << "  ";
		}
		cout << "\n";
	}
}

void GooglePageRank::testFunction(GooglePageRank& gpr, int colNum, double colSum) {

	if (colSum == 0) {

		for (int j = 0; j < sizeSqrt; ++j) {
			gpr.matrix[colNum + (sizeSqrt * j)] = 1 / (double) gpr.sizeSqrt;
		}

	}

	for (int j = 0; j < sizeSqrt; ++j) {

		int val = gpr.matrix[colNum + (sizeSqrt * j)];

		if (val == 1) {
			gpr.matrix[colNum + (sizeSqrt * j)] = (gpr.matrix[colNum + (sizeSqrt * j)] / colSum);
		}
	}
}

void GooglePageRank::randomWalkCalc() {

	for (int i = 0; i < size; ++i) {
		this->matrix[i] = (this->matrix[i] * this->p);
	}

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