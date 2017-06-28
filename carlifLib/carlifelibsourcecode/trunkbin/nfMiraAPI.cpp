#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include "CarLifeLibTest.h"



#define LOG_TAG "nForeMiraAPI"
//Android 4.2
#include <utils/Log.h>
//Android 4.4 add
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeClickDownEvent(JNIEnv *env, jobject thisObj,jint x,jint y){
	ALOGD("call native_nfcarlifedemo_CarlifeClickDownEvent ~~!!");
	jint i = ClickDownEvent(x,y);
	return 1;
}
#include <unistd.h>

#include <cutils/properties.h> //property_set

#define _PATH_PROCNET_ARP "/proc/net/arp"
static const char g_szVersion[] = "nFore WFD library 1.0";
#define JNIREG_CLASS "com/example/carlifeapk/carlifejni"//指定要注册的类

JavaVM *g_JavaVM;
jobject g_obj;

namespace android {


extern "C" JNIEXPORT jint native_nfcarlifedemo_carlifelibtest(JNIEnv *env, jobject thisObj){
	//ALOGD("call native_nfcarlifedemo_carlifelibtest ~~!!");
	env->GetJavaVM(&g_JavaVM);
	g_obj=env->NewGlobalRef(thisObj);
	nfcarlifetest();
	
	return 1;
}

extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeClickUpEvent(JNIEnv *env, jobject thisObj,jint x,jint y){
	//ALOGD("call native_nfcarlifedemo_CarlifeClickUpEvent ~~!!");
	jint i = ClickUpEvent(x,y);
	return 1;
}

extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeOnClickEvent(JNIEnv *env, jobject thisObj,jint x,jint y){
//	ALOGD("call native_nfcarlifedemo_CarlifeOnClickEvent ~~!!");
	jint i = OnClickEvent(x,y);
	return 1;
}


extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeDoubleClickEvent(JNIEnv *env, jobject thisObj,jint x,jint y){
//	ALOGD("call native_nfcarlifedemo_CarlifeDoubleClickEvent ~~!!");
	jint i = DoubleClickEvent(x,y);
	return 1;
}

extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeHoldOnEvent(JNIEnv *env, jobject thisObj,jint x,jint y){
//	ALOGD("call native_nfcarlifedemo_CarlifeHoldOnEvent ~~!!");
	jint i = HoldOnEvent(x,y);
	return 1;
}

extern "C" JNIEXPORT jint native_nfcarlifedemo_CarlifeMoveEvnet(JNIEnv *env, jobject thisObj,jint x,jint y){
//	ALOGD("call native_nfcarlifedemo_CarlifeMoveEvnet ~~!!");
	jint i = MoveEvnet(x,y);
	return 1;
}

extern "C" JNIEXPORT void native_nfcarlifedemo_CarlifeSendVrBuff(JNIEnv *env, jobject thisObj,jint len,jshortArray SendData){
	//ALOGD("call native_nfcarlifedemo_CarlifeSendVrBuff ~~!!");
	short arry[len];
	env->GetShortArrayRegion(SendData,0,len,(jshort*)arry);
	SendAudioRecordData((u8*)arry,len);
	return;
}



/**********************************************************************************/
static JNINativeMethod gMethods[] = {
	{ "carlifelibtest", 			"()I", (void*)native_nfcarlifedemo_carlifelibtest },
	{ "CarlifeClickDownEvent", 		"(II)I", (void*)native_nfcarlifedemo_CarlifeClickDownEvent },
	{ "CarlifeClickUpEvent", 		"(II)I", (void*)native_nfcarlifedemo_CarlifeClickUpEvent },
	{ "CarlifeOnClickEvent", 		"(II)I", (void*)native_nfcarlifedemo_CarlifeOnClickEvent },
	{ "CarlifeDoubleClickEvent", 	"(II)I", (void*)native_nfcarlifedemo_CarlifeDoubleClickEvent },
	{ "CarlifeHoldOnEvent", 		"(II)I", (void*)native_nfcarlifedemo_CarlifeHoldOnEvent },
	{ "CarlifeMoveEvnet", 			"(II)I", (void*)native_nfcarlifedemo_CarlifeMoveEvnet },
	{ "CarlifeSendVrBuff", 			"(I[S)V", (void*)native_nfcarlifedemo_CarlifeSendVrBuff }
};


/*
* Register several native methods for one class.
*/
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;
	clazz = env->FindClass( className);
	if (clazz == NULL) {
		return JNI_FALSE;
	}
	if (env->RegisterNatives( clazz, gMethods, numMethods) < 0) {
		return JNI_FALSE;
	}

	return JNI_TRUE;
}
/*
* Register native methods for all classes we know about.
*/
static int registerNatives(JNIEnv* env)
{
	if (!registerNativeMethods(env, JNIREG_CLASS, gMethods,
                                 sizeof(gMethods) / sizeof(gMethods[0])))
		return JNI_FALSE;

	return JNI_TRUE;
}
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return -1;
	}
	if (!registerNatives(env)) {//注册
		return -1;
	}
	/* success -- return valid version number */
	result = JNI_VERSION_1_4;

	return result;
}

//onUnLoad方法，在JNI组件被释放时调用
extern "C" void JNI_OnUnload(JavaVM* vm, void* reserved){
    ALOGD("call JNI_OnUnload ~~!!");
}

}// namespace android




