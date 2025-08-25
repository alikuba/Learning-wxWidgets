# Programming Notes

## C++ with wxWidgets

### Key Concepts

- **Event-driven programming**: Applications respond to user events
- **Cross-platform**: Same code works on Windows, macOS, and Linux
- **Native look and feel**: Uses platform-specific widgets

### Important Classes

- `wxApp`: Application class, entry point
- `wxFrame`: Main window class
- `wxPanel`: Container for controls
- `wxSizer`: Layout management

### Example Code

```cpp
class MyApp : public wxApp {
public:
    bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
```

## Design Patterns

### Observer Pattern
Used extensively in GUI applications for event handling.

### Model-View-Controller (MVC)
Separates data, presentation, and control logic.

## Resources

- [[Welcome]] - Getting started guide
- [[Project Ideas]] - Future project concepts
- Official wxWidgets documentation
- C++ reference materials

## TODO

- [ ] Learn more about custom drawing
- [ ] Explore advanced layout techniques
- [ ] Study platform-specific features
- [x] Create basic application structure
