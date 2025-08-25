// obsidian_app.cpp - Custom Obsidian-like Note Taking Application
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/html/htmlwin.h>
#include <wx/stc/stc.h>
#include <wx/aui/aui.h>
#include <wx/listctrl.h>
#include <wx/artprov.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/textdlg.h>
#include <wx/config.h>
#include <fstream>
#include <regex>

class ObsidianApp : public wxApp {
public:
	bool OnInit();
};

class MainFrame : public wxFrame {
public:
	MainFrame();
	~MainFrame();

private:
	void CreateMenuBar();
	void CreateToolBar();
	void CreateUI();
	void LoadVault(const wxString& path);
	void PopulateFileTree(const wxString& path);
	void OpenNote(const wxString& filepath);
	void SaveCurrentNote();
	void NewNote();
	void RefreshPreview();
	wxString MarkdownToHTML(const wxString& markdown);
	
	// Event handlers
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnOpenVault(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSearch(wxCommandEvent& event);
	void OnTogglePreview(wxCommandEvent& event);
	void OnPreferences(wxCommandEvent& event);
	
	void OnTreeItemActivated(wxTreeEvent& event);
	void OnTreeItemMenu(wxTreeEvent& event);
	void OnEditorChanged(wxStyledTextEvent& event);
	void OnClose(wxCloseEvent& event);

	// UI Components
	wxAuiManager m_mgr;
	wxSplitterWindow* m_mainSplitter;
	wxSplitterWindow* m_rightSplitter;
	
	wxTreeCtrl* m_fileTree;
	wxStyledTextCtrl* m_editor;
	wxHtmlWindow* m_preview;
	wxTextCtrl* m_searchCtrl;
	wxListCtrl* m_searchResults;
	
	// Data
	wxString m_vaultPath;
	wxString m_currentFile;
	bool m_modified;
	wxTreeItemId m_rootItem;

	enum {
		ID_New = 1000,
		ID_Open = 1001,
		ID_Save = 1002,
		ID_OpenVault = 1003,
		ID_Search = 1004,
		ID_TogglePreview = 1005,
		ID_Preferences = 1006,
		ID_Editor = 1007
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	// File menu
	EVT_MENU(ID_New, MainFrame::OnNew)
	EVT_MENU(ID_Open, MainFrame::OnOpen)
	EVT_MENU(ID_Save, MainFrame::OnSave)
	EVT_MENU(ID_OpenVault, MainFrame::OnOpenVault)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	
	// View menu
	EVT_MENU(ID_Search, MainFrame::OnSearch)
	EVT_MENU(ID_TogglePreview, MainFrame::OnTogglePreview)
	EVT_MENU(ID_Preferences, MainFrame::OnPreferences)
	
	// Help menu
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	
	// Control events
	EVT_TREE_ITEM_ACTIVATED(wxID_ANY, MainFrame::OnTreeItemActivated)
	EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, MainFrame::OnTreeItemMenu)
	EVT_STC_CHANGE(ID_Editor, MainFrame::OnEditorChanged)
	EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(ObsidianApp);

bool ObsidianApp::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show(true);
	return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Custom Obsidian", 
	wxDefaultPosition, wxSize(1200, 800)), m_modified(false) {
	
	Center();
	
	CreateMenuBar();
	CreateToolBar();
	CreateUI();
	
	// Load last vault if available
	wxConfig config("CustomObsidian");
	wxString lastVault;
	if (config.Read("LastVault", &lastVault) && wxDirExists(lastVault)) {
		LoadVault(lastVault);
	}
	
	SetStatusText("Ready - Open a vault to get started");
}

MainFrame::~MainFrame() {
	// Save configuration
	wxConfig config("CustomObsidian");
	if (!m_vaultPath.IsEmpty()) {
		config.Write("LastVault", m_vaultPath);
	}
	
	m_mgr.UnInit();
}

void MainFrame::CreateMenuBar() {
	wxMenuBar* menuBar = new wxMenuBar;

	// File menu
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(ID_OpenVault, "Open &Vault...\tCtrl-O", "Open a notes vault");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_New, "&New Note\tCtrl-N", "Create new note");
	fileMenu->Append(ID_Save, "&Save\tCtrl-S", "Save current note");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-Q", "Exit application");

