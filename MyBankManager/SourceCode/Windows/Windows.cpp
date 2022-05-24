#include "Windows.h"

#define MAXIMUM 5000

void makeBorder(HANDLE& h) // Draws window rectangle (Grey colour)
{
	DWORD written;
	COORD c{ 0, 0 };

	FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 100, c, &written);
	std::cout << std::endl;
	c.X += 1;

	for (int i = 0; i < 26; i++)
	{
		c.X = 0;
		FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 1, c, &written);
		c.X = 100;
		FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 1, c, &written);
		c.Y += 1;
	}
	c.X = 0;
	FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, 101, c, &written);
}

void makeAccountWindow(HANDLE& h) // Makes account window and starts simulating bank
{
	system("CLS");
	makeBorder(h);
	bootWindow(h); // Disable for quicker debugging
	system("CLS");
	makeDisplayWindow(h);
	makeBorder(h);
}

void makeDisplayWindow(HANDLE& h) // Little window to display data about account
{
	DWORD written;
	COORD c{ 8, 3 };
	FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN, 31, c, &written);
	for (int i = 0; i < 5; i++)
	{	
		c.Y += 1;
		FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN, 1, c, &written);
		c.X = 38;
		FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN, 1, c, &written);
		c.X = 8;
	}
	c.X = 8;
	c.Y +=1;
	FillConsoleOutputAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN, 31, c, &written);
}

void makeAskDisplay(HANDLE& h, COORD& c) // Displays text in the account screen
{
	c.X = 15;
	c.Y = 19;
	SetConsoleCursorPosition(h, c);
	std::cout << "Enter 'w' for withdraw or";

	c.Y += 1;
	SetConsoleCursorPosition(h, c);
	std::cout << "enter 'd' for deposit or";

	c.Y += 1;
	SetConsoleCursorPosition(h, c);
	std::cout << "enter 'esc' to logout:";

	c.Y += 1;
	c.X += 7;
	SetConsoleCursorPosition(h, c);
}

void infoWindow(HANDLE& h, COORD& c) // Print info about inputs
{
	c.X = 10;
	c.Y = 2;
	SetConsoleCursorPosition(h, c);
	std::cout << "Username and password allows only characters and numbers!";

	c.Y += 1;
	SetConsoleCursorPosition(h, c);
	std::cout << "\t - if other input, nothing will happen.";

	c.X = 35;
	c.Y = 11;
}

void bootWindow(HANDLE& h) // Boot window to simulate loading the app
{
	COORD coord{ 45, 11 };
	SetConsoleCursorPosition(h, coord);
	std::cout << "Loading";

	coord.Y += 2;
	coord.X -= 2;
	SetConsoleCursorPosition(h, coord);
	short wait = 0;
	while (wait <= MAXIMUM)
	{
		Sleep(1000);
		wait += 1000;
		std::cout << ". ";
	}
	Sleep(1000);
}

void clearDisplayWindow(HANDLE& h) // Removes text from DisplayWindow
{
	COORD c{38, 4};
	for (int i = 0; i < 3; i++)
	{
		c.Y += 1;
		SetConsoleCursorPosition(h, c);
		for(int j = 0; j < 28; j++)
			std::cout << "\b \b";
	}
}

void clearAskDisplay(HANDLE& h, COORD& c) // Removes text made in makeAskDisplay
{
	c.Y = 19;
	c.X = 41;
	SetConsoleCursorPosition(h, c);
	for (int i = 0; i < 26; i++)
		std::cout << "\b \b";
	c.X -= 1;
	c.Y += 1;
	SetConsoleCursorPosition(h, c);
	for (int i = 0; i < 25; i++)
		std::cout << "\b \b";
	c.X -= 2;
	c.Y += 1;
	SetConsoleCursorPosition(h, c);
	for (int i = 0; i < 25; i++)
		std::cout << "\b \b";
}

void clearLine(HANDLE& h, COORD& c) // Removes every character in line in the window
{
	c.X = 100;
	SetConsoleCursorPosition(h, c);
	for (int i = 0; i < 99; i++)
		std::cout << "\b \b";
}

void exitBank(HANDLE& h, COORD& c)
{
	c.X = 0;
	c.Y = 27;
	SetConsoleCursorPosition(h, c);
}