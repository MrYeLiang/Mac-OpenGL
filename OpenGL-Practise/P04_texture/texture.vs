/* 
  texture.vs
  OpenGL-Practise

  Created by 叶亮 on 2019/8/21.
  Copyright © 2019 叶亮. All rights reserved.
*/
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
