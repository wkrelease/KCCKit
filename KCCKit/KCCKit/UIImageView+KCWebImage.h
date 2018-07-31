//
//  UIImageView+KCWebImage.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCWebImageManager.h"

@interface UIImageView (KCWebImage)

@property (nonatomic, strong) NSURL *imageURL;

- (void)setImageWithURL:(NSURL *)imageURL placeholder:(UIImage *)placeholder;

- (void)setImageWithURL:(NSURL *)imageURL options:(KCWebImageOptions)options;

- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
             completion:(KCWebImageCompletionBlock)completion;


/**
 Set the view's `image` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion;

/**
 Set the view's `image` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder he image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param manager     The manager to create image request operation.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setImageWithURL:(NSURL *)imageURL
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
                manager:(KCWebImageManager *)manager
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion;

/**
 Cancel the current image request.
 */
- (void)cancelCurrentImageRequest;



#pragma mark - highlight image

/**
 Current highlighted image URL.
 
 @discussion Set a new value to this property will cancel the previous request
 operation and create a new request operation to fetch image. Set nil to clear
 the highlighted image and image URL.
 */
@property (nonatomic, strong) NSURL *highlightedImageURL;

/**
 Set the view's `highlightedImage` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 */
- (void)setHighlightedImageWithURL:(NSURL *)imageURL placeholder:(UIImage *)placeholder;

/**
 Set the view's `highlightedImage` with a specified URL.
 
 @param imageURL The image url (remote or local file path).
 @param options  The options to use when request the image.
 */
- (void)setHighlightedImageWithURL:(NSURL *)imageURL options:(KCWebImageOptions)options;

/**
 Set the view's `highlightedImage` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setHighlightedImageWithURL:(NSURL *)imageURL
                       placeholder:(UIImage *)placeholder
                           options:(KCWebImageOptions)options
                        completion:(KCWebImageCompletionBlock)completion;

/**
 Set the view's `highlightedImage` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setHighlightedImageWithURL:(NSURL *)imageURL
                       placeholder:(UIImage *)placeholder
                           options:(KCWebImageOptions)options
                          progress:(KCWebImageProgressBlock)progress
                         transform:(KCWebImageTransformBlock)transform
                        completion:(KCWebImageCompletionBlock)completion;

/**
 Set the view's `highlightedImage` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder he image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param manager     The manager to create image request operation.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setHighlightedImageWithURL:(NSURL *)imageURL
                       placeholder:(UIImage *)placeholder
                           options:(KCWebImageOptions)options
                           manager:(KCWebImageManager *)manager
                          progress:(KCWebImageProgressBlock)progress
                         transform:(KCWebImageTransformBlock)transform
                        completion:(KCWebImageCompletionBlock)completion;

/**
 Cancel the current highlighed image request.
 */
- (void)cancelCurrentHighlightedImageRequest;



@end
