//
//  _KCWebImageSetter.m
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "_KCWebImageSetter.h"
#import "KCWebImageOperation.h"
#import <libkern/OSAtomic.h>

NSString *const _KCWebImageFadeAnimationKey = @"KCWebImageFade";
const NSTimeInterval _KCWebImageFadeTime = 0.2;
const NSTimeInterval _KCWebImageProgressiveFadeTime = 0.4;


@implementation _KCWebImageSetter {
    OSSpinLock _lock;
    NSURL *_imageURL;
    NSOperation *_operation;
    int32_t _sentinel;
}

- (instancetype)init {
    self = [super init];
    _lock = OS_SPINLOCK_INIT;
    return self;
}

- (NSURL *)imageURL {
    OSSpinLockLock(&_lock);
    NSURL *imageURL = _imageURL;
    OSSpinLockUnlock(&_lock);
    return imageURL;
}

- (void)dealloc {
    OSAtomicIncrement32(&_sentinel);
    [_operation cancel];
}

- (void)setOperationWithSentinel:(int32_t)sentinel
                             url:(NSURL *)imageURL
                         options:(KCWebImageOptions)options
                         manager:(KCWebImageManager *)manager
                        progress:(KCWebImageProgressBlock)progress
                       transform:(KCWebImageTransformBlock)transform
                      completion:(KCWebImageCompletionBlock)completion {
    if (sentinel != _sentinel) {
        if (completion) completion(nil, imageURL, KCWebImageFromNone, KCWebImageStageCancelled, nil);
        return;
    }
    
    NSOperation *operation = [manager requestImageWithURL:imageURL options:options progress:progress transform:transform completion:completion];
    if (!operation && completion) {
        NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : @"KCWebImageOperation create failed." };
        completion(nil, imageURL, KCWebImageFromNone, KCWebImageStageFinished, [NSError errorWithDomain:@"com.ibireme.kckit.webimage" code:-1 userInfo:userInfo]);
    }
    
    OSSpinLockLock(&_lock);
    if (sentinel == _sentinel) {
        if (_operation) [_operation cancel];
        _operation = operation;
        OSAtomicIncrement32(&_sentinel);
    } else {
        [operation cancel];
    }
    OSSpinLockUnlock(&_lock);
}

- (int32_t)cancel {
    return [self cancelWithNewURL:nil];
}

- (int32_t)cancelWithNewURL:(NSURL *)imageURL {
    int32_t sentinel;
    OSSpinLockLock(&_lock);
    if (_operation) {
        [_operation cancel];
        _operation = nil;
    }
    _imageURL = imageURL;
    sentinel = OSAtomicIncrement32(&_sentinel);
    OSSpinLockUnlock(&_lock);
    return sentinel;
}

+ (dispatch_queue_t)setterQueue {
    static dispatch_queue_t queue;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        queue = dispatch_queue_create("com.ibireme.kckit.webimage.setter", DISPATCH_QUEUE_SERIAL);
        dispatch_set_target_queue(queue, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0));
    });
    return queue;
}

@end
