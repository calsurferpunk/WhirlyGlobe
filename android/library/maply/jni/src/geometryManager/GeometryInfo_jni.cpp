/*
 *  GeometryInfo_jni.cpp
 *  WhirlyGlobeLib
 *
 *  Created by sjg
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
#import "GeometryManager_jni.h"
#import "com_mousebird_maply_GeometryInfo.h"

using namespace WhirlyKit;
using namespace Maply;

template<> GeometryInfoClassInfo *GeometryInfoClassInfo::classInfoObj = NULL;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_GeometryInfo_nativeInit
(JNIEnv *env, jclass cls)
{
    GeometryInfoClassInfo::getClassInfo(env, cls);
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_GeometryInfo_initialise
(JNIEnv *env, jobject obj)
{
    try
    {
        GeometryInfoRef *geomInst = new GeometryInfoRef(new GeometryInfo());
        GeometryInfoClassInfo::getClassInfo()->setHandle(env,obj,geomInst);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in GeometryInfo::initialise()");
    }
}

static std::mutex disposeMutex;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_GeometryInfo_dispose
(JNIEnv *env, jobject obj)
{
    try
    {
        GeometryInfoClassInfo *classInfo = GeometryInfoClassInfo::getClassInfo();
        classInfo->clearHandle(env, obj);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in GeometryInfo::dispose()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_GeometryInfo_setColor
(JNIEnv *env, jobject obj, jfloat r, jfloat g, jfloat b, jfloat a)
{
    try
    {
        GeometryInfoClassInfo *classInfo = GeometryInfoClassInfo::getClassInfo();
        GeometryInfoRef *info = classInfo->getObject(env,obj);
        if (!info)
            return;

        (*info)->colorOverride = true;
        (*info)->color = RGBAColor(r,g,b,a);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in GeometryInstance::setColor()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_GeometryInfo_setPointSize
(JNIEnv *env, jobject obj, jfloat pointSize)
{
    try
    {
        GeometryInfoClassInfo *classInfo = GeometryInfoClassInfo::getClassInfo();
        GeometryInfoRef *info = classInfo->getObject(env,obj);
        if (!info)
            return;

        (*info)->pointSize = pointSize;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in GeometryInstance::setPointSize()");
    }
}
