#include "AccountScreen.h"

using namespace std;

#define MAXIMUM 5000

Account::Account(int userId)
{
	try
	{
		ifstream accFile("ucty.txt", ios::in);
		ifstream loginFile("login", ios::in);
		string name;
		bool foundId = false;
		double amountOfCash;
		int tempId;

		if (!accFile.is_open())
			throw "Couldn't open 'ucty.txt' file!!";
		while (!accFile.eof())
		{
			accFile >> tempId >> amountOfCash;
			if (tempId == userId)
			{
				_id = userId;
				_cash = amountOfCash;
				foundId = true;
				break;
			}
			if (!accFile.good())
				throw "Error while reading 'ucty.txt' file!";
		}

		if (!loginFile.is_open())
			throw "Couldn't open 'login' file!!";
		while (!loginFile.eof())
		{
			loginFile >> tempId >> name;
			if (tempId == userId)
			{
				size_t pos = name.find('|');
				_username = name.substr(0, pos);
				break;
			}
			if (!loginFile.good())
				throw "Error while reading 'login' file!";
		}

		accFile.close();
		loginFile.close();

		if (!foundId)
			throw "User doesn't have bank account!";
	}
	catch (const char* error)
	{
		system("CLS");
		cout << "An error has occured: " << error << endl;
	}
}

Account::~Account()
{
}

void Account::withdraw(double amount)
{
	double tmp = getCash();
	if (tmp - amount < 0)
		throw "You don't have enough money to withdraw!";
	else
		setCash(tmp - amount);
}

void Account::deposit(double amount)
{
	setCash(getCash() + amount);
}

bool Account::save() // Saves acount into database (file)
{
	try
	{
		ifstream outdatedFile("ucty.txt", ios::in);
		vector<int> ids;
		vector<double> money;
		int id;
		double amountOfCash;

		if (!outdatedFile.is_open())
			throw "Couldn't open 'ucty.txt' file!!";

		while (!outdatedFile.eof())
		{
			if (!outdatedFile.good())
				throw "Error while reading 'ucty.txt' file!!";
			outdatedFile >> id;
			ids.push_back(id);
			if (id == _id)
			{
				money.push_back(_cash);
				outdatedFile >> amountOfCash;
			}
			else
			{
				outdatedFile >> amountOfCash;
				money.push_back(amountOfCash);
			}
		}
		
		outdatedFile.close();
		remove("ucty.txt");

		ofstream updatedFile("ucty.txt", ios::out);
		int i = 0;
		for (auto id = ids.begin(); id != ids.end(); id++)
		{
			if(id == ids.end() - 1)
				updatedFile << *id << ' ' << money[i++];
			else
				updatedFile << *id << ' ' << money[i++] << endl;
			if (!updatedFile.good())
				throw "Error while writing into 'ucty.txt' file!!";
		}
		updatedFile.close();
		return true;
	}
	catch (const char* error)
	{
		system("CLS");
		cout << "An error has ocurred: " << error << endl;
		return false;
	}
}

void accountSystem(HANDLE& h, int id, bool askWindow) // System simulating bank app
{
	COORD coord{ 10,5 };
	char input;
	Account accFile(id);

	updateDisplayWindow(h, accFile);
	if (askWindow)
		makeAskDisplay(h, coord);

	coord.X = 23;
	coord.Y = 22;
	while (input = _getch())
	{
		if (input != 'w' && input != 'd' && input != 27)
			continue;
		else
		{
			if (input == 'w' || input == 'd') // Starts either withdraw or deposit on user input
			{
				double money;
				askWindow = false;
				clearAskDisplay(h, coord);
				coord.X = 23;
				coord.Y = 21;
				SetConsoleCursorPosition(h, coord);
				if (input == 'w')
					cout << "How much money do you want to withdraw?";
				else
					cout << "Enter amount of cash to deposit:";
				coord.Y += 1;
				SetConsoleCursorPosition(h, coord);
				cin >> money;
				coord.Y -= 1;
				for (int i = 0; i < 3; i++)
				{
					clearLine(h, coord);
					coord.Y += 1;
				}
				if (input == 'w')
					withdraw(h, coord, accFile, money);
				else
					deposit(h, coord, accFile, money);
			}
			else // Log out from the system
			{
				system("CLS");
				makeBorder(h);
				coord.X = 40;
				coord.Y = 12;
				SetConsoleCursorPosition(h, coord);
				cout << "WAIT TILL LOG OUT...";
				Sleep(3000);
				system("CLS");
				break;
			}
		}
		SetConsoleCursorPosition(h, coord);
	}
	startBank(h);

}

void updateDisplayWindow(HANDLE& h, Account& a) // Updates info about account
{
	COORD c{ 10, 5 };
	for (int i = 0; i < 3; i++) // Dislpays account details into DisplayWindow (blue window)
	{
		switch (i)
		{
		case 0:
			SetConsoleCursorPosition(h, c);
			cout << "ACCOUNT: " << a.getUsername();
			break;
		case 1:
			c.Y += 1;
			SetConsoleCursorPosition(h, c);
			cout << "ID: " << a.getId();
			break;
		case 2:
			c.Y += 1;
			SetConsoleCursorPosition(h, c);
			cout << "CASH: " << a.getCash();
			break;
		}
	}
}

void withdraw(HANDLE& h, COORD& c, Account& acc, double withMoney) // Action to withdraw money
{
	try
	{
			acc.withdraw(withMoney);
			if (acc.save())
			{
				clearDisplayWindow(h);
				updateDisplayWindow(h, acc);
				c.X = 10;
				c.Y = 5;
				makeAskDisplay(h, c);
			}
	}
	catch (const char* error)
	{
		system("CLS");
		cout << "ERROR: " << error;
	}
}

void deposit(HANDLE& h, COORD& c, Account& acc, double deposMoney) // Action to deposit money
{
	acc.deposit(deposMoney);
	if (acc.save())
	{
		clearDisplayWindow(h);
		updateDisplayWindow(h, acc);
		c.X = 10;
		c.Y = 5;
		makeAskDisplay(h, c);
	}
}