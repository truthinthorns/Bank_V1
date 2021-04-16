#pragma once
#include <string>
class Person
{
private:
	int ID;
	std::string primaryAccHolder;
	std::string secondaryAccHolder;
	double funds;

public:
	int getID() { return ID; }
	std::string getPrimaryName() { return primaryAccHolder; }
	std::string getSecondaryName() { return secondaryAccHolder; }
	double getFunds() { return funds; }

	void setPrimaryName(std::string name) { this->primaryAccHolder = name; }
	void setSecondName(std::string name) { this->secondaryAccHolder = name; }
	bool withdraw(double amt) 
	{ 
		if (funds >= amt)
		{
			this->funds -= amt;
			return true;
		}
		return false;
	}
	void deposit(double amt) { this->funds += amt; }

	Person(int ID, std::string name, double funds)
	{
		this->ID = ID;
		this->primaryAccHolder = name;
		this->funds = funds;
	}

	Person(int ID, std::string primary,std::string second, double funds)
	{
		this->ID = ID;
		this->primaryAccHolder = primary;
		this->secondaryAccHolder = second;
		this->funds = funds;
	}
};