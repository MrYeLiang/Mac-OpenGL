//
//  P03_glsl.cpp
//  OpenGL-Practise
//
//  Created by 叶亮 on 2019/8/21.
//  Copyright © 2019 叶亮. All rights reserved.
//
#include "P03_glsl.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include "P03_glsl.hpp"

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace std;

const char *vShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

const char *fShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = ourColor;\n"
        "}\n\0";


int dynamic_set_color()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //apple  Mac OS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    int success;
    char infoLog[512];
    
    //vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //check vertex shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "vertexShader compile error:"<< infoLog << endl;
    }
    
    //fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //check fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "fragmentShader compile error:" << infoLog << endl;
    }
    
    //link shader
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //check link status
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "link shader Error: "<< infoLog << endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    //set up vertex data
    float vertices[] = {
        0.5f,  -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    //1 bind the vertex Array, 2 bind vertex buffer, 3 configure vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAO);
    
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        //render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glad_glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    
    return 0;
    
    
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

