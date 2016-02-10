#include <string>
//#define test
using namespace std;

#ifdef test
	const string base_filename = "test";
#else
	const string base_filename = "WestburyLab.Wikipedia.Corpus";
#endif
const string corpus_filename = base_filename + ".txt";
const string token_filename = base_filename + ".token.txt";
const string totfreq_filename = base_filename + ".totfreq.txt";
const string topKfreq_filename = base_filename + ".topKfreq.txt";
const string cooccur_filename = base_filename + ".cooccur.txt";
const string pmi_filename = base_filename + ".pmi.txt";
