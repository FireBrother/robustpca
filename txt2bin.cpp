#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Please pass filenames as arguments!\n");
		return 0;
	}
	ifstream fin(argv[1]);
	FILE *fo = fopen(argv[2], "wb");
	long long words, size;
	string word;
	float value;
	fin >> words >> size;
	fprintf(fo, "%lld %lld\n", words, size);
	for (int i = 0; i < words; i++) {
		fin >> word;
		fprintf(fo, "%s ", word.c_str());
		for (int j = 0; j < size; j++) {
			fin >> value;
			fwrite(&value, sizeof(float), 1, fo);
		}
	}
}
