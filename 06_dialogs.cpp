// 06_dialogs.cpp - Dialog Boxes Tutorial
#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/progdlg.h>
#include <wx/textdlg.h>
#include <wx/choicdlg.h>
#include <wx/numdlg.h>

// Custom dialog class
class CustomDialog : public wxDialog {
public:
	CustomDialog(wxWindow* parent);
	
	wxString GetUserData() const { return m_userData; }
	
private:
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	
	wxTextCtrl* m_nameText;
	wxTextCtrl* m_emailText;
	wxChoice* m_ageChoice;
	wxCheckBox* m_subscribeCheck;
	wxString m_userData;
	
	wxDECLARE_EVENT_TABLE();
};

// Main application
class DialogApp : public wxApp {
public:
	bool OnInit();
};

class DialogFrame : public wxFrame {
public:
	DialogFrame();

private:
	void OnMessageDialog(wxCommandEvent& event);
	void OnConfirmDialog(wxCommandEvent& event);
	void OnFileDialog(wxCommandEvent& event);
	void OnColorDialog(wxCommandEvent& event);
	void OnFontDialog(wxCommandEvent& event);
	void OnTextDialog(wxCommandEvent& event);
	void OnChoiceDialog(wxCommandEvent& event);
	void OnNumberDialog(wxCommandEvent& event);
	void OnProgressDialog(wxCommandEvent& event);
	void OnCustomDialog(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxTextCtrl* m_logText;
	wxPanel* m_colorPanel;
	wxStaticText* m_fontLabel;

	enum {
		ID_MessageDialog = 1000,
		ID_ConfirmDialog = 1001,
		ID_FileDialog = 1002,
		ID_ColorDialog = 1003,
		ID_FontDialog = 1004,
		ID_TextDialog = 1005,
		ID_ChoiceDialog = 1006,
		ID_NumberDialog = 1007,
		ID_ProgressDialog = 1008,
		ID_CustomDialog = 1009
	};

	wxDECLARE_EVENT_TABLE();
};

// Custom Dialog Event Table
wxBEGIN_EVENT_TABLE(CustomDialog, wxDialog)
	EVT_BUTTON(wxID_OK, CustomDialog::OnOK)
	EVT_BUTTON(wxID_CANCEL, CustomDialog::OnCancel)
wxEND_EVENT_TABLE()

// Main Frame Event Table
wxBEGIN_EVENT_TABLE(DialogFrame, wxFrame)
	EVT_BUTTON(ID_MessageDialog, DialogFrame::OnMessageDialog)
	EVT_BUTTON(ID_ConfirmDialog, DialogFrame::OnConfirmDialog)
	EVT_BUTTON(ID_FileDialog, DialogFrame::OnFileDialog)
	EVT_BUTTON(ID_ColorDialog, DialogFrame::OnColorDialog)
	EVT_BUTTON(ID_FontDialog, DialogFrame::OnFontDialog)
	EVT_BUTTON(ID_TextDialog, DialogFrame::OnTextDialog)
	EVT_BUTTON(ID_ChoiceDialog, DialogFrame::OnChoiceDialog)
	EVT_BUTTON(ID_NumberDialog, DialogFrame::OnNumberDialog)
	EVT_BUTTON(ID_ProgressDialog, DialogFrame::OnProgressDialog)
	EVT_BUTTON(ID_CustomDialog, DialogFrame::OnCustomDialog)
	EVT_MENU(wxID_ABOUT, DialogFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(DialogApp);

// Custom Dialog Implementation
CustomDialog::CustomDialog(wxWindow* parent) 
	: wxDialog(parent, wxID_ANY, "Custom Dialog", wxDefaultPosition, wxSize(400, 300)) {
	
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	
	// Title
	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Please fill in your information:");
	wxFont titleFont = title->GetFont();
	titleFont.SetWeight(wxFONTWEIGHT_BOLD);
	title->SetFont(titleFont);
	mainSizer->Add(title, 0, wxALL | wxCENTER, 10);
	
	// Form fields
	wxFlexGridSizer* formSizer = new wxFlexGridSizer(4, 2, 5, 10);
	formSizer->AddGrowableCol(1, 1);
	
	// Name
	formSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"), 0, wxALIGN_CENTER_VERTICAL);
	m_nameText = new wxTextCtrl(this, wxID_ANY);
	formSizer->Add(m_nameText, 1, wxEXPAND);
	
	// Email
	formSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"), 0, wxALIGN_CENTER_VERTICAL);
	m_emailText = new wxTextCtrl(this, wxID_ANY);
	formSizer->Add(m_emailText, 1, wxEXPAND);
	
	// Age
	formSizer->Add(new wxStaticText(this, wxID_ANY, "Age Range:"), 0, wxALIGN_CENTER_VERTICAL);
	m_ageChoice = new wxChoice(this, wxID_ANY);
	m_ageChoice->Append("Under 18");
	m_ageChoice->Append("18-25");
	m_ageChoice->Append("26-35");
	m_ageChoice->Append("36-50");
	m_ageChoice->Append("Over 50");
	m_ageChoice->SetSelection(1);
	formSizer->Add(m_ageChoice, 1, wxEXPAND);
	
	// Subscribe checkbox
	formSizer->Add(new wxStaticText(this, wxID_ANY, ""), 0); // Empty space
	m_subscribeCheck = new wxCheckBox(this, wxID_ANY, "Subscribe to newsletter");
	formSizer->Add(m_subscribeCheck, 0);
	
	mainSizer->Add(formSizer, 1, wxEXPAND | wxALL, 20);
	
	// Buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxALL | wxCENTER, 10);
	
	SetSizer(mainSizer);
	m_nameText->SetFocus();
}

void CustomDialog::OnOK(wxCommandEvent& event) {
	// Validate input
	if (m_nameText->GetValue().IsEmpty()) {
		wxMessageBox("Please enter your name.", "Validation Error", wxOK | wxICON_WARNING);
		return;
	}
	
	if (m_emailText->GetValue().IsEmpty()) {
		wxMessageBox("Please enter your email.", "Validation Error", wxOK | wxICON_WARNING);
		return;
	}
	
	// Collect data
	m_userData = wxString::Format("Name: %s\nEmail: %s\nAge: %s\nNewsletter: %s",
		m_nameText->GetValue(),
		m_emailText->GetValue(),
		m_ageChoice->GetStringSelection(),
		m_subscribeCheck->IsChecked() ? "Yes" : "No");
	
	EndModal(wxID_OK);
}

void CustomDialog::OnCancel(wxCommandEvent& event) {
	EndModal(wxID_CANCEL);
}

// Main Application
bool DialogApp::OnInit() {
	DialogFrame* frame = new DialogFrame();
	frame->Show(true);
	return true;
}

DialogFrame::DialogFrame() : wxFrame(nullptr, wxID_ANY, "Dialog Boxes Tutorial") {
	SetSize(800, 600);
	Center();

	// Create menu
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "About dialog tutorial");
	menuBar->Append(helpMenu, "&Help");
	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Click buttons to test different dialogs");

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Title
	wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Dialog Boxes Demonstration");
	wxFont titleFont = title->GetFont();
	titleFont.SetPointSize(16);
	titleFont.SetWeight(wxFONTWEIGHT_BOLD);
	title->SetFont(titleFont);
	mainSizer->Add(title, 0, wxALL | wxCENTER, 10);

	// Button grid
	wxGridSizer* buttonSizer = new wxGridSizer(3, 3, 10, 10);
	
	buttonSizer->Add(new wxButton(panel, ID_MessageDialog, "Message\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_ConfirmDialog, "Confirm\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_FileDialog, "File\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_ColorDialog, "Color\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_FontDialog, "Font\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_TextDialog, "Text Input\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_ChoiceDialog, "Choice\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_NumberDialog, "Number\nDialog"), 1, wxEXPAND);
	buttonSizer->Add(new wxButton(panel, ID_ProgressDialog, "Progress\nDialog"), 1, wxEXPAND);
	
	mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 20);

	// Custom dialog button
	wxButton* customBtn = new wxButton(panel, ID_CustomDialog, "Custom Dialog");
	customBtn->SetBackgroundColour(*wxLIGHT_GREY);
	mainSizer->Add(customBtn, 0, wxCENTER | wxALL, 10);

	// Color preview panel
	wxStaticBoxSizer* previewSizer = new wxStaticBoxSizer(wxVERTICAL, panel, "Preview Area");
	m_colorPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 50));
	m_colorPanel->SetBackgroundColour(*wxWHITE);
	previewSizer->Add(m_colorPanel, 0, wxEXPAND | wxALL, 5);
	
