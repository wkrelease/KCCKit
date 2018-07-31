//
//  _KCWebImageSetter.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "KCWebImageManager.h"

UIKIT_EXTERN NSString *const _KCWebImageFadeAnimationKey;
UIKIT_EXTERN const NSTimeInterval _KCWebImageFadeTime;
UIKIT_EXTERN const NSTimeInterval _KCWebImageProgressiveFadeTime;

@interface _KCWebImageSetter : NSObject

@property (nonatomic, readonly) NSURL *imageURL;

/// Create new operation for web image.
- (void)setOperationWithSentinel:(int32_t)sentinel
                             url:(NSURL *)imageURL
                         options:(KCWebImageOptions)options
                         manager:(KCWebImageManager *)manager
                        progress:(KCWebImageProgressBlock)progress
                       transform:(KCWebImageTransformBlock)transform
                      completion:(KCWebImageCompletionBlock)completion;

/// Cancel and return a sentinel value. The imageURL will be set to nil.
- (int32_t)cancel;

/// Cancel and return a sentinel value. The imageURL will be set to new value.
- (int32_t)cancelWithNewURL:(NSURL *)imageURL;

/// A queue to set operation.
+ (dispatch_queue_t)setterQueue;


@end
