# OpenGL Test Application

This is a simple OpenGL testing application that can create a window, draw a triangle, and change the colors of both.
It includes the requisite libraries for Windows for ease of use.

## Prerequisites

### Linux

1. **Install dependencies**:
   To get started, you'll need to install `git`, `cmake`, `glfw`, `glew`, and OpenGL. Run the following commands:

   ```bash
   # Update your package manager
   sudo apt update
   
   # Install git, cmake, and build essentials
   sudo apt install git cmake build-essential

   # Install GLFW
   sudo apt install libglfw3 libglfw3-dev

   # Install GLEW
   sudo apt install libglew-dev

   # Install OpenGL development libraries
   sudo apt install libgl1-mesa-dev
   ```

2. **Clone the repository**:

   ```bash
   git clone https://github.com/movecx/opengl-test-app.git
   cd opengl-test-app
   ```

3. **Build the application**:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the application**:

   ```bash
   ./OpenGLTest
   ```

### Windows

1. **Install dependencies**:
   - Install [Visual Studio Build Tools for C/C++](https://visualstudio.microsoft.com/visual-cpp-build-tools/).
   - Install [CMake](https://cmake.org/download/).
   - Install [Git for Windows](https://gitforwindows.org/).

2. **Clone the repository**:

   Open Git Bash and run:

   ```bash
   git clone https://github.com/movecx/opengl-test-app.git
   cd opengl-test-app
   ```

3. **Open the project in Visual Studio Code**:

   Open Visual Studio Code and load the project folder by selecting **File > Open Folder**, and then choosing the folder that contains the cloned repository.

4. **Configure the project**:

   - Press `Ctrl + Shift + P` to open the command palette.
   - Search for and select **CMake: Configure**.
   - CMake will generate the necessary build files.

5. **Build and run the application**:

   - Press `F5` to run the application with debugging, or `Shift + F5` to run without debugging.
