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
					getCraft(craftNames[z], itemList, price, amount);
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
					getCraftAux(craftNames[z], itemList, price, amount);
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

void getCraft(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount)
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
				file >> auxI >> auxP >> auxA;
				if (auxI != "-")
				{
					itemList.push_back(auxI);
					price.push_back(auxP);
					amount.push_back(auxA);
					i++;
				}
			}
		}
	}
	file.close();
}

void getCraftAux(const string& itemName, vector<string>& itemList, vector<int>& price, vector<int>& amount)
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
				file >> auxI >> auxP >> auxA;
				if (auxI != "-")
				{
					itemList.push_back(auxI);
					price.push_back(auxP);
					amount.push_back(auxA);
					i++;
				}
			}
		}
	}
	file.close();
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
	std::string numStr = ss.str();
	for (int i = numStr.size() - 3; i > 0; i -= 3) {
		numStr.insert(i, ",");
	}
	return numStr;
}

void reorder(vector<string>& craftName, vector<int>& profit)
{
	vector<string> auxS;
	auxS.resize(craftName.size());
	vector<int> auxN;
	auxN.resize(profit.size());
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
		profit[index] = 0;
	}
	swap(auxN, profit);
	swap(auxS, craftName);
}

void profit(vector<string>& craftName, vector<string>& itemList, vector<int>& price, vector<int>& amount, vector<string> nameList, vector<int> prices)
{
	int index = 0, total = 0, rawPrice = 0;
	vector<int> profit;
	getItemList(craftName);
	for (int i = 0; i < craftName.size(); i++)
	{
		index = stringInArray(craftName[i], nameList);
		if (index != -1)
		{
			getCraft(craftName[i], itemList, price, amount);
			rawPrice = prices[index];
			for (int j = 0; j < itemList.size(); j++)
				total += price[j] * amount[j];
			profit.push_back((rawPrice - total) * 0.845);
		}
		else
		{
			cout << endl << "Error: Introduce " << craftName[i] << " in the item list with its price";
		}
		total = 0;
		rawPrice = 0;
	}
	reorder(craftName, profit);
	for (int i = 0; i < craftName.size(); i++)
	{

		cout << endl << " - " << craftName[i] << " --> " << numToString(profit[i]) << endl;
		for (int k = 0; k < itemList.size() - 1; k++)
		{
			cout << "	--> " << itemList[k] << " " << amount[k] << "x" << endl;
		}
	}
}