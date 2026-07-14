#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "shaders/shader.h"
#include "vec3.h"
#include <cmath>
#include <ctime>
#include <iostream>


using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);

    if(window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: load all openGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    const char vertPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/shaders/src/shaders/shader.vs";
    const char fragPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/shaders/src/shaders/shader.fs";

    Shader Shader(vertPath, fragPath);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.0f,  0.5f, 0.0f  // Top
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);



    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 3*sizeof(float) the stride i.e how many elements in each row
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    //Random generator
    srand(time(0));

    color color(0.5f, 0.2f, 0.9f);

    double a = 1.0f;

    color.print_rgb();

    int click = 0;

    while(!glfwWindowShouldClose(window)){
        //input
        processInput(window);

        glClearColor(color.x(), color.y(), color.z(), a);
        glClear(GL_COLOR_BUFFER_BIT);

        //render

        Shader.use();
        glBindVertexArray(VAO);
        //update every thousand clicks
        if(click < 15){
            click++;
        }else{
            for(int i = 0; i< 9; i+=3){
                vertices[i] = vertices[i] + 0.05f;
                if(vertices[i] > 1.0) vertices[i] = -1.0f;
            }
            click = 0;
        }

        cout << click;
        


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 3*sizeof(float) the stride i.e how many elements in each row
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}
