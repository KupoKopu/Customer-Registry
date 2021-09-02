#include "main.h"
#include "Menu.h"
#include "Add.h"

IMPLEMENT_APP(myApp);

myApp::myApp()
{
}

bool myApp::OnInit()
{
	//Menu
	//Menu* menu = new Menu(wxT("Customer Registry"));
	Menu* menu = new Menu();
	menu->Show();

	return true;
}