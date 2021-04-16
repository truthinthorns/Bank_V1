#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <map>
#include <fstream>
#include "Person.h"

class Bank
{
private:
	std::map <int, Person*> personMap;
	double vaultAmt;

public:
	Bank()
	{
		vaultAmt = (double)INT16_MAX;
	}

	void insertPerson(std::string name, int ID, double funds)
	{
		Person* p = new Person(ID, name, funds);
		personMap.emplace(ID, p);
	}
	
	void insertPerson(std::string primary, std::string secondary, int ID, double funds)
	{
		Person* p = new Person(ID, primary,secondary, funds);
		personMap.emplace(ID, p);
	}

	Person* findPerson(int ID)
	{
		auto itr = personMap.find(ID);
		if (itr != personMap.end())
			return itr->second;
		return nullptr;
	}

	bool findID(int ID)
	{
		return personMap.find(ID) != personMap.end();
	}

	Person *createPerson(std::string name, double deposit)
	{
		srand((unsigned int)time(NULL));
		int ID = rand() % 10000 + 1;
		while (findID(ID))
		{
			ID = rand() % 10000 + 1;
		}
		Person* p = new Person(ID, name, deposit);
		personMap.emplace(ID,p);
		std::cout << "Account ID is: " << ID << std::endl;
		return p;
	}

	Person* createPerson(std::string primary, std::string second , double deposit)
	{
		srand((unsigned int)time(NULL));
		int ID = rand() % 10000 + 1;
		while (findID(ID))
		{
			ID = rand() % 10000 + 1;
		}
		Person* p = new Person(ID, primary,second, deposit);
		personMap.emplace(ID, p);
		std::cout << "Account ID is: " << ID << std::endl;
		return p;
	}

	void removeEmplaceSamePerson(int ID,std::string second)
	{
		auto itr = personMap.find(ID);
		Person* p = new Person(ID, itr->second->getPrimaryName(), second, itr->second->getFunds());
		personMap.erase(itr);
		personMap.emplace(ID,p);
	}

	void removeEmplaceSamePerson(int ID)
	{
		auto itr = personMap.find(ID);
		Person* p = new Person(ID, itr->second->getPrimaryName(), itr->second->getFunds());
		personMap.erase(itr);
		personMap.emplace(ID, p);
	}

	void print()
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(2);

		auto itr = personMap.begin();
		while (itr != personMap.end())
		{
			std::cout << "Primary Account Holder Name: " << itr->second->getPrimaryName();
			if (itr->second->getSecondaryName() != "")
				std::cout << "\nSecondary Account Holder Name: " << itr->second->getSecondaryName();
			std::cout << "\nAccount ID: " << itr->second->getID();
			std::cout << "\nFunds: $" << itr->second->getFunds();
			std::cout << "\n\n";
			itr++;
		}
	}
	
	void printPerson(int ID)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(2);

		auto itr = personMap.find(ID);
		if (itr != personMap.end())
		{
			std::cout << "Primary Account Holder Name: " << itr->second->getPrimaryName();
			if (itr->second->getSecondaryName() != "")
				std::cout << "\nSecondary Account Holder Name: " << itr->second->getSecondaryName();
			std::cout << "\nAccount ID: " << itr->second->getID();
			std::cout << "\nFunds: $" << itr->second->getFunds();
			std::cout << "\n";
		}
	}

	void writeToFile(std::ofstream& file)
	{
		auto itr = personMap.begin();
		while (itr != personMap.end())
		{
			if (itr != personMap.begin())
			{
				if (itr->second->getSecondaryName() != "")
					file << "\n" << itr->second->getPrimaryName() << "*" << itr->second->getSecondaryName() << "*" << itr->second->getID() << "*" << itr->second->getFunds();
				else
					file <<  "\n" << itr->second->getPrimaryName() << "*" << itr->second->getID() << "*" << itr->second->getFunds();
			}
			else
			{
				if (itr->second->getSecondaryName() != "")
					file << itr->second->getPrimaryName() << "*" << itr->second->getSecondaryName() << "*" << itr->second->getID() << "*" << itr->second->getFunds();
				else
					file << itr->second->getPrimaryName() << "*" << itr->second->getID() << "*" << itr->second->getFunds();
			}
			itr++;
		}
	}
};