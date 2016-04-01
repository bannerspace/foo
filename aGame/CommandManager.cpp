#include "CommandManager.h"
#include <iostream>
#include <string>

using namespace std;

CommandManager::CommandManager()
{
	
	//NEW THREAD FOR CONSOLE
	system("Color 1A");
	cout << "|------------------Welcome to our game!------------------|" << endl;
	cout << endl;
	cout << "The game is currently under super-early development stage." << endl;
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << endl;
	cout << "Type -c to get list of possible commands" << endl;
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
}


CommandManager::~CommandManager()
{
}


void CommandManager::call()
{
	string input;
	getline(std::cin, input);

	if (input.length() > 10)
	{
		cout << "Command is too long." << endl;
		
	}
	else
	{
		char buffer[11];
		buffer[10] = '\0';
		strcpy(buffer, input.c_str());

		if (buffer[0] == '-')
		{
			char cmd = buffer[1];
			switch (cmd)
			{
			case 'c':
			{
						cout << "[b] press - on/off showing bounding box" << endl;
						cout << "[f] press - on/off free camera mode" << endl;
						cout << "[l] press - on/off locking camera" << endl;
						break;
			}
			default:
			{
					   cout << "wrong command" << endl;
					   break;
			}
			}
		}
	}

	call();
}