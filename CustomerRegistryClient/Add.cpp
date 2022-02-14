#include "Add.h"


Add::Add() : wxFrame(nullptr, wxID_ANY, wxT("Add"), wxDefaultPosition, wxSize(400, 450))
{
	//controls
	wxPanel* background = new wxPanel(this, -1, wxDefaultPosition);

	wxBoxSizer* mainHBox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* rightPanel = new wxPanel(background, -1, wxDefaultPosition, wxSize(100, 100));
	wxBoxSizer* leftVBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightVBox = new wxBoxSizer(wxVERTICAL);

	//left-side controls
	add = new wxButton(background, 1, wxT("Add"));
	clear = new wxButton(background, 3, wxT("Clear"));
	back = new wxButton(background, 2, wxT("Back"));

	//right-side controls
	fNameStatic = new wxStaticText(rightPanel, -1, wxT("First Name"));
	fNameCtrl = new wxTextCtrl(rightPanel, -1);
	lNameStatic = new wxStaticText(rightPanel, -1, wxT("Last Name"));
	lNameCtrl = new wxTextCtrl(rightPanel, -1);
	emailStatic = new wxStaticText(rightPanel, -1, wxT("Email Address"));
	emailCtrl = new wxTextCtrl(rightPanel, -1);
	phoneStatic = new wxStaticText(rightPanel, -1, wxT("Phone Number"));
	phoneCtrl = new wxTextCtrl(rightPanel, -1);

	//colours
	rightPanel->SetBackgroundColour(wxColour(wxT("#e0e0e0")));

	//sizers
	mainHBox->Add(leftVBox, 0, wxEXPAND | wxRIGHT, 10);
	mainHBox->Add(rightPanel, 5, wxEXPAND);

	leftVBox->Add(add);
	leftVBox->Add(clear);
	leftVBox->Add(back);

	rightPanel->SetSizer(rightVBox);
	rightVBox->Add(fNameStatic);
	rightVBox->Add(fNameCtrl);
	rightVBox->Add(lNameStatic);
	rightVBox->Add(lNameCtrl);
	rightVBox->Add(emailStatic);
	rightVBox->Add(emailCtrl);
	rightVBox->Add(phoneStatic);
	rightVBox->Add(phoneCtrl);

	background->SetSizer(mainHBox);

	//Connects
	Connect(2, wxEVT_BUTTON, wxCommandEventHandler(Add::onClickBack));
	Connect(3, wxEVT_BUTTON, wxCommandEventHandler(Add::onClickClear));
	Connect(1, wxEVT_BUTTON, wxCommandEventHandler(Add::onClickAdd));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Add::OnClose));

	//odbc initialise
	odbc::initialise(hEnvironment, hConnection);

	Centre();
}

void Add::onClickBack(wxCommandEvent& event)
{
	Menu* menu = new Menu();
	menu->Show();
	this->Destroy();
}

void Add::OnClose(wxCloseEvent& event)
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

void Add::onClickAdd(wxCommandEvent& event)
{
	int fNameLen = fNameCtrl->GetValue().size();
	int lNameLen = lNameCtrl->GetValue().size();
	int emailLen = emailCtrl->GetValue().size();
	int phoneLen = phoneCtrl->GetValue().size();

	std::string fNameStrValue = fNameCtrl->GetValue().ToStdString();
	std::string lNameStrValue = lNameCtrl->GetValue().ToStdString();
	std::string emailStrValue = emailCtrl->GetValue().ToStdString();
	std::string phoneStrValue = phoneCtrl->GetValue().ToStdString();

	SQLCHAR* fNameValue = (SQLCHAR*)&fNameStrValue[0];
	SQLCHAR* lNameValue = (SQLCHAR*)&lNameStrValue[0];
	SQLCHAR* emailValue = (SQLCHAR*)&emailStrValue[0];
	SQLCHAR* phoneValue = (SQLCHAR*)&phoneStrValue[0];


	//TODO: Need more clean checks on validity
	if (is_digits(phoneStrValue) != true)
	{
		wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Please enter a valid phone number"), wxT("Alert"), wxOK);
		dial->ShowModal();
	}
	else if (is_email(emailStrValue))
	{
		wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Please enter a valid email"), wxT("Alert"), wxOK);
		dial->ShowModal();
	}
	else
	{
		if (is_customer_length_correct(fNameLen, lNameLen, emailLen, phoneLen))
		{
			odbc::connect(hConnection, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=msi, 1433;DATABASE=CustomerRegistry;");
			odbc::initiateStatement(hConnection, hStatement);
			rc = SQLBindParameter(hStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, fNameValue, 0, nullptr);
			rc = SQLBindParameter(hStatement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, lNameValue, 0, nullptr);
			rc = SQLBindParameter(hStatement, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, emailValue, 0, nullptr);
			rc = SQLBindParameter(hStatement, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, phoneValue, 0, nullptr);
			odbc::directExecute(hStatement, (SQLWCHAR*)L"{call spInsert_Customer(?,?,?,?)}");
			odbc::freeStatement(hStatement);
			odbc::disconnect(hConnection);
		}
	}

	
}

void Add::onClickClear(wxCommandEvent& event)
{
	fNameCtrl->Clear();
	lNameCtrl->Clear();
	emailCtrl->Clear();
	phoneCtrl->Clear();

}




//wxPanel* background = new wxPanel(this, wxID_ANY);
//
//wxBoxSizer* hMainSizer = new wxBoxSizer(wxHORIZONTAL);
//
//
//
//
//wxBoxSizer* vLeftBox = new wxBoxSizer(wxVERTICAL);
//hMainSizer->Add(vLeftBox, 1, wxALIGN_RIGHT);
//
//wxButton* add = new wxButton(background, wxID_ANY, wxT("Add"));
//wxButton* clear = new wxButton(background, wxID_ANY, wxT("Clear"));
//wxButton* back = new wxButton(background, wxID_ANY, wxT("Back"));
//vLeftBox->Add(add, 5);
//vLeftBox->Add(clear, 1);
//vLeftBox->Add(back, 1);
//
//
//
//
//
//
//wxBoxSizer* vRightBox = new wxBoxSizer(wxVERTICAL);
//hMainSizer->Add(vRightBox, 1, wxEXPAND);
//
//wxPanel* rightPanel = new wxPanel(background, wxID_ANY, wxDefaultPosition, wxSize(50, 50));
//wxButton* back1 = new wxButton(background, wxID_ANY, wxT("Back"));
//
//rightPanel->SetBackgroundColour(wxColour(wxT("#E5E5E5")));
//
//vRightBox->Add(back1, 0);
//vRightBox->Add(rightPanel, 1, wxEXPAND);
//
//background->SetSizer(hMainSizer);

/*
name.reserve(10);
//name[0] = new wxButton(this, wxID_ANY);

//name1[0] = new wxButton(this, wxID_ANY);
//nam = new wxButton(this, wxID_ANY);
//nam1 = new wxStaticText(this, wxID_ANY, wxT("bob"));

wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

for (size_t i = 0; i < 3; i++)
{
	name.push_back(new wxButton(this, wxID_ANY, wxT("bob" + i)));
	hbox->Add(name[i], 1, wxALL, 10);
}

SetSizer(hbox);
*/