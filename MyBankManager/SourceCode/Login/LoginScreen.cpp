#include "LoginScreen.h"

using namespace std;

void loginScreen(HANDLE &h) // Displays and handles username and password
{
	COORD coord{ 35, 11 };
	string username, password;
	
	infoWindow(h, coord);
	SetConsoleCursorPosition(h, coord);

	cout << "Enter username: ";
	username = inputHandling(); // Gets username from input
	if (username == "\n")
	{
		exitBank(h, coord);
		return;
	}

	coord.Y += 1;
	SetConsoleCursorPosition(h, coord);
	coord.X += 16;

	cout << "Enter password: ";
	password = inputHandling(true); // Gets password from input and hides it
	if (password == "\n")
	{
		exitBank(h, coord);
		return;
	}

	if (checkUser(username, password)) // Login user to account
	{
		makeAccountWindow(h);
		accountSystem(h, getUserId(username), true);
	}
	else // Resets login screen if invalid input is given
	{
		system("CLS");
		makeBorder(h);
		loginScreen(h);
	}
}

string inputHandling(bool passw) // Gets input from user
{
	char name[30];
	char read;
	short pos = 0;

	while (read = _getch())
	{
		if (read != 8 && read != 13 && read != 27)
		{
			if (read >= 48 && read <= 57 ||
				read >= 65 && read <= 90 ||
				read >= 97 && read <= 122) // Allowed only numbers and chars
			{
				name[pos++] = read;
				if (passw)
					cout << "*";
				else
					cout << read;
			}
			else
				continue;
		}
		else if (read == 8) // Backspace input - deletes char on input
		{
			if (pos <= 0)
				pos = 0;
			else
			{
				cout << "\b \b";
				pos--;
			}
		}
		else if (read == 27) // Escape key - exits application
		{
			string outUser = "\n";
			return outUser;
		}
		else
			break;
	}
	name[pos] = '\0';
	string outUser = name;
	return outUser;
}