	// Edit menu
	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_CUT, "Cu&t\tCtrl-X", "Cut selection");
	editMenu->Append(wxID_COPY, "&Copy\tCtrl-C", "Copy selection");
	editMenu->Append(wxID_PASTE, "&Paste\tCtrl-V", "Paste from clipboard");
	editMenu->AppendSeparator();
	editMenu->Append(ID_Search, "&Search in Vault\tCtrl-F", "Search all notes");

	// View menu
	wxMenu* viewMenu = new wxMenu;
	viewMenu->AppendCheckItem(ID_TogglePreview, "Show &Preview\tCtrl-P", "Toggle markdown preview");
	viewMenu->Check(ID_TogglePreview, true);
	viewMenu->Append(ID_Preferences, "Pre&ferences...", "Application preferences");

	// Help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "About Custom Obsidian");

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(viewMenu, "&View");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
}

void MainFrame::CreateToolBar() {
	wxToolBar* toolbar = wxFrame::CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);

	toolbar->AddTool(ID_OpenVault, "Open Vault", 
		wxArtProvider::GetBitmap(wxART_FOLDER_OPEN), "Open Vault");
	toolbar->AddTool(ID_New, "New Note", 
		wxArtProvider::GetBitmap(wxART_NEW), "New Note");
	toolbar->AddTool(ID_Save, "Save", 
		wxArtProvider::GetBitmap(wxART_FILE_SAVE), "Save");
	toolbar->AddSeparator();
	toolbar->AddTool(ID_Search, "Search", 
		wxArtProvider::GetBitmap(wxART_FIND), "Search");
	toolbar->AddTool(ID_TogglePreview, "Preview", 
		wxArtProvider::GetBitmap(wxART_HELP_SIDE_PANEL), "Toggle Preview");

	toolbar->Realize();
}

