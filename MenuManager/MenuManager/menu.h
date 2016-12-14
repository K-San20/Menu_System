#ifndef _MENU_H_
#define	_MENU_H_

#include "menuItem.h"
#include "DynArray.h"
#include <fstream>
#include <iostream>
#include <conio.h>
using namespace std;

#include "ConsoleFunctions.h"
using namespace KSUN;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

class menu
{
	string title;
	DynArray<menuItem> choices;
	int currSelection;
	unsigned int numSubMenus;
public:
	menu()
	{
		title = "N/A";
		currSelection = 0;
		numSubMenus = 0;
	}
	bool Load(const char* fileName = "main.mnu")
	{
		fstream fin;
		fin.open(fileName, ios_base::in);
		char titleBuffer[15];
		unsigned int count;
		char subMenuBuffer[10];
		char itemNameBuffer[30];
		char subMenuFileNameBuffer[30];

		if (fin.is_open())
		{
			fin.getline(titleBuffer, 15, '\n');
			title = titleBuffer;
			fin >> count;
			fin.ignore(INT_MAX, '\n');
			for (unsigned int i = 0; i < count; i++)
			{
				bool isSubMenu = false;
				fin >> subMenuBuffer;
				if (strcmp(subMenuBuffer, "MENU") == 0)
					isSubMenu = true;
				fin.ignore(INT_MAX, '\"');
				fin.getline(itemNameBuffer, 30, '\"');
				if (isSubMenu)
				{
					fin.ignore(INT_MAX, '\"');
					fin.getline(subMenuFileNameBuffer, 30, '\"');
				}
				if (isSubMenu)
				{
					menuItem toAdd(itemNameBuffer, isSubMenu, subMenuFileNameBuffer);
					choices.append(toAdd);
					numSubMenus++;
				}
				else
				{
					menuItem toAdd(itemNameBuffer, isSubMenu);
					choices.append(toAdd);
				}
			}
			menuItem exit("Exit", false);
			choices.append(exit);
			fin.close();
			return true;
		}
		return false;
	}

	void DisplayMenu()
	{
		Console::Lock(true);
		Console::Clear();

		Console::ForegroundColor(Cyan);
		Console::DrawBox(0, 0, Console::WindowWidth(), 3, true);
		Console::SetCursorPosition((Console::WindowWidth() >> 1) - (title.length() >> 1), 1);
		Console::ForegroundColor(White);
		cout << title << '\n';
		Console::ForegroundColor(Cyan);
		Console::DrawBox(0, 2, Console::WindowWidth(), Console::WindowHeight() - 1, true);
		Console::SetCursorPosition(0, 2);
		cout << (char)204;
		Console::SetCursorPosition(Console::WindowWidth(), 2);
		cout << (char)185;
		Console::ResetColor();
		for (unsigned int i = 0; i < choices.size(); i++)
		{
			int nameLen = choices[i].GetNameStr().length();
			Console::ForegroundColor(Magenta);
			Console::DrawBox(((Console::WindowWidth() >> 1) - (nameLen >> 1)) - 1, (3 + i * 3) + 1, nameLen + 2, 3, false);
			Console::SetCursorPosition((Console::WindowWidth() >> 1) - (nameLen >> 1), (3 + i * 3) + 2);
			Console::ForegroundColor(Yellow);
			if (choices[i].GetSubMenu())
				Console::ForegroundColor(Green);
			if (i == currSelection)
				Console::BackgroundColor(Blue);
			if (i == choices.size() - 1)
				Console::ForegroundColor(Red);
			cout << choices[i];
			cout << '\n';
			Console::ResetColor();
		}

		Console::Lock(false);
		Sleep(10);
	}

	menuItem& selectMenu()
	{
		while (true)
		{
			//Console::SetCursorPosition(0, 1);
			string userInput;
			if (_kbhit())
			{
				int c = _getch();
				switch (c)
				{
				case KEY_UP:
				{
					currSelection--;
					if (currSelection < 0)
						currSelection = choices.size() - 1;
					//Console::Clear();
					DisplayMenu();
				}
					break;
				case KEY_DOWN:
				{
					currSelection++;
					if (currSelection > (int)choices.size() - 1)
						currSelection = 0;
					//Console::Clear();
					DisplayMenu();
				}
					break;
				case KEY_ENTER:
				{
					if (choices[currSelection].GetSubMenu() || currSelection == choices.size() - 1)
						return choices[currSelection];
				}
					break;
				}
			}
		}
	}
};
#endif