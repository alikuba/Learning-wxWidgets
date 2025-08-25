// 04_menus_toolbars.cpp - Menus and Toolbars
#include <wx/wx.h>
#include <wx/artprov.h>

class MenuApp : public wxApp {
public:
	bool OnInit();
};

class MenuFrame : public wxFrame {
public:
	MenuFrame();

private:
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnToggleToolbar(wxCommandEvent& event);
	void OnToggleStatusbar(wxCommandEvent& event);

	void CreateMenuBar();
	void CreateToolBar();

	wxTextCtrl* m_textCtrl;
	wxToolBar* m_toolbar;

	enum {
		ID_New = 1000,
		ID_Open = 1001,
		ID_Save = 1002,
		ID_Undo = 1003,
		ID_Redo = 1004,
		ID_ToggleToolbar = 1005,
		ID_ToggleStatusbar = 1006
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MenuFrame, wxFrame)
	EVT_MENU(ID_New, MenuFrame::OnNew)
	EVT_MENU(ID_Open, MenuFrame::OnOpen)
	EVT_MENU(ID_Save, MenuFrame::OnSave)
	EVT_MENU(wxID_EXIT, MenuFrame::OnExit)
	EVT_MENU(ID_Undo, MenuFrame::OnUndo)
	EVT_MENU(ID_Redo, MenuFrame::OnRedo)
	EVT_MENU(wxID_CUT, MenuFrame::OnCut)
	EVT_MENU(wxID_COPY, MenuFrame::OnCopy)
	EVT_MENU(wxID_PASTE, MenuFrame::OnPaste)
	EVT_MENU(wxID_ABOUT, MenuFrame::OnAbout)
	EVT_MENU(ID_ToggleToolbar, MenuFrame::OnToggleToolbar)
	EVT_MENU(ID_ToggleStatusbar, MenuFrame::OnToggleStatusbar)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MenuApp);

bool MenuApp::OnInit() {
	MenuFrame* frame = new MenuFrame();
	frame->Show(true);
	return true;
}

MenuFrame::MenuFrame() : wxFrame(nullptr, wxID_ANY, "Menus and Toolbars Tutorial") {
	SetSize(700, 500);
	Center();

	CreateMenuBar();
	CreateToolBar();
	
	CreateStatusBar();
	SetStatusText("Ready");

	// Create main text control
	m_textCtrl = new wxTextCtrl(this, wxID_ANY, 
		"Welcome to the Menu and Toolbar tutorial!\n\n"
		"Try the menu items and toolbar buttons.\n"
		"You can:\n"
		"• Create new documents\n"
		"• Open and save files\n"
		"• Use edit operations\n"
		"• Toggle UI elements\n\n"
		"Type some text here to test copy/cut/paste operations.",
		wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH);
}

void MenuFrame::CreateMenuBar() {
	wxMenuBar* menuBar = new wxMenuBar;

	// File menu
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(ID_New, "&New\tCtrl-N", "Create a new document");
	fileMenu->Append(ID_Open, "&Open...\tCtrl-O", "Open an existing document");
	fileMenu->Append(ID_Save, "&Save\tCtrl-S", "Save the current document");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-Q", "Exit the application");

	// Edit menu
	wxMenu* editMenu = new wxMenu;
	editMenu->Append(ID_Undo, "&Undo\tCtrl-Z", "Undo the last action");
	editMenu->Append(ID_Redo, "&Redo\tCtrl-Y", "Redo the last undone action");
	editMenu->AppendSeparator();
	editMenu->Append(wxID_CUT, "Cu&t\tCtrl-X", "Cut the selection");
	editMenu->Append(wxID_COPY, "&Copy\tCtrl-C", "Copy the selection");
	editMenu->Append(wxID_PASTE, "&Paste\tCtrl-V", "Paste from clipboard");

	// View menu
	wxMenu* viewMenu = new wxMenu;
	viewMenu->AppendCheckItem(ID_ToggleToolbar, "Show &Toolbar", "Show or hide the toolbar");
	viewMenu->AppendCheckItem(ID_ToggleStatusbar, "Show &Statusbar", "Show or hide the statusbar");
	// Check these items by default
	viewMenu->Check(ID_ToggleToolbar, true);
	viewMenu->Check(ID_ToggleStatusbar, true);

	// Help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	// Add menus to menu bar
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(viewMenu, "&View");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
}