void MainFrame::CreateUI() {
	// Initialize AUI manager
	m_mgr.SetManagedWindow(this);

	// Create file tree
	m_fileTree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(250, -1),
		wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS);
	
	// Create editor with syntax highlighting
	m_editor = new wxStyledTextCtrl(this, ID_Editor);
	
	// Configure editor for markdown
	m_editor->StyleSetFont(wxSTC_STYLE_DEFAULT, wxFont(12, wxFONTFAMILY_TELETYPE, 
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_editor->SetLexer(wxSTC_LEX_MARKDOWN);
	m_editor->SetTabWidth(4);
	m_editor->SetUseTabs(true);
	m_editor->SetWrapMode(wxSTC_WRAP_WORD);
	
	// Markdown syntax highlighting
	m_editor->StyleSetForeground(wxSTC_MARKDOWN_HEADER1, wxColour(0, 0, 255));
	m_editor->StyleSetBold(wxSTC_MARKDOWN_HEADER1, true);
	m_editor->StyleSetSize(wxSTC_MARKDOWN_HEADER1, 16);
	
	m_editor->StyleSetForeground(wxSTC_MARKDOWN_HEADER2, wxColour(0, 100, 0));
	m_editor->StyleSetBold(wxSTC_MARKDOWN_HEADER2, true);
	m_editor->StyleSetSize(wxSTC_MARKDOWN_HEADER2, 14);
	
	m_editor->StyleSetForeground(wxSTC_MARKDOWN_STRONG1, wxColour(139, 69, 19));
	m_editor->StyleSetBold(wxSTC_MARKDOWN_STRONG1, true);
	
	m_editor->StyleSetForeground(wxSTC_MARKDOWN_EM1, wxColour(128, 0, 128));
	m_editor->StyleSetItalic(wxSTC_MARKDOWN_EM1, true);
	
	m_editor->StyleSetForeground(wxSTC_MARKDOWN_CODE, wxColour(220, 20, 60));
	m_editor->StyleSetBackground(wxSTC_MARKDOWN_CODE, wxColour(245, 245, 245));

	// Create preview pane
	m_preview = new wxHtmlWindow(this, wxID_ANY);
	m_preview->SetPage("<html><body><h2>Preview</h2><p>Markdown preview will appear here when you start typing.</p></body></html>");

	// Create search panel
	wxPanel* searchPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* searchLabel = new wxStaticText(searchPanel, wxID_ANY, "Search:");
	searchSizer->Add(searchLabel, 0, wxALL, 5);
	
	m_searchCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	searchSizer->Add(m_searchCtrl, 0, wxEXPAND | wxALL, 5);
	
	m_searchResults = new wxListCtrl(searchPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
		wxLC_REPORT | wxLC_SINGLE_SEL);
	m_searchResults->AppendColumn("File", wxLIST_FORMAT_LEFT, 150);
	m_searchResults->AppendColumn("Line", wxLIST_FORMAT_LEFT, 50);
	m_searchResults->AppendColumn("Preview", wxLIST_FORMAT_LEFT, 200);
	searchSizer->Add(m_searchResults, 1, wxEXPAND | wxALL, 5);
	
	searchPanel->SetSizer(searchSizer);

	// Add panes to AUI manager
	m_mgr.AddPane(m_fileTree, wxAuiPaneInfo()
		.Name("files")
		.Caption("Files")
		.Left()
		.MinSize(200, -1)
		.BestSize(250, -1)
		.CloseButton(false));

	m_mgr.AddPane(m_editor, wxAuiPaneInfo()
		.Name("editor")
		.Caption("Editor")
		.Center()
		.CloseButton(false));

	m_mgr.AddPane(m_preview, wxAuiPaneInfo()
		.Name("preview")
		.Caption("Preview")
		.Right()
		.MinSize(300, -1)
		.BestSize(400, -1)
		.CloseButton(false));

	m_mgr.AddPane(searchPanel, wxAuiPaneInfo()
		.Name("search")
		.Caption("Search")
		.Bottom()
		.MinSize(-1, 200)
		.BestSize(-1, 250)
		.Hide()
		.CloseButton(true));

	// Commit all changes
	m_mgr.Update();

	CreateStatusBar(2);
	int widths[] = {-1, 200};
	GetStatusBar()->SetStatusWidths(2, widths);
	SetStatusText("Ready", 0);
	SetStatusText("No vault loaded", 1);
}

void MainFrame::LoadVault(const wxString& path) {
	if (!wxDirExists(path)) {
		wxMessageBox("Invalid vault path: " + path, "Error", wxOK | wxICON_ERROR);
		return;
	}

	m_vaultPath = path;
	SetTitle("Custom Obsidian - " + wxFileName(path).GetName());
	
	// Clear and populate file tree
	m_fileTree->DeleteAllItems();
	PopulateFileTree(path);
	
	SetStatusText("Vault loaded: " + wxFileName(path).GetName(), 1);
	GetToolBar()->EnableTool(ID_New, true);
}

void MainFrame::PopulateFileTree(const wxString& path) {
	m_rootItem = m_fileTree->AddRoot(wxFileName(path).GetName());
	m_fileTree->SetItemData(m_rootItem, new wxTreeItemData());

	wxDir dir(path);
	if (!dir.IsOpened()) return;

	wxString filename;
	
	// Add markdown files
	bool cont = dir.GetFirst(&filename, "*.md", wxDIR_FILES);
	while (cont) {
		wxTreeItemId item = m_fileTree->AppendItem(m_rootItem, filename);
		m_fileTree->SetItemData(item, new wxTreeItemData());
		cont = dir.GetNext(&filename);
	}
	
	// Add subdirectories
	cont = dir.GetFirst(&filename, "", wxDIR_DIRS);
	while (cont) {
		if (filename != "." && filename != "..") {
			wxTreeItemId dirItem = m_fileTree->AppendItem(m_rootItem, filename);
			m_fileTree->SetItemData(dirItem, new wxTreeItemData());
			
			// Recursively add subdirectory contents
			wxString subPath = wxFileName(path, filename).GetFullPath();
			if (wxDirExists(subPath)) {
				wxDir subDir(subPath);
				wxString subFile;
				bool subCont = subDir.GetFirst(&subFile, "*.md", wxDIR_FILES);
				while (subCont) {
					wxTreeItemId subItem = m_fileTree->AppendItem(dirItem, subFile);
					m_fileTree->SetItemData(subItem, new wxTreeItemData());
					subCont = subDir.GetNext(&subFile);
				}
			}
		}
		cont = dir.GetNext(&filename);
	}
	
	m_fileTree->Expand(m_rootItem);
}

void MainFrame::OpenNote(const wxString& filepath) {
	if (m_modified) {
		int result = wxMessageBox("Current note has unsaved changes. Save before opening new note?",
			"Unsaved Changes", wxYES_NO | wxCANCEL | wxICON_QUESTION);
		
		if (result == wxCANCEL) return;
		if (result == wxYES) SaveCurrentNote();
	}

	std::ifstream file(filepath.ToStdString());
	if (file.is_open()) {
		std::string content((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		file.close();
		
		m_editor->SetText(wxString(content));
		m_currentFile = filepath;
		m_modified = false;
		
		SetTitle("Custom Obsidian - " + wxFileName(filepath).GetName());
		SetStatusText("Opened: " + wxFileName(filepath).GetName(), 0);
		
		RefreshPreview();
	} else {
		wxMessageBox("Failed to open file: " + filepath, "Error", wxOK | wxICON_ERROR);
	}
}

void MainFrame::SaveCurrentNote() {
	if (m_currentFile.IsEmpty()) return;

	std::ofstream file(m_currentFile.ToStdString());
	if (file.is_open()) {
		file << m_editor->GetText().ToStdString();
		file.close();
		
		m_modified = false;
		SetStatusText("Saved: " + wxFileName(m_currentFile).GetName(), 0);
	} else {
		wxMessageBox("Failed to save file: " + m_currentFile, "Error", wxOK | wxICON_ERROR);
	}
}

void MainFrame::NewNote() {
	if (m_vaultPath.IsEmpty()) {
		wxMessageBox("Please open a vault first.", "No Vault", wxOK | wxICON_WARNING);
		return;
	}

	wxTextEntryDialog dialog(this, "Enter note name:", "New Note");
	if (dialog.ShowModal() == wxID_OK) {
		wxString noteName = dialog.GetValue();
		if (!noteName.IsEmpty()) {
			if (!noteName.EndsWith(".md")) {
				noteName += ".md";
			}
			
			wxString filepath = wxFileName(m_vaultPath, noteName).GetFullPath();
			
			if (wxFileExists(filepath)) {
				wxMessageBox("A note with this name already exists.", "File Exists", 
					wxOK | wxICON_WARNING);
				return;
			}
			
			// Create empty file
			std::ofstream file(filepath.ToStdString());
			file << "# " << dialog.GetValue().ToStdString() << "\n\n";
			file.close();
			
			// Refresh file tree and open the new note
			PopulateFileTree(m_vaultPath);
			OpenNote(filepath);
		}
	}
}

void MainFrame::RefreshPreview() {
	if (m_editor->GetText().IsEmpty()) {
		m_preview->SetPage("<html><body><p><i>Start typing to see preview...</i></p></body></html>");
		return;
	}

	wxString html = MarkdownToHTML(m_editor->GetText());
	m_preview->SetPage(html);
}

wxString MainFrame::MarkdownToHTML(const wxString& markdown) {
	wxString html = "<html><head><style>"
		"body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Arial, sans-serif; "
		"line-height: 1.6; margin: 20px; }"
		"h1 { color: #2c3e50; border-bottom: 2px solid #3498db; }"
		"h2 { color: #34495e; border-bottom: 1px solid #bdc3c7; }"
		"h3 { color: #7f8c8d; }"
		"code { background-color: #f8f9fa; padding: 2px 4px; border-radius: 3px; "
		"font-family: 'Monaco', 'Courier New', monospace; }"
		"pre { background-color: #f8f9fa; padding: 10px; border-radius: 5px; overflow-x: auto; }"
		"blockquote { border-left: 4px solid #3498db; margin-left: 0; padding-left: 15px; "
		"color: #7f8c8d; font-style: italic; }"
		"a { color: #3498db; text-decoration: none; }"
		"a:hover { text-decoration: underline; }"
		"</style></head><body>";

	wxString text = markdown;
	
	// Basic markdown parsing (simplified)
	// Headers
	text.Replace("### ", "<h3>");
	text.Replace("## ", "<h2>");
	text.Replace("# ", "<h1>");
	
	// Bold and italic
	std::regex boldRegex("\\*\\*(.*?)\\*\\*");
	std::string textStr = text.ToStdString();
	textStr = std::regex_replace(textStr, boldRegex, "<strong>$1</strong>");
	
	std::regex italicRegex("\\*(.*?)\\*");
	textStr = std::regex_replace(textStr, italicRegex, "<em>$1</em>");
	
	// Code blocks
	std::regex codeRegex("`(.*?)`");
	textStr = std::regex_replace(textStr, codeRegex, "<code>$1</code>");
	
	// Links [[note]]
	std::regex linkRegex("\\[\\[(.*?)\\]\\]");
	textStr = std::regex_replace(textStr, linkRegex, "<a href=\"#\">$1</a>");
	
	// Convert line breaks
	wxString result(textStr);
	result.Replace("\n\n", "</p><p>");
	result.Replace("\n", "<br>");
	
	// Process headers properly (simplified approach)
	result.Replace("<h1>", "<h1>");
	result.Replace("<h2>", "<h2>");
	result.Replace("<h3>", "<h3>");
	
	html += "<p>" + result + "</p></body></html>";
	return html;
}

// Event Handlers
void MainFrame::OnNew(wxCommandEvent& event) {
	NewNote();
}

void MainFrame::OnOpen(wxCommandEvent& event) {
	wxFileDialog dialog(this, "Open Note", m_vaultPath, "",
		"Markdown files (*.md)|*.md|Text files (*.txt)|*.txt|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dialog.ShowModal() == wxID_OK) {
		OpenNote(dialog.GetPath());
	}
}

void MainFrame::OnSave(wxCommandEvent& event) {
	SaveCurrentNote();
}

void MainFrame::OnOpenVault(wxCommandEvent& event) {
	wxDirDialog dialog(this, "Choose vault directory");
	
	if (dialog.ShowModal() == wxID_OK) {
		LoadVault(dialog.GetPath());
	}
}

void MainFrame::OnSearch(wxCommandEvent& event) {
	wxAuiPaneInfo& pane = m_mgr.GetPane("search");
	pane.Show(!pane.IsShown());
	m_mgr.Update();
	
	if (pane.IsShown()) {
		m_searchCtrl->SetFocus();
	}
}

void MainFrame::OnTogglePreview(wxCommandEvent& event) {
	wxAuiPaneInfo& pane = m_mgr.GetPane("preview");
	pane.Show(!pane.IsShown());
	m_mgr.Update();
}

void MainFrame::OnPreferences(wxCommandEvent& event) {
	wxMessageBox("Preferences dialog would be implemented here.\n\n"
		"Future features:\n"
		"• Theme selection\n"
		"• Font preferences\n"
		"• Vault settings\n"
		"• Keyboard shortcuts",
		"Preferences", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnTreeItemActivated(wxTreeEvent& event) {
	wxTreeItemId item = event.GetItem();
	if (item == m_rootItem) return;
	
	wxString filename = m_fileTree->GetItemText(item);
	if (filename.EndsWith(".md")) {
		wxTreeItemId parent = m_fileTree->GetItemParent(item);
		wxString parentPath = (parent == m_rootItem) ? m_vaultPath : 
			wxFileName(m_vaultPath, m_fileTree->GetItemText(parent)).GetFullPath();
		
		wxString filepath = wxFileName(parentPath, filename).GetFullPath();
		OpenNote(filepath);
	}
}

void MainFrame::OnTreeItemMenu(wxTreeEvent& event) {
	// Context menu for file tree
	wxMenu menu;
	menu.Append(wxID_ANY, "Rename");
	menu.Append(wxID_ANY, "Delete");
	menu.AppendSeparator();
	menu.Append(wxID_ANY, "New Note Here");
	
	PopupMenu(&menu);
}

void MainFrame::OnEditorChanged(wxStyledTextEvent& event) {
	m_modified = true;
	RefreshPreview();
	
	// Update status
	int lines = m_editor->GetLineCount();
	int chars = m_editor->GetTextLength();
	SetStatusText(wxString::Format("Lines: %d, Characters: %d %s", 
		lines, chars, m_modified ? "(modified)" : ""), 0);
}

void MainFrame::OnClose(wxCloseEvent& event) {
	if (m_modified) {
		int result = wxMessageBox("Current note has unsaved changes. Save before closing?",
			"Unsaved Changes", wxYES_NO | wxCANCEL | wxICON_QUESTION);
		
		if (result == wxCANCEL) {
			event.Veto();
			return;
		}
		if (result == wxYES) SaveCurrentNote();
	}
	
	m_mgr.UnInit();
	Destroy();
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Custom Obsidian v1.0\n\n"
		"A custom note-taking application inspired by Obsidian.\n\n"
		"Features:\n"
		"• Markdown editing with syntax highlighting\n"
		"• Live preview\n"
		"• File browser\n"
		"• Search functionality\n"
		"• Note linking\n\n"
		"Built with wxWidgets",
		"About Custom Obsidian", wxOK | wxICON_INFORMATION);
}
