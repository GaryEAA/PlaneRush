#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;
    std::stringstream vertexShaderStream, fragmentShaderStream;
    const char* vertexShaderData, * fragmentShaderData;
    unsigned int vertex, fragment;
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
   
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
};