#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "config.h"
using namespace std;

map<int, long long> freq;

int main() {
	ifstream fin(token_filename);
	ofstream fout(totfreq_filename);
	int token;
	while (fin >> token) {
		freq[token]++;
	}
	printf("Counting finished.\n");

	for (auto mitr = freq.begin(); mitr != freq.end(); ++mitr) {
		fout << mitr->first << ' ' << mitr->second << endl;
	}
}
