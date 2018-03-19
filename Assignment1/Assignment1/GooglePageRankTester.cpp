#include "GooglePageRank.hpp"

using namespace std;

string readFile();
string convertFile(string s);

int main() {

	string textFile = readFile();

	string fileContents = convertFile(textFile);
	int size = ((fileContents.length() + 1) / 2);
	int sizeSqrt = (sqrt(size));

	GooglePageRank a(fileContents, size);

	cout << a << endl;

	GooglePageRank b(a);

	b.changeCol(a);

	cout << b << endl;

	b.randomWalkCalc();

	cout << b << endl;

	GooglePageRank c(sizeSqrt);

	cout << c << endl;

	for (int i = 0; i < c.getSize(); ++i) {
		double a = c.get_value(i) * 0.15;

		c.set_value(i, a);
	}
	
	cout << c << endl;


	b.addMatrix(c);

	cout << b << endl;

	
	double * d = b.markovProcess();

	for (int i = 0; i < sizeSqrt; ++i) {
		d[i] = 1.0;
	}

	b.markovProcess(d);
	

	system("PAUSE");

	return 0;
}


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