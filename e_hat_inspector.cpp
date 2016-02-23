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
vector<int> topKfreqid;
map<string, map<string, double> > e_hat;

int main(int argc, char *argv[]) {
	ifstream dictfin(dict_filename);
	ifstream topKfin(topKfreq_filename);
	ifstream ehatfin(ehat_filename);

	int id;
	string buff;
	while (getline(dictfin, buff)) {
		istringstream iss(buff);
		iss >> id;
		iss >> dict[id];
	}
	cout << "Reading dict finished." << endl;

	int freq;
	topKfreqid.push_back(0);
	while (getline(topKfin, buff)) {
		istringstream iss(buff);
		iss >> id;
		topKfreqid.push_back(id);
		iss >> freq;
	}
	cout << "Reading TopK finished." << endl;

	int k1, k2;
	double v;
	while (ehatfin >> k1 >> k2 >> v) {
		e_hat[dict[topKfreqid[k1]]][dict[topKfreqid[k2]]] = v;
	}
	cout << "Reading e_hat finished." << endl;

	string query;
	do {
		cout << "Please input a word (EXIT for exit): ";
		cin >> query;
		if (e_hat.find(query) != e_hat.end()) {
			vector<pair<string, double> > vec(e_hat[query].begin(), e_hat[query].end());
			sort(vec.begin(), vec.end(), [](auto x, auto y) { return x.second > y.second; });
			for_each(vec.begin(), vec.end(), [](auto x) { cout << x.second << ' ' << x.first << endl; });
		}
		else {
			cout << "no such word." << endl;
		}
	} while (query != "EXIT");
}