	m_fontLabel = new wxStaticText(panel, wxID_ANY, "Sample text with current font");
	previewSizer->Add(m_fontLabel, 0, wxCENTER | wxALL, 5);
	
	mainSizer->Add(previewSizer, 0, wxEXPAND | wxALL, 20);

	// Log text
	wxStaticBoxSizer* logSizer = new wxStaticBoxSizer(wxVERTICAL, panel, "Dialog Results Log");
	m_logText = new wxTextCtrl(panel, wxID_ANY, "Dialog results will appear here...\n",
		wxDefaultPosition, wxSize(-1, 150), wxTE_MULTILINE | wxTE_READONLY);
	m_logText->SetBackgroundColour(wxColour(248, 248, 248));
	logSizer->Add(m_logText, 1, wxEXPAND | wxALL, 5);
	
	mainSizer->Add(logSizer, 1, wxEXPAND | wxALL, 20);

	panel->SetSizer(mainSizer);
}

void DialogFrame::OnMessageDialog(wxCommandEvent& event) {
	wxMessageBox("This is a simple message dialog.\n\nYou can display information to users this way!",
		"Information", wxOK | wxICON_INFORMATION);
	
	m_logText->AppendText("Message dialog shown\n");
	SetStatusText("Message dialog closed");
}

void DialogFrame::OnConfirmDialog(wxCommandEvent& event) {
	int result = wxMessageBox("Do you want to continue with this operation?",
		"Confirm Action", wxYES_NO | wxICON_QUESTION);
	
	wxString resultText = (result == wxYES) ? "User clicked YES" : "User clicked NO";
	m_logText->AppendText("Confirm dialog: " + resultText + "\n");
	SetStatusText("Confirm dialog: " + resultText);
}

