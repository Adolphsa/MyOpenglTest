//
// Created by Administrator on 2021/5/11.
//

#ifndef MYOPENGLTEST_TEXTUREMAPSAMPLE_H
#define MYOPENGLTEST_TEXTUREMAPSAMPLE_H

#include "GLSampleBase.h"

class TextureMapSample : public GLSampleBase
{
public:
    TextureMapSample();

    virtual ~TextureMapSample();

    void LoadImage(NativeImage *pImage);

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

private:
    GLuint m_TextureId;
    GLint m_SamplerLoc;
    NativeImage m_RenderImage;
};


#endif //MYOPENGLTEST_TEXTUREMAPSAMPLE_H
