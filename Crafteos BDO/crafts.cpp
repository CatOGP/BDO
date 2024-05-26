#include "crafts.h"
#include "prices.h"

/*
	The method adds a recipe onto the file "crafts.txt"
*/

void addCraft(vector<string>& nameList, vector<int>& prices, vector<string>& craftNames, vector<string>& itemList, vector<int>& price, vector<int>& amount)
{

	// stop and confirmed are used in loops in order to finish them

	bool stop = false, confirmed = false;

	// Auxiliar vectors needed to copy and reorganise the ones received as parameters

	vector<string> nameAuxVector;
	vector<int> amountAuxVector;
	vector<int> amountCraftedAuxVector;

	// Auxiliar strings to save the input introduced by the user 

	string craftName = "", answer = "", nameAux = "";

	// Auxiliar ints to save the input introduced by the user

	int index = 0, i = 0, amountAux = 0, amountCrafted = 0;	

	// While loop used to add the recipe, it only ends when a dash is introduced
		
	while (!stop)
	{

		// Ask the user to introduce the name of the recipe

		cout << endl << "Introduce the item / a dash to stop: ";
		cin >> craftName;
		cout << endl << "How many are crafted each time?" ;
		cin >> amountCrafted;

		// Looking if it has to stop as a dash was introduced 

		if (craftName == "-")
			stop = true;
		else
		{

			// Do / While loop used to introduce every material and amount of the recipe. Same as before, it ends with a dash.

			do
			{

				// Asking for the name of the material

				cout << endl << "Introduce a material / a dash to stop: ";
				cin >> nameAux;

				// Looking if it has to stop as a dash was introduced 

				if (nameAux == "-")
					stop = true;
				else
				{

					// It searchs the material id on the vector nameList to get its price
					// then it is added to the price vector

					index = stringInArray(nameAux, nameList);
					if (index != -1)
					{
						nameAuxVector.push_back(nameAux);

						// Asking for the material amount

						cout << "Introduce the amount: ";
						cin >> amountAux;
						amountAuxVector.push_back(amountAux);
						i++;
					}

					// If the material selected is not in the item lsit "prices.txt" an error message is shown
					else
					{
						cout << "Error: The item is not registered" << endl;
					}
				}
			} while (!stop);
			stop = false;
		}

		// Only enters if there has been no dash introduced at the start
		// It shows the recipe added and then asks a confirmation

		if (!stop)
		{
			cout << "Is this the wanted recipe? " << endl << endl;
			cout << " - " << craftName << ":" << endl;
			for (int j = 0; j < i; j++)
			{
				cout << "     " << nameAuxVector[j] << " " << amountAuxVector[j] << "x" << endl;
			}
			cout << endl << "Introduce Y to confirm: ";
			cin >> answer;
			if (answer == "Y" || answer == "y")
				confirmed = true;
			else
				stop = true;
		}

		// Only enters if the recipe has been confirmed
		// Writes the new recipe in "crafts.txt" and "craftsAux.txt"

		if (confirmed)
		{
			
			// The vector craftNames gets a list of every recipe name "itemCraft.txt"

			getItemList(craftNames, amountCraftedAuxVector);

			// Writes every recipe on "craftsAux.txt"
			// It first writes the previous recipes, then the new one 

			ofstream file;
			file.open("craftsAux.txt");
			if (file.is_open())
			{

				// Loop to write the old recipes

				for (int z = 0; z < craftNames.size(); z++)
				{
					file << "- " << craftNames[z] << " :" << endl;
					crafts(craftNames[z], itemList, price, amount, prices);
					for (int j = 0; j < itemList.size(); j++)
					{
						file << itemList[j] << " " << amount[j] << endl;
					}
				}

				// New recipe 

				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{ 
					file << nameAuxVector[j] << " " << amountAuxVector[j] << endl;
				}
				cout << endl;
			}
			file.close();

			// Writes every recipe on "crafts.txt"
			// It first writes the previous recipes, then the new one 

			file.open("crafts.txt");
			if (file.is_open())
			{

				// Loop to write the old recipes

				for (int z = 0; z < craftNames.size(); z++)
				{
					file << "- " << craftNames[z] << " :" << endl;
					craftsAux(craftNames[z], itemList, price, amount, prices);
					for (int j = 0; j < itemList.size(); j++)
					{
						file << itemList[j] << " " << amount[j] << endl;
					}
				}
				
				// New recipe 

				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{
					file << nameAuxVector[j] << " " << amountAuxVector[j] << endl;
				}
				cout << endl;
			}
			file.close();

			// Adds the recipe name on "itemCrafts.txt"

			file.open("itemCrafts.txt");
			if (file.is_open())
			{
				for(int i = 0; i < craftNames.size(); i++)
					file << craftNames[i] << " " << amountCraftedAuxVector[i] << endl;
				file << craftName << " " << amountCrafted << endl;
			}
			file.close();
			stop = true;
			confirmed = false;
		}
	}
}

