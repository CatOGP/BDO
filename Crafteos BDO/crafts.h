#ifndef CRAFTS_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

/*
	Using addCraft the user can add one recipe to the file "crafts.txt"

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index

		craftName is a vector with the names of all the possible recipes
		itemList is a vector with the names of all the materials of one recipe
		price is a vector with the prices of all the materials of one recipe
		amount is a vector with the amounts of all the materials of one recipe
*/

void addCraft(vector<string>& nameList, vector<int>& prices, vector<string>& craftNames, vector<string>& itemList, vector<int>& price, vector<int>& amount);

/*
	searchItemPrice search the price of the introduced item in the file "prices.txt"
		
		itemName is a string with the name of the item that needs its price to be searched
		prices is a vector with the prices of every item
*/

int searchItemPrice(const string& itemName, vector<int>& prices);

/*
	getItemList initializes craftName with all the strings in "itemCrafts.txt"
		
		craftName is a vector that has every craftable item in it
*/

void getItemList(vector<string>& craftName);

/*
	Both crafts and craftsAux return itemList, price and amount with the names, prices and amounts needed for the recipe of the itemName
		
		itemName is a string with the name of the recipe
		itemList is a vector with the names of every material 
		price is a vector with the prices of every material
		amount is a vector with the amounts of every material
*/

void crafts(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices);
void craftsAux(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices);

/*
	numToString transforms the number received into a string with the commas added every three digits
*/

string numToString(int n);

/*
	reorder reorganize the profit vector from the biggest to the smallest

		craftName is a vector with the names of every recipe
		profit is a vector with the profit amount of every recipe
		rawPrice is a vector with the raw sell price of every recipe
*/

void reorder(vector<string>& craftName, vector<int>& profit, vector<int>& rawPrice);

/*
	The function profit calculates the profit of every item craft in the file "crafts.txt"

		craftName is a vector with the names of all the possible recipes
		itemList is a vector with the names of all the materials of one recipe
		price is a vector with the prices of all the materials of one recipe
		amount is a vector with the amounts of all the materials of one recipe

		nameList is a vector with the name of all the items
		prices is a vector witht the price of all the items
		They both have the same index

*/

void profit(vector<string>& craftName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<string> nameList, vector<int> prices);

/*
	showMaterials is a method that shows all the materials required to craft an item

		itemName is a string with the name of the desired item
		itemList is a vector with the name of all the materials
		amount is a vector with the amount of all the materials
*/

void showMaterials(const string& itemName, vector<string> itemList, vector<int> amount);
#endif
