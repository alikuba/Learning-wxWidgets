// 03_layout_sizers.cpp - Layout Management with Sizers
#include <wx/wx.h>

class LayoutApp : public wxApp {
public:
	bool OnInit();
};

class LayoutFrame : public wxFrame {
public:
	LayoutFrame();

private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnButtonClick(wxCommandEvent& event);

	wxTextCtrl* m_textInput;
	wxTextCtrl* m_textOutput;
	wxListBox* m_listBox;

	enum {
		ID_ProcessButton = 1000,
		ID_ClearButton = 1001,
		ID_AddItem = 1002
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(LayoutFrame, wxFrame)
	EVT_MENU(wxID_EXIT, LayoutFrame::OnExit)
	EVT_MENU(wxID_ABOUT, LayoutFrame::OnAbout)
	EVT_BUTTON(ID_ProcessButton, LayoutFrame::OnButtonClick)
	EVT_BUTTON(ID_ClearButton, LayoutFrame::OnButtonClick)
	EVT_BUTTON(ID_AddItem, LayoutFrame::OnButtonClick)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(LayoutApp);

bool LayoutApp::OnInit() {
	LayoutFrame* frame = new LayoutFrame();
	frame->Show(true);
	return true;
}

LayoutFrame::LayoutFrame() : wxFrame(nullptr, wxID_ANY, "Layout Management Tutorial") {
	// Set minimum size
	SetMinSize(wxSize(500, 400));
	SetSize(600, 500);
	Center();

	// Create menu bar
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-Q", "Exit the application");
	menuBar->Append(fileMenu, "&File");

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Layout example ready");

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create main vertical sizer
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Top section with input controls
	wxStaticBoxSizer* inputSection = new wxStaticBoxSizer(wxVERTICAL, panel, "Input Section");
	
	wxStaticText* inputLabel = new wxStaticText(panel, wxID_ANY, "Enter text:");
	inputSection->Add(inputLabel, 0, wxALL, 5);
	
	m_textInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	inputSection->Add(m_textInput, 1, wxEXPAND | wxALL, 5);
	
	// Horizontal sizer for buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* processBtn = new wxButton(panel, ID_ProcessButton, "Process Text");
	wxButton* clearBtn = new wxButton(panel, ID_ClearButton, "Clear");
	
	buttonSizer->Add(processBtn, 0, wxALL, 5);
	buttonSizer->Add(clearBtn, 0, wxALL, 5);
	buttonSizer->AddStretchSpacer(); // Push buttons to left
	
	inputSection->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);

	// Middle section with two columns
	wxBoxSizer* middleSizer = new wxBoxSizer(wxHORIZONTAL);
	
	// Left column - Output text
	wxStaticBoxSizer* outputSection = new wxStaticBoxSizer(wxVERTICAL, panel, "Output");
	m_textOutput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_READONLY);
	outputSection->Add(m_textOutput, 1, wxEXPAND | wxALL, 5);
	
	// Right column - List box
	wxStaticBoxSizer* listSection = new wxStaticBoxSizer(wxVERTICAL, panel, "Items");
	m_listBox = new wxListBox(panel, wxID_ANY);
	m_listBox->Append("Item 1");
	m_listBox->Append("Item 2");
	m_listBox->Append("Item 3");
	
	listSection->Add(m_listBox, 1, wxEXPAND | wxALL, 5);
	
	wxButton* addItemBtn = new wxButton(panel, ID_AddItem, "Add Item");
	listSection->Add(addItemBtn, 0, wxEXPAND | wxALL, 5);
	
	// Add columns to middle sizer (2:1 ratio)
	middleSizer->Add(outputSection, 2, wxEXPAND | wxALL, 5);
	middleSizer->Add(listSection, 1, wxEXPAND | wxALL, 5);

	// Add all sections to main sizer
	mainSizer->Add(inputSection, 1, wxEXPAND | wxALL, 10);
	mainSizer->Add(middleSizer, 2, wxEXPAND | wxALL, 10);

	// Set the sizer to the panel
	panel->SetSizer(mainSizer);
	
	// Layout the sizers
	mainSizer->Layout();
}

void LayoutFrame::OnButtonClick(wxCommandEvent& event) {
	switch (event.GetId()) {
		case ID_ProcessButton: {
			wxString input = m_textInput->GetValue();
			wxString processed = input.Upper(); // Convert to uppercase
			processed.Replace(" ", "_"); // Replace spaces with underscores
			m_textOutput->SetValue("Processed: " + processed);
			SetStatusText("Text processed");
			break;
		}
		case ID_ClearButton:
			m_textInput->Clear();
			m_textOutput->Clear();
			SetStatusText("Text cleared");
			break;
		case ID_AddItem: {
			static int itemCount = 4;
			wxString newItem = wxString::Format("Item %d", itemCount++);
			m_listBox->Append(newItem);
			SetStatusText("Item added: " + newItem);
			break;
		}
	}
}

void LayoutFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void LayoutFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This demonstrates wxWidgets layout management using sizers.\n\n"
		"Features shown:\n"
		"• wxBoxSizer for flexible layouts\n"
		"• wxStaticBoxSizer for grouped controls\n"
		"• Proper resizing behavior\n"
		"• Multiple columns with different proportions",
		"About Layout Tutorial", wxOK | wxICON_INFORMATION);
}
