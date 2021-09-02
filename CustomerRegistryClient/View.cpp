#include "View.h"

View::View() : wxFrame(nullptr, wxID_ANY, wxT("View"), wxDefaultPosition, wxSize(400, 450))
{
	//controls
	wxPanel* background = new wxPanel(this, -1, wxDefaultPosition);

	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* rightPanel = new wxPanel(background, -1, wxDefaultPosition, wxSize(100, 100));
	wxBoxSizer* leftVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* EmailBox = new wxBoxSizer(wxHORIZONTAL);

	//left-side controls
	back = new wxButton(background, 2, wxT("Back"));

	//right-side controls
	emailStatic = new wxStaticText(rightPanel, -1, wxT("Email Address"));
	emailCtrl = new wxTextCtrl(rightPanel, -1);
	emailQuery = new wxButton(rightPanel, 3, wxT("Search"));
	fNameStatic = new wxStaticText(rightPanel, -1, wxT("First Name"));
	fNameCtrl = new wxTextCtrl(rightPanel, -1);
	lNameStatic = new wxStaticText(rightPanel, -1, wxT("Last Name"));
	lNameCtrl = new wxTextCtrl(rightPanel, -1);
	phoneStatic = new wxStaticText(rightPanel, -1, wxT("Phone Number"));
	phoneCtrl = new wxTextCtrl(rightPanel, -1);

	//colours
	rightPanel->SetBackgroundColour(wxColour(wxT("#e0e0e0")));

	//sizers
	mainHBox->Add(leftVBox, 0, wxEXPAND | wxRIGHT, 10);
	mainHBox->Add(rightPanel, 5, wxEXPAND);

	//left-side
	leftVBox->Add(back);

	//right-side
	rightPanel->SetSizer(rightVBox);
	rightVBox->Add(emailStatic);
	rightVBox->Add(EmailBox);

	rightVBox->Add(fNameStatic);
	rightVBox->Add(fNameCtrl);
	rightVBox->Add(lNameStatic);
	rightVBox->Add(lNameCtrl);
	
	rightVBox->Add(phoneStatic);
	rightVBox->Add(phoneCtrl);

	//TODO: Figure out how to get borders without using sizers
	EmailBox->Add(emailCtrl, 0, wxRIGHT, 10);
	EmailBox->Add(emailQuery, 0);

	background->SetSizer(mainHBox);

	//Connects
	Connect(2, wxEVT_BUTTON, wxCommandEventHandler(View::onClickBack));
	Connect(3, wxEVT_BUTTON, wxCommandEventHandler(View::onClickView));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(View::OnClose));

	//odbc initialise
	odbc::initialise(hEnvironment, hConnection);

	Centre();
}

void View::onClickBack(wxCommandEvent& event)
{
	Menu* menu = new Menu();
	menu->Show();
	this->Destroy();
}

void View::onClickView(wxCommandEvent& event)
{
	std::string emailStrValue = emailCtrl->GetValue().ToStdString();

	SQLCHAR* emailValue = (SQLCHAR*)&emailStrValue[0];

	odbc::connect(hConnection, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=tcp:92.23.221.140, 1433;DATABASE=Customer Registry;UID=tester;PWD=tester123;");
	odbc::initiateStatement(hConnection, hStatement);
	SQLBindParameter(hStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, emailValue, 0, nullptr);
	odbc::directExecute(hStatement, (SQLWCHAR*)L"{call spView_Customer(?)}");

	SQLCHAR fName[30]{};
	SQLCHAR lName[30]{};
	SQLCHAR phone[20]{};

	wxString fNameWx = fName;
	wxString lNameWx = lName;
	wxString phoneWx = phone;

	odbc::prepareColContainer(hStatement, *fName, 1, SQL_CHAR, 30);
	odbc::prepareColContainer(hStatement, *lName, 2, SQL_CHAR, 30);
	odbc::prepareColContainer(hStatement, *phone, 3, SQL_CHAR, 20);
	odbc::fetchCol(hStatement);

	fNameCtrl->SetValue(fName);
	lNameCtrl->SetValue(lName);
	phoneCtrl->SetValue(phone);

	odbc::freeStatement(hStatement);
	odbc::disconnect(hConnection);
}

void View::OnClose(wxCloseEvent& event)
{
	wxMessageDialog* dial = new wxMessageDialog(NULL,
		wxT("Are you sure to quit?"), wxT("Question"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	Centre();

	int ret = dial->ShowModal();

	dial->Destroy();

	if (ret == wxID_YES)
	{
		Destroy();
	}
	else
	{
		event.Veto();
	}

}
