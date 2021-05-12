#include "util/LogUtil.h"
#include <MyGLRenderContext.h>
#include <jni.h>
#include <string>

#define NATIVE_RENDER_CLASS_NAME "com/lucas/opengl/MyNativeRender"

#ifdef __cplusplus
extern "C" {
#endif

/**
* class:   com_lucas_opengl_MyNativeRender
* method:  native_StringFromJNI
* signature:   ()V
*/
JNIEXPORT jstring JNICALL native_StringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C+++_20210510";
    return env->NewStringUTF(hello.c_str());
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_OnInit
 * signature:   ()V
 */
JNIEXPORT void JNICALL native_OnInit(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance();
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_OnUnInit
 * signature:   ()V
 */
JNIEXPORT void JNICALL native_OnUnInit(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::DestroyInstance();
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_UpdateTransformMatrix
 * signature:   (FFFF)V
 */
JNIEXPORT void JNICALL
native_UpdateTransformMatrix(JNIEnv *env, jobject instance, jfloat rotateX, jfloat rotateY,
                             jfloat scaleX, jfloat scaleY) {
    MyGLRenderContext::GetInstance()->UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_SetImageData
 * signature:   (III[B)V
 */
JNIEXPORT void JNICALL native_SetImageData(JNIEnv *env, jobject thiz, jint format,
                                           jint width, jint height,
                                           jbyteArray bytes) {
    int len = env->GetArrayLength(bytes);
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(bytes, 0, len, reinterpret_cast<jbyte *>(buf));
    MyGLRenderContext::GetInstance()->SetImageData(format, width, height, buf);
    delete[] buf;
    env->DeleteLocalRef(bytes);
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_OnSurfaceCreated
 * signature:   ()V
 */
JNIEXPORT void JNICALL native_OnSurfaceCreated(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_OnSurfaceChanged
 * signature:   (II)V
 */
JNIEXPORT void JNICALL native_OnSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                               jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

/**
 * class:   com_lucas_opengl_MyNativeRender
 * method:  native_OnDrawFrame
 * signature:   ()V
 */
JNIEXPORT void JNICALL native_OnDrawFrame(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}

#ifdef __cplusplus
}
#endif

//动态注册方法
static JNINativeMethod g_RenderMethods[] = {
        {"native_StringFromJNI",         "()Ljava/lang/String;", (void *) (native_StringFromJNI)},
        {"native_OnInit",                "()V",                  (void *) (native_OnInit)},
        {"native_OnUnInit",              "()V",                  (void *) (native_OnUnInit)},
        {"native_UpdateTransformMatrix", "(FFFF)V",              (void *) (native_UpdateTransformMatrix)},
        {"native_SetImageData",          "(III[B)V",             (void *) (native_SetImageData)},
        {"native_OnSurfaceCreated",      "()V",                  (void *) (native_OnSurfaceCreated)},
        {"native_OnSurfaceChanged",      "(II)V",                (void *) (native_OnSurfaceChanged)},
        {"native_OnDrawFrame",           "()V",                  (void *) (native_OnDrawFrame)},
};

static int
RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum) {
    LOGCATD("RegisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        LOGCATE("RegisterNativeMethods fail. clazz == NULL");
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, methods, methodNum) < 0) {
        LOGCATE("RegisterNativeMethods fail");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className) {
    LOGCATE("UnregisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr) {
        LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
        return;
    }
    if (env != nullptr) {
        env->UnregisterNatives(clazz);
    }
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p) {
    LOGCATE("===== JNI_OnLoad =====");
    jint jniRet = JNI_ERR;
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return jniRet;
    }

    jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME, g_RenderMethods,
                                        sizeof(g_RenderMethods) /
                                        sizeof(g_RenderMethods[0]));
    if (regRet != JNI_TRUE) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p) {
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return;
    }

    UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
}

