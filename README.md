# Watchtower
---

Developed by the ground station team
The Als Rocketry Club
The University of Southern Denmark (SDU)
Sonderborg, Denmark

---

## Table of contents (needed?)
- [Description](#description)
- [Folder structure](#folder-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Main contributors](#main-contributors)

---

## Description
Source code and for the "Watchtower" ground station managing launch, controls, data and communication to S3 and future rockets.

---

## Folder structure (TODO)

---
## Installation (Local)(TODO)
### 1. Visual Studio Code
Visual Studio Code (VSCode) is a code editor that is used to develop the Watchtower project. It is recommended to use VSCode as the primary code editor for this project. To install VSCode, follow the instructions on the [official website](https://code.visualstudio.com/).

### 2. Clone the repository in VSCode
To clone the repository, open the [Watchtower repository](https://github.com/AlsRocketryClub/watchtower), choose / make a branch and click on the green "Code" button. Then, copy the URL and in the address bar type `> Git: Clone`, press enter then paste the URL and press enter again. Choose the folder where you want to clone the repository and press enter.

### 3. Install the required extensions
The following extensions are required to develop the Watchtower project in VSCode:
- C/C++
- CMake
- Python

To install the extensions, click on the "Extensions" icon on the left sidebar, search for the extension in the search bar, and click on the "Install" button.

### 4. Install the required packages
The following packages are required to build the Watchtower project:
- 

--- 

## Installation (Github codespace)
### 1. Open the codespace in a browser
The codespace is set up with Visual Studio Code. To access the codespace, click on the "Open with Codespaces" button on the [Watchtower github](https://github.com/AlsRocketryClub/watchtower) page.

### 2. Open the codespace in local VS Code (optional)
This step is optional if you have already opened the codespace in the previous step. To open the codespace in your own VS Code application as an alternative to the browser, click on the menu button in the top left corner of the codespace and click on "Open in VS Code Desktop".

### 3. Install the required packages
### CMake
`CMake` is an open-source, cross-platform family of tools designed to build, test and package software. It is used to build the Watchtower project. To install `CMake`, run the following commands in a VSCode bash terminal:

```bash
sudo apt-get update
sudo apt-get install cmake
```

### pybind11
`pybind11` is a lightweight header-only library that exposes C++ types in Python. It is used to interface the C++ code with the Python code. In this project, it is primarily used to interface the C++ code with the Python code in the `watchtower` package for plotting data and running the ground station app in a Python interface.

To install `pybind11`, run the following commands in a VSCode terminal: (TODO)


---

## Usage (TODO)

---

## Main contributors
- Arturo Guiraud
- Arkadiusz Jan Tuzimek
- Kyril Alsheuski
- Hans Verdolaga

