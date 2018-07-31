//
//  UIButton+KCWebImage.m
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "UIButton+KCWebImage.h"
#import "KCWebImageOperation.h"
#import "_KCWebImageSetter.h"
#import "KCKitMacro.h"
#import <libkern/OSAtomic.h>
#import <objc/runtime.h>

KCSYNTH_DUMMY_CLASS(UIButton_KCWebImage)

static inline NSNumber *UIControlStateSingle(UIControlState state) {
    if (state & UIControlStateHighlighted) return @(UIControlStateHighlighted);
    if (state & UIControlStateDisabled) return @(UIControlStateDisabled);
    if (state & UIControlStateSelected) return @(UIControlStateSelected);
    return @(UIControlStateNormal);
}

static inline NSArray *UIControlStateMulti(UIControlState state) {
    NSMutableArray *array = [NSMutableArray new];
    if (state & UIControlStateHighlighted) [array addObject:@(UIControlStateHighlighted)];
    if (state & UIControlStateDisabled) [array addObject:@(UIControlStateDisabled)];
    if (state & UIControlStateSelected) [array addObject:@(UIControlStateSelected)];
    if ((state & 0xFF) == 0) [array addObject:@(UIControlStateNormal)];
    return array;
}

static int _KCWebImageSetterKey;
static int _KCWebImageBackgroundSetterKey;


@interface _KCWebImageSetterDicForButton : NSObject
- (_KCWebImageSetter *)setterForState:(NSNumber *)state;
- (_KCWebImageSetter *)lazySetterForState:(NSNumber *)state;
@end

@implementation _KCWebImageSetterDicForButton {
    NSMutableDictionary *_dic;
    OSSpinLock _lock;
}
- (instancetype)init {
    self = [super init];
    _lock = OS_SPINLOCK_INIT;
    _dic = [NSMutableDictionary new];
    return self;
}
- (_KCWebImageSetter *)setterForState:(NSNumber *)state {
    OSSpinLockLock(&_lock);
    _KCWebImageSetter *setter = _dic[state];
    OSSpinLockUnlock(&_lock);
    return setter;
    
}
- (_KCWebImageSetter *)lazySetterForState:(NSNumber *)state {
    OSSpinLockLock(&_lock);
    _KCWebImageSetter *setter = _dic[state];
    if (!setter) {
        setter = [_KCWebImageSetter new];
        _dic[state] = setter;
    }
    OSSpinLockUnlock(&_lock);
    return setter;
}
@end




@implementation UIButton (KCWebImage)




#pragma mark - image

- (void)_setImageWithURL:(NSURL *)imageURL
          forSingleState:(NSNumber *)state
             placeholder:(UIImage *)placeholder
                 options:(KCWebImageOptions)options
                 manager:(KCWebImageManager *)manager
                progress:(KCWebImageProgressBlock)progress
               transform:(KCWebImageTransformBlock)transform
              completion:(KCWebImageCompletionBlock)completion {
    if ([imageURL isKindOfClass:[NSString class]]) imageURL = [NSURL URLWithString:(id)imageURL];
    manager = manager ? manager : [KCWebImageManager sharedManager];
    
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    if (!dic) {
        dic = [_KCWebImageSetterDicForButton new];
        objc_setAssociatedObject(self, &_KCWebImageSetterKey, dic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    _KCWebImageSetter *setter = [dic lazySetterForState:state];
    int32_t sentinel = [setter cancelWithNewURL:imageURL];
    
    dispatch_async_on_main_queue(^{
        if (!imageURL) {
            if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
                [self setImage:placeholder forState:state.integerValue];
            }
            return;
        }
        
        // get the image from memory as quickly as possible
        UIImage *imageFromMemory = nil;
        if (manager.cache &&
            !(options & KCWebImageOptionUseNSURLCache) &&
            !(options & KCWebImageOptionRefreshImageCache)) {
            imageFromMemory = [manager.cache getImageForKey:[manager cacheKeyForURL:imageURL] withType:KCImageCacheTypeMemory];
        }
        if (imageFromMemory) {
            if (!(options & KCWebImageOptionAvoidSetImage)) {
                [self setImage:imageFromMemory forState:state.integerValue];
            }
            if(completion) completion(imageFromMemory, imageURL, KCWebImageFromMemoryCacheFast, KCWebImageStageFinished, nil);
            return;
        }
        
        
        if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
            [self setImage:placeholder forState:state.integerValue];
        }
        
        __weak typeof(self) _self = self;
        dispatch_async([_KCWebImageSetter setterQueue], ^{
            KCWebImageProgressBlock _progress = nil;
            if (progress) _progress = ^(NSInteger receivedSize, NSInteger expectedSize) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    progress(receivedSize, expectedSize);
                });
            };
            
            KCWebImageCompletionBlock _completion = ^(UIImage *image, NSURL *url, KCWebImageFromType from, KCWebImageStage stage, NSError *error) {
                __strong typeof(_self) self = _self;
                BOOL setImage = (stage == KCWebImageStageFinished || stage == KCWebImageStageProgress) && image && !(options & KCWebImageOptionAvoidSetImage);
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (setImage && self) {
                        [self setImage:image forState:state.integerValue];
                    }
                    if (completion) completion(image, url, from, stage, error);
                });
            };
            
            [setter setOperationWithSentinel:sentinel url:imageURL options:options manager:manager progress:_progress transform:transform completion:_completion];
        });
    });
}

