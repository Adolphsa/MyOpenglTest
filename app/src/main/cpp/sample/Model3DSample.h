//
// Created by Administrator on 2021/5/12.
//

#ifndef MYOPENGLTEST_MODEL3DSAMPLE_H
#define MYOPENGLTEST_MODEL3DSAMPLE_H

#include "../glm/detail/type_mat.hpp"
#include "../glm/detail/type_mat4x4.hpp"
#include "../model/shader.h"
#include "../model/model.h"
#include "GLSampleBase.h"

class Model3DSample : public GLSampleBase{
public:
    Model3DSample();

    virtual ~Model3DSample();

    virtual void LoadImage(NativeImage *pImage);

    virtual void Init();
    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);

private:
    glm::mat4 m_MVPMatrix;
    glm::mat4 m_ModelMatrix;
    Shader *m_pShader;
    Model *m_pModel;

    int m_AngleX;
    int m_AngleY;
    float m_ScaleX;
    float m_ScaleY;
};


#endif //MYOPENGLTEST_MODEL3DSAMPLE_H
