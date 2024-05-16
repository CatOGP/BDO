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

int main()
{
	// Vectors used mainly in prices functions

	// prices has the information of each item price
	// nameList has the information of each item name
	// They both use the same index for each item

	vector<int> prices;
	vector<string> nameList;

	// Vectors used mainly in crafts functions
	
	// craftName has the name of every craftable item
	
	vector<string> craftName;

	// itemList is used to save all the materials used for one craft, it is deleted after each craft
	// price is used to save the price of each material used for one craft, it is deleted after each craft
	// amount is used to save the amount of each material used for one craft, it is deleted after each craft
	// They all share the same index for each material item

	vector<string> itemList;
	vector<int> price;
	vector<int> amount;

	// option is used to select which option of the menu is selected

	int option = 0;

	// used in bucles to see if it is a possible answer

	bool found = false;

	// answer is used in case 3 to save the name of the item recipe chosen

	string answer = "";

	// getPrices initializes nameList and prices with a file that contains every item added next to its price "itemCrafts.txt"

	getPrices(nameList, prices);

	// do/while loop to choose a possible opion of the menu

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

		// In setPrices you select an item name and then change its price, this process repeats until you decide to stop
		
		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		setPrices(nameList, prices); 

		// addPriceFile adds to the file "prices.txt" all the item names with the prices changed
		
		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		addPriceFile(nameList, prices);
		break;

	// Add an item to the txt with the items | name + price

	case 2: 

		// In addItems you add an item name its price, this process repeats until you decide to stop
		
		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		addItems(nameList, prices);

		// addPriceFile adds to the file "prices.txt" all the item names with the prices changed
		
		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		addPriceFile(nameList, prices);
		break;

	// Shows how much profit you have with each craft, 
	// then it can show you the recipe of the selected one

	case 3:

		// The function profit calculates the profit of every item craft in the file "crafts.txt"

		// craftName is a vector with the names of all the possible recipes
		// itemList is a vector with the names of all the materials of one recipe
		// price is a vector with the prices of all the materials of one recipe
		// amount is a vector with the amounts of all the materials of one recipe

		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		profit(craftName, itemList, price, amount, nameList, prices);

		// After all the profits are shown on the screen, it asks the user if he wants to know any materials needed
		// It is confirmed using a Y or a y

		cout << endl << "Do you wanna know any recipe?";
		cout << endl << "   || Confirm with a Y ||" << endl;
		cin >> answer;

		// It continues only if the answer is a yes

		if (answer == "Y" || answer == "y")
		{

			// itemName is used to save the answer of the user of the name of the recipe

			string itemName = "";

			// do/while loop until the name introduced exist in the file "itemCrafts.txt"

			do
			{
				cout << endl << "Introduce the item to craft: ";
				cin >> itemName;
				
				// The if is used to search if the item introduced exists int the file "prices.txt"
				// if it exists, found is set to true and the loop stops
				
				// stringInArray is used to find out if the string itemName is in the vector craftName
				// it returns a -1 if it is not in it

				if (stringInArray(itemName, craftName) != -1)
					found = true;

				// If it is not found an error message is shown saying that the introduced item does not exist
				// if the user wants to leave without knowing any recipe he can introduce a slash

				else
					cout << endl << "Error: Item not found. If you want to leave introduce a " - ": ";
			} while (!found || itemName == "-");

			// If the user selected an existing item, it shows the materials required for the recipe;

			if (itemName != "-")

				// showMaterials is a method that shows all the materials required to craft an item

				// itemName is a string with the name of the desired item
				// itemList is a vector with the name of all the materials
				// amount is a vector with the amount of all the materials

				showMaterials(itemName, itemList, amount);
		}
		break;

	// Adds a new recipe | item name + materials + amount

	case 4:

		// Using addCraft the user can add one recipe to the file "crafts.txt"

		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index

		// craftName is a vector with the names of all the possible recipes
		// itemList is a vector with the names of all the materials of one recipe
		// price is a vector with the prices of all the materials of one recipe
		// amount is a vector with the amounts of all the materials of one recipe

		addCraft(nameList, prices, craftName, itemList, price, amount);
		break;

	// Change the prices of all items, there is an option to keep it the same for some items

	case 5:

		// In setAllPrices change the price of all the items, you can mantain its price by introducing the new one as a 0
		// The items that had previously a price of 0 are not asked to change

		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index 
		setAllPrices(nameList, prices);

		// addPriceFile adds to the file "prices.txt" all the item names with the prices changed

		// nameList is a vector with the name of all the items
		// prices is a vector witht the price of all the items
		// They both have the same index
		//  
		addPriceFile(nameList, prices);
		break;
	default:
		option = 0;
		break;
	}
}

/*
Melody Of Stars price changed
*/