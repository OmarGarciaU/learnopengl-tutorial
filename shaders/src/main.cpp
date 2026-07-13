#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "vec3.h"
#include "shaders/shader.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*
 * Vertex Shader
*/

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "EnigmaTek", NULL, NULL);

  //Winodw creation failure
  //---------------------
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Build And Compile shader program
  // ------------------------------- 
  const char vertPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/shaders/src/shaders/shader.vs";
  const char fragPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/shaders/src/shaders/shader.fs";
  Shader Shader(vertPath,fragPath);
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[]{
     0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,   0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
  };
  
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1,&VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  //Random generator
  srand(time(0));

  //Generate a random color
  color color(rand() % 255 / 255.0,rand() % 255 / 255.0,rand() % 255 / 255.0);

  double a = 1.0f;

  color.print_rgb();

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // render 
    glClearColor(color.x(), color.y(), color.z(), a);
    glClear(GL_COLOR_BUFFER_BIT);


    Shader.use();
    Shader.setFloat("someUniform", 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1,&VAO);
  glDeleteBuffers(1, &VBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
