#ifndef PARSER_H_
#define PARSER_H_

#include "csv_v3.h"
#include <string>
#include <vector>

#define SHIFT 10
#define SCALE 10
#define Q 0.055555555556 // 1 / 180
#define J 0.002666666666667 // 1 / 360
#define _USE_MATH_DEFINES
#define LAT_0 131.8
#define LON_0 43.02
#define ROWS_NUMBER 4
#define R 6371

using namespace std;

struct ParsedLine {
	ParsedLine(int, int, double, double);
	int lineStringId, pointIdx;
	double lat, lon;
};

class Parser {
private:
	vector<ParsedLine*>* parsedData;
	vector<string*>* rows;
	vector<string*>* files;
	vector<pair<double, double>*>* mercatorLocalProjWithScale;
	double xConversion(double);
	double yConversion(double);
	void convert();
public:
	Parser(vector<string*>*, vector<string*>*);
	vector<ParsedLine*> parse();
	void convertToObj();
};

#endif