void DialogFrame::OnFileDialog(wxCommandEvent& event) {
	wxFileDialog dialog(this, "Choose a file", "", "",
		"Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (dialog.ShowModal() == wxID_OK) {
		wxString path = dialog.GetPath();
		m_logText->AppendText("File selected: " + path + "\n");
		SetStatusText("File selected: " + dialog.GetFilename());
	} else {
		m_logText->AppendText("File dialog cancelled\n");
		SetStatusText("File selection cancelled");
	}
}

void DialogFrame::OnColorDialog(wxCommandEvent& event) {
	wxColourDialog dialog(this);
	
	if (dialog.ShowModal() == wxID_OK) {
		wxColour color = dialog.GetColourData().GetColour();
		m_colorPanel->SetBackgroundColour(color);
		m_colorPanel->Refresh();
		
		m_logText->AppendText(wxString::Format("Color selected: RGB(%d, %d, %d)\n",
			color.Red(), color.Green(), color.Blue()));
		SetStatusText("Color selected and applied to preview panel");
	} else {
		m_logText->AppendText("Color dialog cancelled\n");
		SetStatusText("Color selection cancelled");
	}
}

void DialogFrame::OnFontDialog(wxCommandEvent& event) {
	wxFontDialog dialog(this);
	
	if (dialog.ShowModal() == wxID_OK) {
		wxFont font = dialog.GetFontData().GetChosenFont();
		m_fontLabel->SetFont(font);
		
		m_logText->AppendText(wxString::Format("Font selected: %s, %d pt\n",
			font.GetFaceName(), font.GetPointSize()));
		SetStatusText("Font selected and applied to sample text");
	} else {
		m_logText->AppendText("Font dialog cancelled\n");
		SetStatusText("Font selection cancelled");
	}
}

