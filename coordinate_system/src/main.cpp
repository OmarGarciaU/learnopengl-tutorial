#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/ext/matrix_clip_space.hpp"
#include "include/glm/ext/matrix_transform.hpp"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/glm/trigonometric.hpp"
#include "shaders/shader.h"
#include "vec3.h"
#include <ctime>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

    const char vertPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/coordinate_system/src/shaders/shader.vs";
    const char fragPath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/coordinate_system/src/shaders/shader.fs";

    Shader Shader(vertPath, fragPath);


    float vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0,1,3, // triangle one
        1,2,3  //triangle two
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // n*sizeof(float) the stride i.e how many elements in each row
    glEnableVertexAttribArray(0);

    //texture coordinate attribute
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //Load and create multiple texture
    //-------------------------
    unsigned int texture1, texture2;

    //Texture 1
    //---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    //set wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set texture filtering params
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    //load image create texture and gen mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    const char filePath[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/coordinate_system/src/resources/container.jpg";
    const char filePath2[] = "/Users/omargarcia/Desktop/Programming/Repos/Learning_and_Books/learnopengl-tutorial/coordinate_system/src/resources/awesomeface.png";
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    //Texture 2
    //---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);
    //set wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set texture filtering params
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    data = stbi_load(filePath2, &width, &height, &nrChannels, 0);


    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    Shader.use();
    Shader.setInt("texture1", 0);
    Shader.setInt("texture2", 1);

    //Random color generator
    srand(time(0));
    color color(0.5f, 0.2f, 0.9f);
    double a = 1.0f;
    color.print_rgb();

    while(!glfwWindowShouldClose(window)){
        //input
        processInput(window);

        //render
        glClearColor(color.x(), color.y(), color.z(), a);
        glClear(GL_COLOR_BUFFER_BIT);

        //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //activate shader
        Shader.use();

        //create transformations
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);

        //retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(Shader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(Shader.ID, "view");

        //pass them to the shader (3 dif ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        //perspective usually doesnt change so it is more effecient to set it outside the main loop
        Shader.setMat4("projection", projection);

        //render constainer
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
