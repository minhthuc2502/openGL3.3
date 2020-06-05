# Arm LynxMotion AL5D 3D

## Description
Design 3D graphique with openGL 3.3 (Open Graphics Library) and control graphique 3D with keyboard.

## Installation packages 
- Intall packages for application:

```
# Install libglfw3-dev for glfw3. This is a framework supports environment for openGL. It provides API to handle input, events, create Windows...
$ sudo apt-get install libglfw3-dev
# Install libglew-dev for glew (OpenGL Extension Wrangler Library) to load extension necessary.
$ sudo apt-get install libglew-dev
# Install libglm-dev. A header for C++ mathematics library for graphics software.
$ sudo apt-get install libglm-dev
# Install libassimp-dev. Library to load model from file .obj
$ sudo apt-get install libassimp-dev
```

## Run 3D graphique

```
# Run application
$ ./build.sh all
# Remove output of the compile
$ ./build.sh clean
```
## How to use

- Using **A**, **W**, **S**, **D** and mouse to modify the view of graphique
- **Left** and **Right** : rotate shoulder
- **Up** and **Down** : rotate bicep below
- **KP8** and **KP2** : rotate bicep above
- **KP4** and **KP6** : rotate wrist
- **KP1** and **KP3** : rotate rail
- **KP7** and **KP9** : open/close gripper
- **ESC** : close window

## Note
- if you have the problem with cmake. Please update path of `CMAKE_MODULE_PATH` in **CMakeLists.txt** 