void DialogFrame::OnTextDialog(wxCommandEvent& event) {
	wxTextEntryDialog dialog(this, "Please enter some text:", "Text Input");
	
	if (dialog.ShowModal() == wxID_OK) {
		wxString text = dialog.GetValue();
		m_logText->AppendText("Text entered: \"" + text + "\"\n");
		SetStatusText("Text input received");
	} else {
		m_logText->AppendText("Text input cancelled\n");
		SetStatusText("Text input cancelled");
	}
}

void DialogFrame::OnChoiceDialog(wxCommandEvent& event) {
	wxArrayString choices;
	choices.Add("Option 1");
	choices.Add("Option 2"); 
	choices.Add("Option 3");
	choices.Add("Option 4");
	choices.Add("Option 5");
	
	wxSingleChoiceDialog dialog(this, "Please select an option:", "Choice Dialog", choices);
	
	if (dialog.ShowModal() == wxID_OK) {
		wxString choice = dialog.GetStringSelection();
		int index = dialog.GetSelection();
		m_logText->AppendText(wxString::Format("Choice selected: \"%s\" (index %d)\n", choice, index));
		SetStatusText("Choice selected: " + choice);
	} else {
		m_logText->AppendText("Choice dialog cancelled\n");
		SetStatusText("Choice selection cancelled");
	}
}

void DialogFrame::OnNumberDialog(wxCommandEvent& event) {
	long number = wxGetNumberFromUser("Enter a number between 1 and 100:",
		"Number:", "Number Input Dialog", 50, 1, 100, this);
	
	if (number != -1) {
		m_logText->AppendText(wxString::Format("Number entered: %ld\n", number));
		SetStatusText(wxString::Format("Number entered: %ld", number));
	} else {
		m_logText->AppendText("Number input cancelled\n");
		SetStatusText("Number input cancelled");
	}
}

void DialogFrame::OnProgressDialog(wxCommandEvent& event) {
	wxProgressDialog dialog("Progress Dialog", "Working, please wait...", 100, this,
		wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_REMAINING_TIME | wxPD_AUTO_HIDE);
	
	bool cancelled = false;
	for (int i = 0; i <= 100 && !cancelled; i++) {
		wxString message = wxString::Format("Processing step %d of 100...", i);
		cancelled = !dialog.Update(i, message);
		
		// Simulate work
		wxMilliSleep(50);
	}
	
	if (cancelled) {
		m_logText->AppendText("Progress dialog cancelled by user\n");
		SetStatusText("Progress cancelled");
	} else {
		m_logText->AppendText("Progress dialog completed successfully\n");
		SetStatusText("Progress completed");
	}
}

void DialogFrame::OnCustomDialog(wxCommandEvent& event) {
	CustomDialog dialog(this);
	
	if (dialog.ShowModal() == wxID_OK) {
		wxString userData = dialog.GetUserData();
		m_logText->AppendText("Custom dialog data:\n" + userData + "\n\n");
		SetStatusText("Custom dialog completed");
	} else {
		m_logText->AppendText("Custom dialog cancelled\n");
		SetStatusText("Custom dialog cancelled");
	}
}

void DialogFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This demonstrates various wxWidgets dialog types.\n\n"
		"Dialogs shown:\n"
		"• Message dialogs\n"
		"• File/Color/Font dialogs\n"
		"• Input dialogs\n"
		"• Progress dialogs\n"
		"• Custom dialogs\n\n"
		"Each dialog type serves different purposes in GUI applications.",
		"About Dialog Tutorial", wxOK | wxICON_INFORMATION);
}
