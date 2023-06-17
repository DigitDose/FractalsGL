#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>


void przyb(GLFWwindow* window, double/* xoffset */, double yoffset);
void klaw (GLFWwindow* window, int key, int scancode, int action, int mods);
unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
std::string LoadShader(const std::string& filepath);


