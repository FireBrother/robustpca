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
		printf("Please pass filenames as arguments!\n");
		return 0;
	}
	ifstream dictfin(dict_filename);
	ifstream vectorsfin(argv[1]);
	ofstream vectorsfout(argv[2]);

	int id;
	string buff;
	while (getline(dictfin, buff)) {
		istringstream iss(buff);
		iss >> id;
		iss >> dict[id];
	}

	int words, size;
	vectorsfin >> words >> size;
	vectorsfout << words << ' ' << size << endl;
	while (vectorsfin >> id) {
		getline(vectorsfin, buff);
		if (dict[id] == "") dict[id] = "[NOWORD]";
		vectorsfout << dict[id] << buff << endl;
	}
}
