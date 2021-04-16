#pragma warning(disable : 4996)

#include <regex>
#include "Bank.h"

void menu()
{
	std::cout << "***************************\n";
	std::cout << "******Banking System*******\n\n";
	std::cout << "1) Create Account\n";
	std::cout << "2) Deposit/Withdraw\n";
	std::cout << "3) View Account\n";
	std::cout << "4) Edit Account\n";
	std::cout << "5) Print All Accounts\n";
	std::cout << "0) Exit Program\n";
	std::cout << "Option: ";
}

void checkDouble(std::string &input)
{
	std::string reg1 = "[0-9][0-9]*";
	std::string reg2 = "[0-9][0-9]*\\.[0-9]+";
	while (!std::regex_match(input, std::regex(reg1)) && !std::regex_match(input, std::regex(reg2)))
	{
		std::cout << "Must enter a numerical value! (decimals are okay)" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> input;
	}
}

void checkInteger(int &input)
{
	while (std::cin.fail()) {
		std::cout << "Must enter an integer!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> input;
	}
}

void readFileAndInsertPersons (std::ifstream &file, Bank &bank)
{
	std::string line;
	std::string arr[4];
	int ctr;

	if (file.good() && file.peek() != std::fstream::traits_type::eof()) {
		while (!file.eof())
		{
			ctr = 0;
			std::getline(file, line);
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (line[i] != '*')
					arr[ctr] += line[i];
				else
					ctr++;
			}
			if (ctr == 2)
				bank.insertPerson(arr[0], stoi(arr[1]), stod(arr[2]));
			else
				bank.insertPerson(arr[0], arr[1], stoi(arr[2]), stod(arr[3]));
			arr[0] = "";
			arr[1] = "";
			arr[2] = "";
			arr[3] = "";
		}
	}
	file.close();
}

