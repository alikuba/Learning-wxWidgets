// 07_comprehensive_app.cpp - Comprehensive wxWidgets Application
#include <wx/wx.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/artprov.h>
#include <wx/filename.h>

class ComprehensiveApp : public wxApp {
public:
	bool OnInit();
};

class MainFrame : public wxFrame {
public:
	MainFrame();

private:
	void CreateMenuBar();
	void CreateToolBar();
	void CreateStatusBar();
	void CreateMainContent();

	// Menu/toolbar event handlers
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnFont(wxCommandEvent& event);
	void OnColor(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	// Control event handlers
	void OnTextChanged(wxCommandEvent& event);
	void OnListItemSelected(wxListEvent& event);
	void OnTreeItemSelected(wxTreeEvent& event);
	void OnNotebookPageChanged(wxBookCtrlEvent& event);
	void OnAddListItem(wxCommandEvent& event);
	void OnDeleteListItem(wxCommandEvent& event);
	void OnClearLog(wxCommandEvent& event);

	// UI components
	wxSplitterWindow* m_splitter;
	wxNotebook* m_notebook;
	wxTextCtrl* m_textEditor;
	wxTextCtrl* m_logText;
	wxListCtrl* m_listCtrl;
	wxTreeCtrl* m_treeCtrl;
	wxPanel* m_drawingPanel;

	wxString m_currentFile;
	int m_listItemCounter;

	enum {
		ID_New = 1000,
		ID_Open = 1001,
		ID_Save = 1002,
		ID_AddListItem = 1003,
		ID_DeleteListItem = 1004,
		ID_ClearLog = 1005,
		ID_TextEditor = 1006,
		ID_Font = 1007,
		ID_Color = 1008
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	// File menu
	EVT_MENU(ID_New, MainFrame::OnNew)
	EVT_MENU(ID_Open, MainFrame::OnOpen)
	EVT_MENU(ID_Save, MainFrame::OnSave)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	
	// Edit menu
	EVT_MENU(wxID_CUT, MainFrame::OnCut)
	EVT_MENU(wxID_COPY, MainFrame::OnCopy)
	EVT_MENU(wxID_PASTE, MainFrame::OnPaste)
	
	// Format menu
	EVT_MENU(ID_Font, MainFrame::OnFont)
	EVT_MENU(ID_Color, MainFrame::OnColor)
	
	// Help menu
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	
	// Control events
	EVT_TEXT(ID_TextEditor, MainFrame::OnTextChanged)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, MainFrame::OnListItemSelected)
	EVT_TREE_SEL_CHANGED(wxID_ANY, MainFrame::OnTreeItemSelected)
	EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, MainFrame::OnNotebookPageChanged)
	EVT_BUTTON(ID_AddListItem, MainFrame::OnAddListItem)
	EVT_BUTTON(ID_DeleteListItem, MainFrame::OnDeleteListItem)
	EVT_BUTTON(ID_ClearLog, MainFrame::OnClearLog)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(ComprehensiveApp);

bool ComprehensiveApp::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show(true);
	return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Comprehensive wxWidgets Application"),
	m_listItemCounter(1) {
	
	SetSize(1000, 700);
	Center();

	CreateMenuBar();
	CreateToolBar();
	CreateStatusBar();
	CreateMainContent();

	SetStatusText("Ready - Comprehensive wxWidgets demo application");
}

void MainFrame::CreateMenuBar() {
	wxMenuBar* menuBar = new wxMenuBar;

	// File menu
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(ID_New, "&New\tCtrl-N", "Create new document");
	fileMenu->Append(ID_Open, "&Open...\tCtrl-O", "Open existing document");
	fileMenu->Append(ID_Save, "&Save\tCtrl-S", "Save current document");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-Q", "Exit application");

	// Edit menu
	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CUT, "Cu&t\tCtrl-X", "Cut selection");
	editMenu->Append(wxID_COPY, "&Copy\tCtrl-C", "Copy selection");
	editMenu->Append(wxID_PASTE, "&Paste\tCtrl-V", "Paste from clipboard");

	// Format menu
	wxMenu* formatMenu = new wxMenu;
	formatMenu->Append(ID_Font, "&Font...", "Change font");
	formatMenu->Append(ID_Color, "&Color...", "Change text color");

	// Help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "About this application");

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(formatMenu, "F&ormat");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
}

