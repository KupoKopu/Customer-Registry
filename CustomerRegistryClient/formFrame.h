#ifndef FORMFRAME
#define FORMFRAME
#include "Includes.h"

class formFrame
{
public:
	formFrame(wxFrame* parent, wxGridSizer* gridParent, int records = 0);
	~formFrame();
public:
	int m_records{};
	wxFrame* m_parent;
	wxGridSizer* m_gridParent;
	wxStaticText** entryText;
	wxTextCtrl** entryForm;
public:
	void generateForm();
};
#endif // !FORMFRAME