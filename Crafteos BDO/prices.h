#ifndef PRICES_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int stringInArray(const string& s, vector<string>& nameList);
void ABC(vector<string>& nameList, vector<int>& prices);
void setPrices(vector<string>& nameList, vector<int>& prices);
void setAllPrices(vector<string>& nameList, vector<int>& prices);
void addItems(vector<string>& nameList, vector<int>& prices);
void addPriceFile(vector<string>& nameList, vector<int>& prices);
void getPrices(vector<string>& nameList, vector<int>& prices);

#endif
