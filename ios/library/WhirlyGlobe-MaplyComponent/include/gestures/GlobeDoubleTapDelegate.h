/*  GlobeDoubleTapDelegate.h
 *
 *  Created by Steve Gifford on 2/7/14.
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

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WhirlyGlobeDoubleTapDelegate : NSObject<UIGestureRecognizerDelegate>

@property (nonatomic,weak) UIGestureRecognizer *gestureRecognizer;

// How much we zoom in by
@property (nonatomic) float zoomTapFactor;

// How long the zoom animation takes
@property (nonatomic) float zoomAnimationDuration;

/// Zoom limits
@property (nonatomic) float minZoom,maxZoom;

/// Set this to let other gesture recognizers run all the time
@property (nonatomic) bool approveAllGestures;

@end
