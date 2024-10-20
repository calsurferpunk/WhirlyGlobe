/*
 *  com_mousebird_maply_DirectionalLight.cpp
 *  WhirlyGlobeLib
 *
 *  Created by jmnavarro
 *  Copyright 2011-2022 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import "Scene_jni.h"
#import "Geometry_jni.h"
#include "com_mousebird_maply_DirectionalLight.h"

using namespace Eigen;
using namespace WhirlyKit;

template<> DirectionalLightClassInfo *DirectionalLightClassInfo::classInfoObj = NULL;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_nativeInit
(JNIEnv *env, jclass cls)
{
    DirectionalLightClassInfo::getClassInfo(env,cls);
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_initialise
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = new DirectionalLight();
        classInfo->setHandle(env, obj, inst);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::initialise()");
    }
}

static std::mutex disposeMutex;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_dispose
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        {
            std::lock_guard<std::mutex> lock(disposeMutex);
            DirectionalLight *inst = classInfo->getObject(env, obj);
            if (!inst)
                return;

            delete inst;
            classInfo->clearHandle(env, obj);
        }
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::dispose()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_setPos
(JNIEnv *env, jobject obj, jobject objPos)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        Point3d *pos = Point3dClassInfo::getClassInfo()->getObject(env, objPos);
        if (!inst || !pos)
            return;

        inst->setPos(pos->cast<float>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::setPos()");
    }
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_DirectionalLight_getPos
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return NULL;
        
        return MakePoint3d(env,inst->getPos().cast<double>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::getPos()");
    }
    
    return NULL;
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_setViewDependent
(JNIEnv *env, jobject obj, jboolean viewDependent)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return;

        inst->setViewDependent(viewDependent);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::setViewDependent()");
    }
}

extern "C"
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_DirectionalLight_getViewDependent
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return false;

        return inst->getViewDependent();
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::getViewDependent()");
    }
    
    return false;
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_setAmbient
(JNIEnv *env, jobject obj, jobject ambientObj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        Point4d *ambient = Point4dClassInfo::getClassInfo()->getObject(env, ambientObj);
        if (!inst || !ambient)
            return;

        inst->setAmbient(ambient->cast<float>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::setAmbient()");
    }
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_DirectionalLight_getAmbient
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return NULL;

        return MakePoint4d(env, inst->getAmbient().cast<double>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::getAmbient()");
    }
    
    return NULL;
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_setDiffuse
(JNIEnv *env, jobject obj, jobject objDiffuse)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        Point4d *diffuse = Point4dClassInfo::getClassInfo()->getObject(env, objDiffuse);
        if (!inst || !diffuse)
            return;

        inst->setDiffuse(diffuse->cast<float>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::setDiffuse()");
    }
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_DirectionalLight_getDifusse
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return NULL;
        
        return MakePoint4d(env, inst->getDiffuse().cast<double>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::getDiffuse()");
    }

    return NULL;
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_DirectionalLight_setSpecular
(JNIEnv *env, jobject obj, jobject objSpecular)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        Point4d *specular = Point4dClassInfo::getClassInfo()->getObject(env, objSpecular);
        if (!inst || !specular)
            return;

        inst->setSpecular(specular->cast<float>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::setSpecular()");
    }
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_DirectionalLight_getSpecular
(JNIEnv *env, jobject obj)
{
    try
    {
        DirectionalLightClassInfo *classInfo = DirectionalLightClassInfo::getClassInfo();
        DirectionalLight *inst = classInfo->getObject(env, obj);
        if (!inst)
            return NULL;
        
        return MakePoint4d(env, inst->getSpecular().cast<double>());
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in DirectionalLight::getSpecular()");
    }

    return NULL;
}
