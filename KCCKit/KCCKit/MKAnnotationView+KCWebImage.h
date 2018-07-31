//
//  MKAnnotationView+KCWebImage.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

#import "KCWebImageManager.h"

@interface MKAnnotationView (KCWebImage)

@property (nonatomic, strong) NSURL *imageURL;

/**
 Set the view's `image` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 */
- (void)setImageWithURL:(NSURL *)imageURL placeholder:(UIImage *)placeholder;

/**
 Set the view's `image` with a specified URL.
 
 @param imageURL The image url (remote or local file path).
 @param options  The options to use when request the image.
 */
- (void)setImageWithURL:(NSURL *)imageURL options:(KCWebImageOptions)options;

/**
 Set the view's `image` with a specified URL.
 
 @param imageURL    The image url (remote or local file path).
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param completion  The block invoked (on main thread) when image request completed.
 */
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



@end
