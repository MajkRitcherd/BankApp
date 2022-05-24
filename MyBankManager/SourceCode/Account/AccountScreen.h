#pragma once

#include "Includes.h"
#include "Login\LoginScreen.h"
#include "Main.h"


class Account // Holds information about account represented as FILE
{
public:
	Account(int);
	~Account();
	int getId() { return _id; }
	double getCash() { return _cash; }
	std::string getUsername() { return _username; }
	void setCash(double amount) { _cash = amount; }
	void withdraw(double);
	bool save(); // Saves info to file
	void deposit(double);

private:
	int _id = 0;
	std::string _username = "DFAULT";
	double _cash = 0;
};

void accountSystem(HANDLE&, int, bool);

void updateDisplayWindow(HANDLE&, Account&);

void withdraw(HANDLE&, COORD&, Account&, double);

void deposit(HANDLE&, COORD&, Account&, double);