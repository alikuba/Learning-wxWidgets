// 01_hello_world.cpp - Basic wxWidgets Hello World
#include <wx/wx.h>

// Application class
class HelloWorldApp : public wxApp {
public:
	bool OnInit();
};

// Main frame class
class HelloWorldFrame : public wxFrame {
public:
	HelloWorldFrame();

private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();
};

// Event table
wxBEGIN_EVENT_TABLE(HelloWorldFrame, wxFrame)
	EVT_MENU(wxID_EXIT, HelloWorldFrame::OnExit)
	EVT_MENU(wxID_ABOUT, HelloWorldFrame::OnAbout)
	EVT_CLOSE(HelloWorldFrame::OnClose)
wxEND_EVENT_TABLE()

// Application implementation
wxIMPLEMENT_APP(HelloWorldApp);

bool HelloWorldApp::OnInit() {
	HelloWorldFrame* frame = new HelloWorldFrame();
	frame->Show(true);
	return true;
}

// Frame implementation
HelloWorldFrame::HelloWorldFrame() : wxFrame(nullptr, wxID_ANY, "Hello World - wxWidgets Tutorial") {
	// Set frame size
	SetSize(400, 300);
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

	// Create status bar
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	// Create a panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	
	// Create a static text control
	new wxStaticText(panel, wxID_ANY, "Hello, wxWidgets World!", 
		wxPoint(50, 50), wxDefaultSize, wxALIGN_CENTER);
}

void HelloWorldFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void HelloWorldFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a Hello World sample for wxWidgets",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

void HelloWorldFrame::OnClose(wxCloseEvent& event) {
	Destroy();
}
