//
//  UIScreen+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIScreen (KCAdd)

+ (CGFloat)screenScale;

- (CGRect)currentBounds NS_EXTENSION_UNAVAILABLE_IOS("");

- (CGRect)boundsForOrientation:(UIInterfaceOrientation)orientation;

@property (nonatomic, readonly) CGSize sizeInPixel;

@property (nonatomic, readonly) CGFloat pixelsPerInch;


@end
