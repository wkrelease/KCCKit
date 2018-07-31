//
//  KCAsyncLayer.h
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

@import UIKit;

@class KCAsyncLayerDisplayTask;

@interface KCAsyncLayer : CALayer

@property BOOL displaysAsynchronously;

@end

@protocol KCAsyncLayerDelegate <NSObject>

@required

- (KCAsyncLayerDisplayTask *)newAsyncDisplayTask;

@end


@interface KCAsyncLayerDisplayTask : NSObject

@property (nonatomic, copy) void (^willDisplay)(CALayer *layer);

@property (nonatomic, copy) void (^display)(CGContextRef context, CGSize size, BOOL(^isCancelled)(void));

@property (nonatomic, copy) void (^didDisplay)(CALayer *layer, BOOL finished);


@end





