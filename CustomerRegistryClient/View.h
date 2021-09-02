#ifndef VIEW
#define VIEW
#include "Includes.h"
#include <vector>
#include "Menu.h"
class View : public wxFrame
{
public:
	View();
	/*std::vector<wxButton*> name{};
	wxButton* name1[5]{};
	wxButton* nam{};
	wxStaticText* nam1;*/

	wxButton* back;

	wxStaticText* fNameStatic;
	wxTextCtrl* fNameCtrl;
	wxStaticText* lNameStatic;
	wxTextCtrl* lNameCtrl;
	wxStaticText* emailStatic;
	wxTextCtrl* emailCtrl;
	wxButton* emailQuery;
	wxStaticText* phoneStatic;
	wxTextCtrl* phoneCtrl;

	void onClickBack(wxCommandEvent& event);
	void onClickView(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

private:
	RETCODE rc{};
	SQLHANDLE hEnvironment{};
	SQLHANDLE hConnection{};
	SQLHSTMT hStatement{};
};
#endif // !VIEW




