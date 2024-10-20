/*
 *  VectorIterator_jni.cpp
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
#import "com_mousebird_maply_VectorIterator.h"

using namespace WhirlyKit;

// Used to store position in a set of shapes
class VectorIterator
{
public:
	VectorIterator(VectorObjectRef vecObj)
		: vecObj(vecObj)
	{
		it = vecObj->shapes.begin();
	}

	VectorObjectRef vecObj;
	ShapeSet::iterator it;
};

typedef JavaClassInfo<VectorIterator> VectorIteratorClassInfo;
template<> VectorIteratorClassInfo *VectorIteratorClassInfo::classInfoObj = NULL;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_VectorIterator_nativeInit
  (JNIEnv *env, jclass cls)
{
	VectorIteratorClassInfo::getClassInfo(env,cls);
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_VectorIterator_initialise
  (JNIEnv *env, jobject obj, jobject vecObj)
{
	try
	{
		VectorObjectRef *vec = VectorObjectClassInfo::getClassInfo()->getObject(env,vecObj);
		VectorIterator *vecIter = new VectorIterator(*vec);
		VectorIteratorClassInfo::getClassInfo()->setHandle(env,obj,vecIter);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in VectorIterator::initialise()");
	}
}

static std::mutex disposeMutex;

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_VectorIterator_dispose
  (JNIEnv *env, jobject obj)
{
	try
	{
		VectorIteratorClassInfo *classInfo = VectorIteratorClassInfo::getClassInfo();
        {
            std::lock_guard<std::mutex> lock(disposeMutex);
            VectorIterator *vecIter = classInfo->getObject(env,obj);
            if (!vecIter)
                return;
            delete vecIter;

            classInfo->clearHandle(env,obj);
        }
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in VectorIterator::dispose()");
	}
}

extern "C"
JNIEXPORT jboolean JNICALL Java_com_mousebird_maply_VectorIterator_hasNext
  (JNIEnv *env, jobject obj)
{
	try
	{
		VectorIteratorClassInfo *classInfo = VectorIteratorClassInfo::getClassInfo();
		VectorIterator *vecIter = classInfo->getObject(env,obj);
		if (!vecIter)
			return false;

		return vecIter->it != vecIter->vecObj->shapes.end();
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in VectorIterator::hasNext()");
	}
    
    return false;
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_VectorIterator_next
  (JNIEnv *env, jobject obj)
{
	try
	{
		VectorIteratorClassInfo *classInfo = VectorIteratorClassInfo::getClassInfo();
		VectorIterator *vecIter = classInfo->getObject(env,obj);
		if (!vecIter)
			return NULL;

		if (vecIter->it == vecIter->vecObj->shapes.end())
			return NULL;
		VectorObjectRef vec(new VectorObject());
		vec->shapes.insert(*(vecIter->it));
		jobject retObj = MakeVectorObject(env,vec);
		vecIter->it++;
		return retObj;
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in VectorIterator::next()");
	}
    
    return NULL;
}

extern "C"
JNIEXPORT void JNICALL Java_com_mousebird_maply_VectorIterator_remove
  (JNIEnv *env, jobject obj)
{
	// Note: Not bothering to implement
}
