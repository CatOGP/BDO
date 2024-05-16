#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "prices.h"
#include "crafts.h"

using namespace std;


void showMenu()
{
	cout << "Select an option:" << endl << endl;
	cout << " 1 - Change prices" << endl;
	cout << " 2 - Add an item" << endl;
	cout << " 3 - Calculate crafting worthiness" << endl;
	cout << " 4 - Add crafting recipe" << endl;
	cout << " 5 - Change all prices " << endl << endl;
}

int main()
{
	// Prices

	vector<int> prices;
	vector<string> nameList;

	// Crafts

	vector<string> craftName;
	vector<string> itemList;
	vector<int> price;
	vector<int> amount;

	int option = 0;
	bool found = false;
	getPrices(nameList, prices);
	do
	{
		showMenu();
		cin >> option;
		switch (option)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			found = true;
		}
	} while (!found);
	switch (option)
	{
	case 1:
		setPrices(nameList, prices); 
		addPriceFile(nameList, prices);
		break;
	case 2: 
		addItems(nameList, prices);
		addPriceFile(nameList, prices);
		break;
	case 3:
		profit(craftName, itemList, price, amount, nameList, prices);
		break;
	case 4:
		addCraft(nameList, prices, craftName, itemList, price, amount);
		break;
	case 5:
		setAllPrices(nameList, prices);
		addPriceFile(nameList, prices);
		break;
	default:
		option = 0;
		break;
	}
}

/*
Los precios para calcular los beneficios son los del fichero donde se guardan los crafteos,
al cambiar los precios globales no se actualizan, por lo q nada cambia.
*/