// 02_buttons_events.cpp - Buttons and Event Handling
#include <wx/wx.h>
#include <wx/tglbtn.h>

class ButtonApp : public wxApp {
public:
	bool OnInit();
};

class ButtonFrame : public wxFrame {
public:
	ButtonFrame();

private:
	void OnButtonClick(wxCommandEvent& event);
	void OnToggleButton(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	wxButton* m_button;
	wxToggleButton* m_toggleButton;
	wxStaticText* m_label;
	wxTextCtrl* m_textCtrl;
	int m_clickCount;

	enum {
		ID_Button = 1000,
		ID_ToggleButton = 1001
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ButtonFrame, wxFrame)
	EVT_BUTTON(ID_Button, ButtonFrame::OnButtonClick)
	EVT_TOGGLEBUTTON(ID_ToggleButton, ButtonFrame::OnToggleButton)
	EVT_CLOSE(ButtonFrame::OnClose)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(ButtonApp);

bool ButtonApp::OnInit() {
	ButtonFrame* frame = new ButtonFrame();
	frame->Show(true);
	return true;
}

ButtonFrame::ButtonFrame() : wxFrame(nullptr, wxID_ANY, "Buttons and Events Tutorial", 
	wxDefaultPosition, wxSize(400, 300)), m_clickCount(0) {
	
	Center();

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create controls
	m_label = new wxStaticText(panel, wxID_ANY, "Click count: 0", 
		wxPoint(20, 20));

	m_button = new wxButton(panel, ID_Button, "Click Me!", 
		wxPoint(20, 50), wxSize(100, 30));

	m_toggleButton = new wxToggleButton(panel, ID_ToggleButton, "Toggle", 
		wxPoint(140, 50), wxSize(100, 30));

	m_textCtrl = new wxTextCtrl(panel, wxID_ANY, "Type here...", 
		wxPoint(20, 100), wxSize(200, 25));

	// Additional buttons for demonstration
	wxButton* closeBtn = new wxButton(panel, wxID_EXIT, "Close", 
		wxPoint(20, 150), wxSize(100, 30));

	// Bind additional events
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent&) { Close(true); }, wxID_EXIT);

	CreateStatusBar();
	SetStatusText("Ready");
}

void ButtonFrame::OnButtonClick(wxCommandEvent& event) {
	m_clickCount++;
	m_label->SetLabel(wxString::Format("Click count: %d", m_clickCount));
	
	SetStatusText(wxString::Format("Button clicked %d times", m_clickCount));
	
	// Change button color after 5 clicks
	if (m_clickCount >= 5) {
		m_button->SetBackgroundColour(*wxRED);
		m_button->SetLabel("Wow!");
	}
}

void ButtonFrame::OnToggleButton(wxCommandEvent& event) {
	if (m_toggleButton->GetValue()) {
		m_toggleButton->SetLabel("ON");
		m_textCtrl->SetBackgroundColour(*wxLIGHT_GREY);
		SetStatusText("Toggle is ON");
	} else {
		m_toggleButton->SetLabel("OFF");
		m_textCtrl->SetBackgroundColour(*wxWHITE);
		SetStatusText("Toggle is OFF");
	}
	m_textCtrl->Refresh();
}

void ButtonFrame::OnClose(wxCloseEvent& event) {
	Destroy();
}
