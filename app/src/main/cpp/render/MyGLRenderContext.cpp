//
// Created by Administrator on 2021/4/30.
//

#include "MyGLRenderContext.h"
#include "../util/LogUtil.h"
#include "../util/ImageDef.h"
#include <TextureMapSample.h>
#include <NV21TextureMapSample.h>
#include <Model3DSample.h>

MyGLRenderContext* MyGLRenderContext::m_pContext = nullptr;

MyGLRenderContext::MyGLRenderContext()
{
    m_pCurSample = new TriangleSample();
//    m_pCurSample = new TextureMapSample();
//    m_pCurSample = new NV21TextureMapSample();
//    m_pCurSample = new Model3DSample();
}

MyGLRenderContext::~MyGLRenderContext()
{

}

void MyGLRenderContext::SetImageData(int format, int width, int height, uint8_t *pData)
{
    LOGCATE("MyGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width*height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width*height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width*height/4;
            break;
        default:
            break;
    }

    if (m_pCurSample) {
        m_pCurSample->LoadImage(&nativeImage);
    }
}

void MyGLRenderContext::OnSurfaceCreated()
{
    LOGCATE("MyGLRenderContext::OnSurfaceCreated");
    glClearColor(1.0f,1.0f,1.0f, 1.0f);
}

void MyGLRenderContext::OnSurfaceChanged(int width, int height)
{
    LOGCATE("MyGLRenderContext::OnSurfaceChanged [w, h] = [%d, %d]", width, height);
    glViewport(0, 0, width, height);
    m_ScreenW = width;
    m_ScreenH = height;
}

void MyGLRenderContext::OnDrawFrame()
{
    LOGCATE("MyGLRenderContext::OnDrawFrame");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (m_pCurSample)
    {
        m_pCurSample->Init();
        m_pCurSample->Draw(m_ScreenW, m_ScreenH);
    }
}

void MyGLRenderContext::UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY)
{
    LOGCATE("MyGLRenderContext::UpdateTransformMatrix [rotateX, rotateY, scaleX, scaleY] = [%f, %f, %f, %f]", rotateX, rotateY, scaleX, scaleY);
    if (m_pCurSample)
    {
        m_pCurSample->UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    }
}

void MyGLRenderContext::UpdateTransformMatrix2(float offsetX, float offsetY, float scaleX, float scaleY)
{
    LOGCATE("MyGLRenderContext::UpdateTransformMatrix [offsetX, offsetY, scaleX, scaleY] = [%f, %f, %f, %f]", offsetX, offsetY, scaleX, scaleY);
    if (m_pCurSample)
    {
        m_pCurSample->UpdateTransformMatrix2(offsetX, offsetY, scaleX, scaleY);
    }
}

MyGLRenderContext* MyGLRenderContext::GetInstance()
{
    LOGCATE("MyGLRenderContext::GetInstance");
    if (m_pContext == nullptr)
    {
        m_pContext = new MyGLRenderContext();
    }
    return m_pContext;
}

void MyGLRenderContext::DestroyInstance()
{
    LOGCATE("MyGLRenderContext::DestroyInstance");
    if (m_pContext)
    {
        delete m_pContext;
        m_pContext = nullptr;
    }
}

