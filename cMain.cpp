#include "cMain.h"
#include "discord.h"
#include <vector>

#include <wx/msgdlg.h>
#include <wx/spinctrl.h>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, onButtonClicked)
wxEND_EVENT_TABLE()

using std::string;
using std::vector;

#define wxMICHAEL_STYLE (wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCLIP_CHILDREN | wxCAPTION)

const string labels[8] = { "State", "Details", "Start Time", "End Time", "Party Size", "Party Max", "7", "8" };

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Michael's Custom Rich Presence", wxPoint(100, 100), wxSize(400, 300), wxMICHAEL_STYLE)
{
	m_btn1 = new wxButton(this, 10001, "Update Presence", wxPoint(150, 25), wxSize(100, 25));

	stateLabel = new wxStaticText(this, wxID_ANY, labels[0], wxPoint(10, 103), wxSize(75, 25), wxALIGN_RIGHT);
	stateBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(90, 100), wxSize(250, 25));

	detailLabel = new wxStaticText(this, wxID_ANY, labels[1], wxPoint(10, 78), wxSize(75, 25), wxALIGN_RIGHT);
	detailBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(90, 75), wxSize(250, 25));

	timeLabel = new wxStaticText(this, wxID_ANY, labels[2], wxPoint(10, 128), wxSize(75, 25), wxALIGN_RIGHT);
	timeBox = new wxTimePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(90, 125), wxDefaultSize);

	endTimeLabel = new wxStaticText(this, wxID_ANY, labels[3], wxPoint(10, 153), wxSize(75, 25), wxALIGN_RIGHT);
	endTimeBox = new wxTimePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(90, 150), wxDefaultSize);

	partySizeLabel = new wxStaticText(this, wxID_ANY, labels[4], wxPoint(10, 178), wxSize(75, 25), wxALIGN_RIGHT);
	partySize = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(92, 175), wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 0);
	//partySize = new wxChoice(this, wxID_ANY, , wxPoint(90, 175), wxDefaultSize);

	partyMaxLabel = new wxStaticText(this, wxID_ANY, labels[5], wxPoint(10, 203), wxSize(75, 25), wxALIGN_RIGHT);
	partyMax = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(92, 200), wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 0);
	//partyMax = new wxChoice(this, wxID_ANY, , wxPoint(90, 200), wxDefaultSize);

	// Image Select here...

	initDiscord();
}

cMain::~cMain()
{

}

void cMain::onButtonClicked(wxCommandEvent& e)
{
	//m_list1->AppendString(m_text1->GetValue
	//string state(statebox->GetValue().mb_str());
	//string detail(detailbox->GetValue().mb_str());
	
	vector<string> strings;

	strings.push_back(string(stateBox->GetValue().mb_str()));
	strings.push_back(string(detailBox->GetValue().mb_str()));
	//strings.push_back(string({VAR}->GetValue().mb_str()));

	// Bug here: wxWidgets default time control does not 'go to the next day' when passing time forward
	//		leading to start: 9pm end: 1am only
	// Could just have a "Ends in" time and allow user to select hours, minutes, and seconds until end
	time_t start = timeBox->GetValue().GetTicks();
	time_t end = endTimeBox->GetValue().GetTicks();

	strings.push_back(std::to_string(start));
	strings.push_back(std::to_string(end));

	strings.push_back(std::to_string(partySize->GetValue()));
	strings.push_back(std::to_string(partyMax->GetValue()));


	//wxMessageBox(std::to_string(timebox->GetValue().GetTicks()));
	bool err = false;
	vector<string> errs;

	for (size_t i = 0; i < 3; i++)
	{
		if (strings[i].length() < 2)
		{
			err = true;
			errs.push_back(labels[i]);
		}
	}

	if (err)
	{
		string msg = "Errors in these entries:\n";
		for (size_t i = 0; i < errs.size(); i++)
		{
			msg += errs[i] + '\n';
		}
		wxMessageBox(msg, wxT("Error!"), wxICON_ERROR);
	}
	else
	{
		updatePresence(strings);
	}
	e.Skip();
}