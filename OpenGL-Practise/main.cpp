//
//  main.cpp
//  OpenGL-Practise
//
//  Created by 叶亮 on 2019/8/7.
//  Copyright © 2019 叶亮. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

//显示一个深蓝绿色的窗口
int main()
{
    //初始化GLFW
    glfwInit();
    
    //设置OpenGl的主版本号和副版本号 OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    //使用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //不允许用户调整窗口的大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    //Mac OS需要添加这一行
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //创建窗口对象
    GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if(window == nullptr){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    //===============  GLEW  ===================
    //GLEW是用来管理OpenGl的函数指针的'
    
    glfwSetKeyCallback(window, key_callback);
    
    //设置为true 这样会在管理OpenGl的函数指针时更多地使用现代化的技术
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    //0,0表示窗口左下角的位置 width,height表示窗口大小
    glViewport(0, 0, width, height);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        //清空颜色的缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){
    //当用户按下ESC键，我们设置window窗口的WindowShouldClose属性为true
    //关闭应用程序
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
