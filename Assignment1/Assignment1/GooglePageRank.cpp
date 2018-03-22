#include "GooglePageRank.hpp"

using namespace std;

//Constructor - instantiate a GooglePageRank object containing a 
//double array based on a passed in file of 0s and 1s
//PRE - file must be a .txt file made up of 0s and 1s seperated by spaces
//PRE - 's' is a integer representing the size of the matric passed in through the file
//POST - GooglePageRank object created with all data members initialized
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
}

//Constructor - Instantiate a GooglePageRank object with a double matrix filled with values 
//of 1 / n (n being the size of the 
//PRE - 's' is an integer repreesnting the size of the matrix
//POST - 
GooglePageRank::GooglePageRank(int s) {

	sizeSqrt = { s };
	size = { s * s };
	matrix = new (nothrow) double[size]();

	for (int i = 0; i < size; ++i) {
		matrix[i] = 1 / (double)sizeSqrt;
	}

}

//Copy Constructor - Creates a new GooglePageRank object and copies the values based on 
//a passed in GooglePageRank object
//PRE - GooglePageRank parameter must be instantiated before hand
//POST - copy of the GooglePageRank object created
GooglePageRank::GooglePageRank(const GooglePageRank& gpr) {

	matrix = new (nothrow) double[gpr.size]();
	size = { gpr.size };
	sizeSqrt = { gpr.sizeSqrt };

	for (int i = 0; i < size; ++i) {

		matrix[i] = gpr.matrix[i];

	}
}


//Sets the value for location inside the Matrix object
//PRE - first parameter 'row' specifies the row of the matrix and must be an integer
//      within the bounds of the matrix 
//PRE - second paramter 'col' specifies the column of the matrix and must be an integer
//      within the bounds of the matrix 
//PRE - third parameter 'val' specifies the value that is to be stored at that location
//      and must be of type double
//POST - value will be set inside the matrix a specified location
void GooglePageRank::set_value(int row, int col, double val) {

	int plc = (sizeSqrt * row) + col;

	matrix[plc] = val;


}


//Sets the value for location inside the Matrix object
//PRE - first parameter 'index' specifies the location of the matrix and must be an integer
//      within the bounds of the matrix 
//PRE - third parameter 'val' specifies the value that is to be stored at that location
//      and must be of type double
//POST - value will be set inside the matrix a specified location
void GooglePageRank::set_value(int index, double val) {

	matrix[index] = val;

}


//Returns a value inside the Matrix based on the specified row and column
//PRE - first parameter 'row' specifies the row of the matrix and must be an integer 
//      within the bounds of the matrix 
//PRE - second paramter 'col' specifies the column of the matrix and must be an integer
//      within the bounds of the matrix 
//POST - Value at the specified row and column will be returned
//Returns - double representing the value inside the Matrix
double GooglePageRank::get_value(int row, int col) {

	int plc = (sizeSqrt * row) + col;

	return (matrix[plc]);

}


//Returns a value inside the Matrix based on the specified index
//PRE - first parameter 'index' specifies the location of the matrix and must be an integer 
//      within the bounds of the matrix 
//POST - Value at the specified index will be returned
//Returns - double number representing the value inside the Matrix
double GooglePageRank::get_value(int index) {
	return (matrix[index]);
}

//Return the size of a GooglePageRank objects matrix data member
//PRE - Object must be instansiated beforehand
//POST - size of the GooglePageRanks matrix data member returned
//REturns - integer number representing the size of the matrix data member
int GooglePageRank::getSize() {
	return size;
}


//Calculate the column sums of a GooglePageRank objects matrix data member
//Pass that calculated value on to create the left stochastic matrix
//PRE - GooglePageRank gpr parameter object must be created
//POST - Passed in GooglePageRank parameter updated to reflect change to a left stochastic matrix
void GooglePageRank::changeCol(GooglePageRank gpr) {

	for (int i = 0; i < sizeSqrt; ++i) {

		int colSum = 0;

		for (int j = 0; j < sizeSqrt; ++j) {

			int val = matrix[i + (sizeSqrt * j)];
			colSum += val;

		}

		testFunction(*this, i, colSum);

	}
}


//Given a GooglePageRank object and the sum of values in a passed in column,
//convert the objects matrix into a left stochastic matrix
//PRE - P1: GooglePageRank object gpr must be instantiated beforehand
//PRE - P2: colNum represents a column in the ohjects matrix and must be an int 
//PRE - P3: colSum represents the sum of all the values in the colNum variable and must be double
//PRE - if colSum is 0, each element in the column will be set to 1 / n (n being sizeSqrt data member)
//POST - GooglePageRank objects matrix columns will be updated based on passed in column sum
void GooglePageRank::testFunction(GooglePageRank& gpr, int colNum, double colSum) {

	if (colSum == 0) {

		for (int j = 0; j < sizeSqrt; ++j) {
			gpr.matrix[colNum + (sizeSqrt * j)] = 1 / (double)gpr.sizeSqrt;
		}

	}

	else {

		for (int j = 0; j < sizeSqrt; ++j) {

			int val = gpr.matrix[colNum + (sizeSqrt * j)];

			if (val == 1) {
				gpr.matrix[colNum + (sizeSqrt * j)] = (gpr.matrix[colNum + (sizeSqrt * j)] / colSum);
			}
		}
	}
}