int main()
{
	std::ofstream outFile;
	std::ofstream personFile;
	std::ifstream inFile("C:/Users/justw/Desktop/personList.txt");
	outFile.open("C:/Users/justw/Desktop/bankHistory.txt",std::ios_base::app);
	Bank bank = Bank();
	readFileAndInsertPersons(inFile, bank);
	personFile.open("C:/Users/justw/Desktop/personList.txt", std::ios_base::trunc);
	time_t currTime;
	tm localTime;
	int choice;
	std::string prim;
	std::string second;
	std::string funds;
	int ID = -1;
	Person* person;
	do
	{
		menu();
		std::cin >> choice;
		checkInteger(choice);
		switch (choice)
		{
		case 1:
		{
			system("cls");
			std::cout << "CREATE ACCOUNT\n";
			AccountCreation:
			std::cin.get();
			std::cout << "1) Primary Holder ONLY\n2) Primary AND Secondary Holders\nOption: ";
			std::cin >> choice;
			checkInteger(choice);
			if (choice == 1)
			{
				std::cout << "Enter name: ";
				std::cin.get();
				getline(std::cin, prim);
				std::cout << "Enter deposit amount: ";
				std::cin >> funds;
				checkDouble(funds);
				person = bank.createPerson(prim, std::stod(funds));
				currTime = time(nullptr);
				localTime = *localtime(&currTime);
				outFile << "\nAdded customer on: ";
				outFile << std::put_time(&localTime, "%m-%d-%Y at %H:%M:%S") << std::endl;
				outFile << "Name: " << prim << std::endl;
				outFile << "Account ID: " << person->getID() << std::endl;
				outFile << "Amount deposited: $" << funds << "\n";
				std::cout << "\n";
			}
			else if (choice == 2)
			{
				std::cin.get();
				std::cout << "Enter PRIMARY'S Name: ";
				getline(std::cin, prim);
				std::cout << "Enter SECONDARY'S Name: ";
				getline(std::cin, second);
				std::cout << "Enter deposit amount: ";
				std::cin >> funds;
				checkDouble(funds);
				person = bank.createPerson(prim, second, std::stod(funds));
				currTime = time(nullptr);
				localTime = *localtime(&currTime);
				outFile << "\nAdded customer on: ";
				outFile << std::put_time(&localTime, "%m-%d-%Y at %H:%M:%S") << std::endl;
				outFile << "Primary Name: " << prim << std::endl;
				outFile << "Secondary Name: " << second << std::endl;
				outFile << "Account ID: " << person->getID() << std::endl;
				outFile << "Amount deposited: $" << funds << "\n";
				std::cout << "\n";
			}
			else
			{
				std::cout << "Invalid Option!\n";
				std::cout << "\n";
				goto AccountCreation;
			}
			break;
		}
		case 2:
		{
			system("cls");
			std::cout << "DEPOSIT/WITHDRAW\n";
			DepWith:
			std::cout << "Enter ID: ";
			std::cin >> ID;
			checkInteger(ID);
			person = bank.findPerson(ID);
			if (person)
			{
				ChooseDepWith:
				std::cout << "1) Deposit\n2) Withdraw\nOption: ";
				std::cin >> choice;
				checkInteger(choice);
				if (choice == 1)
				{
					std::cout << "Enter amount to deposit: $";
					std::cin >> funds;
					checkDouble(funds);
					person->deposit(stod(funds));
					currTime = time(nullptr);
					localTime = *localtime(&currTime);
					outFile << "\nAccount number " << ID << " deposited $" << funds << " on: ";
					outFile << std::put_time(&localTime, "%m-%d-%Y at %H:%M:%S\n") << std::endl;
					system("cls");
					std::cout << "Successfully deposited $" << funds << " into account number " << ID;
					std::cout << "\n";
				}
				else if (choice == 2)
				{
					EnterAmt:
					std::cout << "Enter amount to withdraw: $";
					std::cin >> funds;
					checkDouble(funds);
					if (person->withdraw(stod(funds)))
					{
						currTime = time(nullptr);
						localTime = *localtime(&currTime);
						outFile << "\nAccount number " << ID << " withdrew $" << funds << " on: ";
						outFile << std::put_time(&localTime, "%m-%d-%Y at %H:%M:%S\n") << std::endl;
						system("cls");
						std::cout << "Successfully withdrew $" << funds << " into account number " << ID;
						std::cout << "\n";
					}
					else
					{
						std::cout << "Insufficient funds!";
						goto EnterAmt;
					}
				}
				else
				{
					std::cout << "Invalid Option!\n";
					goto ChooseDepWith;
				}
			}
			else
			{
				std::cout << "Nobody was found with that ID.\n";
				goto DepWith;
			}
			std::cin.get();
			std::cout << "\n";
			break;
		}
		case 3:
		{
			system("cls");
			std::cout << "VIEW ACCOUNT\n";
			ViewAcct:
			std::cout << "Enter ID: ";
			std::cin >> ID;
			checkInteger(ID);
			if (bank.findPerson(ID))
				bank.printPerson(ID);
			else
			{
				std::cout << "Nobody was found with that ID.\n";
				goto ViewAcct;
			}
			std::cout << "\n";
			break;
		}
		case 4:
		{
			system("cls");
			std::cout << "EDIT ACCOUNT\n";
			EditAcct:
			std::cout << "Enter ID: ";
			std::cin >> ID;
			checkInteger(ID);
			if (bank.findPerson(ID))
			{
				bank.printPerson(ID);
				EditAcct2:
				std::cout << "1) Edit Primary's Name\n2) Edit Secondary's Name\n3) Add Secondary\n4) Remove Secondary\n0) Go back\nOption: ";
				std::cin >> choice;
				checkInteger(choice);
				if (choice == 1)
				{
					std::cout << "Enter Primary's Name: ";
					std::cin.get();
					getline(std::cin, prim);
					bank.findPerson(ID)->setPrimaryName(prim);
					system("cls");
					std::cout << "Name changed successfully!\n";
				}
				else if (choice == 2)
				{
					std::cout << "Enter Secondary's Name: ";
					std::cin.get();
					getline(std::cin, second);
					bank.findPerson(ID)->setSecondName(second);
					system("cls");
					std::cout << "Name Changed Successfully!\n";
				}
				else if (choice == 3)
				{
					std::cout << "Enter Secondary's Name: ";
					std::cin.get();
					getline(std::cin, second);
					bank.removeEmplaceSamePerson(ID,second);
				}
				else if (choice == 4)
				{
					bank.removeEmplaceSamePerson(ID);
					system("cls");
					std::cout << "Secondary Removed Successfully!\n";
				}
				else if (choice == 0)
				{
					system("cls");
					break;
				}
				else
				{
					std::cout << "Invalid Option!\n";
					goto EditAcct2;

				}
			}
			else
			{
				std::cout << "Nobody was found with that ID.\n";
				goto EditAcct;
			}
			std::cout << "\n";
			break;
		}
		case 5:
		{
			system("cls");
			bank.print();
			std::cout << "\n";
			break;
		}
		case 0:
		{
			bank.writeToFile(personFile);
			outFile.close();
			personFile.close();
			system("pause");
			return 0;
		}
		default:
		{
			system("cls");
			std::cout << "Invalid Option!\n";
			std::cout << "\n";
			break;
		}
		}
	} while (true);
}

/*
* Add a passcode/security question
* Checking/savings joint account
*/