void MenuFrame::CreateToolBar() {
    wxFrame::CreateToolBar(); // Create default toolbar
    m_toolbar = GetToolBar(); // Get the created toolbar

	// Add toolbar tools
m_toolbar->AddTool(ID_New, "New", wxArtProvider::GetBitmap(wxART_NEW), "New document");
m_toolbar->AddTool(ID_Open, "Open", wxArtProvider::GetBitmap(wxART_FILE_OPEN), "Open document");
m_toolbar->AddTool(ID_Save, "Save", wxArtProvider::GetBitmap(wxART_FILE_SAVE), "Save document");
	
	m_toolbar->AddSeparator();
	
m_toolbar->AddTool(ID_Undo, "Undo", wxArtProvider::GetBitmap(wxART_UNDO), "Undo");
m_toolbar->AddTool(ID_Redo, "Redo", wxArtProvider::GetBitmap(wxART_REDO), "Redo");
	
	m_toolbar->AddSeparator();
	
m_toolbar->AddTool(wxID_CUT, "Cut", wxArtProvider::GetBitmap(wxART_CUT), "Cut");
m_toolbar->AddTool(wxID_COPY, "Copy", wxArtProvider::GetBitmap(wxART_COPY), "Copy");
m_toolbar->AddTool(wxID_PASTE, "Paste", wxArtProvider::GetBitmap(wxART_PASTE), "Paste");

	m_toolbar->Realize();
}

void MenuFrame::OnNew(wxCommandEvent& event) {
	m_textCtrl->Clear();
	SetStatusText("New document created");
}

void MenuFrame::OnOpen(wxCommandEvent& event) {
	wxFileDialog openDialog(this, "Open file", "", "", 
		"Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openDialog.ShowModal() == wxID_CANCEL) {
		SetStatusText("Open cancelled");
		return;
	}

	wxString filename = openDialog.GetPath();
	if (!m_textCtrl->LoadFile(filename)) {
		wxMessageBox("Failed to open file: " + filename, "Error", 
			wxOK | wxICON_ERROR);
		SetStatusText("Failed to open file");
	} else {
		SetStatusText("Opened: " + filename);
	}
}

void MenuFrame::OnSave(wxCommandEvent& event) {
	wxFileDialog saveDialog(this, "Save file", "", "", 
		"Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveDialog.ShowModal() == wxID_CANCEL) {
		SetStatusText("Save cancelled");
		return;
	}

	wxString filename = saveDialog.GetPath();
	if (!m_textCtrl->SaveFile(filename)) {
		wxMessageBox("Failed to save file: " + filename, "Error", 
			wxOK | wxICON_ERROR);
		SetStatusText("Failed to save file");
	} else {
		SetStatusText("Saved: " + filename);
	}
}

void MenuFrame::OnUndo(wxCommandEvent& event) {
	if (m_textCtrl->CanUndo()) {
		m_textCtrl->Undo();
		SetStatusText("Undo performed");
	} else {
		SetStatusText("Nothing to undo");
	}
}

void MenuFrame::OnRedo(wxCommandEvent& event) {
	if (m_textCtrl->CanRedo()) {
		m_textCtrl->Redo();
		SetStatusText("Redo performed");
	} else {
		SetStatusText("Nothing to redo");
	}
}

void MenuFrame::OnCut(wxCommandEvent& event) {
	m_textCtrl->Cut();
	SetStatusText("Text cut to clipboard");
}

void MenuFrame::OnCopy(wxCommandEvent& event) {
	m_textCtrl->Copy();
	SetStatusText("Text copied to clipboard");
}

void MenuFrame::OnPaste(wxCommandEvent& event) {
	m_textCtrl->Paste();
	SetStatusText("Text pasted from clipboard");
}

void MenuFrame::OnToggleToolbar(wxCommandEvent& event) {
	wxToolBar* toolbar = GetToolBar();
	if (toolbar->IsShown()) {
		toolbar->Show(false);
		SetStatusText("Toolbar hidden");
	} else {
		toolbar->Show(true);
		SetStatusText("Toolbar shown");
	}
	SendSizeEvent(); // Refresh layout
}

void MenuFrame::OnToggleStatusbar(wxCommandEvent& event) {
	wxStatusBar* statusbar = GetStatusBar();
	if (statusbar->IsShown()) {
		statusbar->Show(false);
	} else {
		statusbar->Show(true);
		SetStatusText("Statusbar shown");
	}
	SendSizeEvent(); // Refresh layout
}

void MenuFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MenuFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This demonstrates wxWidgets menus and toolbars.\n\n"
		"Features shown:\n"
		"• Menu bar with multiple menus\n"
		"• Toolbar with icons and text\n"
		"• Keyboard shortcuts\n"
		"• Checkable menu items\n"
		"• File dialogs\n"
		"• Standard edit operations\n"
		"• Dynamic UI toggling",
		"About Menu Tutorial", wxOK | wxICON_INFORMATION);
}
