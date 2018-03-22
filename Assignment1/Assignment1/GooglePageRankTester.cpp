#include "GooglePageRank.hpp"

using namespace std;

string readFile();
string convertFile(string s);

int main() {

	//Read in text file
	string textFile = readFile();

	//Convert given text file to String
	string fileContents = convertFile(textFile);

	//Compute the length of the array stored in text file
	int sizeofFileArray = ((fileContents.length() + 1) / 2);
	int sizeSqrt = (sqrt(sizeofFileArray));

	//Initialize object G - matrix will be instantiated with values from text file
	GooglePageRank G(fileContents, sizeofFileArray);

	//Create a new object S using the copy constructor 
	GooglePageRank S(G);

	//Invoke changeCol on S using the column sums of G to convert the objects
	//matrix into a left stochastic matrix
	S.changeCol(G);

	//Calculate the random walk factor on object S and its matrix values
	S.randomWalkCalc();

	//Initialize Q which will contain the same size matrix of S but values
	//initalized to 1/n (n being the dimension of matrix S and G)
	GooglePageRank Q(sizeSqrt);


	//Perform calcualtion on Q's matrix 
	for (int i = 0; i < Q.getSize(); ++i) {
		double a = Q.get_value(i) * 0.15;

		Q.set_value(i, a);
	}


	//Add Q and S matricies and store result in S
	S.addMatrix(Q);

	//Initialize rank matrix for calcuating chance of user visiting a page
	double * rank = S.initializeRank();

	//Perform Markov Process on S with dynamic double array rank
	S.markovProcess(rank);

	//Calcualte percentage chance a page gets visited
	S.calcRank(rank);

	//Send results to a .txt file
	S.streamResults(rank);


	//system("PAUSE");

	return 0;
}

//Read in name of text file that contains GooglePageRank web
//
string readFile() {

	cout << "Enter Text File with connectivity matrix" << endl;

	string s;

	cin >> s;

	return s;

}

string convertFile(string s) {

	ifstream f;
	f.open(s);

	if (!f) {
		cout << "Unable to open file" << endl;
	}

	string file;

	char c;
	while ((c = f.get()) != EOF) {
		file = file + c;
	}

	return file;

}