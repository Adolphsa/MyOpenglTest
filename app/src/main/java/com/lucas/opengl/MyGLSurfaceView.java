package com.lucas.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

/**
 * Created by lucas on 2021/4/30.
 */
public class MyGLSurfaceView extends GLSurfaceView {

    public static final int IMAGE_FORMAT_RGBA = 0x01;
    //YUV420SP YYYY UVUV
    public static final int IMAGE_FORMAT_NV21 = 0x02;
    //YUV420SP YYYY VUVU
    public static final int IMAGE_FORMAT_NV12 = 0x03;
    //YUV420P YYYY
    public static final int IMAGE_FORMAT_I420 = 0x04;

    private MyGLRender mGLRender;

    public MyGLSurfaceView(Context context) {
        this(context, null);
    }

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.setEGLContextClientVersion(2);
        mGLRender = new MyGLRender();
        setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        setRenderer(mGLRender);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }
}
