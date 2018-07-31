//
//  KCFrameImage.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCAnimatedImageView.h"

@interface KCFrameImage : UIImage<KCAnimatedImage>

- (instancetype)initWithImagePaths:(NSArray *)paths oneFrameDuration:(NSTimeInterval)oneFrameDuration loopCount:(NSUInteger)loopCount;
- (instancetype)initWithImagePaths:(NSArray *)paths frameDurations:(NSArray *)frameDurations loopCount:(NSUInteger)loopCount;
- (instancetype)initWithImageDataArray:(NSArray *)dataArray oneFrameDuration:(NSTimeInterval)oneFrameDuration loopCount:(NSUInteger)loopCount;
- (instancetype)initWithImageDataArray:(NSArray *)dataArray frameDurations:(NSArray *)frameDurations loopCount:(NSUInteger)loopCount;


@end
