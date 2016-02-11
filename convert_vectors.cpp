#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "config.h"
using namespace std;

map<int, string> dict;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Please pass words and size as arguments!\n");
		return 0;
	}
	int words = strtol(argv[1], NULL, 10);
	int size = strtol(argv[2], NULL, 10);
	ifstream dictfin(dict_filename);
	ifstream vectorsfin("vectors.txt");
	ofstream vectorsfout("vectors_rpca.txt");

	int id;
	string buff;
	while (getline(dictfin, buff)) {
		istringstream iss(buff);
		iss >> id;
		iss >> dict[id];
	}

	vectorsfout << words << ' ' << size << endl;
	while (vectorsfin >> id) {
		getline(vectorsfin, buff);
		if (dict[id] == "") dict[id] = "[NOWORD]";
		vectorsfout << dict[id] << buff << endl;
	}
}
