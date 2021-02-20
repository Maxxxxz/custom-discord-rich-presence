#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void onButtonClicked(wxCommandEvent& e);

	wxDECLARE_EVENT_TABLE();

private:
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_text1 = nullptr;
	wxListBox* m_list1 = nullptr;

};

