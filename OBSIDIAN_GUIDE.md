# Custom Obsidian - Usage Guide

## 🚀 Quick Start

1. **Launch the application**: `./obsidian_app`
2. **Open a vault**: File → Open Vault... (or Ctrl+O) and select the `test_vault` directory
3. **Start editing**: Click on any `.md` file in the file browser to open it
4. **Create new notes**: Ctrl+N or click "New Note" button

## 🎯 Key Features

### ✅ Currently Implemented

#### File Management
- **Vault-based organization**: Open any directory as a note vault
- **File browser**: Tree view showing all markdown files and folders
- **Auto-detection**: Automatically loads `.md` files
- **New note creation**: Create notes with proper naming

#### Editor
- **Syntax highlighting**: Full markdown syntax highlighting
- **Smart indentation**: Uses tabs (as configured)
- **Word wrapping**: Automatic word wrap for better readability
- **Modification tracking**: Shows when files are modified

#### Preview
- **Live preview**: Real-time HTML rendering of markdown
- **Beautiful styling**: Clean, readable CSS styling
- **Responsive**: Updates automatically as you type
- **Toggleable**: Show/hide with Ctrl+P

#### User Interface
- **Dockable panels**: Resizable and movable panels using wxAUI
- **Professional layout**: Multi-pane interface like modern IDEs
- **Status information**: Line count, character count, modification status
- **Keyboard shortcuts**: Common shortcuts for efficiency

### 🚧 Partially Implemented

#### Search System
- **Search panel**: Available (Ctrl+F) but needs implementation
- **Search results**: UI framework ready

### 📝 Planned Features

#### Note Linking
- **[[Wikilinks]]**: Parse and handle note connections
- **Backlinks**: Show which notes link to current note
- **Graph view**: Visual representation of note connections

#### Enhanced Editor
- **Auto-completion**: Suggest note names and tags
- **Live link preview**: Hover to see linked note content
- **Tag system**: #tags for organization

#### Advanced Features
- **Themes**: Dark/light mode support
- **Plugins**: Extensible architecture
- **Export**: PDF, HTML export options
- **Sync**: Cloud synchronization

## 🎮 How to Use

### Opening a Vault
1. Click "Open Vault" in toolbar or use Ctrl+O
2. Navigate to and select the `test_vault` directory (or any folder with `.md` files)
3. The file browser will populate with your notes

### Creating Notes
1. Ensure a vault is open
2. Press Ctrl+N or click "New Note"
3. Enter a name (`.md` extension is added automatically)
4. Start writing in markdown format

### Editing Features
- **Headers**: Use `#`, `##`, `###` for different heading levels
- **Bold text**: Use `**bold text**`
- **Italic text**: Use `*italic text*`
- **Code**: Use `inline code` or code blocks with triple backticks
- **Links**: Use `[[Note Name]]` to link to other notes

### Navigation
- **File browser**: Click any `.md` file to open it
- **Auto-save**: Files are saved when you switch between notes
- **Unsaved changes**: Application prompts before losing changes

### Interface Controls
- **Toggle preview**: Ctrl+P or View menu
- **Search panel**: Ctrl+F (UI ready, search logic to be implemented)
- **Panels**: Drag panel headers to rearrange layout

## 🛠️ Building from Source

### Prerequisites
- wxWidgets 3.2.x with STC, AUI, and HTML libraries
- C++17 compatible compiler
- Make utility

### Build Commands
```bash
# Using the provided Makefile
make obsidian_manual

# Or manually
g++ obsidian_app.cpp -o obsidian_app \
  -I/path/to/wxwidgets/include \
  -I/path/to/wxwidgets/build/lib/wx/include/platform-unicode-3.2 \
  -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -DwxUSE_GUI=1 -std=c++17 \
  -L/path/to/wxwidgets/build/lib \
  -Wl,-rpath,/path/to/wxwidgets/build/lib \
  -lwx_osx_cocoau_core-3.2 -lwx_baseu-3.2 -lwx_osx_cocoau_stc-3.2 \
  -lwx_osx_cocoau_aui-3.2 -lwx_osx_cocoau_html-3.2 \
  -framework IOKit -framework Carbon -framework Cocoa \
  -framework AudioToolbox -framework System -framework OpenGL
```

## 🔧 Configuration

### Settings Storage
- Configuration is automatically saved using wxConfig
- Last opened vault is remembered between sessions
- Window layout preferences are preserved

### File Formats
- **Primary**: Markdown (`.md`) files
- **Future**: Support for other text formats

## 💡 Tips

1. **Organization**: Create folders within your vault for better organization
2. **Linking**: Use descriptive names for notes to make linking easier
3. **Preview**: Keep the preview pane open to see formatting in real-time
4. **Shortcuts**: Learn the keyboard shortcuts for faster workflow

## 🐛 Known Issues

1. **Search functionality**: UI is ready but search logic needs implementation
2. **Note linking**: [[links]] are styled but don't navigate yet
3. **Complex markdown**: Some advanced markdown features not yet supported

## 🚀 Future Enhancements

### Phase 1 (Core Functionality)
- [ ] Implement full-text search across vault
- [ ] Add functional note linking
- [ ] Create preferences dialog
- [ ] Add more markdown rendering features

### Phase 2 (Advanced Features)
- [ ] Tag system with auto-completion
- [ ] Graph view of note connections
- [ ] Theme support (dark/light modes)
- [ ] Export functionality

### Phase 3 (Professional Features)
- [ ] Plugin system
- [ ] Cloud synchronization
- [ ] Collaborative editing
- [ ] Advanced search with filters

## 📚 Architecture

The application uses several advanced wxWidgets features:

- **wxAUI**: Advanced User Interface for dockable panels
- **wxStyledTextCtrl**: Scintilla-based editor with syntax highlighting
- **wxHtmlWindow**: For rendering markdown preview
- **wxTreeCtrl**: File browser with hierarchical display
- **Event-driven design**: Responsive to user interactions

This creates a modern, professional note-taking application that rivals commercial solutions while being completely customizable.

---

*Your personal knowledge management system is ready to use!*
