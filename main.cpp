#include "globals.h"
#include "functions.h"

int main(void)
{
    GLFWwindow* window;
    GLFWwindow* window2;
    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* MAKING WINDOW AND CONTEXT */

    window = glfwCreateWindow(1920, 1080, "Fraktale" , NULL, NULL);
    window2 = glfwCreateWindow(300,  200, "Functions", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, klaw);
    glfwSetScrollCallback(window, przyb);


    // INIT FUNCTION MUST BE CALLED IN CREATED CONTEXT
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Initialize has been failed" << std::endl;
    }
    // GETING INFO ABOUT GLSL
    const GLubyte* version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    if (version)
    {
        std::cout << "Version GLSL: " << version << std::endl;
    }
    else
    {
        std::cout << "Can't get info about GLSL" << std::endl;
    }


    std::string vertexShaderSource = LoadShader("shaders/vertexShader.vert");
    std::string fragmentShaderSource = LoadShader("shaders/fragmentShader.frag");

    unsigned int shader = CreateShader(vertexShaderSource,fragmentShaderSource);
    int offsetLocation = glGetUniformLocation(shader, "offset");
    int zoomLocation = glGetUniformLocation(shader, "zoomlvl");
    int zwiekLocation = glGetUniformLocation(shader, "zwiek");
    int c1Location = glGetUniformLocation(shader, "c1");
    int c2Location = glGetUniformLocation(shader, "c2");
    int zmienLocation = glGetUniformLocation(shader, "zmien");
    int parametry_7 = glGetUniformLocation(shader, "p7");
    int parametry_8= glGetUniformLocation(shader, "p8");
    int parametry_9 = glGetUniformLocation(shader, "p9");
    //DEFINITON OF VERTEX ARRAY 2D
    float wierzch[] = {

        -1.0f,-1.0f,
         1.0f,-1.0f,
        -1.0f, 1.0f,
         1.0f, 1.0f,
    };
    //CREATING VBO AND GIVE HIM DATA
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wierzch), wierzch, GL_STATIC_DRAW);
    //CREATING VCO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    while (!glfwWindowShouldClose(window) || !glfwWindowShouldClose(window2))
    {

        /* Render FRACTAL window */
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glUniform2d(offsetLocation, offsetX, offsetY);
        glUniform1d(zoomLocation, zoomlvl);
        glUniform1d(zwiekLocation, zwiek);
        glUniform1i(zmienLocation, zmien ? 1 : 0);
        glUniform1d(c1Location, paramC1);
        glUniform1d(c2Location, paramC2);
        glUniform1d(parametry_7, param_7);
        glUniform1d(parametry_8, param_8);
        glUniform1d(parametry_9, param_9);
        glBindVertexArray(VAO);
	//RENDERING SQUARE BY TWO TRIANGLES
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /*Rebder FUNCTIONS window*/
        glfwMakeContextCurrent(window2);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window2);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
