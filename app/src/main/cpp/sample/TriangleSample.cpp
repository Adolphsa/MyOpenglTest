//
// Created by Administrator on 2021/5/10.
//

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
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
            "layout(location = 0) in vec3 vPosition;  \n"
            "uniform float xOffset;  \n"
            "uniform float YOffset;  \n"
            "uniform mat4 transform;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = transform*vec4(vPosition, 1.0);              \n"
            "   gl_PointSize = 50.0;              \n"
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
            -0.5f, 0.5f, 0.0f,   // 左上角
            -0.5f, -0.5f, 0.0f, // 左下角
            0.5f, -0.5f, 0.0f,  // 右下角
            0.5f, 0.5f, 0.0f,   // 右上角
    };

//    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    GLushort indices[] = { 0, 1, 2};

    if(m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    int vertexColorLocation = glGetUniformLocation(m_ProgramObj, "ourColor");
    int xOffsetLocation = glGetUniformLocation(m_ProgramObj, "xOffset");
    int yOffsetLocation = glGetUniformLocation(m_ProgramObj, "xOffset");
    int transformLoc = glGetUniformLocation(m_ProgramObj, "transform");

    // Use the program object
    glUseProgram (m_ProgramObj);
    glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
    glUniform1f(xOffsetLocation, 0.0f);
    glUniform1f(yOffsetLocation, 0.0f);

    //平移矩阵
    glm::mat4 trans = glm::mat4 (1.0f);
    trans = glm::translate(trans, glm::vec3(mOffsetX, mOffsetY, 0.0f));
//    trans = glm::scale(trans, glm::vec3(mCurrentScale, mCurrentScale, 1.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    // Load the vertex data
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray (0);


//    glDrawArrays (GL_TRIANGLES, 0, 3);

    glDrawElements(GL_POINTS, 3, GL_UNSIGNED_SHORT, indices);
    glUseProgram (GL_NONE);
}

void TriangleSample::UpdateTransformMatrix2(float offsetX, float offsetY, float scaleX, float scaleY)
{
    LOGCATE("UpdateTransformMatrix2 offsetX = %f, offsetY = %f", offsetX, offsetY);
    mCurrentScale = scaleX;
    mOffsetX = offsetX;
    mOffsetY = offsetY;
}

void TriangleSample::Destroy()
{
    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}