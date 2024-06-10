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
### 1. Visual Studio
Visual Studio is an integrated development environment (IDE) used to develop computer programs, websites, web apps, web services, and mobile apps. It is used to develop the Watchtower project. To install Visual Studio, follow the instructions on the [Visual Studio website](https://visualstudio.microsoft.com/).

### 2. Clone the repository in Visual Studio
To clone the Watchtower repository in Visual Studio, open the watchtower Code" button, click "Open with Visual Studio", and follow the instructions to clone the repository in Visual Studio.

### 3. Install CMake
CMake is an open-source, cross-platform family of tools designed to build, test and package software. It is used to build the Watchtower project. To install CMake, follow the instructions on the [CMake website](https://cmake.org/).

### 4. Install Python
Python is a programming language that is used to run the user application and graphical features of the watchtower project. To install Python, follow the instructions on the [Python website](https://www.python.org/).

### 5. Source the Python virtual environment
To source the Python virtual environment `venv` within the repository, run the following commands in a Visual Studio terminal:

```bash
.\venv\Scripts\activate
```

This environment features the following libraries:
- `matplotlib`
- `numpy`
- `pyinstaller` 
- `pybind11` (pybind11 Python/C++ binding development)
- `pywin32` (Inter-process communication development)


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