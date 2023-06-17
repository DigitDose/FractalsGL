#include "globals.h"
#include "functions.h"


const double PI = 3.14159265358979323846;
double offsetX = 0.0f;
double offsetY= 0.0f;
double zoomlvl = 1.1f;
double zwiek = 1.0f;
double zoom_it = 0;
const int max_zoom_it = 100;
double paramC1 = 0.0;
double paramC2 = 0.0;
double param_7 = 0.0;
double param_8 = 0.0;
double param_9 = 0.0;
bool zmien;

void przyb(GLFWwindow* window, double/* xoffset */, double yoffset)
{
    if (yoffset > 0)
    {
        zoomlvl *= 1.1f;
    }
    else if (yoffset < 0)
    {
        zoomlvl /= 1.1f;
    }

    if (zoom_it >= max_zoom_it) {
        offsetX *= zoom_it;
        offsetY *= zoom_it;
        zoomlvl = 1.1f;
        zoom_it = 0;
    }
}


void klaw(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    double offset_in = 0.05f*zoomlvl;
    double krok = 0.1;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) 
    {
        switch (key) {
            case GLFW_KEY_7:
                param_7 *= krok;
                break;
            case GLFW_KEY_U:
                param_7 /= krok;
                break;
            case GLFW_KEY_8:
                param_8 *= krok;
                break;
            case GLFW_KEY_I:
                param_8 /= krok;
                break;
            case GLFW_KEY_9:
                param_9 *= krok;
                break;
            case GLFW_KEY_O:
                param_9 /= krok;
                break;
            case GLFW_KEY_1:
                zwiek /= 1.1f;
                break;
            case GLFW_KEY_2:
                zwiek *= 1.1f;
                break;
            case GLFW_KEY_LEFT:
                offsetX += offset_in;
                break;
            case GLFW_KEY_RIGHT:
                offsetX -= offset_in;
                break;
            case GLFW_KEY_DOWN:
                offsetY += offset_in;
                break;
            case GLFW_KEY_UP:
                offsetY -= offset_in;
                break;
            case GLFW_KEY_A:
                offsetX += offset_in;
                break;
            case GLFW_KEY_D:
                offsetX -= offset_in;
                break;
            case GLFW_KEY_S:
                offsetY += offset_in;
                break;
            case GLFW_KEY_W:
                offsetY -= offset_in;
                break;
            case GLFW_KEY_E:   // Dodajemy przycisk 'e' do oddalania
                zoomlvl /= 1.1f;
                break;
            case GLFW_KEY_Q:   // Dodajemy przycisk 'q' do przybli
                zoomlvl *= 1.1f;
                break;
            case GLFW_KEY_3:
                paramC1 -= krok;
                break;
            case GLFW_KEY_4:
                paramC1 += krok;
                break;
            case GLFW_KEY_5:
                paramC2 -= krok;
                break;
            case GLFW_KEY_6:
                paramC2 += 2*krok;
                break;
            case GLFW_KEY_M:
                zmien = !zmien;
                std::cout << zmien << std::endl;
                break;
            default:
                break;
        }

    }
}

unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)

    {
        int lenght;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)malloc(lenght * sizeof(char));
        glGetShaderInfoLog(id,lenght, &lenght, message);
        std::cout << "FAILED TO COMPILE " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        free(message);
        message = nullptr;
        return 0;
    }
    return id;
}
std::string LoadShader(const std::string& filepath) 
{
    std::string shader_code;
    std::ifstream shaderStream(filepath, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shader_code = sstr.str();
        shaderStream.close();
    }
    else {
        std::cout << "Faild to open" << filepath << std::endl;
        return "";
    }
    return shader_code;
}
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
