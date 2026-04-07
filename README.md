# 🎧 AudioVault: IEM & DAC Collection Manager

**AudioVault** is a high-performance desktop application built in C++ for managing high-fidelity audio gear collections. It provides a persistent, searchable database for In-Ear Monitors (IEMs) and Digital-to-Analog Converters (DACs), combining a sleek **Dear ImGui** interface with a robust **SQLite3** backend.

---

## 🚀 Key Features

* **Modular Gear Management**: Dedicated sections for IEMs and DACs, managed through a central UI orchestrator.
* **Persistent Storage**: All data is saved in a local `collection.db` file. The application automatically handles table creation and schema management on startup.
* **Fuzzy Search Engine**: Real-time searching using SQL `LIKE` queries with wildcard support, allowing you to find gear with partial names.
* **Dynamic UI Rendering**: 
    * **Immediate Mode Logic**: Uses ImGui's ID stack (`PushID`/`PopID`) to ensure unique interaction for every item in the list.
    * **Real-time Updates**: The UI reflects database changes (Add/Delete) instantly without needing to restart.
* **Optimized Performance**: Leverages C++ modern features like range-based for loops and constant references to maintain high frame rates during UI rendering.

---

## 🛠️ Technical Stack

* **Language**: C++17
* **GUI Framework**: [Dear ImGui](https://github.com/ocornut/imgui)
* **Database**: [SQLite3](https://sqlite.org/)
* **Windowing/API**: GLFW & OpenGL3

---

## 📂 Project Structure

| File | Description |
| :--- | :--- |
| `main.cpp` | Entry point, GLFW/OpenGL setup, and main UI loop. |
| `database.h` | SQLite3 wrapper handling connections, table creation, and queries. |
| `Iembank.h` | The main UI orchestrator that routes between IEM and DAC pages. |
| `iems.h` | Logic and rendering specific to the IEM management section. |
| `dacs.h` | Logic and rendering specific to the DAC management section. |

---

## ⚙️ Installation & Build

### Prerequisites
You will need the following libraries installed on your environment (**Pop!_OS** or **Windows**):
* `glfw`
* `glew` (or your preferred GL loader)
* `sqlite3`

### Compiling
You can compile the project using a standard C++ compiler. For example, using `g++`:
```bash
g++ main.cpp -lglfw -lGL -lsqlite3 -o AudioVault
