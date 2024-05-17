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
	vector<int> priceAuxVector;
	vector<int> amountAuxVector;

	// Auxiliars strings to save the input introduced by the user 

	string craftName = "", answer = "", nameAux = "";

	// Auxiliar ints to save the input introduced by the user

	int index = 0, i = 0, priceAux = 0, amountAux = 0;	

	// While loop used to add the recipe, it only ends when a dash is introduced
		
	while (!stop)
	{

		// Ask the user to introduce the name of the recipe

		cout << endl << "Introduce the item / a dash to stop: ";
		cin >> craftName;

		// Looking if it has to stop as a dash was introduced 

		if (craftName == "-")
			stop = true;
		else
		{

			// Do/While loop used to introduce every material and amount of the recipe. Same as before, it ends with a dash.

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
						priceAux = prices[index];
						priceAuxVector.push_back(priceAux);

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
				cout << "     " << nameAuxVector[j] << " " << priceAuxVector[j] << " " << amountAuxVector[j] << "x" << endl;
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

			getItemList(craftNames);

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
						file << itemList[j] << " " << price[j] << " " << amount[j] << endl;
					}
				}

				// New recipe 

				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{ 
					file << nameAuxVector[j] << " " << priceAuxVector[j] << " " << amountAuxVector[j] << endl;
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
						file << itemList[j] << " " << price[j] << " " << amount[j] << endl;
					}
				}
				
				// New recipe 

				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{
					file << nameAuxVector[j] << " " << priceAuxVector[j] << " " << amountAuxVector[j] << endl;
				}
				cout << endl;
			}
			file.close();

			// Adds the recipe name on "itemCrafts.txt"

			file.open("itemCrafts.txt");
			if (file.is_open())
			{
				for(int i = 0; i < craftNames.size(); i++)
					file << craftNames[i] << endl;
				file << craftName << endl;
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
	
*/

void crafts(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices)
{
	itemList.clear();
	price.clear();
	amount.clear();
	string auxN = "", aux = "", auxI = "";
	bool found = false;
	int i = 0, auxP = 0, auxA = 0;
	ifstream file;
	file.open("crafts.txt");
	if (file.is_open())
	{
		while (!found && !file.eof())
		{
			file >> auxN;
			if (auxN == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}
		if (found)
		{
			while (auxI != "-" && !file.eof())
			{
				file >> auxI >> auxA;
				if (auxI != "-")
				{
					if (!count(itemList.begin(), itemList.end(), auxI))
					{
						itemList.push_back(auxI);
						amount.push_back(auxA);
					}
					i++;
				}
			}
		}
	}
	file.close();
	for (int i = 0; i < itemList.size(); i++)
		price.push_back(searchItemPrice(itemList[i], prices));
}

void craftsAux(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<int>& prices)
{
	itemList.clear();
	price.clear();
	amount.clear();
	string auxN = "", aux = "", auxI = "";
	bool found = false;
	int i = 0, auxP = 0, auxA = 0;
	ifstream file;
	file.open("craftsAux.txt");
	if (file.is_open())
	{
		while (!found && !file.eof())
		{
			file >> auxN;
			if (auxN == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}
		if (found)
		{
			while (auxI != "-" && !file.eof())
			{
				file >> auxI >> auxA;
				if (auxI != "-")
				{
					if (!count(itemList.begin(), itemList.end(), auxI))
					{
						itemList.push_back(auxI);
						amount.push_back(auxA);
					}
					i++;
				}
			}
		}
	}
	file.close();
	for (int i = 0; i < itemList.size(); i++)
		price.push_back(searchItemPrice(itemList[i], prices));
}

void getItemList(vector<string>& craftName)
{
	ifstream file;
	string auxN, aux2;
	file.open("itemCrafts.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> auxN;
			if (aux2 != auxN)
			{
				craftName.push_back(auxN);
				aux2 = auxN;
			}
		}
	}
	file.close();
}

string numToString(int n)
{
	stringstream ss;
	ss << n;
	string numStr = ss.str();
	bool cicle = false;
	if (n > 0)
	{
		for (int i = numStr.size() - 3; i > 0; i -= 3)
			numStr.insert(i, ",");
	}
	if (n < 0)
	{
		for (int i = numStr.size() - 3; i > 1; i -= 3)
			numStr.insert(i, ",");
	}
	return numStr;
}

void reorder(vector<string>& craftName, vector<int>& profit, vector<int>& rawPrice)
{
	vector<string> auxS;
	auxS.resize(craftName.size());
	vector<int> auxN;
	auxN.resize(profit.size());
	vector<int> rawPriceAux;
	rawPriceAux.resize(rawPrice.size());
	int max, index;
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
		auxN[j] = max;
		auxS[j] = craftName[index];
		rawPriceAux[j] = rawPrice[index];
		profit[index] = 0;
	}
	swap(auxN, profit);
	swap(auxS, craftName);
	swap(rawPriceAux, rawPrice);
}

void profit(vector<string>& craftName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<string> nameList, vector<int> prices)
{
	int index = 0, total = 0;
	vector<int> rawPrice;
	vector<int> profit;
	getItemList(craftName);
	for (int i = 0; i < craftName.size(); i++)
	{
		index = stringInArray(craftName[i], nameList);
		if (index != -1)
		{
			crafts(craftName[i], itemList, price, amount, prices);
			rawPrice.push_back(prices[index]);
			for (int j = 0; j < itemList.size(); j++)
				total += price[j] * amount[j];
			profit.push_back((rawPrice[i] - total) * 0.845);
		}
		else
		{
			cout << endl << "Error: Introduce " << craftName[i] << " in the item list with its price";
		}
		total = 0;
	}
	reorder(craftName, profit, rawPrice);
	for (int i = 0; i < craftName.size(); i++)
	{

		cout << endl << i + 1 <<  " - " << craftName[i] << " --> " << numToString(profit[i]) << " | " << numToString(rawPrice[i]) << endl;
	}
}

void showMaterials(const string& itemName, vector<string> itemList, vector<int> amount)
{
	itemList.clear();
	amount.clear();
	string auxN = "", aux = "", auxI = "";
	bool found = false;
	int i = 0, auxP = 0, auxA = 0;
	ifstream file;
	file.open("crafts.txt");
	if (file.is_open())
	{
		while (!found && !file.eof())
		{
			file >> auxN;
			if (auxN == itemName)
			{
				file >> aux;
				if (aux == ":")
				{
					found = true;
				}
			}
		}
		if (found)
		{
			while (auxI != "-" && !file.eof())
			{
				file >> auxI >> auxA;
				if (auxI != "-")
				{
					if (!count(itemList.begin(), itemList.end(), auxI))
					{
						itemList.push_back(auxI);
						amount.push_back(auxA);
					}
					i++;
				}
			}
		}
		cout << endl << "Materials required to craft " << itemName << ":" << endl;
		for (int i = 0; i < itemList.size(); i++)
		{
			cout << endl << " --> " << itemList[i] << " " << amount[i] << "x";
		}
	}
}