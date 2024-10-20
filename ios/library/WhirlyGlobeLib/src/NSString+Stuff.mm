/*  NSString+Stuff.mm
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 5/11/11.
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

#import "NSString+Stuff.h"

@implementation NSString(Stuff)

- (nullable const char *)cStringUsingEncoding:(NSStringEncoding)encoding
                                  withDefault:(const char*)def
{
    const char * const tmpStr = [self cStringUsingEncoding:NSUTF8StringEncoding];
    return tmpStr ? tmpStr : def;
}

- (std::string) asStdString
{
    return [self cStringUsingEncoding:NSUTF8StringEncoding withDefault:""];
}

// Courtesy: http://stackoverflow.com/questions/3552195/how-to-convert-stdstring-to-nsstring
+ (NSString*) stringWithwstring:(const std::wstring&)ws
{
    const char* data = (char*)ws.data();
    const unsigned int size = (unsigned int)(ws.size() * sizeof(wchar_t));
    const auto enc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingUTF32LE);
    return [[NSString alloc] initWithBytes:data length:size encoding:enc];
}

@end

// A function we can call to force the linker to bring in categories
void NSStringDummyFunc()
{
}
