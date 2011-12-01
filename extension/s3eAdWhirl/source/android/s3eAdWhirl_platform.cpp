/*
 * android-specific implementation of the s3eAdWhirl extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eAdWhirl_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3eAdWhirlStart;
static jmethodID g_s3eAdWhirlRequestFreshAd;
static jmethodID g_s3eAdWhirlShow;
static jmethodID g_s3eAdWhirlHide;

s3eResult s3eAdWhirlInit_platform()
{
    //Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    //Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eAdWhirl");
    if (!cls)
        goto fail;

    //Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    //Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    //Get all the extension methods
    g_s3eAdWhirlStart = env->GetMethodID(cls, "s3eAdWhirlStart", "(Ljava/lang/String;)I");
    if (!g_s3eAdWhirlStart)
        goto fail;

    g_s3eAdWhirlRequestFreshAd = env->GetMethodID(cls, "s3eAdWhirlRequestFreshAd", "()I");
    if (!g_s3eAdWhirlRequestFreshAd)
        goto fail;

    g_s3eAdWhirlShow = env->GetMethodID(cls, "s3eAdWhirlShow", "()I");
    if (!g_s3eAdWhirlShow)
        goto fail;

    g_s3eAdWhirlHide = env->GetMethodID(cls, "s3eAdWhirlHide", "()I");
    if (!g_s3eAdWhirlHide)
        goto fail;



    IwTrace(ADWHIRL, ("ADWHIRL init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);
    
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
    
fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eAdWhirl, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eAdWhirlTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult s3eAdWhirlStart_platform(const char* appKey)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring appKey_jstr = env->NewStringUTF(appKey);
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3eAdWhirlStart, appKey_jstr);
}

s3eResult s3eAdWhirlRequestFreshAd_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3eAdWhirlRequestFreshAd);
}

s3eResult s3eAdWhirlShow_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3eAdWhirlShow);
}

s3eResult s3eAdWhirlHide_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3eAdWhirlHide);
}
