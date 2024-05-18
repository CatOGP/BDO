#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "prices.h"
#include "crafts.h"

using namespace std;

// Method to show the possible options 

void showMenu()
{
	cout << "Select an option:" << endl << endl;

	// Change the prices of a selected item

	cout << " 1 - Change prices" << endl;

	// Add an item to the txt with the items | name + price

	cout << " 2 - Add an item" << endl;

	// Shows how much profit you have with each craft, 
	// then it can show you the recipe of the selected one

	cout << " 3 - Calculate crafting worthiness" << endl;

	// Adds a new recipe | item name + materials + amount

	cout << " 4 - Add crafting recipe" << endl;

	// Change the prices of all items, there is an option to keep it the same for some items

	cout << " 5 - Change all prices " << endl << endl;
}

// Main program

int main()
{
	// Vectors used mainly in prices functions

	/*
		prices has the information of each item price
		nameList has the information of each item name
		They both use the same index for each item
	*/

	vector<int> prices;
	vector<string> nameList;

	// Vectors used mainly in crafts functions

	// craftName has the name of every craftable item
	
	vector<string> craftName;

	/*
		itemList is used to save all the materials used for one craft, it is deleted after each craft
		price is used to save the price of each material used for one craft, it is deleted after each craft
		amount is used to save the amount of each material used for one craft, it is deleted after each craft
		They all share the same index for each material item
	*/

	vector<string> itemList;
	vector<int> price;
	vector<int> amount;

	// option is used to select which option of the menu is selected

	int option = 0;

	// itemName is used to save the answer of the user of the name of the recipe

	int itemName = 0;

	// used in bucles to see if it is a possible answer

	bool found = false;

	// answer is used in case 3 to save the name of the item recipe chosen

	string answer = "";

	// nameList and prices are initialized

	getPrices(nameList, prices);

	// do/while loop to choose a possible option of the menu

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
	found = false;

	// Switch with the option of the menu chosen

	switch (option)
	{

	// Change the prices of a selected item

	case 1:
		setPrices(nameList, prices); 
		addPriceFile(nameList, prices);
		break;

	// Add an item to the txt with the items | name + price

	case 2: 
		addItems(nameList, prices);
		addPriceFile(nameList, prices);
		break;

	// Shows how much profit you have with each craft and the total value, 
	// then it can show you the recipe of the selected one

	case 3:
		profit(craftName, itemList, price, amount, nameList, prices);
		
		// do/while loop until the name introduced exist in the file "itemCrafts.txt"

		do
		{
			do
			{
				cout << endl << endl << "Introduce the item to craft: ";
				cin >> itemName;

				// The if is used to search if the item introduced exists int the file "prices.txt"
				// if it exists, found is set to true and the loop stops

				if (itemName > 0 && itemName - 1 < craftName.size())
					found = true;

				// If it is not found an error message is shown saying that the introduced item does not exist
				// if the user wants to leave without knowing any recipe he can introduce a slash

				else
					cout << endl << "Error: Item not found. If you want to leave introduce a -1: ";
			} while (!found && itemName != -1);

			// If the user selected an existing item, it shows the materials required for the recipe;

			if (itemName != -1)
				showMaterials(craftName[itemName - 1], itemList, amount);
		} while (itemName != -1);
		break;

	// Adds a new recipe | item name + materials + amount

	case 4:
		addCraft(nameList, prices, craftName, itemList, price, amount);
		break;

	// Change the prices of all items, there is an option to keep it the same for some items

	case 5:
		setAllPrices(nameList, prices);		
		addPriceFile(nameList, prices);
		break;
	default:
		break;
	}
}

/*
	Añadir una forma de quitar materiales en las recetas al momento de confirmarlas por si te has equivocado
*/