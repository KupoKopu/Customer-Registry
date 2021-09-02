#include "Menu.h"



Menu::Menu() : wxFrame(nullptr, wxID_ANY, "Customer Registry", wxDefaultPosition, wxSize(450,400))
{

	wxPanel* background = new wxPanel(this, wxID_ANY);
	
	// Main sizer
	wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	
	space = new wxPanel(background, wxID_ANY);
	add = new wxButton(background, 1, wxT("Add"));
	view = new wxButton(background, 2, wxT("View"));
	modify = new wxButton(background, 3, wxT("Modify"));
	exit = new wxButton(background, wxID_EXIT);

	

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);


	hbox1->Add(add, 1);
	hbox2->Add(view, 1);
	hbox3->Add(modify, 1);
	hbox4->Add(exit, 1);




	vBox->Add(space, wxEXPAND);
	vBox->Add(hbox1, -1, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 10);
	vBox->Add(-1, 2);
	vBox->Add(hbox2, 1, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 10);
	vBox->Add(-1, 2);
	vBox->Add(hbox3, 2, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 10);
	vBox->Add(-1, 2);
	vBox->Add(hbox4, 1, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 20);
	vBox->Add(-1, 2);


	background->SetSizer(vBox);
	
	//Connects
	Connect(1, wxEVT_BUTTON, wxCommandEventHandler(Menu::onClickAdd));
	Connect(2, wxEVT_BUTTON, wxCommandEventHandler(Menu::onClickView));
	Connect(3, wxEVT_BUTTON, wxCommandEventHandler(Menu::onClickModify));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Menu::OnClose));
	Connect(wxID_EXIT, wxEVT_BUTTON, wxCloseEventHandler(Menu::OnClose));

	Centre();
}

void Menu::onClickAdd(wxCommandEvent& event)
{
	Add* add = new Add();
	add->Show();
	this->Destroy();
}

void Menu::onClickView(wxCommandEvent& event)
{
	View* view = new View();
	view->Show();
	this->Destroy();
}

void Menu::onClickModify(wxCommandEvent& event)
{
	Modify* modify = new Modify();
	modify->Show();
	this->Destroy();
}

void Menu::OnClose(wxCloseEvent& event)
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

