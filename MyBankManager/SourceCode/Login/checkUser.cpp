#include "checkUser.h"

using namespace std;

bool checkUser(string &name, string &passw) // Checks whether user with password is registered in the system or not
{
	try 
	{
		string line;
		int id;
		ifstream file("login", ios::in);
		if (!file.is_open())
			throw "Couldn't open the 'login' file!";
		
		while (!file.eof())
		{
			file >> id;
			file >> line;
			size_t pos = line.find('|');
			string user = line.substr(0, pos);
			string password = line.substr(pos + 1);
			if (compareStrings(name, user) && compareStrings(passw, password))
			{
				file.close();
				return true;
			}
			if (!file.good())
				throw "An error has occured while reading from file!";
		}
		file.close();
		return false;
	}
	catch (const char* error)
	{
		system("CLS");
		cout << error << endl;
	}
	return false;
}

bool compareStrings(string& s1, string& s2) // Compares two string by its content
{
	if (s1.length() == 0 || s2.length() == 0)
		return false;
	for (int i = 0; i < s1.length(); i++)
		if (s1[i] != s2[i])
			return false;
	return true;
}

int getUserId(string& user) // Returns ID of the user
{
	try
	{
		ifstream inFile("login", ios::in);
		string username;
		int id;

		if (!inFile.is_open())
			throw "Couldn't open the file to get UserId!";
		while (!inFile.eof())
		{
			inFile >> id >> username;
			if (compareStrings(user, username))
			{
				inFile.close();
				return id;
			}
		}
		inFile.close();
		throw "Couldn't find the user in login!";
	}
	catch (const char* error)
	{
		cout << "An error has occured: " << error << endl;
	}
	return -1;
}