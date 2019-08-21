/* 
  shader.fs
  OpenGL-Practise

  Created by 叶亮 on 2019/8/21.
  Copyright © 2019 叶亮. All rights reserved.
*/
#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}
