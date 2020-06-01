#ifndef WINDOW_3D_HPP
#define WINDOW_3D_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
class window {
private:
  float width;
  float height;
  char *title;

public:
  GLFWwindow *mpwindow;
  window(char *name, float w = 800.0f, float h = 600.0f) {
    width = w;
    height = h;
    title = new char[strlen(name)];
    strcpy(title, name);
  };
  ~window(){};

  void initialize();
  void terminate();
  float getWidth();
  float getHeight();
};
#endif