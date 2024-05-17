#include "prices.h"

/*
	The function searchs if a string is inside a vector
	If it is the function returns its index
	If not, it returns a -1
*/

int stringInArray(const string& s, vector<string>& nameList)
{

	// Auxiliar bool for loops

	bool found = false;

	// Auxiliar integer for loops

	int i = 0;
	
	// Loop to search for the string

	while (!found && i < nameList.size())
	{
		if (nameList[i] == s)
			found = true;
		else
			i++;
	}

	// If it is not found, the auxiliar i which represents the index is changed to a -1
	if (!found)
		i = -1;
	return i;
}

/*
	Method that reorganises the nameList vector alphabetically
*/

void ABC(vector<string>& nameList, vector<int>& prices)
{
	// Auxiliar vectors with the size of its corresponding one
	// The auxiliar vectors are swapped with the vectors received as parameters

	vector<string> stringAux;
	stringAux.resize(nameList.size());
	swap(nameList, stringAux);
	vector<int> nameAux;
	nameAux.resize(nameList.size());
	swap(prices, nameAux);

	// Auxiliar string with the min value

	string min = "ZZZ";

	// Auxiliar integer that will save the index of the position changed

	int index = 0;

	// Auxiliar bool for loops

	bool found = false;

	//

	for (int j = 0; j < nameList.size(); j++)
	{

		// For loop to search for the smallest string value

		for (int i = 0; i < nameList.size(); i++)
		{

			// If to initialise min as a value of stringAux
			// It only enters once when a valid value of stringAux is found

			if (stringAux[i] != "" && !found)
			{
				min = stringAux[i];
				index = i;
				found = true;
			}

			// If that compares the auxiliar min and each string of stringAux
			// It only enters if the value of stringAux[i] is valid

			if (min.compare(stringAux[i]) > 0 && (stringAux[i] != ""))
			{
				min = stringAux[i];
				index = i;
			}
		}

		// Vectors are filled with the min value each loop

		nameList[j] = stringAux[index];
		prices[j] = nameAux[index];

		// Auxiliar variables are restarted

		stringAux[index] = "";
		min = "";
		found = false;
	}
}

/*
	Method to change the price of an specific item on "prices.txt"
*/

void setPrices(vector<string>& nameList, vector<int>& prices)
{

	// Auxiliar bool for loops

	bool stop = false;

	// Auxiliar string to read user's inputs

	string name = "";

	// Auxiliar integer to save the position of where the price has to change

	int index = 0;

	// While loop that asks the user an item name until a dash is introduced

	while (!stop)
	{
		cout << "Introduce an item name / a dash to stop:" << endl;
		cin >> name;
		if (name == "-")
			stop = true;

		// If a dash has not been introduced the item name is searched in nameList 
		// and if found the price is changed

		else
		{
			index = stringInArray(name, nameList);

			// Only enters if the item is found

			if (index != -1)
			{
				cout << "Introduce a price:" << endl;
				cin >> prices[index];
			}
		}
	}
}

/*
	Method to change the price of every item on "prices.txt"
*/

void setAllPrices(vector<string>& nameList, vector<int>& prices)
{

	// Auxiliar integer to save the input introduced by the user

	int price;

	cout << "If you do not want to change the price write a 0" << endl;

	// For loop to change the prices of every item

	for (int i = 0; i < nameList.size(); i++)
	{

		// If the price of the item was 0 it cannot change

		if (prices[i] != 0)
		{
			cout << endl << "Select a new price for " << nameList[i] << ": ";
			cin >> price;
			if (price != 0)
				prices[i] = price;
		}
	}
}

void addItems(vector<string>& nameList, vector<int>& prices)
{
	bool stop = false;
	string name = "";
	int index = 0, price;
	while (!stop)
	{
		cout << endl << "Introduce an item name / a dash to stop: ";
		cin >> name;
		if (name == "-")
			stop = true;
		else
		{
			nameList.push_back(name);
			cout << "Introduce a price: ";
			cin >> price;
			prices.push_back(price);
		}
	}
}

void addPriceFile(vector<string>& nameList, vector<int>& prices)
{
	ABC(nameList, prices);
	ofstream file;
	file.open("prices.txt");
	if (file.is_open())
	{
		for (int i = 0; i < nameList.size(); i++)
			file << nameList[i] << " " << prices[i] << endl;
	}
	file.close();
}

void getPrices(vector<string>& nameList, vector<int>& prices)
{
	int aux;
	ifstream file;
	file.open("prices.txt");
	if (file.is_open())
	{
		string name;
		int price;
		while (file >> name >> price)
		{
			nameList.push_back(name);
			prices.push_back(price);
		}
	}
	file.close();
}