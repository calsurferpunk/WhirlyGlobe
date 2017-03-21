/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mousebird_maply_Quaternion */

#ifndef _Included_com_mousebird_maply_Quaternion
#define _Included_com_mousebird_maply_Quaternion
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    multiply
 * Signature: (Lcom/mousebird/maply/Quaternion;)Lcom/mousebird/maply/Quaternion;
 */
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_Quaternion_multiply__Lcom_mousebird_maply_Quaternion_2
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    multiply
 * Signature: (Lcom/mousebird/maply/Point3d;)Lcom/mousebird/maply/Point3d;
 */
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_Quaternion_multiply__Lcom_mousebird_maply_Point3d_2
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    multiply
 * Signature: (Lcom/mousebird/maply/AngleAxis;)Lcom/mousebird/maply/Quaternion;
 */
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_Quaternion_multiply__Lcom_mousebird_maply_AngleAxis_2
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    slerp
 * Signature: (Lcom/mousebird/maply/Quaternion;D)Lcom/mousebird/maply/Quaternion;
 */
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_Quaternion_slerp
  (JNIEnv *, jobject, jobject, jdouble);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_Quaternion_nativeInit
  (JNIEnv *, jclass);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    initialise
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_Quaternion_initialise__
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    initialise
 * Signature: (Lcom/mousebird/maply/Point3d;Lcom/mousebird/maply/Point3d;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_Quaternion_initialise__Lcom_mousebird_maply_Point3d_2Lcom_mousebird_maply_Point3d_2
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     com_mousebird_maply_Quaternion
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_Quaternion_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
