#include "menuManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();

	Console::SetWindowSize(40, 40);
	Console::SetBufferSize(40, 40);
	Console::CursorVisible(false);
	Console::EOLWrap(false);

	menuManager manager;
	menu mainMenu;
	mainMenu.Load();
	mainMenu.DisplayMenu();
	manager.addMenu(mainMenu);
	while (true)
	{
		menuItem selectedItem = manager.currMenu().selectMenu();
		if (strcmp(selectedItem.GetName(), "Exit") == 0)
		{
			if (manager.numMenus() == 1)
				return 0;
			else
			{
				manager.removeMenu();
				manager.currMenu().DisplayMenu();
			}
		}
		else
		{
			menu newMenu;
			newMenu.Load(selectedItem.GetPath());
			newMenu.DisplayMenu();
			manager.addMenu(newMenu);
		}
	}

	return 0;
}