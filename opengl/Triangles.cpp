//
//  Triangles.cpp
//  opengl
//
//  Created by 天元创想 on 2021/2/15.
//

#include <iostream>
using namespace std;

#include "LoadShaders.h"
#include <GLUT/GLUT.h>

#define BUFFER_OFFSET(x)((const void*)(x))


enum VAO_IDs{Triangles,NumVAOs};
enum Buffer_IDs{ArrayBuffer,NumBuffers};

enum Attrib_IDs{vPosition=0};
GLuint VAOs[NumVAOs];
GLuint BUffers[NumBuffers];

const GLuint NumVertices=6;
const char *pTriangleVert="#version 410 core\n\
layout(location = 0) in vec4 vPosition;\n\
void\n\
main()\n\
{\n\
gl_Position= vPosition;\n\
}";

const char *pTriangleFrag = "#version 410 core\n\
out vec4 fColor;\n\
void\n\
main()\n\
{\n\
fColor = vec4(0.0, 0.0, 1.0, 1.0);\n\
}";

void init()
{
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    GLfloat vertices[NumVertices] [2]=
    {
        {-0.90,-0.90},
        {0.85,-0.90},
        {-0.90,0.85},
        {0.90,-0.85},
        {0.90,0.90},
        {-0.85,0.90}
    };
    
    glGenBuffers(NumBuffers, BUffers);
    glBindBuffer(GL_ARRAY_BUFFER, BUffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    ShaderInfo shaders[]=
    {
        {GL_VERTEX_SHADER,pTriangleVert},{GL_FRAGMENT_SHADER,pTriangleFrag},{GL_NONE,NULL}
        
    };
    
    GLuint program=LoadShaders(shaders);
    glUseProgram(program);
    
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    glFlush();
    
}

int main(int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(512, 512);
    
    glutCreateWindow(argv[0]);
    
    cout<<"supported GLSL version is:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<endl;
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
}
