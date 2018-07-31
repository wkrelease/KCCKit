//
//  MKAnnotationView+KCWebImage.m
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "MKAnnotationView+KCWebImage.h"

#import "KCWebImageOperation.h"
#import "_KCWebImageSetter.h"
#import "KCKitMacro.h"
#import <objc/runtime.h>

KCSYNTH_DUMMY_CLASS(MKAnnotationView_KCWebImage)

static int _KCWebImageSetterKey;


@implementation MKAnnotationView (KCWebImage)

- (NSURL *)imageURL {
    _KCWebImageSetter *setter = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    return setter.imageURL;
}

- (void)setImageURL:(NSURL *)imageURL {
    [self setImageWithURL:imageURL
              placeholder:nil
                  options:kNilOptions
                  manager:nil
                 progress:nil
                transform:nil
               completion:nil];
}

- (void)setImageWithURL:(NSURL *)imageURL placeholder:(UIImage *)placeholder {
    [self setImageWithURL:imageURL
              placeholder:placeholder
                  options:kNilOptions
                  manager:nil
                 progress:nil
                transform:nil
               completion:nil];
}

- (void)setImageWithURL:(NSURL *)imageURL options:(KCWebImageOptions)options {
    [self setImageWithURL:imageURL
              placeholder:nil
                  options:options
                  manager:nil
                 progress:nil
                transform:nil
               completion:nil];
}

- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
             completion:(KCWebImageCompletionBlock)completion {
    [self setImageWithURL:imageURL
              placeholder:placeholder
                  options:options
                  manager:nil
                 progress:nil
                transform:nil
               completion:completion];
}

- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion {
    [self setImageWithURL:imageURL
              placeholder:placeholder
                  options:options
                  manager:nil
                 progress:progress
                transform:transform
               completion:completion];
}

- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
                manager:(KCWebImageManager *)manager
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion {
    if ([imageURL isKindOfClass:[NSString class]]) imageURL = [NSURL URLWithString:(id)imageURL];
    manager = manager ? manager : [KCWebImageManager sharedManager];
    
    _KCWebImageSetter *setter = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    if (!setter) {
        setter = [_KCWebImageSetter new];
        objc_setAssociatedObject(self, &_KCWebImageSetterKey, setter, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    int32_t sentinel = [setter cancelWithNewURL:imageURL];
    
    dispatch_async_on_main_queue(^{
        if ((options & KCWebImageOptionSetImageWithFadeAnimation) &&
            !(options & KCWebImageOptionAvoidSetImage)) {
            if (!self.highlighted) {
                [self.layer removeAnimationForKey:_KCWebImageFadeAnimationKey];
            }
        }
        if (!imageURL) {
            if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
                self.image = placeholder;
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
                self.image = imageFromMemory;
            }
            if(completion) completion(imageFromMemory, imageURL, KCWebImageFromMemoryCacheFast, KCWebImageStageFinished, nil);
            return;
        }
        
        if (!(options & KCWebImageOptionIgnorePlaceHolder)) {
            self.image = placeholder;
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
                BOOL showFade = ((options & KCWebImageOptionSetImageWithFadeAnimation) && !self.highlighted);
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (setImage && self) {
                        if (showFade) {
                            CATransition *transition = [CATransition animation];
                            transition.duration = stage == KCWebImageStageFinished ? _KCWebImageFadeTime : _KCWebImageProgressiveFadeTime;
                            transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
                            transition.type = kCATransitionFade;
                            [self.layer addAnimation:transition forKey:_KCWebImageFadeAnimationKey];
                        }
                        self.image = image;
                    }
                    if (completion) completion(image, url, from, stage, error);
                });
            };
            
            [setter setOperationWithSentinel:sentinel url:imageURL options:options manager:manager progress:_progress transform:transform completion:_completion];
        });
    });
}

- (void)cancelCurrentImageRequest {
    _KCWebImageSetter *setter = objc_getAssociatedObject(self, &_KCWebImageSetterKey);
    if (setter) [setter cancel];
}

@end

