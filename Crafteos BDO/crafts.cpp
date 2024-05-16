#include "crafts.h"
#include "prices.h"

void addCraft(vector<string>& nameList, vector<int>& prices, vector<string>& craftNames, vector<string>& itemList, vector<int>& price, vector<int>& amount)
{
	bool stop = false, confirmed = false;
	vector<string> nameAux;
	vector<int> priceAux;
	vector<int> amountAux;
	string craftName = "", answer = "", auxN = "";
	int index = 0, i = 0, auxP = 0, auxA = 0;	
	while (!stop)
	{
		cout << endl << "Introduce the item / a dash to stop: ";
		cin >> craftName;
		if (craftName == "-")
			stop = true;
		else
		{
			do
			{
				cout << endl << "Introduce a material / a dash to stop: ";
				cin >> auxN;
				if (auxN == "-")
					stop = true;
				else
				{
					index = stringInArray(auxN, nameList);
					if (index != -1)
					{
						nameAux.push_back(auxN);
						auxP = prices[index];
						priceAux.push_back(auxP);
						cout << "Introduce the amount: ";
						cin >> auxA;
						amountAux.push_back(auxA);
						i++;
					}
					else
					{
						cout << "Error: The item is not registered" << endl;
					}
				}
			} while (!stop);
			stop = false;
		}
		if (!stop)
		{
			cout << "Is this the wanted recipe? " << endl << endl;
			cout << " - " << craftName << ":" << endl;
			for (int j = 0; j < i; j++)
			{
				cout << "     " << nameAux[j] << " " << priceAux[j] << " " << amountAux[j] << "x" << endl;
			}
			cout << endl << "Introduce Y to confirm: ";
			cin >> answer;
			if (answer == "Y" || answer == "y")
				confirmed = true;
			else
				stop = true;
		}
		if (confirmed)
		{
			getItemList(craftNames);
			ofstream file;
			file.open("craftsAux.txt");
			if (file.is_open())
			{
				for (int z = 0; z < craftNames.size(); z++)
				{
					file << "- " << craftNames[z] << " :" << endl;
					crafts(craftNames[z], itemList, price, amount, prices);
					for (int j = 0; j < itemList.size(); j++)
					{
						file << itemList[j] << " " << price[j] << " " << amount[j] << endl;
					}
				}
				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{ 
					file << nameAux[j] << " " << priceAux[j] << " " << amountAux[j] << endl;
				}
				cout << endl;
			}
			file.close();
			file.open("crafts.txt");
			if (file.is_open())
			{
				for (int z = 0; z < craftNames.size(); z++)
				{
					file << "- " << craftNames[z] << " :" << endl;
					craftsAux(craftNames[z], itemList, price, amount, prices);
					for (int j = 0; j < itemList.size(); j++)
					{
						file << itemList[j] << " " << price[j] << " " << amount[j] << endl;
					}
				}
				file << "- " << craftName << " :" << endl;
				for (int j = 0; j < i; j++)
				{
					file << nameAux[j] << " " << priceAux[j] << " " << amountAux[j] << endl;
				}
				cout << endl;
			}
			file.close();
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

int searchItemPrice(const string& itemName, vector<int>& prices)
{
	bool found = false;
	int i = 0, price = 0;;
	string auxS;
	ifstream file;
	file.open("prices.txt");
	if (file.is_open())
	{
		while (!found && i < (prices.size() * 2))
		{
			file >> auxS;
			if (itemName == auxS)
			{
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