/*
	The method searchs the price of the item name received as a parameter and returns it as an int
*/

int searchItemPrice(const string& itemName, vector<int>& prices)
{

	// stop is used in loops in order to finish them 

	bool found = false;

	// Auxiliar ints 

	int i = 0, price = 0;;

	// Auxiliar string

	string stringAux;

	ifstream file;
	file.open("prices.txt");
	if (file.is_open())
	{

		// While loop to search for the price of the item

		while (!found && i < (prices.size() * 2))
		{

			// It saves every string of the file in stringAux and then checks if it matches with the one received

			file >> stringAux;
			if (itemName == stringAux)
			{

				// The price is next to the string in the file, so after reading the name it directly reads the price

				file >> price;
				found = true;
			}
			else
				i++;
		}
	}
	file.close();
	return price;
}

/*
	crafts method charges the vectors itemList, price and amount with the information 
	needed for the recipe of the itemName received as a parameter
*/

void crafts(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices)
{

	// The vectors are emptied

	itemList.clear();
	price.clear();
	amount.clear();

	// Auxiliar strings for the recipe name, the material name and to read the : next to the recipe name in the txt

	string nameAux = "", aux = "", itemAux = "";

	// Auxiliar for loops

	bool found = false;

	// Auxiliar integers for the amount vector and for loops

	int i = 0,  amountAux = 0;

	ifstream file;
	file.open("crafts.txt");
	if (file.is_open())
	{

		// Loop to search for the recipe name on "crafts.txt"

		while (!found && !file.eof())
		{
			file >> nameAux;
			if (nameAux == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}

		// When the recipe is found it adds the materials and amount to the vectors

		if (found)
		{
			while (itemAux != "-" && !file.eof())
			{
				file >> itemAux >> amountAux;
				if (itemAux != "-")
				{
					if (!count(itemList.begin(), itemList.end(), itemAux))
					{
						itemList.push_back(itemAux);
						amount.push_back(amountAux);
					}
					i++;
				}
			}
		}
	}
	file.close();

	// For loop to search for the material prices and add them to the vector
	
	for (int i = 0; i < itemList.size(); i++)
		price.push_back(searchItemPrice(itemList[i], prices));
}

void craftsAux(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices)
{
	// The vectors are emptied

	itemList.clear();
	price.clear();
	amount.clear();

	// Auxiliar strings for the recipe name, the material name and to read the : next to the recipe name in the txt

	string nameAux = "", aux = "", itemAux = "";

	// Auxiliar for loops

	bool found = false;

	// Auxiliar integers for the amount vector and for loops

	int i = 0, amountAux = 0;

	ifstream file;
	file.open("craftsAux.txt");
	if (file.is_open())
	{

		// Loop to search for the recipe name on "craftsAux.txt"

		while (!found && !file.eof())
		{
			file >> nameAux;
			if (nameAux == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}
		
		// When the recipe is found it adds the materials and amount to the vectors
		
		if (found)
		{

			// The search ends when it reaches the next recipe "-" or when there is nothing else to read

			while (itemAux != "-" && !file.eof())
			{
				file >> itemAux >> amountAux;
				if (itemAux != "-")
				{
					if (!count(itemList.begin(), itemList.end(), itemAux))
					{
						itemList.push_back(itemAux);
						amount.push_back(amountAux);
					}
					i++;
				}
			}
		}
	}
	file.close();

	// For loop to search for the material prices and add them to the vector

	for (int i = 0; i < itemList.size(); i++)
		price.push_back(searchItemPrice(itemList[i], prices));
}

/*
	The method charges craftName vector with the names of every recipe in the file "itemCraft.txt"
*/

void getItemList(vector<string>& craftName, vector<int>& amountCraft)
{
	ifstream file;
	string nameAux, nameAux2;
	int amountAux;
	file.open("itemCrafts.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> nameAux >> amountAux;

			// Check if it is reapeted just in case

			if (nameAux2 != nameAux)
			{
				craftName.push_back(nameAux);
				amountCraft.push_back(amountAux);
				nameAux2 = nameAux;
			}
		}
	}
	file.close();
}

/*
	The function recieves a number and transforms it into a string with commas added every 3 digits
*/

string numToString(int n)
{
	stringstream ss;
	ss << n;
	string numStr = ss.str();
	bool cicle = false;

	// If the number if bigger than 0 we add it every 3 numbers until the first one

	if (n > 0)
	{
		for (int i = numStr.size() - 3; i > 0; i -= 3)
			numStr.insert(i, ",");
	}

	// If the number if smaller than 0 we add it every 3 numbers until the first one + 1, because there is a minus in the first position

	if (n < 0)
	{
		for (int i = numStr.size() - 3; i > 1; i -= 3)
			numStr.insert(i, ",");
	}
	return numStr;
}

/*
	The method reorganises the profit vector from bigger to smaller
*/

void reorder(vector<string>& craftName, vector<int>& profit, vector<int>& rawPrice)
{

	// Auxiliar vectors with the size of its corresponding vector to organise them 
	// from bigger to smaller and then doing a swap

	vector<string> stringAux;
	stringAux.resize(craftName.size());
	vector<int> nameAux;
	nameAux.resize(profit.size());
	vector<int> rawPriceAux;
	rawPriceAux.resize(rawPrice.size());

	// Auxiliar integers to save the max profit value and its index

	int max, index;

	// For loops to search for the max profit

	for (int j = 0; j < craftName.size(); j++)
	{
		max = 0, index = 0;
		for (int i = 0; i < profit.size(); i++)
		{
			if (max < profit[i])
			{
				max = profit[i];
				index = i;
			}
		}

		// Searching for negatives profits

		if (max == 0)
		{
			for (int i = 0; i < profit.size(); i++)
			{
				if (max > profit[i])
				{
					max = profit[i];
					index = i;
				}
			}
		}

		// After doing the search each value is added to its corresponding auxiliar vector

		nameAux[j] = max;
		stringAux[j] = craftName[index];
		rawPriceAux[j] = rawPrice[index];

		// The position that had the max value is changed to a 0 to avoid search errors

		profit[index] = 0;
	}

	// Swapping the auxiliar vectors to the real ones

	swap(nameAux, profit);
	swap(stringAux, craftName);
	swap(rawPriceAux, rawPrice);
}

/*
	Method that prints on the screen the profit of each recipe next to the total value 
	and its organised from most profitable to the least
*/

void profit(vector<string>& craftName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<string> nameList, vector<int> prices)
{

	// Auxiliar integers 

	int index = 0, total = 0;

	// Auxiliar vectors used to save the total value and the profit of each recipe

	vector<int> rawPrice;
	vector<int> amountCraft;
	vector<int> profit;

	// We charge the craftName vector with all possible recipes

	getItemList(craftName, amountCraft);

	// For loop to get every total value and profit of each recipe in craftName vector

	for (int i = 0; i < craftName.size(); i++)
	{

		// Index has the position of the value of the recipe name saved

		index = stringInArray(craftName[i], nameList);
		if (index != -1)
		{

			// crafts charges the vectors with the materials, amounts and prices

			crafts(craftName[i], itemList, price, amount, prices);

			// Value of the recipe is added to its vector

			rawPrice.push_back(prices[index]);
			for (int j = 0; j < itemList.size(); j++)
				total += price[j] * amount[j];

			// Profit of the recipe is added to its vector

			profit.push_back((rawPrice[i] * 0.845) * amountCraft[i] - total);
		}

		// If the recipe value is not found on "prices.txt" an error message is shown 

		else
		{
			cout << endl << "Error: Introduce " << craftName[i] << " in the item list with its price";
		}
		total = 0;
	}

	// Reorganising the profit vector from bigger to smaller

	reorder(craftName, profit, rawPrice);

	// For loop to show on the screen the profits and total values

	for (int i = 0; i < craftName.size(); i++)
		cout << endl << i + 1 <<  " - " << craftName[i] << " --> " << numToString(profit[i]) << " | " << numToString(rawPrice[i]) << endl;
}

/*
	The method shows on the screen the materials and amounts needed for the craft received as a parameter
*/

void showMaterials(const string& itemName, vector<string> itemList, vector<int> amount)
{
		
	// The vectors are emptied
	itemList.clear();
	amount.clear();

	// Auxiliar strings used to add information to vectors

	string nameAux = "", aux = "", itemAux = "";

	// Auxiliar bool for loops

	bool found = false;

	// Auxiliar integers for loops and to add information to vectors

	int i = 0, amountAux = 0;

	ifstream file;
	file.open("crafts.txt");
	if (file.is_open())
	{

		// The item is searched in "crafts.txt"

		while (!found && !file.eof())
		{
			file >> nameAux;
			if (nameAux == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}

		// If it is found itemList and amount vectors are charged with the information needed

		if (found)
		{
			while (itemAux != "-" && !file.eof())
			{
				file >> itemAux >> amountAux;
				if (itemAux != "-")
				{
					if (!count(itemList.begin(), itemList.end(), itemAux))
					{
						itemList.push_back(itemAux);
						amount.push_back(amountAux);
					}
					i++;
				}
			}
		}

		// For loop that shows on the screen the materials and amounts

		cout << endl << "Materials required to craft " << itemName << ":" << endl;
		for (int i = 0; i < itemList.size(); i++)
		{
			cout << endl << " --> " << itemList[i] << " " << amount[i] << "x";
		}
	}
}