#include "Main.h"

/**********************************************
*                                             *
*                                             *
*               SIMULATES BANK                *
*                                             *
*                                             *
***********************************************/

/*****************************************************
*                                                    *
*         - This application uses                    *
*              files as Database                     *
*				(to improve my skills                *
*				 working with files)                 *
*											         *
*         - Files:                                   *
*			  - 'Windows.cpp'                        *
*			       Creates window to                 *
*				   the console                       *
*			  - 'checkUser'                          *
*				   Checks if user exists             *
*				   in database (file)                *
*			  - 'LoginScreen'                        *
*				   Does all things                   *
*				   related to login screen           *
*			  - 'AccountScreen'                      *
*				   Does all things                   *
*				   related to account screen         *
*				   (Contain Account class)           *
*				                                     *
*			                                         *
*                                                    *
******************************************************/

bool exists(const std::string& name) 
{
	std::ifstream file(name); 
	if (!file)
	{
		file.close();
		return false;
	}
	else
	{
		file.close();
		return true;
	}
}

void makeUsers() // Creates file with records in form: username|password
{
	std::string namePassw[3] = { "misutak|Kokos78365", "adakr|Adam2007", "KrupikJ|neniCo" };
	int ids[3] = { 1,2,3 };

	try
	{
		std::ofstream file("login", std::ios::out);
		if (!file.is_open())
			throw "Creation of 'login' file has failed!";
		for (int i = 0; i < 3; i++)
		{
			file << ids[i] << ' ' << namePassw[i] << '\n';
			if (!file.good())
				throw "Couldn't write username|password into 'login' file!";
		}
		file.close();
	}
	catch (const char* error)
	{
		system("CLS");
		COORD c{ 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << "An error has ocurred: " << error << std::endl;
	}

}

void makeAccounts() // Creates file with records in form: id amountOfCash
{
	int ids[3] = { 1, 2, 3 };
	double cash[3] = { 15000, 20000, 12000 };

	try
	{
		std::ofstream file("ucty.txt", std::ios::out);
		if (!file.is_open())
			throw "Creation of 'ucty.txt' file has failed!";
		
		for (int i = 0; i < 3; i++)
		{
			file << ids[i] << ' ' << cash[i] << '\n';
			if (!file.good())
				throw "Couldn't write id amountOfCash into 'ucty.txt' file!";
		}
		file.close();
	}
	catch (const char* error)
	{
		system("CLS");
		COORD c{ 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << "An error has ocurred: " << error << std::endl;
	}
}

void startBank(HANDLE &h) // Entry point for Bank app
{
	if (!exists("login"))
		makeUsers();

	if (!exists("ucty.txt"))
		makeAccounts();

	makeBorder(h);
	loginScreen(h);
}

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	startBank(h);
	return 0;
}