//
// Created by Administrator on 2021/5/10.
//

#include "GLUtils.h"
#include "TriangleSample.h"

TriangleSample::TriangleSample()
{

}

TriangleSample::~TriangleSample()
{

}

void TriangleSample::LoadImage(NativeImage *pImage)
{
    //null implement
}

void TriangleSample::Init()
{
    if (m_ProgramObj != 0) return;

    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "uniform float xOffset;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4(vPosition.x+xOffset, -vPosition.y, vPosition.z, 1.0);              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "uniform vec4 ourColor;                       \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = ourColor;  \n"
            "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

}

void TriangleSample::Draw(int screenW, int screenH)
{
    LOGCATE("TriangleSample::Draw");
    GLfloat vVertices[] = {
            // first triangle
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };

    if(m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    int vertexColorLocation = glGetUniformLocation(m_ProgramObj, "ourColor");
    int vertexOffsetLocation = glGetUniformLocation(m_ProgramObj, "xOffset");

    // Use the program object
    glUseProgram (m_ProgramObj);
    glUniform4f(vertexColorLocation, 0.6f, 1.0f, 0.0f, 0.0f);
    glUniform1f(vertexOffsetLocation, 0.8f);

    // Load the vertex data
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray (0);

    glDrawArrays (GL_TRIANGLES, 0, 6);
    glUseProgram (GL_NONE);
}

void TriangleSample::Destroy()
{
    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}