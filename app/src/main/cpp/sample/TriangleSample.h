//
// Created by Administrator on 2021/5/10.
//

#ifndef MYOPENGLTEST_TRIANGLESAMPLE_H
#define MYOPENGLTEST_TRIANGLESAMPLE_H

#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase
{
public:
    TriangleSample();
    virtual ~TriangleSample();

    virtual void LoadImage(NativeImage *pImage);

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();
};


#endif //MYOPENGLTEST_TRIANGLESAMPLE_H
