//
// Created by Administrator on 2021/5/10.
//

#ifndef MYOPENGLTEST_IMAGEDEF_H
#define MYOPENGLTEST_IMAGEDEF_H

#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include "stdio.h"
#include "sys/stat.h"
#include "stdint.h"
#include "LogUtil.h"

#define IMAGE_FORMAT_RGBA           0x01
#define IMAGE_FORMAT_NV21           0x02
#define IMAGE_FORMAT_NV12           0x03
#define IMAGE_FORMAT_I420           0x04

#define IMAGE_FORMAT_RGBA_EXT       "RGB32"
#define IMAGE_FORMAT_NV21_EXT       "NV21"
#define IMAGE_FORMAT_NV12_EXT       "NV12"
#define IMAGE_FORMAT_I420_EXT       "I420"

typedef struct _tag_NativeRectF
{
    float left;
    float top;
    float right;
    float bottom;
    _tag_NativeRectF()
    {
        left = top = right = bottom = 0.0f;
    }
} RectF;

typedef struct _tag_NativeImage
{
    int width;
    int height;
    int format;
    uint8_t *ppPlane[3];

    _tag_NativeImage()
    {
        width = 0;
        height = 0;
        format = 0;
        ppPlane[0] = nullptr;
        ppPlane[1] = nullptr;
        ppPlane[2] = nullptr;
    }
} NativeImage;

#endif //MYOPENGLTEST_IMAGEDEF_H