void MainFrame::CreateToolBar() {
	wxToolBar* toolbar = wxFrame::CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);

	toolbar->AddTool(ID_New, "New", wxArtProvider::GetBitmap(wxART_NEW), "New");
	toolbar->AddTool(ID_Open, "Open", wxArtProvider::GetBitmap(wxART_FILE_OPEN), "Open");
	toolbar->AddTool(ID_Save, "Save", wxArtProvider::GetBitmap(wxART_FILE_SAVE), "Save");
	toolbar->AddSeparator();
	toolbar->AddTool(wxID_CUT, "Cut", wxArtProvider::GetBitmap(wxART_CUT), "Cut");
	toolbar->AddTool(wxID_COPY, "Copy", wxArtProvider::GetBitmap(wxART_COPY), "Copy");
	toolbar->AddTool(wxID_PASTE, "Paste", wxArtProvider::GetBitmap(wxART_PASTE), "Paste");

	toolbar->Realize();
}

void MainFrame::CreateStatusBar() {
	wxStatusBar* statusBar = wxFrame::CreateStatusBar(3);
	int widths[] = {-1, 100, 150};
	statusBar->SetStatusWidths(3, widths);
	statusBar->SetStatusText("Ready", 0);
	statusBar->SetStatusText("Lines: 0", 1);
	statusBar->SetStatusText("Characters: 0", 2);
}