//Multiplies our left stochastic matrix by a random walk factor that has been set as 0.85
//PRE - GooglePageRank object using this function must be instantiated
//POST - GooglePageRank objects matrix elements will be multiplied by random walk factor
void GooglePageRank::randomWalkCalc() {

	for (int i = 0; i < size; ++i) {
		this->matrix[i] = (this->matrix[i] * this->p);
	}

}

//Adds 2 matricies together
//PRE - GooglePageRank gpr parameter must be instantiated beforehand
//POST - Paramter gpr matrix and object invoking this method will be added together
void GooglePageRank::addMatrix(GooglePageRank gpr) {

	for (int i = 0; i < size; ++i) {

		this->matrix[i] = this->matrix[i] + gpr.matrix[i];

	}

}

//Required 'Rank' matrix initialize and returned based on object invoking this method
//PRE - GooglePageRank object invoking this method must be instantiated
//POST - 'Rank' matrix created and returned for use
//REturns - dynamically allocated double array filled with the value of 1
double * GooglePageRank::initializeRank() {

	double * rank = new double[this->sizeSqrt];

	for (int i = 0; i < this->sizeSqrt; ++i) {
		rank[i] = 1.0;
	}

	return rank;

}

//Markov Process implemented here which calculates the likelihood a page will be clicked
//PRE - parameter 'rank' is a dynamically allocated double array with all values set to 1.0
//POST - Rank matrix will continiously update to reflect the Markov Process calculations
//until the result of our GooglePageRank objects matrix multiplied with the 'rank' matrix is 
//equal to the 'rank' matrix (Ex. matrix * rank = rank)
void GooglePageRank::markovProcess(double * rank) {

	double * tmp = new double[this->sizeSqrt];

	int rA = this->sizeSqrt;
	int cA = this->sizeSqrt;

	int rB = this->sizeSqrt;
	int cB = 1;

	int cC = 1;

	int count = 0;

	while (1) {


		for (int i = 0; i < rA; i++) {
			for (int j = 0; j < cB; j++) {
				double sum = 0.0;
				for (int k = 0; k < rB; k++)
					sum = sum + this->matrix[i * cA + k] * rank[k * cB + j];
				tmp[i * cC + j] = sum;
			}
		}

		if (compareRank(rank, tmp)) {
			break;
		}

		else {
			count++;
		}

	}

}

//Compare the 'rank' matrix to the 'tmp' matrix (tmp is the result of the GooglePageRank
//objects matrix multiplied by the 'rank' matrix)
//PRE - parameter 'rank' is a dynamically allocated double array
//PRE - paramter 'tmp' is a dynamically allocated double array
//POST - true or false will be returned depending on if the 2 'matricies' are equal
//RETurns - true if the 2 objects contents are equal, false otherwise
bool GooglePageRank::compareRank(double * rank, double * tmp) {

	int countSame = 0;

	for (int i = 0; i < this->sizeSqrt; ++i) {

		if ((rank[i] - tmp[i]) < 0.0000001) {
			countSame++;
		}

	}

	if (countSame == this->sizeSqrt) {
		return true;
	}

	else {

		for (int i = 0; i < this->sizeSqrt; ++i) {
			rank[i] = tmp[i];
		}

		return false;

	}

}

//Divide the 'rank' matrix by the dimension of the GooglePageRanks matrix object
//PRE - parameter 'rank' will be is a dynamically allocated array of type double
//POST - 'rank' elements will be divided by the dimension of matrix data member
void GooglePageRank::calcRank(double * rank) {

	double sum = 0;

	for (int i = 0; i < sizeSqrt; ++i) {
		sum += rank[i];
	}

	for (int i = 0; i < sizeSqrt; ++i) {
		rank[i] = rank[i] / sum;
	}

}


//Stream Google Page Rank results to "Rank.txt" file
//PRE - 'rank' parameter is a dynamically allocated array of type double
//POST - elements of 'rank' streamed to Rank.txt file
void GooglePageRank::streamResults(double * rank) {

	char start = 65;

	ofstream fout;

	fout.open("Rank.txt");

	for (int i = 0; i < sizeSqrt; ++i) {
		fout << start++ << ":" << rank[i] << "\n";
	}

}



//Overloaded insertion operator
//PRE - Matrix object has to be on right of the insertion operator
//POST - Matrix object will be printed
//Returns - reference to a output stream
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
