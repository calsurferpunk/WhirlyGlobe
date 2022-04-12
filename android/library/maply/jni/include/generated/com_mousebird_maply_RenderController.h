/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mousebird_maply_RenderController */

#ifndef _Included_com_mousebird_maply_RenderController
#define _Included_com_mousebird_maply_RenderController
#ifdef __cplusplus
extern "C" {
#endif
#undef com_mousebird_maply_RenderController_ImageLayerDrawPriorityDefault
#define com_mousebird_maply_RenderController_ImageLayerDrawPriorityDefault 100L
#undef com_mousebird_maply_RenderController_FeatureDrawPriorityBase
#define com_mousebird_maply_RenderController_FeatureDrawPriorityBase 20000L
#undef com_mousebird_maply_RenderController_MarkerDrawPriorityDefault
#define com_mousebird_maply_RenderController_MarkerDrawPriorityDefault 40000L
#undef com_mousebird_maply_RenderController_LabelDrawPriorityDefault
#define com_mousebird_maply_RenderController_LabelDrawPriorityDefault 60000L
#undef com_mousebird_maply_RenderController_ParticleDrawPriorityDefault
#define com_mousebird_maply_RenderController_ParticleDrawPriorityDefault 1000L
/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setScene
 * Signature: (Lcom/mousebird/maply/Scene;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setScene
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setupShadersNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setupShadersNative
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setViewNative
 * Signature: (Lcom/mousebird/maply/View;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setViewNative
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setClearColor
 * Signature: (FFFF)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setClearColor
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    teardown
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_RenderController_teardownNative
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    resize
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_RenderController_resize
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_render
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    hasChanges
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_RenderController_hasChanges
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setPerfInterval
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setPerfInterval
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    setModelsHaveDepth
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_setModelsHaveDepth
  (JNIEnv *, jobject , jboolean);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    addLight
 * Signature: (Lcom/mousebird/maply/DirectionalLight;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_addLight
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    replaceLights
 * Signature: ([Lcom/mousebird/maply/DirectionalLight;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_replaceLights
  (JNIEnv *, jobject, jobjectArray);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    renderToBitmapNative
 * Signature: (Landroid/graphics/Bitmap;)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_renderToBitmapNative
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_nativeInit
  (JNIEnv *, jclass);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    initialise
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_initialise__II
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    initialise
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_initialise__
  (JNIEnv *, jobject);

/*
 * Class:     com_mousebird_maply_RenderController
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mousebird_maply_RenderController_dispose
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