- (void)_cancelImageRequestForSingleState:(NSNumber *)state {
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    _KCWebImageSetter *setter = [dic setterForState:state];
    if (setter) [setter cancel];
}

- (NSURL *)imageURLForState:(UIControlState)state {
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    _KCWebImageSetter *setter = [dic setterForState:UIControlStateSingle(state)];
    return setter.imageURL;
}

- (void)setImageWithURL:(NSURL *)imageURL forState:(UIControlState)state placeholder:(UIImage *)placeholder {
    [self setImageWithURL:imageURL
                 forState:state
              placeholder:placeholder
                  options:kNilOptions
                  manager:nil
                 progress:nil
                transform:nil
               completion:nil];
}

- (void)setImageWithURL:(NSURL *)imageURL forState:(UIControlState)state options:(KCWebImageOptions)options {
    [self setImageWithURL:imageURL
                 forState:state
              placeholder:nil
                  options:options
                  manager:nil
                 progress:nil
                transform:nil
               completion:nil];
}

- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
             completion:(KCWebImageCompletionBlock)completion {
    [self setImageWithURL:imageURL
                 forState:state
              placeholder:placeholder
                  options:options
                  manager:nil
                 progress:nil
                transform:nil
               completion:completion];
}

- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion {
    [self setImageWithURL:imageURL
                 forState:state
              placeholder:placeholder
                  options:options
                  manager:nil
                 progress:progress
                transform:transform
               completion:completion];
}

- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
                manager:(KCWebImageManager *)manager
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion {
    for (NSNumber *num in UIControlStateMulti(state)) {
        [self _setImageWithURL:imageURL
                forSingleState:num
                   placeholder:placeholder
                       options:options
                       manager:manager
                      progress:progress
                     transform:transform
                    completion:completion];
    }
}

- (void)cancelImageRequestForState:(UIControlState)state {
    for (NSNumber *num in UIControlStateMulti(state)) {
        [self _cancelImageRequestForSingleState:num];
    }
}


#pragma mark - background image

