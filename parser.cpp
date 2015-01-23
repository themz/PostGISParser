#include "parser.h"
#include <math.h>
#include <fstream>

ParsedLine::ParsedLine(int id, int ix, double la, double lo) : lineStringId(id), pointIdx(ix), lat(la), lon(lo) { }

Parser::Parser(vector<string*>* rowNames, vector<string*>* fileNames) : parsedData(new vector<ParsedLine*>()), 
																		rows(rowNames), files(fileNames),
																		mercatorLocalProjWithScale(new vector<pair<double, double>*>()) {}

vector<ParsedLine*> Parser::parse ()
{
	for (vector<string*>::iterator it = files->begin(); it != files->end(); ++it) {
		io::CSVReader<ROWS_NUMBER> in(*(*it));
		in.read_header(io::ignore_extra_column, *rows->at(0), *rows->at(1), *rows->at(2), *rows->at(3));
		int line_string_id, point_idx; 
		double lat, lon;
		while (in.read_row(line_string_id, point_idx, lat, lon)){
			ParsedLine* pl = new ParsedLine(line_string_id, point_idx, lat, lon);
			parsedData->push_back(pl);
		}
	}
	return *parsedData;
}

void Parser::convert()
{
	double t1, t2;
	for (vector<ParsedLine*>::iterator it = parsedData->begin(); it != parsedData->end(); ++it) {
		mercatorLocalProjWithScale->push_back(new pair<double, double>(
			modf( abs(xConversion((*it)->lon) - xConversion(LON_0)) * SCALE, &t1 ) * SHIFT,
			modf( abs(yConversion((*it)->lat) - yConversion(LAT_0)) * SCALE, &t2 ) * SHIFT
		));		
	}
}

double Parser::xConversion(double l) 
{
	return R * l * M_PI * Q;
}

double Parser::yConversion(double l)
{
	return R * log10(tan(M_PI * 0.25 + l * J));
}

void Parser::convertToObj()
{
	ofstream o("level_10.obj");
	convert();
	for (vector<pair<double, double>*>::iterator it = mercatorLocalProjWithScale->begin(); it != mercatorLocalProjWithScale->end(); ++it) {
		o << "v " << (*it)->first << ' ' << (*it)->second << ' ' << '1' << '\n';
	}
}
