#ifndef ADD
#define ADD
#include "Includes.h"
#include <vector>
#include "Menu.h"
class Add : public wxFrame
{
public:
	Add();

	wxButton* add;
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

	void onClickAdd(wxCommandEvent& event);
	void onClickClear(wxCommandEvent& event);
	void onClickBack(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

private:
	RETCODE rc{};
	SQLHANDLE hEnvironment{};
	SQLHANDLE hConnection{};
	SQLHSTMT hStatement{};
};
#endif // !ADD


