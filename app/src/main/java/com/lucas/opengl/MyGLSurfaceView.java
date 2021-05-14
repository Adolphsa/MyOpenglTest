package com.lucas.opengl;

import android.content.Context;
import android.content.res.Resources;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;

/**
 * Created by lucas on 2021/4/30.
 */
public class MyGLSurfaceView extends GLSurfaceView implements ScaleGestureDetector.OnScaleGestureListener {

    private static final String TAG = "MyGLSurfaceView";

    public static final int IMAGE_FORMAT_RGBA = 0x01;
    //YUV420SP YYYY UVUV
    public static final int IMAGE_FORMAT_NV21 = 0x02;
    //YUV420SP YYYY VUVU
    public static final int IMAGE_FORMAT_NV12 = 0x03;
    //YUV420P YYYY
    public static final int IMAGE_FORMAT_I420 = 0x04;

    private MyGLRender mGLRender;

    private float mPreviousY;
    private float mPreviousX;
    private int mXOffset;
    private int mYOffset;

    private ScaleGestureDetector mScaleGestureDetector;
    private float mPreScale = 1.0f;
    private float mCurScale = 1.0f;

    public MyGLSurfaceView(Context context, MyGLRender glRender) {
        this(context, glRender, null);
    }

    public MyGLSurfaceView(Context context, MyGLRender glRender, AttributeSet attrs)  {
        super(context, attrs);
        this.setEGLContextClientVersion(2);
        mGLRender = glRender;
        setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        setRenderer(mGLRender);
        setRenderMode(RENDERMODE_WHEN_DIRTY);

        mScaleGestureDetector = new ScaleGestureDetector(context, this);
    }

    public MyGLRender getGLRender() {
        return mGLRender;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getPointerCount() == 1) {

//            float x = event.getX();
//            float y = event.getY();

            float x = toOpenGLCoord(event.getX(), true);
            float y = toOpenGLCoord(event.getY(), false);

            switch (event.getAction()) {
                case MotionEvent.ACTION_UP:
                    break;
                case MotionEvent.ACTION_DOWN:
                    Log.d(TAG, "onTouchEvent: ACTION_DOWN");
                    mPreviousX = toOpenGLCoord(event.getX(), true);
                    mPreviousY = toOpenGLCoord(event.getY(), false);
                    break;
                case MotionEvent.ACTION_POINTER_DOWN:
                    Log.d(TAG, "onTouchEvent: ACTION_POINTER_DOWN");
                    break;
                case MotionEvent.ACTION_MOVE:
                    Log.d(TAG, "onTouchEvent: ACTION_MOVE");
                    float dx = x - mPreviousX;
                    float dy = y - mPreviousY;
//                    Log.d(TAG, "onTouchEvent: dx = " + dx + ",dy = " + dy);
                    mGLRender.updateTransformMatrix2(x, y, mCurScale, mCurScale);
                    requestRender();
                    break;
                default:
                    break;
            }

        }else {
            mScaleGestureDetector.onTouchEvent(event);
        }
        return true;
    }

    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        float preSpan = detector.getPreviousSpan();
        float curSpan = detector.getCurrentSpan();
        if (curSpan < preSpan) {
            mCurScale = mPreScale - (preSpan - curSpan) / 200;
        } else {
            mCurScale = mPreScale + (curSpan - preSpan) / 200;
        }
        mCurScale = Math.max(0.05f, Math.min(mCurScale, 80.0f));
        Log.d(TAG, "onScale: =" + mCurScale);
        return false;
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector detector) {
        return true;
    }

    @Override
    public void onScaleEnd(ScaleGestureDetector detector) {
        mPreScale = mCurScale;
    }

    /**
     * 屏幕坐标系点转OpenGL坐标系
     * @return
     */
    private static float toOpenGLCoord(float value, boolean isWidth){
        if(isWidth){
            return (value / (float) Resources.getSystem().getDisplayMetrics().widthPixels) * 2 - 1;
        }else {
            return -((value / (float) Resources.getSystem().getDisplayMetrics().heightPixels) * 2 - 1);
        }
    }

}
