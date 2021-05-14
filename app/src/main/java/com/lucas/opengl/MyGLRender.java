package com.lucas.opengl;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by lucas on 2021/5/10.
 */
public class MyGLRender implements GLSurfaceView.Renderer {
    private static final String TAG = "MyGLRender";
    private MyNativeRender myNativeRender;

    public MyGLRender() {
        myNativeRender = new MyNativeRender();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        myNativeRender.native_OnSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        myNativeRender.native_OnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        Log.d(TAG, "onDrawFrame: ");
        myNativeRender.native_OnDrawFrame();
    }

    public void init() {
        myNativeRender.native_OnInit();
    }

    public void unInit() {
        myNativeRender.native_OnUnInit();
    }

    public void setImageData(int format, int width, int height, byte[] bytes) {
        myNativeRender.native_SetImageData(format, width, height, bytes);
    }

    public void updateTransformMatrix2(float offsetX, float offsetY, float scaleX, float scaleY)
    {
        myNativeRender.native_UpdateTransformMatrix2(offsetX, offsetY, scaleX, scaleY);
    }


}
