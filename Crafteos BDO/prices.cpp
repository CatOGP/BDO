#include "prices.h"

int stringInArray(const string& s, vector<string>& nameList)
{
	bool found = false;
	int i = 0;
	while (!found && i < nameList.size())
	{
		if (nameList[i] == s)
			found = true;
		i++;
	}
	if (found)
		return i - 1;
	else
		return -1;
}

void ABC(vector<string>& nameList, vector<int>& prices)
{
	vector<string> auxS;
	auxS.resize(nameList.size());
	swap(nameList, auxS);
	vector<int> auxN;
	auxN.resize(nameList.size());
	swap(prices, auxN);
	string min = "ZZZ";
	int index = 0;
	bool found = false;
	for (int j = 0; j < nameList.size(); j++)
	{
		for (int i = 0; i < nameList.size(); i++)
		{
			if (auxS[i] != "" && !found)
			{
				min = auxS[i];
				index = i;
				found = true;
			}
			if (min.compare(auxS[i]) > 0 && (auxS[i] != ""))
			{
				min = auxS[i];
				index = i;
			}
		}
		nameList[j] = auxS[index];
		prices[j] = auxN[index];
		auxS[index] = "";
		min = "";
		found = false;
	}
}

void setPrices(vector<string>& nameList, vector<int>& prices)
{
	bool stop = false;
	string name = "";
	int index = 0;
	while (!stop)
	{
		cout << "Introduce an item name / a dash to stop:" << endl;
		cin >> name;
		if (name == "-")
			stop = true;
		else
		{
			index = stringInArray(name, nameList);
			if (index != -1)
			{
				cout << "Introduce a price:" << endl;
				cin >> prices[index];
			}
		}
	}
}

void setAllPrices(vector<string>& nameList, vector<int>& prices)
{
	int price;
	cout << "If you do not want to change the price write a 0" << endl;
	for (int i = 0; i < nameList.size(); i++)
	{
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