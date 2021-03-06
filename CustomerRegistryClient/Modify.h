#ifndef MODIFY
#define MODIFY
#include "Includes.h"
#include <vector>
#include "Menu.h"
class Modify : public wxFrame
{
public:
	Modify();


	wxButton* modify;
	wxButton* clear;
	wxButton* back;

	wxStaticText* fNameStatic;
	wxTextCtrl* fNameCtrl;
	wxStaticText* lNameStatic;
	wxTextCtrl* lNameCtrl;
	wxStaticText* emailStatic;
	wxTextCtrl* emailCtrl;
	wxStaticText* phoneStatic;
	wxTextCtrl* phoneCtrl;

	void onClickModify(wxCommandEvent& event);
	void onClickClear(wxCommandEvent& event);
	void onClickBack(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

private:
	RETCODE rc{};
	SQLHANDLE hEnvironment{};
	SQLHANDLE hConnection{};
	SQLHSTMT hStatement{};
};
#endif // !MODIFY