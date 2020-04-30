#ifndef LOCALDEFINES_H_
#define LOCALDEFINES_H_

#include <jni.h>

#ifndef LOG_TAG
#define LOG_TAG "airplay"
#endif



#define USE_LOGALL	// If you don't need to all LOG, comment out this line and select follows
//#define USE_LOGV
//#define USE_LOGD
#define USE_LOGI
#define USE_LOGW
#define USE_LOGE
#define USE_LOGF

#ifdef NDEBUG
#undef USE_LOGALL
#endif

#ifdef LOG_NDEBUG
#undef USE_LOGALL
#endif

// Absolute class name of Java object
// if you change the package name of UVCCamera library, you must fix these
#define		JTYPE_SYSTEM				"Ljava/lang/System;"
#define		JTYPE_UVCCAMERA				"Lcom/serenegiant/usb/UVCCamera;"
//
typedef		jlong						ID_TYPE;

#endif /* LOCALDEFINES_H_ */
