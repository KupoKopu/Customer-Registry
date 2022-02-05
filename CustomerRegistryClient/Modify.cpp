#include "Modify.h"

Modify::Modify() : wxFrame(nullptr, wxID_ANY, wxT("Modify"), wxDefaultPosition, wxSize(400, 450))
{
	//add background
	//separate two vertical slices (sizers)
	//populate left side with button actions
	//populate right side with static form
	//can use static form for other functions
	//once ready try dynamic form, start code is at bottom


	//controls
	wxPanel* background = new wxPanel(this, -1, wxDefaultPosition);

	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* rightPanel = new wxPanel(background, -1, wxDefaultPosition, wxSize(100, 100));
	wxBoxSizer* leftVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* EmailBox = new wxBoxSizer(wxHORIZONTAL);

	//left-side controls
	modify = new wxButton(background, 1, wxT("Modify"));
	clear = new wxButton(background, 3, wxT("Clear"));
	back = new wxButton(background, 2, wxT("Back"));

	//right-side controls
	emailStatic = new wxStaticText(rightPanel, -1, wxT("Email Address"));
	emailCtrl = new wxTextCtrl(rightPanel, -1);
	fNameStatic = new wxStaticText(rightPanel, -1, wxT("First Name"));
	fNameCtrl = new wxTextCtrl(rightPanel, -1);
	lNameStatic = new wxStaticText(rightPanel, -1, wxT("Last Name"));
	lNameCtrl = new wxTextCtrl(rightPanel, -1);
	phoneStatic = new wxStaticText(rightPanel, -1, wxT("Phone Number"));
	phoneCtrl = new wxTextCtrl(rightPanel, -1);


	//colours
	rightPanel->SetBackgroundColour(wxColour(wxT("#e0e0e0")));

	//Split in half
	mainHBox->Add(leftVBox, 0, wxEXPAND | wxRIGHT, 10);
	mainHBox->Add(rightPanel, 5, wxEXPAND);

	//Elements added on left
	leftVBox->Add(modify);
	leftVBox->Add(clear);
	leftVBox->Add(back);

	//Elements added on right
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
	EmailBox->Add(emailCtrl, wxRIGHT, 10);

	background->SetSizer(mainHBox);

	//Connects
	Connect(2, wxEVT_BUTTON, wxCommandEventHandler(Modify::onClickBack));
	Connect(3, wxEVT_BUTTON, wxCommandEventHandler(Modify::onClickClear));
	Connect(1, wxEVT_BUTTON, wxCommandEventHandler(Modify::onClickModify));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Modify::OnClose));

	//odbc initialise
	odbc::initialise(hEnvironment, hConnection);

	Centre();
}

void Modify::onClickBack(wxCommandEvent& event)
{
	Menu* menu = new Menu();
	menu->Show();
	this->Destroy();
}

void Modify::OnClose(wxCloseEvent& event)
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

void Modify::onClickModify(wxCommandEvent& event)
{
	int emailLen = emailCtrl->GetValue().size();
	int fNameLen = fNameCtrl->GetValue().size();
	int lNameLen = lNameCtrl->GetValue().size();
	int phoneLen = phoneCtrl->GetValue().size();


	std::string emailStrValue = emailCtrl->GetValue().ToStdString();
	std::string fNameStrValue = fNameCtrl->GetValue().ToStdString();
	std::string lNameStrValue = lNameCtrl->GetValue().ToStdString();
	std::string phoneStrValue = phoneCtrl->GetValue().ToStdString();


	SQLCHAR* emailValue = (SQLCHAR*)&emailStrValue[0];
	SQLCHAR* fNameValue = (SQLCHAR*)&fNameStrValue[0];
	SQLCHAR* lNameValue = (SQLCHAR*)&lNameStrValue[0];
	SQLCHAR* phoneValue = (SQLCHAR*)&phoneStrValue[0];

	if (is_digits(phoneStrValue) != true)
	{
		wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Please enter a valid phone number"), wxT("Alert"), wxOK);
		dial->ShowModal();
	}
	else
	{
		if (fNameLen < 30 and lNameLen < 30 and emailLen < 50 and phoneLen < 20)
		{
			odbc::connect(hConnection, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=msi, 1433;DATABASE=CustomerRegistry;");
			odbc::initiateStatement(hConnection, hStatement);

			SQLBindParameter(hStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, fNameValue, 0, nullptr);
			SQLBindParameter(hStatement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, lNameValue, 0, nullptr);
			SQLBindParameter(hStatement, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, emailValue, 0, nullptr);
			SQLBindParameter(hStatement, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, phoneValue, 0, nullptr);
			odbc::directExecute(hStatement, (SQLWCHAR*)L"{call spUpdate_Customer(?,?,?,?)}");

			odbc::freeStatement(hStatement);
			odbc::disconnect(hConnection);
		}
	}

	

	
}

void Modify::onClickClear(wxCommandEvent& event)
{
	fNameCtrl->Clear();
	lNameCtrl->Clear();
	emailCtrl->Clear();
	phoneCtrl->Clear();

}