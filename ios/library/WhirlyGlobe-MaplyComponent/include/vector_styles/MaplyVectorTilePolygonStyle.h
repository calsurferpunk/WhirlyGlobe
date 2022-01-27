/*  MaplyVectorPolygonStyle.h
 *  WhirlyGlobe-MaplyComponent
 *
 *  Created by Steve Gifford on 1/3/14.
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
 */

#import <WhirlyGlobeMaplyComponent/MaplyVectorStyle.h>
#import <WhirlyGlobeMaplyComponent/MaplyVectorTileStyle.h>

/** 
    Implementation of the polygon style symbolizer for Maply Vector Tiles.
 */
@interface MaplyVectorTileStylePolygon : MaplyVectorTileStyle

- (instancetype)initWithStyleEntry:(NSDictionary *)styleEntry settings:(MaplyVectorStyleSettings *)settings viewC:(NSObject<MaplyRenderControllerProtocol> *)viewC;

@end
