#include <iostream>
#include <fstream>
using namespace std;

int main() {
	srand(42);
	char DNA[] = "ATGC";
	char name[50];
	for (int i = 13; i < 20; ++i) {
		ofstream file;
		sprintf(name, "%d.in", i);
		file.open(name);
		file << rand() % 1000 << endl;
		for (int j = 0; j < 1000; ++j)
			file << DNA[rand()%4];
		file << endl;
		file.close();
	}
}