# wxWidgets Tutorial

A comprehensive tutorial series demonstrating wxWidgets GUI programming concepts with practical examples.

## Table of Contents

1. [Getting Started](#getting-started)
2. [Building the Examples](#building-the-examples)  
3. [Tutorial Examples](#tutorial-examples)
4. [Key Concepts](#key-concepts)
5. [Advanced Topics](#advanced-topics)
6. [Resources](#resources)

## Getting Started

### Prerequisites

- C++ compiler (g++, clang++, or Visual Studio)
- wxWidgets 3.2.x library installed
- Basic knowledge of C++ programming

### wxWidgets Installation

#### macOS (Homebrew)
```bash
brew install wxwidgets
```

#### macOS (From Source)
```bash
# Download wxWidgets from https://www.wxwidgets.org/
# Extract and build:
cd wxWidgets-3.2.8
mkdir macbuild && cd macbuild
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libwxgtk3.2-dev
```

#### Windows
Download pre-compiled binaries or build from source. See [wxWidgets documentation](https://docs.wxwidgets.org/trunk/plat_msw_install.html).

## Building the Examples

Each example can be built independently using the provided compilation command format:

```bash
g++ example_name.cpp -o example_name `wx-config --cxxflags --libs`
```

### Individual Examples:

```bash
# Basic Hello World
g++ 01_hello_world.cpp -o hello_world `wx-config --cxxflags --libs`

# Button Events
g++ 02_buttons_events.cpp -o buttons_events `wx-config --cxxflags --libs`

# Layout Management
g++ 03_layout_sizers.cpp -o layout_sizers `wx-config --cxxflags --libs`

# Menus and Toolbars
g++ 04_menus_toolbars.cpp -o menus_toolbars `wx-config --cxxflags --libs`

# Text Controls
g++ 05_text_controls.cpp -o text_controls `wx-config --cxxflags --libs`

# Dialog Boxes
g++ 06_dialogs.cpp -o dialogs `wx-config --cxxflags --libs`

# Comprehensive App
g++ 07_comprehensive_app.cpp -o comprehensive_app `wx-config --cxxflags --libs`
```

### Alternative Build Method (if wx-config not found)

If you built wxWidgets manually, replace `wx-config --cxxflags --libs` with the full paths:

```bash
g++ example.cpp -o example \
  -I/path/to/wxwidgets/include \
  -I/path/to/wxwidgets/build/lib/wx/include/platform-unicode-3.2 \
  -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -DwxUSE_GUI=1 \
  -L/path/to/wxwidgets/build/lib \
  -lwx_osx_cocoau_core-3.2 -lwx_baseu-3.2 \
  -framework IOKit -framework Carbon -framework Cocoa \
  -framework AudioToolbox -framework System -framework OpenGL
```

## Tutorial Examples

### 1. Hello World (`01_hello_world.cpp`)
**Concepts:** Basic application structure, frames, menus, status bars

- Creates a minimal wxWidgets application
- Demonstrates the `wxApp` and `wxFrame` classes
- Shows basic menu bar and status bar creation
- Introduces event handling with `wxDECLARE_EVENT_TABLE()`

**Key Learning Points:**
- Application entry point with `wxIMPLEMENT_APP()`
- Frame construction and basic properties
- Simple menu creation and event binding

### 2. Button Events (`02_buttons_events.cpp`)
**Concepts:** Button controls, event handling, lambda functions

- Various button types (regular, toggle)
- Event handling methods (event tables vs. Bind())
- Text controls and user interaction
- Dynamic UI updates

**Key Learning Points:**
- Different ways to handle events in wxWidgets
- Button states and properties
- Text control manipulation
- UI feedback and status updates

### 3. Layout Management (`03_layout_sizers.cpp`)
**Concepts:** Sizers, flexible layouts, control grouping

- `wxBoxSizer` for linear layouts
- `wxStaticBoxSizer` for grouped controls
- Proportional sizing and stretching
- Complex nested layouts

**Key Learning Points:**
- Importance of sizers for responsive UI
- Different sizer types and their use cases
- Layout proportions and alignment
- Handling window resizing properly

### 4. Menus and Toolbars (`04_menus_toolbars.cpp`)
**Concepts:** Menu bars, toolbars, keyboard shortcuts, file operations

- Comprehensive menu system with multiple menus
- Toolbar with icons and text
- Keyboard accelerators
- File dialogs and operations
- Standard UI conventions

**Key Learning Points:**
- Menu organization and best practices
- Toolbar creation and customization
- File I/O with wxWidgets
- Standard application patterns

### 5. Text Controls (`05_text_controls.cpp`)
**Concepts:** Various text controls, text formatting, input validation

- Single-line and multi-line text controls
- Password fields and read-only controls
- Spin controls and checkboxes
- Text processing and formatting

**Key Learning Points:**
- Different text control types and their purposes
- Text events and validation
- Control states and properties
- User input handling

### 6. Dialog Boxes (`06_dialogs.cpp`)
**Concepts:** Modal dialogs, standard dialogs, custom dialogs

- Message boxes and confirmation dialogs
- File, color, and font dialogs
- Input and choice dialogs
- Progress dialogs
- Custom dialog creation

**Key Learning Points:**
- When and how to use different dialog types
- Modal vs. modeless dialogs
- Dialog result handling
- Creating custom dialogs for specific needs

### 7. Comprehensive Application (`07_comprehensive_app.cpp`)
**Concepts:** Complex application architecture, multiple controls, real-world patterns

- Multi-panel application with splitter windows
- Notebook (tab) controls
- List and tree controls
- Integration of all previous concepts
- Professional application structure

**Key Learning Points:**
- Application architecture for larger projects
- Complex layout management
- Integration of multiple control types
- Event coordination between components

## Key Concepts

### Application Structure
```cpp
class MyApp : public wxApp {
public:
    bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();
private:
    void OnMenuNew(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_APP(MyApp);
```

### Event Handling
wxWidgets provides two main ways to handle events:

**Event Tables (Classic Method):**
```cpp
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_NEW, MyFrame::OnMenuNew)
    EVT_BUTTON(ID_BUTTON, MyFrame::OnButton)
wxEND_EVENT_TABLE()
```

**Bind Method (Modern, Flexible):**
```cpp
Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnMenuNew, this, wxID_NEW);
Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent&) { 
    // Lambda function handler
}, ID_BUTTON);
```

### Layout Management
Always use sizers for proper layout:

```cpp
wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
sizer->Add(control1, 0, wxEXPAND | wxALL, 5);
sizer->Add(control2, 1, wxEXPAND | wxALL, 5);
panel->SetSizer(sizer);
```

### Common Control Creation Pattern
```cpp
// Create control
wxTextCtrl* textCtrl = new wxTextCtrl(parent, ID_TEXT, "Default text",
    wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

// Add to layout
sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);

// Bind events (if needed)
Bind(wxEVT_TEXT, &MyFrame::OnTextChanged, this, ID_TEXT);
```

## Advanced Topics

### Custom Drawing
```cpp
void OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    dc.DrawText("Hello", 10, 10);
    dc.DrawCircle(50, 50, 25);
}
```

### Threading
```cpp
class WorkerThread : public wxThread {
public:
    virtual wxThread::ExitCode Entry() {
        // Background work
        wxTheApp->CallAfter([this]() {
            // Update UI on main thread
        });
        return (wxThread::ExitCode)0;
    }
};
```

### Custom Controls
```cpp
class CustomControl : public wxPanel {
public:
    CustomControl(wxWindow* parent) : wxPanel(parent) {
        Bind(wxEVT_PAINT, &CustomControl::OnPaint, this);
    }
private:
    void OnPaint(wxPaintEvent& event);
};
```

## Best Practices

1. **Always use sizers** for layout management
2. **Use appropriate control types** for different data inputs
3. **Provide visual feedback** for user actions
4. **Handle errors gracefully** with proper dialogs
5. **Follow platform conventions** for menus and shortcuts
6. **Validate user input** before processing
7. **Use meaningful IDs** for controls
8. **Keep event handlers focused** and delegate complex logic
9. **Provide status information** through status bars
10. **Test on target platforms** for consistent behavior

## Common Patterns

### Application Initialization
```cpp
bool MyApp::OnInit() {
    // Set application properties
    SetAppName("My Application");
    
    // Create main window
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    
    return true;
}
```

### Menu Creation
```cpp
void CreateMenuBar() {
    wxMenuBar* menuBar = new wxMenuBar;
    
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&New\tCtrl-N");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tCtrl-Q");
    
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);
}
```

### Dialog Usage
```cpp
void OnSaveAs() {
    wxFileDialog dialog(this, "Save file", "", "",
        "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        // Save file
    }
}
```

## Troubleshooting

### Common Issues

1. **Linking errors:** Make sure wxWidgets is properly installed and wx-config works
2. **Layout problems:** Always use sizers, avoid absolute positioning
3. **Event not firing:** Check event table entries and control IDs
4. **Crash on startup:** Verify wxWidgets version compatibility
5. **Text not updating:** Call `Refresh()` after programmatic changes

### Build Issues

If you encounter build issues:
1. Check that wxWidgets is installed: `wx-config --version`
2. Verify compiler compatibility
3. Check library paths and linking flags
4. Ensure all required frameworks are linked (macOS)

## Resources

- [Official wxWidgets Documentation](https://docs.wxwidgets.org/)
- [wxWidgets Wiki](https://wiki.wxwidgets.org/)
- [wxWidgets Samples](https://github.com/wxWidgets/wxWidgets/tree/master/samples)
- [wxWidgets Tutorial](https://zetcode.com/gui/wxwidgets/)

## Contributing

Feel free to improve these examples or add new ones! The goal is to provide clear, practical examples for learning wxWidgets.

## License

These examples are provided for educational purposes. wxWidgets itself is licensed under the wxWindows Library License.
