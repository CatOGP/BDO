#ifndef CRAFTS_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

void addCraft(vector<string>& nameList, vector<int>& prices, vector<string>& craftNames, vector<string>& itemList, vector<int>& price, vector<int>& amount);
int searchItemPrice(const string& itemName, vector<int>& prices);
void getItemList(vector<string>& craftName);
void Crafts(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices);
void AuxiliarCrafter(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices);
string numToString(int n);
void reorder(vector<string>& craftName, vector<int>& profit);
void profit(vector<string>& craftName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<string> nameList, vector<int> prices);
void showMaterials(const string& itemName, vector<string> itemList, vector<int> amount);
#endif
