#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "config.h"
using namespace std;

map<int, long long> freq;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please pass K as argument!\n");
		return 0;
	}
	int K = strtol(argv[1], NULL, 10);
	printf("Get top %d freq.\n", K);
	ifstream fin(totfreq_filename);
	ofstream fout(topKfreq_filename);
	int token;
	while (fin >> token) {
		fin >> freq[token];
	}
	printf("Reading freq finished.\n");

	vector<pair<int, long long> > vfreq(freq.begin(), freq.end());
	sort(vfreq.begin(), vfreq.end(), [](const pair<int, long long> &a,
		const pair<int, long long> &b) {
		return a.second > b.second;
	});
	printf("Sorting finished.\n");
	for (int i = 0; i < K; i++) {
		fout << vfreq[i].first << ' ' << vfreq[i].second << endl;
	}
}
