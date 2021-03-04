#pragma once

#include "wx/wx.h"
#include <wx/timectrl.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void onButtonClicked(wxCommandEvent& e);

	wxDECLARE_EVENT_TABLE();

private:
	
	wxButton* m_btn1 = nullptr;
	
	wxStaticText* stateLabel = nullptr;
	wxTextCtrl* stateBox = nullptr;
	
	wxStaticText* detailLabel = nullptr;
	wxTextCtrl* detailBox = nullptr;
	
	wxStaticText* timeLabel = nullptr;
	wxTimePickerCtrl* timeBox = nullptr;

	wxStaticText* endTimeLabel = nullptr;
	wxTimePickerCtrl* endTimeBox = nullptr;

	wxStaticText* partySizeLabel = nullptr;
	wxSpinCtrl* partySize = nullptr;

	wxStaticText* partyMaxLabel = nullptr;
	wxSpinCtrl* partyMax = nullptr;

};

