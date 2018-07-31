//
//  UIButton+KCWebImage.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCWebImageManager.h"

@interface UIButton (KCWebImage)

- (NSURL *)imageURLForState:(UIControlState)state;

/**
 Set the button's image with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 */
- (void)setImageWithURL:(NSURL *)imageURL forState:(UIControlState)state placeholder:(UIImage *)placeholder;

/**
 Set the button's image with a specified URL for the specified state.
 
 @param imageURL The image url (remote or local file path).
 @param state    The state that uses the specified image.
 @param options  The options to use when request the image.
 */
- (void)setImageWithURL:(NSURL *)imageURL forState:(UIControlState)state options:(KCWebImageOptions)options;

/**
 Set the button's image with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
             completion:(KCWebImageCompletionBlock)completion;

/**
 Set the button's image with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion;

/**
 Set the button's image with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param manager     The manager to create image request operation.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setImageWithURL:(NSURL *)imageURL
               forState:(UIControlState)state
            placeholder:(UIImage *)placeholder
                options:(KCWebImageOptions)options
                manager:(KCWebImageManager *)manager
               progress:(KCWebImageProgressBlock)progress
              transform:(KCWebImageTransformBlock)transform
             completion:(KCWebImageCompletionBlock)completion;

/**
 Cancel the current image request for a specified state.
 @param state The state that uses the specified image.
 */
- (void)cancelImageRequestForState:(UIControlState)state;



#pragma mark - background image

/**
 Current backgroundImage URL for the specified state.
 @return The image URL, or nil.
 */
- (NSURL *)backgroundImageURLForState:(UIControlState)state;

/**
 Set the button's backgroundImage with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 */
- (void)setBackgroundImageWithURL:(NSURL *)imageURL forState:(UIControlState)state placeholder:(UIImage *)placeholder;

/**
 Set the button's backgroundImage with a specified URL for the specified state.
 
 @param imageURL The image url (remote or local file path).
 @param state    The state that uses the specified image.
 @param options  The options to use when request the image.
 */
- (void)setBackgroundImageWithURL:(NSURL *)imageURL forState:(UIControlState)state options:(KCWebImageOptions)options;

/**
 Set the button's backgroundImage with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                       completion:(KCWebImageCompletionBlock)completion;

/**
 Set the button's backgroundImage with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                         progress:(KCWebImageProgressBlock)progress
                        transform:(KCWebImageTransformBlock)transform
                       completion:(KCWebImageCompletionBlock)completion;

/**
 Set the button's backgroundImage with a specified URL for the specified state.
 
 @param imageURL    The image url (remote or local file path).
 @param state       The state that uses the specified image.
 @param placeholder The image to be set initially, until the image request finishes.
 @param options     The options to use when request the image.
 @param manager     The manager to create image request operation.
 @param progress    The block invoked (on main thread) during image request.
 @param transform   The block invoked (on background thread) to do additional image process.
 @param completion  The block invoked (on main thread) when image request completed.
 */
- (void)setBackgroundImageWithURL:(NSURL *)imageURL
                         forState:(UIControlState)state
                      placeholder:(UIImage *)placeholder
                          options:(KCWebImageOptions)options
                          manager:(KCWebImageManager *)manager
                         progress:(KCWebImageProgressBlock)progress
                        transform:(KCWebImageTransformBlock)transform
                       completion:(KCWebImageCompletionBlock)completion;

/**
 Cancel the current backgroundImage request for a specified state.
 @param state The state that uses the specified image.
 */
- (void)cancelBackgroundImageRequestForState:(UIControlState)state;


@end
