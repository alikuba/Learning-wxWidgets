// 05_text_controls.cpp - Text Controls and Manipulation
#include <wx/wx.h>
#include <wx/spinctrl.h>

class TextApp : public wxApp {
public:
	bool OnInit();
};

class TextFrame : public wxFrame {
public:
	TextFrame();

private:
	void OnTextChanged(wxCommandEvent& event);
	void OnTextEnter(wxCommandEvent& event);
	void OnFormatText(wxCommandEvent& event);
	void OnClearAll(wxCommandEvent& event);
	void OnSpinChanged(wxSpinEvent& event);
	void OnCheckBox(wxCommandEvent& event);

	wxTextCtrl* m_singleLineText;
	wxTextCtrl* m_multiLineText;
	wxTextCtrl* m_passwordText;
	wxTextCtrl* m_readOnlyText;
	wxTextCtrl* m_outputText;
	wxSpinCtrl* m_spinCtrl;
	wxCheckBox* m_wordWrapCheck;
	wxStaticText* m_statusLabel;

	enum {
		ID_SingleLine = 1000,
		ID_MultiLine = 1001,
		ID_Password = 1002,
		ID_FormatButton = 1003,
		ID_ClearButton = 1004,
		ID_SpinCtrl = 1005,
		ID_WordWrapCheck = 1006
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(TextFrame, wxFrame)
	EVT_TEXT(ID_SingleLine, TextFrame::OnTextChanged)
	EVT_TEXT(ID_MultiLine, TextFrame::OnTextChanged)
	EVT_TEXT(ID_Password, TextFrame::OnTextChanged)
	EVT_TEXT_ENTER(ID_SingleLine, TextFrame::OnTextEnter)
	EVT_BUTTON(ID_FormatButton, TextFrame::OnFormatText)
	EVT_BUTTON(ID_ClearButton, TextFrame::OnClearAll)
	EVT_SPINCTRL(ID_SpinCtrl, TextFrame::OnSpinChanged)
	EVT_CHECKBOX(ID_WordWrapCheck, TextFrame::OnCheckBox)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(TextApp);

bool TextApp::OnInit() {
	TextFrame* frame = new TextFrame();
	frame->Show(true);
	return true;
}

TextFrame::TextFrame() : wxFrame(nullptr, wxID_ANY, "Text Controls Tutorial") {
	SetSize(800, 600);
	Center();

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create main sizer
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Title
	wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Text Controls Demonstration");
	wxFont titleFont = title->GetFont();
	titleFont.SetPointSize(16);
	titleFont.SetWeight(wxFONTWEIGHT_BOLD);
	title->SetFont(titleFont);
	mainSizer->Add(title, 0, wxALL | wxCENTER, 10);

	// Input section
	wxStaticBoxSizer* inputSection = new wxStaticBoxSizer(wxVERTICAL, panel, "Input Controls");

	// Single line text
	inputSection->Add(new wxStaticText(panel, wxID_ANY, "Single Line Text (type and press Enter):"), 
		0, wxALL, 5);
	m_singleLineText = new wxTextCtrl(panel, ID_SingleLine, "Hello World", 
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	inputSection->Add(m_singleLineText, 0, wxEXPAND | wxALL, 5);

	// Password text
	inputSection->Add(new wxStaticText(panel, wxID_ANY, "Password Text:"), 0, wxALL, 5);
	m_passwordText = new wxTextCtrl(panel, ID_Password, "", 
		wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	inputSection->Add(m_passwordText, 0, wxEXPAND | wxALL, 5);

	// Multi-line text with word wrap checkbox
	wxBoxSizer* multiLineSizer = new wxBoxSizer(wxHORIZONTAL);
	multiLineSizer->Add(new wxStaticText(panel, wxID_ANY, "Multi-line Text:"), 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	m_wordWrapCheck = new wxCheckBox(panel, ID_WordWrapCheck, "Word Wrap");
	m_wordWrapCheck->SetValue(true);
	multiLineSizer->Add(m_wordWrapCheck, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	inputSection->Add(multiLineSizer, 0, wxEXPAND);

	m_multiLineText = new wxTextCtrl(panel, ID_MultiLine, 
		"This is a multi-line text control.\nYou can type multiple lines here.\n\nTry typing some text and see how it responds!",
		wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_WORDWRAP);
	inputSection->Add(m_multiLineText, 0, wxEXPAND | wxALL, 5);

	// Read-only text
	inputSection->Add(new wxStaticText(panel, wxID_ANY, "Read-Only Text:"), 0, wxALL, 5);
	m_readOnlyText = new wxTextCtrl(panel, wxID_ANY, 
		"This text cannot be edited - it's read-only!",
		wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_readOnlyText->SetBackgroundColour(*wxLIGHT_GREY);
	inputSection->Add(m_readOnlyText, 0, wxEXPAND | wxALL, 5);

	// Spin control
	wxBoxSizer* spinSizer = new wxBoxSizer(wxHORIZONTAL);
	spinSizer->Add(new wxStaticText(panel, wxID_ANY, "Spin Control:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	m_spinCtrl = new wxSpinCtrl(panel, ID_SpinCtrl, wxEmptyString, 
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 50);
	spinSizer->Add(m_spinCtrl, 0, wxALL, 5);
	inputSection->Add(spinSizer, 0, wxALL, 5);

	// Control buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* formatBtn = new wxButton(panel, ID_FormatButton, "Format Text");
	wxButton* clearBtn = new wxButton(panel, ID_ClearButton, "Clear All");
	buttonSizer->Add(formatBtn, 0, wxALL, 5);
	buttonSizer->Add(clearBtn, 0, wxALL, 5);
	inputSection->Add(buttonSizer, 0, wxALL, 5);

	mainSizer->Add(inputSection, 0, wxEXPAND | wxALL, 10);

	// Output section
	wxStaticBoxSizer* outputSection = new wxStaticBoxSizer(wxVERTICAL, panel, "Output and Status");

	m_outputText = new wxTextCtrl(panel, wxID_ANY, "Output will appear here...\n",
		wxDefaultPosition, wxSize(-1, 150), 
		wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
	m_outputText->SetBackgroundColour(wxColour(240, 248, 255));
	outputSection->Add(m_outputText, 1, wxEXPAND | wxALL, 5);

	// Status label
	m_statusLabel = new wxStaticText(panel, wxID_ANY, "Status: Ready");
	outputSection->Add(m_statusLabel, 0, wxALL, 5);

	mainSizer->Add(outputSection, 1, wxEXPAND | wxALL, 10);

	panel->SetSizer(mainSizer);
	CreateStatusBar();
	SetStatusText("Text Controls Tutorial - Ready");
}

void TextFrame::OnTextChanged(wxCommandEvent& event) {
	wxString output;
	
	switch (event.GetId()) {
		case ID_SingleLine:
			output = wxString::Format("Single line changed: \"%s\" (length: %lu)\n",
				m_singleLineText->GetValue(), (unsigned long)m_singleLineText->GetValue().length());
			break;
		case ID_MultiLine:
			output = wxString::Format("Multi-line changed: %lu lines, %lu characters\n",
				(unsigned long)m_multiLineText->GetNumberOfLines(), (unsigned long)m_multiLineText->GetValue().length());
			break;
		case ID_Password:
			output = wxString::Format("Password changed: %lu characters (hidden)\n",
				(unsigned long)m_passwordText->GetValue().length());
			break;
	}
	
	m_outputText->AppendText(output);
	m_statusLabel->SetLabel("Status: Text modified");
	SetStatusText("Text control modified");
}

void TextFrame::OnTextEnter(wxCommandEvent& event) {
	wxString text = m_singleLineText->GetValue();
	m_outputText->AppendText(wxString::Format("ENTER pressed with text: \"%s\"\n", text));
	m_statusLabel->SetLabel("Status: Enter key pressed");
	SetStatusText("Enter key pressed in single line text");
}

void TextFrame::OnFormatText(wxCommandEvent& event) {
	// Get text from single line
	wxString text = m_singleLineText->GetValue();
	
	// Apply various formatting
	wxString formatted;
	formatted += "Original: " + text + "\n";
	formatted += "UPPERCASE: " + text.Upper() + "\n";
	formatted += "lowercase: " + text.Lower() + "\n";
	formatted += "Reversed: ";
	
	// Reverse the string
	for (int i = text.length() - 1; i >= 0; i--) {
		formatted += text[i];
	}
	formatted += "\n";
	
	// Character count
	formatted += wxString::Format("Character count: %lu\n", (unsigned long)text.length());
	formatted += wxString::Format("Word count: %d\n", 
		text.IsEmpty() ? 0 : (int)text.Freq(' ') + 1);
	
	// Set formatted text to multi-line control
	m_multiLineText->SetValue(formatted);
	
	m_outputText->AppendText("Text formatting applied!\n");
	m_statusLabel->SetLabel("Status: Text formatted");
	SetStatusText("Text formatting complete");
}

void TextFrame::OnClearAll(wxCommandEvent& event) {
	m_singleLineText->Clear();
	m_multiLineText->Clear();
	m_passwordText->Clear();
	m_outputText->Clear();
	
	m_singleLineText->SetValue("Hello World");
	m_multiLineText->SetValue("This is a multi-line text control.\nYou can type multiple lines here.\n\nTry typing some text and see how it responds!");
	m_outputText->AppendText("All text controls cleared and reset!\n");
	
	m_statusLabel->SetLabel("Status: All cleared");
	SetStatusText("All text controls cleared");
}

void TextFrame::OnSpinChanged(wxSpinEvent& event) {
	int value = event.GetInt();
	m_outputText->AppendText(wxString::Format("Spin control value changed to: %d\n", value));
	
	// Change font size based on spin value
	wxFont font = m_readOnlyText->GetFont();
	font.SetPointSize(8 + value / 10);
	m_readOnlyText->SetFont(font);
	m_readOnlyText->SetValue(wxString::Format("Font size: %d (based on spin value %d)", 
		8 + value / 10, value));
	
	m_statusLabel->SetLabel(wxString::Format("Status: Spin value = %d", value));
}

void TextFrame::OnCheckBox(wxCommandEvent& event) {
	bool wordWrap = event.IsChecked();
	
	// Get current text and position
	wxString currentText = m_multiLineText->GetValue();
	long insertionPoint = m_multiLineText->GetInsertionPoint();
	
	// Simply update the style - this is a simplified approach
	// In a real application, you might want to recreate the control properly
	// For now, we'll just log the change
	m_outputText->AppendText(wxString::Format("Word wrap %s\n", 
		wordWrap ? "enabled" : "disabled"));
	
	// Note: Actually changing word wrap dynamically requires recreating the control
	// which is complex and prone to issues. For this tutorial, we'll just show the intent.
	
	m_statusLabel->SetLabel(wxString::Format("Status: Word wrap %s", 
		wordWrap ? "ON" : "OFF"));
}
