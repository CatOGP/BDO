#ifndef PRICES_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
	stringInArray is used to find out if the string itemName is in the vector craftName
	If it is found it returns its position
	If not it returns a -1

		s is a string with the name of the item
		nameList is a vector with all the names saved
*/

int stringInArray(const string& s, vector<string>& nameList);

/*
	ABC reorganise the vectors nameList and prices in an alphabetical order
		
		nameList is a vector with the names of every item
		prices is a vector with the prices of every item
		They both have the same index
*/

void ABC(vector<string>& nameList, vector<int>& prices);

/*
	In setPrices you select an item name and then change its price, this process repeats until you decide to stop

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index
*/

void setPrices(vector<string>& nameList, vector<int>& prices);

/*
	In setAllPrices change the price of all the items, you can mantain its price by introducing the new one as a 0
	The items that had previously a price of 0 are not asked to change

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index
*/


void setAllPrices(vector<string>& nameList, vector<int>& prices);

/*
	In addItems you add an item name its price, this process repeats until you decide to stop

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index
*/

void addItems(vector<string>& nameList, vector<int>& prices);

/*
	addPriceFile adds to the file "prices.txt" all the item names with the prices changed

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index
*/

void addPriceFile(vector<string>& nameList, vector<int>& prices);

/*
	getPrices initializes nameList and prices with a file that contains every item added next to its price "itemCrafts.txt"
		
		nameList is a vector with the names of every item
		prices is a vector with the prices of every item
		They both have the same index
*/

void getPrices(vector<string>& nameList, vector<int>& prices);

#endif
