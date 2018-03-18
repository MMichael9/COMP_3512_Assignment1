#include "GooglePageRank.hpp"

using namespace std;

string readFile();
string convertFile(string s);

int main() {

	string textFile = readFile();

	string fileContents = convertFile(textFile);
	int size = ((fileContents.length() + 1) / 2);

	GooglePageRank a(fileContents, size);

	cout << a << endl;


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