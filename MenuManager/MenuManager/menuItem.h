#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
using namespace std;

class menuItem
{
	string name;
	bool is_subMenu;
	string subMenuPath;

public:
	menuItem()
	{
		name = "N/A";
		is_subMenu = false;
		subMenuPath = "N/A";
	}
	menuItem(const char* _name, bool _subMenu, const char* _subMenuPath)
	{
		name = _name;
		is_subMenu = _subMenu;
		subMenuPath = _subMenuPath;
	}
	menuItem(const char* _name, bool _subMenu)
	{
		name = _name;
		is_subMenu = _subMenu;
	}
	friend ostream& operator<<(ostream& os, const menuItem& item)
	{
		os << item.name;
		return os;
	}
	
	//Accessors
	const char* GetName(){ return name.c_str(); }
	string GetNameStr(){ return name; }
	bool GetSubMenu(){ return is_subMenu; }
	const char* GetPath(){ return subMenuPath.c_str(); }
};
#endif