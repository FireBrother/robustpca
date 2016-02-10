#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "config.h"
using namespace std;

long long sum_freq = 0;
map<int, long long> topKfreq;
map<int, map<int, long long> > cooccur;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please pass window size as argument!\n");
		return 0;
	}
	int window = strtol(argv[1], NULL, 10);
	printf("Get pmi with window size of %d .\n", window);
	ifstream topKfin(topKfreq_filename);
	ifstream tokenfin(token_filename);
	ifstream totfreqfin(totfreq_filename);
	ofstream pmifout(pmi_filename);
	ofstream cooccurfout(cooccur_filename);
	int token, freq;
	while (totfreqfin >> token) {
		totfreqfin >> freq;
		sum_freq += freq;
	}
	printf("sum freq is %d.\n", sum_freq);
	while (topKfin >> token) {
		topKfin >> topKfreq[token];
	}
	printf("Reading topKfreq finished.\n");

	string buff;
	while (getline(tokenfin, buff)) {
		vector<int> tokens;
		int token;
		istringstream iss(buff);
		while (iss >> token) {
			tokens.push_back(token);
		}
		for (int i = (window - 1) / 2; i < tokens.size(); i++) {
			if (topKfreq.find(tokens[i]) == topKfreq.end())
				continue;
			for (int j = i - (window - 1) / 2; j < i; j++) {
				if (topKfreq.find(tokens[j]) == topKfreq.end())
					continue;
				int k1 = min(tokens[i], tokens[j]);
				int k2 = max(tokens[i], tokens[j]);
				cooccur[k1][k2]++;
			}
		}
	}
	printf("Counting cooccur finished.\n");
	for (auto k1 = cooccur.begin(); k1 != cooccur.end(); ++k1) {
		for (auto k2 = k1->second.begin(); k2 != k1->second.end(); ++k2) {
			cooccurfout << k1->first << ' ' << k2->first << ' ' << k2->second << endl;
			double pmi = log(double(k2->second * sum_freq) / double(topKfreq[k1->first] * topKfreq[k2->first])) / log(2);
			pmifout << k1->first << ' ' << k2->first << ' ' << pmi << endl;
		}
	}
}
