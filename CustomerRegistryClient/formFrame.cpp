#include "formFrame.h"

formFrame::formFrame(wxFrame* parent, wxGridSizer* gridParent, int records)
	: m_records(records), m_parent(parent), m_gridParent(gridParent)
{
	generateForm();
}

formFrame::~formFrame()
{
	delete[] entryText;
	delete[] entryForm;
}

void formFrame::generateForm()
{
	entryText = new wxStaticText * [m_records];
	entryForm = new wxTextCtrl * [m_records];

	for (int x = 0; x < m_records; x++)
	{
		entryText[x] = new wxStaticText(m_parent, wxID_ANY, "Entry text");
		m_gridParent->Add(entryText[x], 1, wxEXPAND | wxALL);
		entryForm[x] = new wxTextCtrl(m_parent, wxID_ANY);
		m_gridParent->Add(entryForm[x], 1, wxEXPAND | wxALL);
	}
}