# Dooda
My personal game engine. The aim is to slowly develop this engine while learning about how all the different systems are designed, structured and utilised. Along with the base engine, it includes an editor for designing games and other applications. 

## Getting Started
1. Clone the repository
  - `git clone --recursive https://github.com/TheCherno/Hazel`
  - `git submodule update --init`
2. Configure the Dependencies
  - Run the `Setup.bash` file located in the scripts file (or alternativly run `Setup.py` using python)
  - Install any recomended files or libraries
  - This file may need to be run a second time to allow the Vulkan SDK to install the debugging libraries
  - If the `Win-GenProjects.bat` file is not run, run this file seperatly to generate the Visual Studio solution file

## Features
- Graphics
  - OpenGL rendering for Windows platform
- Editor (Adood)
  - Scene creation and management
  - Drag and Drop assests from files
  - Cameras and Sprite Renderers
- Rendering
  - Batch Rendering
- Physics
  - Box2D physics

## Reference & Learning Resources
- Hazel by TheCherno 
  - Base structure and set up of the engine. Basic editor scene and OpenGl rendering. Generally learning about game engines and what they require. 
  - GitHub: https://github.com/TheCherno/Hazel 
  - YouTube: https://www.youtube.com/@TheCherno
  
## Goals
- Graphics
  - Set up graphics for Mac and Linux
  - Switch to Vulkun for Windows
- Rendering 
  - Instance Rendering
- Editor (Adood)
  - Tile system
  - Partical System
- Physics 
  - Set up a personal physics library
