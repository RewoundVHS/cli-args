#include <iostream>
#include <string.h>

using namespace std;

void Usage(char * progname);
void GetHighAndLow(const char * param, int & low, int & high);

int main(int argc, char * argv[]) {
	string argument;
	bool reverse = false;
	bool verbose = false;
	bool help = false;
	string lowString;
	string highString;
	string limitString;
	string stepString;
	int low = 1;
	int high = 10;
	int step = 1;

	int i = 1;
	while (i < argc) {

		argument = argv[i];

		// Print help menu
		if (!strcmp(argv[i], "-h") or !strcmp(argv[i], "--help")) {
			Usage(argv[0]);
			help = true;
			i++;
		// Set bottom value
		} else if (!strcmp(argv[i], "-b")) {
			i++;
			if (i < argc) {
				low = atoi(argv[i]);
				i++;
			} else {
				cerr << "\t-b requires an integer argument" << endl;
			}
		} else if (!strncmp(argv[i], "-b", 2))  {
			lowString = argv[i];
			low = stoi(lowString.substr(2, argument.size()));
			i++;
		} else if (!strncmp(argv[i], "--bottom=", 9)) {
			lowString = argv[i];
			low = stoi(lowString.substr(9, argument.size()));
			i++;
		// Set top value
		} else if (!strcmp(argv[i], "-t")) {
			i++;
			if (i < argc) {
				high = atoi(argv[i]);
				i++;
			} else {
				cerr << "\t-t requires an integer argument" << endl;
			}
		} else if (!strncmp(argv[i],"-t", 2))  {
			highString = argv[i];
			high = stoi(highString.substr(2, argument.size()));
			i++;
		} else if (!strncmp(argv[i], "--top=", 6)) {
			highString = argv[i];
			high = stoi(highString.substr(6, argument.size()));
			i++;
		// Set upper and lower limits
		} else if (!strcmp(argv[i], "-l"))  {
			i++;
			if (i < argc) {
				GetHighAndLow(argv[i], low, high);
				i++;
			} else {
				cerr << "\t-l requires an argument" << endl;
			}
		} else if (!strncmp(argv[i], "-l", 2)) {
			i++;
			argument = argument.substr(2, argument.size());
			GetHighAndLow(argument.c_str(), low, high);
			i++;
		} else if (!strncmp(argv[i], "--limit=", 8)) {
			limitString = argument.substr(8, argument.size());
			GetHighAndLow(limitString.c_str(), low, high);
			i++;
		// Set reverse mode
		} else if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--reverse")) {
			reverse = true;
			i++;
		// Set step
		} else if (!strcmp(argv[i], "-s"))  {
			i++;
			if (i < argc) {
				step = atoi(argv[i]);
				i++;
			} else {
				cerr << "\t-s requires an integer argument" << endl;
			}
		} else if (!strncmp(argv[i], "-s", 2))  {
			stepString = argv[i];
			step = stoi(stepString.substr(2, argument.size()));
			i++;
		} else if (!strncmp(argv[i], "--step=", 7)) {
			stepString = argv[i];
			step = stoi(stepString.substr(7, argument.size()));
			i++;
		// Set verbose mode
		} else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
			verbose = true;
			i++;
		// Invalid argument
		} else {
			cerr << "Unknown argument " << argv[i] << endl;
			Usage(argv[0]);
			i++;
		}

	}

	// Check if low greater than high, if so, print error and exit
	if (low > high) {
		cerr << "Low value greater than high value" << endl;
	// Check if step is negative or zero, if so print an error and exit
	} else if (step <= 0) {
		cerr << "Step negative or zero"	<< endl;
	// Verbose mode, print a summary of all values set by arguments
	} else if (verbose) {
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
		if (!reverse) {
			// Count from low value to high value
			for (int k=low; k<=high; k+=step) {
				cout << k;
				if (k < high && (k+step <= high)) {
					cout << ' ';
				}
			}
		} else {
			// Count from high value to low value
			for (int k=high; k>=low; k-=step) {
				cout << k;
				if (k > low && (k-step >= low)) {
					cout << ' ';
				}
			}
		}
		cout << endl;
	}

	return 0;
}

// Finds the comma separated high and low values
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

// Print the help section, explains command line argument usage
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
