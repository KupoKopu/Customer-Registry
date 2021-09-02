#ifndef MENU
#define MENU
#include "Includes.h"
#include "Add.h"
#include "View.h"
#include "Modify.h"
class Menu : public wxFrame
{
public:
	Menu();
	wxPanel* space;
	wxButton* add;
	wxButton* view;
	wxButton* modify;
	wxButton* exit;

	//add button events
	void onClickAdd(wxCommandEvent& event);
	void onClickModify(wxCommandEvent& event);
	void onClickView(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
#endif // !MENU


