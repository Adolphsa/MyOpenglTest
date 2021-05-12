//
// Created by Administrator on 2021/4/30.
//

#ifndef MYOPENGLTEST_MYGLRENDERCONTEXT_H
#define MYOPENGLTEST_MYGLRENDERCONTEXT_H

#include "stdint.h"
#include "TriangleSample.h"

class MyGLRenderContext
{
    MyGLRenderContext();

    ~MyGLRenderContext();

public:
    void SetImageData(int format, int width, int height, uint8_t *pData);

    void OnSurfaceCreated();

    void OnSurfaceChanged(int width, int height);

    void OnDrawFrame();

    void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    static MyGLRenderContext* GetInstance();
    static void DestroyInstance();

private:
    static MyGLRenderContext *m_pContext;
    GLSampleBase *m_pCurSample;
    int m_ScreenW;
    int m_ScreenH;
};


#endif //MYOPENGLTEST_MYGLRENDERCONTEXT_H
