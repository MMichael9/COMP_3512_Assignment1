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

GooglePageRank::GooglePageRank(int s) {

	sizeSqrt = { s };
	size = { s * s };
	matrix = new (nothrow) double[size]();

	for (int i = 0; i < size; ++i) {
		matrix[i] = 1 / (double) sizeSqrt;
	}

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

void GooglePageRank::set_value(int index, double val) {

	matrix[index] = val;

}



double GooglePageRank::get_value(int row, int col) {

	int plc = (sizeSqrt * row) + col;

	return (matrix[plc]);

}

double GooglePageRank::get_value(int index) {
	return (matrix[index]);
}

int GooglePageRank::getSize() {
	return size;
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

void GooglePageRank::addMatrix(GooglePageRank gpr) {

	for (int i = 0; i < size; ++i) {

		this->matrix[i] = this->matrix[i] + gpr.matrix[i];

	}

}

double * GooglePageRank::markovProcess() {

	double * rank = new double[this->sizeSqrt];

	return rank;

}

void GooglePageRank::markovProcess(double * rank) {

	for (int i = 0; i < this->sizeSqrt; ++i) {
		cout << rank[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < this->sizeSqrt; ++i) {
		for (int j = 0; j < this->sizeSqrt; ++j) {
			cout << setw(5) << this->matrix[i * this->sizeSqrt + j] << "  ";
		}
		cout << "\n";
	}



	double * result = new double[this->sizeSqrt];

	int rA = sizeSqrt;
	int cA = sizeSqrt;

	int rB = sizeSqrt;
	int cB = 1;

	int cC = 1;

	int count = 0;

	while (count < 4) {

		for (int i = 0; i < rA; i++) {
			for (int j = 0; j < cB; j++) {
				double sum = 0.0;
				for (int k = 0; k < rB; k++)
					sum = sum + this->matrix[i * cA + k] * rank[k * cB + j];
				result[i * cC + j] = sum;
			}

		}

		for (int i = 0; i < rA; i++) {
			for (int j = 0; j < cB; j++) {
				double sum = 0.0;
				for (int k = 0; k < rB; k++)
					sum = sum + this->matrix[i * cA + k] * result[k * cB + j];
				result[i * cC + j] = sum;
			}

		}



		cout << endl << endl;

		for (int i = 0; i < this->sizeSqrt; ++i) {
			cout << result[i] << " ";
		}

		cout << endl;

		count++;
	}


	cout << endl;
	
}


std::ostream & operator<<(std::ostream & out, const GooglePageRank & gpr)
{
	for (int i = 0; i < gpr.sizeSqrt; ++i) {
		for (int j = 0; j < gpr.sizeSqrt; ++j) {
			out << setw(5) << gpr.matrix[i * gpr.sizeSqrt + j] << "  ";
		}
		out << "\n";
	}
	return out;
}