- (void)_setBackgroundImageWithURL:(NSURL *)imageURL
                    forSingleState:(NSNumber *)state
                       placeholder:(UIImage *)placeholder
                           options:(KCWebImageOptions)options
                           manager:(KCWebImageManager *)manager
                          progress:(KCWebImageProgressBlock)progress
                         transform:(KCWebImageTransformBlock)transform
                        completion:(KCWebImageCompletionBlock)completion {
    if ([imageURL isKindOfClass:[NSString class]]) imageURL = [NSURL URLWithString:(id)imageURL];
    manager = manager ? manager : [KCWebImageManager sharedManager];
    
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageBackgroundSetterKey);
    if (!dic) {
        dic = [_KCWebImageSetterDicForButton new];
        objc_setAssociatedObject(self, &_KCWebImageBackgroundSetterKey, dic, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    _KCWebImageSetter *setter = [dic lazySetterForState:state];
    int32_t sentinel = [setter cancelWithNewURL:imageURL];
    
    dispatch_async_on_main_queue(^{
        if (!imageURL) {
            if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
                [self setBackgroundImage:placeholder forState:state.integerValue];
            }
            return;
        }
        
        // get the image from memory as quickly as possible
        UIImage *imageFromMemory = nil;
        if (manager.cache &&
            !(options & KCWebImageOptionUseNSURLCache) &&
            !(options & KCWebImageOptionRefreshImageCache)) {
            imageFromMemory = [manager.cache getImageForKey:[manager cacheKeyForURL:imageURL] withType:KCImageCacheTypeMemory];
        }
        if (imageFromMemory) {
            if (!(options & KCWebImageOptionAvoidSetImage)) {
                [self setBackgroundImage:imageFromMemory forState:state.integerValue];
            }
            if(completion) completion(imageFromMemory, imageURL, KCWebImageFromMemoryCacheFast, KCWebImageStageFinished, nil);
            return;
        }
        
        
        if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
            [self setBackgroundImage:placeholder forState:state.integerValue];
        }
        
        __weak typeof(self) _self = self;
        dispatch_async([_KCWebImageSetter setterQueue], ^{
            KCWebImageProgressBlock _progress = nil;
            if (progress) _progress = ^(NSInteger receivedSize, NSInteger expectedSize) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    progress(receivedSize, expectedSize);
                });
            };
            
            KCWebImageCompletionBlock _completion = ^(UIImage *image, NSURL *url, KCWebImageFromType from, KCWebImageStage stage, NSError *error) {
                __strong typeof(_self) self = _self;
                BOOL setImage = (stage == KCWebImageStageFinished || stage == KCWebImageStageProgress) && image && !(options & KCWebImageOptionAvoidSetImage);
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (setImage && self) {
                        [self setBackgroundImage:image forState:state.integerValue];
                    }
                    if (completion) completion(image, url, from, stage, error);
                });
            };
            
            [setter setOperationWithSentinel:sentinel url:imageURL options:options manager:manager progress:_progress transform:transform completion:_completion];
        });
    });
}

- (void)_cancelBackgroundImageRequestForSingleState:(NSNumber *)state {
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageBackgroundSetterKey);
    _KCWebImageSetter *setter = [dic setterForState:state];
    if (setter) [setter cancel];
}

- (NSURL *)backgroundImageURLForState:(UIControlState)state {
    _KCWebImageSetterDicForButton *dic = objc_getAssociatedObject(self, &_KCWebImageBackgroundSetterKey);
    _KCWebImageSetter *setter = [dic setterForState:UIControlStateSingle(state)];
    return setter.imageURL;
}

- (void)setBackgroundImageWithURL:(NSURL *)imageURL forState:(UIControlState)state placeholder:(UIImage *)placeholder {
    [self setBackgroundImageWithURL:imageURL
                           forState:state
                        placeholder:placeholder
                            options:kNilOptions
                            manager:nil
                           progress:nil
                          transform:nil
                         completion:nil];
}

- (void)setBackgroundImageWithURL:(NSURL *)imageURL forState:(UIControlState)state options:(KCWebImageOptions)options {
    [self setBackgroundImageWithURL:imageURL
                           forState:state
                        placeholder:nil
                            options:options
                            manager:nil
                           progress:nil
                          transform:nil
                         completion:nil];
}

- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                       completion:(KCWebImageCompletionBlock)completion {
    [self setBackgroundImageWithURL:imageURL
                           forState:state
                        placeholder:placeholder
                            options:options
                            manager:nil
                           progress:nil
                          transform:nil
                         completion:completion];
}

- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                         progress:(KCWebImageProgressBlock)progress
                        transform:(KCWebImageTransformBlock)transform
                       completion:(KCWebImageCompletionBlock)completion {
    [self setBackgroundImageWithURL:imageURL
                           forState:state
                        placeholder:placeholder
                            options:options
                            manager:nil
                           progress:progress
                          transform:transform
                         completion:completion];
}

- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                          manager:(KCWebImageManager *)manager
                         progress:(KCWebImageProgressBlock)progress
                        transform:(KCWebImageTransformBlock)transform
                       completion:(KCWebImageCompletionBlock)completion {
    for (NSNumber *num in UIControlStateMulti(state)) {
        [self _setBackgroundImageWithURL:imageURL
                          forSingleState:num
                             placeholder:placeholder
                                 options:options
                                 manager:manager
                                progress:progress
                               transform:transform
                              completion:completion];
    }
}

- (void)cancelBackgroundImageRequestForState:(UIControlState)state {
    for (NSNumber *num in UIControlStateMulti(state)) {
        [self _cancelBackgroundImageRequestForSingleState:num];
    }
}

@end





