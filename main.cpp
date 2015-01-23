#include <iostream>
#include <string>
#include <vector>
#include "parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<string*> rows = *new vector<string*>();
	vector<string*> files = *new vector<string*>();
	if (argc > 1) {
		for (int i = 1; i < ROWS_NUMBER + 1; ++i) {
			rows.push_back(new string(argv[i]));
		}	
		for (int i = ROWS_NUMBER + 1; i < argc; ++i) {
			files.push_back(new string(argv[i]));
		}
		Parser parser = *new Parser(&rows, &files);
		vector<ParsedLine*> data = parser.parse();	
		parser.convertToObj();
	} else {
		cout << "Ќв вход подайте файлы в формате .csv";
	}
	return 0;
}
