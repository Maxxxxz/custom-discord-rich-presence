#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, onButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "wxTemplate!", wxPoint(100, 100), wxSize(500, 500))
{
	m_btn1 = new wxButton(this, 10001, "Click Me!", wxPoint(25, 25), wxSize(100, 25));
	m_text1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(25, 75), wxSize(250, 100));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(25, 200), wxSize(250, 100));
}

cMain::~cMain()
{

}

void cMain::onButtonClicked(wxCommandEvent& e)
{
	m_list1->AppendString(m_text1->GetValue());
	e.Skip();
}