void MainFrame::CreateMainContent() {
	// Create main splitter window
	m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxSP_3D | wxSP_LIVE_UPDATE);

	// Left panel with notebook
	m_notebook = new wxNotebook(m_splitter, wxID_ANY);

	// Tab 1: Text Editor
	wxPanel* editorPanel = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* editorSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* editorLabel = new wxStaticText(editorPanel, wxID_ANY, "Text Editor:");
	editorSizer->Add(editorLabel, 0, wxALL, 5);
	
	m_textEditor = new wxTextCtrl(editorPanel, ID_TextEditor, 
		"Welcome to the comprehensive wxWidgets application!\n\n"
		"This application demonstrates:\n"
		"• Multiple UI controls\n"
		"• Event handling\n"
		"• Layout management\n"
		"• Menu and toolbar integration\n"
		"• File operations\n"
		"• Custom drawing\n\n"
		"Try editing this text, using the menus, and exploring other tabs!",
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	editorSizer->Add(m_textEditor, 1, wxEXPAND | wxALL, 5);
	
	editorPanel->SetSizer(editorSizer);
	m_notebook->AddPage(editorPanel, "Text Editor");

	// Tab 2: List Control
	wxPanel* listPanel = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* listSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* listLabel = new wxStaticText(listPanel, wxID_ANY, "List Control:");
	listSizer->Add(listLabel, 0, wxALL, 5);
	
	m_listCtrl = new wxListCtrl(listPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
		wxLC_REPORT | wxLC_SINGLE_SEL);
	
	// Add columns
	m_listCtrl->AppendColumn("Name", wxLIST_FORMAT_LEFT, 120);
	m_listCtrl->AppendColumn("Type", wxLIST_FORMAT_LEFT, 80);
	m_listCtrl->AppendColumn("Size", wxLIST_FORMAT_RIGHT, 80);
	
	// Add sample items
	long index = m_listCtrl->InsertItem(0, "Document.txt");
	m_listCtrl->SetItem(index, 1, "Text");
	m_listCtrl->SetItem(index, 2, "1.2 KB");
	
	index = m_listCtrl->InsertItem(1, "Image.png");
	m_listCtrl->SetItem(index, 1, "Image");
	m_listCtrl->SetItem(index, 2, "45.3 KB");
	
	listSizer->Add(m_listCtrl, 1, wxEXPAND | wxALL, 5);
	
	// List control buttons
	wxBoxSizer* listButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	listButtonSizer->Add(new wxButton(listPanel, ID_AddListItem, "Add Item"), 0, wxALL, 5);
	listButtonSizer->Add(new wxButton(listPanel, ID_DeleteListItem, "Delete Selected"), 0, wxALL, 5);
	listSizer->Add(listButtonSizer, 0, wxALL, 5);
	
	listPanel->SetSizer(listSizer);
	m_notebook->AddPage(listPanel, "List Control");

	// Tab 3: Tree Control
	wxPanel* treePanel = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* treeSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* treeLabel = new wxStaticText(treePanel, wxID_ANY, "Tree Control:");
	treeSizer->Add(treeLabel, 0, wxALL, 5);
	
	m_treeCtrl = new wxTreeCtrl(treePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxTR_DEFAULT_STYLE);
	
	// Populate tree
	wxTreeItemId root = m_treeCtrl->AddRoot("Project");
	wxTreeItemId srcFolder = m_treeCtrl->AppendItem(root, "Source Files");
	m_treeCtrl->AppendItem(srcFolder, "main.cpp");
	m_treeCtrl->AppendItem(srcFolder, "app.cpp");
	m_treeCtrl->AppendItem(srcFolder, "dialog.cpp");
	
	wxTreeItemId headerFolder = m_treeCtrl->AppendItem(root, "Header Files");
	m_treeCtrl->AppendItem(headerFolder, "app.h");
	m_treeCtrl->AppendItem(headerFolder, "dialog.h");
	
	wxTreeItemId resourceFolder = m_treeCtrl->AppendItem(root, "Resources");
	m_treeCtrl->AppendItem(resourceFolder, "icons.rc");
	m_treeCtrl->AppendItem(resourceFolder, "manifest.xml");
	
	m_treeCtrl->Expand(root);
	m_treeCtrl->Expand(srcFolder);
	
	treeSizer->Add(m_treeCtrl, 1, wxEXPAND | wxALL, 5);
	treePanel->SetSizer(treeSizer);
	m_notebook->AddPage(treePanel, "Tree Control");

	// Right panel: Log area
	wxPanel* logPanel = new wxPanel(m_splitter, wxID_ANY);
	wxBoxSizer* logSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* logLabel = new wxStaticText(logPanel, wxID_ANY, "Activity Log:");
	logSizer->Add(logLabel, 0, wxALL, 5);
	
	m_logText = new wxTextCtrl(logPanel, wxID_ANY, "Application started...\n",
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	m_logText->SetBackgroundColour(wxColour(248, 248, 248));
	logSizer->Add(m_logText, 1, wxEXPAND | wxALL, 5);
	
	wxButton* clearLogBtn = new wxButton(logPanel, ID_ClearLog, "Clear Log");
	logSizer->Add(clearLogBtn, 0, wxALL, 5);
	
	logPanel->SetSizer(logSizer);

	// Setup splitter
	m_splitter->SplitVertically(m_notebook, logPanel, 600);
	m_splitter->SetMinimumPaneSize(200);

	// Log initial state
	m_logText->AppendText("UI components initialized\n");
	m_logText->AppendText("Ready for user interaction\n");
}

void MainFrame::OnNew(wxCommandEvent& event) {
	if (!m_textEditor->IsModified() || 
		wxMessageBox("Current document has unsaved changes. Continue?", 
			"Confirm", wxYES_NO | wxICON_QUESTION) == wxYES) {
		
		m_textEditor->Clear();
		m_currentFile.clear();
		SetTitle("Comprehensive wxWidgets Application - [New Document]");
		m_logText->AppendText("New document created\n");
		SetStatusText("New document created");
	}
}

void MainFrame::OnOpen(wxCommandEvent& event) {
	wxFileDialog dialog(this, "Open file", "", "",
		"Text files (*.txt)|*.txt|C++ files (*.cpp)|*.cpp|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dialog.ShowModal() == wxID_OK) {
		m_currentFile = dialog.GetPath();
		if (m_textEditor->LoadFile(m_currentFile)) {
			SetTitle("Comprehensive wxWidgets Application - " + dialog.GetFilename());
			m_logText->AppendText("Opened: " + m_currentFile + "\n");
			SetStatusText("File opened: " + dialog.GetFilename());
		} else {
			wxMessageBox("Failed to open file: " + m_currentFile, "Error", 
				wxOK | wxICON_ERROR);
			m_logText->AppendText("Failed to open: " + m_currentFile + "\n");
		}
	}
}

void MainFrame::OnSave(wxCommandEvent& event) {
	if (m_currentFile.IsEmpty()) {
		wxFileDialog dialog(this, "Save file", "", "",
			"Text files (*.txt)|*.txt|C++ files (*.cpp)|*.cpp|All files (*.*)|*.*",
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dialog.ShowModal() == wxID_OK) {
			m_currentFile = dialog.GetPath();
		} else {
			return;
		}
	}

	if (m_textEditor->SaveFile(m_currentFile)) {
		SetTitle("Comprehensive wxWidgets Application - " + wxFileName(m_currentFile).GetFullName());
		m_logText->AppendText("Saved: " + m_currentFile + "\n");
		SetStatusText("File saved: " + wxFileName(m_currentFile).GetFullName());
	} else {
		wxMessageBox("Failed to save file: " + m_currentFile, "Error", 
			wxOK | wxICON_ERROR);
		m_logText->AppendText("Failed to save: " + m_currentFile + "\n");
	}
}

void MainFrame::OnCut(wxCommandEvent& event) {
	if (m_textEditor->HasFocus()) {
		m_textEditor->Cut();
		m_logText->AppendText("Text cut to clipboard\n");
		SetStatusText("Text cut");
	}
}

void MainFrame::OnCopy(wxCommandEvent& event) {
	if (m_textEditor->HasFocus()) {
		m_textEditor->Copy();
		m_logText->AppendText("Text copied to clipboard\n");
		SetStatusText("Text copied");
	}
}

void MainFrame::OnPaste(wxCommandEvent& event) {
	if (m_textEditor->HasFocus()) {
		m_textEditor->Paste();
		m_logText->AppendText("Text pasted from clipboard\n");
		SetStatusText("Text pasted");
	}
}

void MainFrame::OnFont(wxCommandEvent& event) {
	wxFontDialog dialog(this);
	dialog.GetFontData().SetInitialFont(m_textEditor->GetFont());

	if (dialog.ShowModal() == wxID_OK) {
		wxFont font = dialog.GetFontData().GetChosenFont();
		m_textEditor->SetFont(font);
		m_logText->AppendText(wxString::Format("Font changed to: %s, %d pt\n",
			font.GetFaceName(), font.GetPointSize()));
		SetStatusText("Font changed");
	}
}

void MainFrame::OnColor(wxCommandEvent& event) {
	wxColourDialog dialog(this);

	if (dialog.ShowModal() == wxID_OK) {
		wxColour color = dialog.GetColourData().GetColour();
		m_textEditor->SetForegroundColour(color);
		m_textEditor->Refresh();
		m_logText->AppendText(wxString::Format("Text color changed to RGB(%d, %d, %d)\n",
			color.Red(), color.Green(), color.Blue()));
		SetStatusText("Text color changed");
	}
}

void MainFrame::OnTextChanged(wxCommandEvent& event) {
	wxString text = m_textEditor->GetValue();
	int lines = m_textEditor->GetNumberOfLines();
	size_t chars = text.length();
	
	// Update status bar
	GetStatusBar()->SetStatusText(wxString::Format("Lines: %d", lines), 1);
	GetStatusBar()->SetStatusText(wxString::Format("Characters: %lu", (unsigned long)chars), 2);
}

void MainFrame::OnListItemSelected(wxListEvent& event) {
	long index = event.GetIndex();
	wxString name = m_listCtrl->GetItemText(index);
	wxString type = m_listCtrl->GetItemText(index, 1);
	
	m_logText->AppendText(wxString::Format("List item selected: %s (%s)\n", name, type));
	SetStatusText("Selected: " + name);
}

void MainFrame::OnTreeItemSelected(wxTreeEvent& event) {
	wxTreeItemId item = event.GetItem();
	wxString text = m_treeCtrl->GetItemText(item);
	
	m_logText->AppendText("Tree item selected: " + text + "\n");
	SetStatusText("Tree item: " + text);
}

void MainFrame::OnNotebookPageChanged(wxBookCtrlEvent& event) {
	int page = event.GetSelection();
	wxString pageName = m_notebook->GetPageText(page);
	
	m_logText->AppendText("Switched to tab: " + pageName + "\n");
	SetStatusText("Current tab: " + pageName);
}

void MainFrame::OnAddListItem(wxCommandEvent& event) {
	wxTextEntryDialog dialog(this, "Enter item name:", "Add List Item");
	
	if (dialog.ShowModal() == wxID_OK) {
		wxString name = dialog.GetValue();
		if (!name.IsEmpty()) {
			long index = m_listCtrl->InsertItem(m_listCtrl->GetItemCount(), name);
			m_listCtrl->SetItem(index, 1, "Custom");
			m_listCtrl->SetItem(index, 2, "New");
			
			m_logText->AppendText("Added list item: " + name + "\n");
			SetStatusText("Item added: " + name);
		}
	}
}

void MainFrame::OnDeleteListItem(wxCommandEvent& event) {
	long selected = m_listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (selected != -1) {
		wxString name = m_listCtrl->GetItemText(selected);
		m_listCtrl->DeleteItem(selected);
		m_logText->AppendText("Deleted list item: " + name + "\n");
		SetStatusText("Item deleted: " + name);
	} else {
		wxMessageBox("Please select an item to delete.", "No Selection", 
			wxOK | wxICON_WARNING);
	}
}

void MainFrame::OnClearLog(wxCommandEvent& event) {
	m_logText->Clear();
	m_logText->AppendText("Log cleared\n");
	SetStatusText("Log cleared");
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Comprehensive wxWidgets Application\n\n"
		"This application demonstrates:\n"
		"• Menu bars and toolbars\n"
		"• Multiple types of controls\n"
		"• Event handling\n"
		"• Layout management with sizers\n"
		"• Splitter windows\n"
		"• Notebook controls (tabs)\n"
		"• File operations\n"
		"• Text formatting\n"
		"• Status bars\n\n"
		"Built with wxWidgets 3.2.x",
		"About Comprehensive App", wxOK | wxICON_INFORMATION);
}
