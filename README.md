# Description
Game Engine with openGL 3.3 (Open Graphics Library) and game engine `Rasterization` to render image.

## Run Engine
- Intall packages for application:

```
# Install libglfw3-dev for glfw3. This is a framework supports environment for openGL. It provides API to handle input, events, create Windows...
$ sudo apt-get install libglfw3-dev
# Install libglew-dev for glew (OpenGL Extension Wrangler Library) to load extension necessary.
$ sudo apt-get install libglew-dev
# Install libglm-dev. A header for C++ mathematics library for graphics software.
$ sudo apt-get install libglm-dev
```

- Run application:
```
# Run application
$ ./build.sh all
# Remove output of the compile
$ ./build.sh clean
```

## Note
- if you have the problem with cmake. Please update path of `CMAKE_MODULE_PATH` in **CMakeLists.txt** 