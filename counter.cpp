#include <iostream>
#include <string.h>


using namespace std;

void Usage(char * progname);
void PrintGreeting(string greeting, int start, int end);
void GetMandN(const char * param, int & start, int & end);
void GetHighAndLow(const char * param, int & low, int & high);

int main(int argc, char * argv[]) {
	string greeting = "hello";
	int greetCount = 1;
	bool reverse = false;
	bool verbose = false;
	bool help = false;

	int charStart = 0;
	int charEnd = -1;

	string lowString;
	string highString;
	int low = 1;
	int high = 10;
	int step = 1;

	int i = 1;
	while (i < argc) {
		if (!strcmp(argv[i],"-h") or !strcmp(argv[i],"--help")) {
			Usage(argv[0]);
			help = true;
			i++;
		} else if (!strcmp(argv[i],"-g") or !strcmp(argv[i],"--greeting")) {
			i++;
			if (i < argc) {
				greeting = argv[i];
				i++;
			} else {
				cerr <<"Error: " << argv[i-1] << " requires a string" << endl;
			}
		} else if (!strncmp(argv[i],"-g", 2))  {
			greeting = argv[i];
			greeting = greeting.substr(2, greeting.size());
			i++;
		} else if (!strncmp(argv[i],"-b", 2))  {
			lowString = argv[i];
			low = stoi(lowString.substr(2, greeting.size()));
			i++;
		} else if (!strncmp(argv[i],"-t", 2))  {
			highString = argv[i];
			high = stoi(highString.substr(2, greeting.size()));
			i++;
		} else if (!strncmp(argv[i],"--greeting=", 11))  {
			greeting = argv[i];
			greeting = greeting.substr(11, greeting.size());
			i++;
		} else if (!strcmp(argv[i],"-m"))  {
			i++;
			if (i < argc) {
				greetCount = atoi(argv[i]);
				i++;
			} else {
				cerr << "\t-m requires an integer argument" << endl;
			}
		} else if (!strcmp(argv[i], "-x"))  {
			i++;
			if (i < argc) {
				GetMandN(argv[i],charStart,charEnd);
				i++;
			} else {
				cerr << "\t-x requires an argument" << endl;
			}
		} else if (!strcmp(argv[i], "-l"))  {
			i++;
			if (i < argc) {
				GetHighAndLow(argv[i], low, high);
				i++;
			} else {
				cerr << "\t-t requires an argument" << endl;
			}
		} else if (!strncmp(argv[i], "--range=", 8))  {
			string tmp = argv[i];
			tmp = tmp.substr(8, string::npos);
			GetMandN(tmp.c_str(), charStart, charEnd);
			i++;
		} else if (!strcmp(argv[i],"-r") || !strcmp(argv[i], "--reverse")) {
			reverse = true;
			i++;
		// Needs fixed to allow -sn, --step=n
		} else if (!strcmp(argv[i], "-s"))  {
			i++;
			if (i < argc) {
				step = atoi(argv[i]);
				i++;
			} else {
				cerr << "\t-s requires an integer argument" << endl;
			}
		} else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
			verbose = true;
			i++;
		} else {
			cerr << "Unknown argument " << argv[i] << endl;
			Usage(argv[0]);
			i++;
		}

	}

	// fix a value at the end.
	if (greetCount < 1 or greetCount > 100) {
		cerr << "\tNumber of greetings shold be between 1 and 100, setting to 1"
			<< endl;
		greetCount = 1;
	}

	// Verbose mode
	if (verbose) {
		cout << "Low = " << low << endl;
		cout << "High = " << high << endl;
		cout << "Step = " << step << endl;
		cout << "Reverse = ";
		if (reverse)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		cout << "Help = ";
		if (help)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		cout << "Verbose = Yes" << endl;

	} else {

		// perform a task.
		if (reverse) {
			string tmp;
			for (size_t j=greeting.size()-1; j != 0; j--) {
				tmp += greeting[j];
			}
			tmp += greeting[0];
			greeting = tmp;
		}

		/*
		for (i=0;i<greetCount; i++) {
			PrintGreeting(greeting, charStart, charEnd);
		}
		*/

		if (!reverse) {
			// Count from low value to high value
			for (int k=low; k<=high; k+=step) {
				cout << k << ' ';
			}
		} else {
			// Count from high value to low value
			for (int k=high; k>=low; k-=step) {
				cout << k << ' ';
			}
		}
		cout << endl;
	}

	return 0;
}

void GetHighAndLow(const char* param, int & low, int & high) {
	string tmp = param;

	size_t pos;

	pos = tmp.find(',');
	if (pos == string::npos) {
		high = -1;
		low = atoi(param);
	} else {
		string first, second;
		first = tmp.substr(0,pos);
		low = atoi(tmp.c_str());
		second = tmp.substr(pos+1,string::npos);
		high = atoi(second.c_str());
	}
	return;
}

void Usage(char * progname) {
	cout << "Usage: " << progname << endl;
	cout << "\t-h --help: print a help message describing command line arguments" << endl;
	cout << "\t-b n, --bottom=n: set the low value to be the integer n." << endl;
	cout << "\t-t n, --top=n: set the high value to be the integer n." << endl;
	cout << "\t-l m, n -lm, --limit=m,n: set the low value to be m and the high value to be n." << endl;
	cout << "\t-r --reverse: print from high to low, not low to high." << endl;
	cout << "\t-s n, -sn, --step=n: increment (or decrement) by n, the default is 1." << endl
		<< "\tThe step value is restricted to positive integers (no negatives or 0)." << endl;
	cout << "\t-v, --verbose: parse command line arguments and print a summary of the values." << endl;
	return;
}

void PrintGreeting(string greeting, int & start, int & end){
	int i;

	if (end == -1 or end > int(greeting.size())) {
		end = greeting.size();
	}

	for (i = start; i<end; i++) {
		cout << greeting[i];
	}
	cout << endl;
	return;
}

void GetMandN(const char * param, int & start, int & end){
	string tmp = param;

	size_t pos;

	pos = tmp.find(',');
	if (pos == string::npos) {
		end = -1;
		start = atoi(param);
	} else {
		string first, second;
		first = tmp.substr(0,pos);
		start = atoi(tmp.c_str());
		second = tmp.substr(pos+1,string::npos);
		end = atoi(second.c_str());
	}
	return;
}
