#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include "SLList.h"
#include "menu.h"
//#include "ConsoleFunctions.h"
//using namespace KSUN;

class menuManager
{
	SLList<menu> activeMenus;

public:
	void addMenu(menu& toAdd){ activeMenus.addHead(toAdd); }
	menu& currMenu()
	{
		SLLIter<menu> menuIter(activeMenus);
		menuIter.begin();
		return menuIter.current();
	}
	unsigned int numMenus(){ return activeMenus.size(); }
	void removeMenu()
	{
		SLLIter<menu> menuIter(activeMenus);
		menuIter.begin();
		activeMenus.remove(menuIter);
	}
};

#endif