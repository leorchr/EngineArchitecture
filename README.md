# 🏗️ Game Engine Architecture Refactor

This project is a **complete refactor** of an existing engine, focusing on **modern C++ practices, modularity, and dependency reduction**.

## 🔍 Key Features  

### 🏗️ **Actor-Component System**  
- **Actors**: Independent game entities.  
- **Components**: Modular, reusable behaviors that can be attached to actors.  
- **Decoupled Logic**: Enables dynamic entity behavior without tight coupling.  

### 🚀 **Dependency Optimization**  
- **Circular Dependency Removal**: Proper module separation and **forward declarations**.  
- **RAII Implementation**: Resource cleanup with constructors/destructors.  
- **Smart Pointer Management**: Eliminates raw pointers, reducing memory leaks.

## 🛠 Installation

The following tools are required:

1. [Premake 5](https://premake.github.io/download.html)
2. [Visual Studio 2017 or higher](https://www.visualstudio.com/downloads/)

If you're not on Windows, or cannot use Visual Studio, Premake allows to use other toolchains, please read its documentation.

## 🏗 Build

Open a terminal in _StealthFactor_ directory and follow the instructions for your platform.

### 🪟 Windows

    premake5.exe vs2022

Open _build\StealthFactor.sln_, choose your target, and build.

### 🐧 Linux

    apt-get install -y g++ g++-multilib libode-dev libsfml-dev make
    premake5 gmake2
    cd build
    make config=release_linux64

## External dependencies

1. [cli.cpp](https://github.com/KoltesDigital/cli.cpp), a CLI argument parser (header-only)
2. [ODE](http://www.ode.org/), a physics engine
3. [pugixml](http://pugixml.org/), an XML parser (header-only)
4. [SFML](https://www.sfml-dev.org/), a small multimedia framework
