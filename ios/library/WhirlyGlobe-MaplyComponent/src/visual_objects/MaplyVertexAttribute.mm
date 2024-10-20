/*  MaplyVertexAttribute.mm
 *  WhirlyGlobe-MaplyComponent
 *
 *  Created by Steve Gifford on 11/29/13.
 *  Copyright 2011-2023 mousebird consulting
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
 */

#import "MaplyVertexAttribute_private.h"
#import "UIColor+Stuff.h"

using namespace WhirlyKit;

@implementation MaplyVertexAttribute

- (instancetype)initWithName:(NSString *)name slot:(int)slot float:(float)val
{
    if (!(self = [super init]))
    {
        return nil;
    }
    attr.type = BDFloatType;
    attr.slot = slot;
    attr.nameID = StringIndexer::getStringID([name cStringUsingEncoding:NSASCIIStringEncoding]);
    attr.data.floatVal = val;
    
    return self;
}

- (instancetype)initWithName:(NSString *)name slot:(int)slot floatX:(float)x y:(float)y
{
    if (!(self = [super init]))
    {
        return nil;
    }
    attr.type = BDFloat2Type;
    attr.slot = slot;
    attr.nameID = StringIndexer::getStringID([name cStringUsingEncoding:NSASCIIStringEncoding]);
    attr.data.vec2[0] = x;
    attr.data.vec2[1] = y;
    
    return self;
}

- (instancetype)initWithName:(NSString *)name slot:(int)slot floatX:(float)x y:(float)y z:(float)z
{
    if (!(self = [super init]))
    {
        return nil;
    }
    attr.type = BDFloat3Type;
    attr.slot = slot;
    attr.nameID = StringIndexer::getStringID([name cStringUsingEncoding:NSASCIIStringEncoding]);
    attr.data.vec3[0] = x;
    attr.data.vec3[1] = y;
    attr.data.vec3[2] = z;
    
    return self;
}

- (instancetype)initWithName:(NSString *)name slot:(int)slot color:(UIColor *)color
{
    if (!(self = [super init]))
    {
        return nil;
    }
    attr.type = BDChar4Type;
    attr.slot = slot;
    attr.nameID = StringIndexer::getStringID([name cStringUsingEncoding:NSASCIIStringEncoding]);
    WhirlyKit::RGBAColor rgbaColor = [color asRGBAColor];
    attr.data.color[0] = rgbaColor.r;
    attr.data.color[1] = rgbaColor.g;
    attr.data.color[2] = rgbaColor.b;
    attr.data.color[3] = rgbaColor.a;
    
    return self;
}

- (instancetype)initWithName:(NSString *)name slot:(int)slot int:(int)val
{
    if (!(self = [super init]))
    {
        return nil;
    }
    attr.type = BDIntType;
    attr.slot = slot;
    attr.nameID = StringIndexer::getStringID([name cStringUsingEncoding:NSASCIIStringEncoding]);
    attr.data.intVal = val;
    
    return self;
}

@end
