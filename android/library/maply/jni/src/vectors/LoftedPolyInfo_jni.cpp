/*
 *  VectorInfo_jni.cpp
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 6/2/14.
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

#import "Vectors_jni.h"
#import "Geometry_jni.h"
#import "com_mousebird_maply_LoftedPolyInfo.h"

using namespace Eigen;
using namespace WhirlyKit;

template<> LoftedPolyInfoClassInfo *LoftedPolyInfoClassInfo::classInfoObj = NULL;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_nativeInit
        (JNIEnv *env, jclass cls)
{
    LoftedPolyInfoClassInfo::getClassInfo(env,cls);
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_initialise
        (JNIEnv *env, jobject obj)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = new LoftedPolyInfoRef(new LoftedPolyInfo());
        LoftedPolyInfoClassInfo::getClassInfo()->setHandle(env,obj,loftInfo);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::initialise()");
    }
}

static std::mutex disposeMutex;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_dispose
        (JNIEnv *env, jobject obj)
{
    try
    {
        LoftedPolyInfoClassInfo *classInfo = LoftedPolyInfoClassInfo::getClassInfo();
        {
            std::lock_guard<std::mutex> lock(disposeMutex);
            LoftedPolyInfoRef *loftInfo = classInfo->getObject(env,obj);
            if (!loftInfo)
                return;
            delete loftInfo;

            classInfo->clearHandle(env,obj);
        }
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::dispose()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setHeight
        (JNIEnv *env, jobject obj, jdouble height)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->height = height;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setHeight()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setBase
        (JNIEnv *env, jobject obj, jdouble base)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->base = base;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setBase()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setTop
        (JNIEnv *env, jobject obj, jboolean top)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->top = top;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setTop()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setSide
        (JNIEnv *env, jobject obj, jboolean side)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->side = side;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setSide()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutline
        (JNIEnv *env, jobject obj, jboolean outline)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outline = outline;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutline()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutlineSide
        (JNIEnv *env, jobject obj, jboolean outlineSide)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outlineSide = outlineSide;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutlineSide()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutlineBottom
        (JNIEnv *env, jobject obj, jboolean outlineBottom)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outlineBottom = outlineBottom;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutlineBottom()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutlineDrawPriority
        (JNIEnv *env, jobject obj, jint outlineDrawPriority)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outlineDrawPriority = outlineDrawPriority;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutlineDrawPriority()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setColor
        (JNIEnv *env, jobject obj, jfloat r, jfloat g, jfloat b, jfloat a)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->color = RGBAColor(r*255.0,g*255.0,b*255.0,a*255.0);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setColor()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutlineColor
        (JNIEnv *env, jobject obj, jfloat r, jfloat g, jfloat b, jfloat a)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outlineColor = RGBAColor(r*255.0,g*255.0,b*255.0,a*255.0);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutlineColor()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setOutlineWidth
        (JNIEnv *env, jobject obj, jdouble width)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->outlineWidth = width;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setOutlineWidth()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setCenter
        (JNIEnv *env, jobject obj, jobject centerObj)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        Point2d *center = Point2dClassInfo::getClassInfo()->getObject(env,centerObj);
        if (!loftInfo || !center)
            return;
        (*loftInfo)->center = *center;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setCenter()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setUseCenter
        (JNIEnv *env, jobject obj, jboolean useCenter)
{
    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->centered = useCenter;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setUseCenter()");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_LoftedPolyInfo_setGridSize
        (JNIEnv *env, jobject obj, jdouble gridSize)
{    try
    {
        LoftedPolyInfoRef *loftInfo = LoftedPolyInfoClassInfo::getClassInfo()->getObject(env,obj);
        if (!loftInfo)
            return;
        (*loftInfo)->gridSize = gridSize;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in LoftedPolyInfo::setGridSize()");
    }
}
