//
//  KCWebImageManager.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "KCImageCache.h"

@class KCWebImageOperation;

/// The options to control image operation.
typedef NS_OPTIONS(NSUInteger, KCWebImageOptions) {
    
    /// Show network activity on status bar when download image.
    KCWebImageOptionShowNetworkActivity = 1 << 0,
    
    /// Display progressive/interlaced/baseline image during download (same as web browser).
    KCWebImageOptionProgressive = 1 << 1,
    
    /// Display blurred progressive JPEG or interlaced PNG image during download.
    /// This will ignore baseline image for better user experience.
    KCWebImageOptionProgressiveBlur = 1 << 2,
    
    /// Use NSURLCache instead of YYImageCache.
    KCWebImageOptionUseNSURLCache = 1 << 3,
    
    /// Allows untrusted SSL ceriticates.
    KCWebImageOptionAllowInvalidSSLCertificates = 1 << 4,
    
    /// Allows background task to download image when app is in background.
    KCWebImageOptionAllowBackgroundTask = 1 << 5,
    
    /// Handles cookies stored in NSHTTPCookieStore.
    KCWebImageOptionHandleCookies = 1 << 6,
    
    /// Load the image from remote and refresh the image cache.
    KCWebImageOptionRefreshImageCache = 1 << 7,
    
    /// Do not load image from/to disk cache.
    KCWebImageOptionIgnoreDiskCache = 1 << 8,
    
    /// Do not change the view's image before set a new URL to it.
    KCWebImageOptionIgnorePlaceHolder = 1 << 9,
    
    /// Ignore image decoding.
    /// This may used for image downloading without display.
    KCWebImageOptionIgnoreImageDecoding = 1 << 10,
    
    /// Ignore multi-frame image decoding.
    /// This will handle the GIF/APNG/WebP/ICO image as single frame image.
    KCWebImageOptionIgnoreAnimatedImage = 1 << 11,
    
    /// Set the image to view with a fade animation.
    /// This will add a "fade" animation on image view's layer for better user experience.
    KCWebImageOptionSetImageWithFadeAnimation = 1 << 12,
    
    /// Do not set the image to the view when image fetch complete.
    /// You may set the image manually.
    KCWebImageOptionAvoidSetImage = 1 << 13,
    
    /// This flag will add the URL to a blacklist (in memory) when the URL fail to be downloaded,
    /// so the library won't keep trying.
    KCWebImageOptionIgnoreFailedURL = 1 << 14,
};

/// Indicated where the image came from.
typedef NS_ENUM(NSUInteger, KCWebImageFromType) {
    
    /// No value.
    KCWebImageFromNone = 0,
    
    /// Fetched from memory cache immediately.
    /// If you called "setImageWithURL:..." and the image is already in memory,
    /// then you will get this value at the same call.
    KCWebImageFromMemoryCacheFast,
    
    /// Fetched from memory cache.
    KCWebImageFromMemoryCache,
    
    /// Fetched from disk cache.
    KCWebImageFromDiskCache,
    
    /// Fetched from remote (web or file path).
    KCWebImageFromRemote,
};

/// Indicated image fetch complete stage.
typedef NS_ENUM(NSInteger, KCWebImageStage) {
    
    /// Incomplete, progressive image.
    KCWebImageStageProgress  = -1,
    
    /// Cancelled.
    KCWebImageStageCancelled = 0,
    
    /// Finished (succeed or failed).
    KCWebImageStageFinished  = 1,
};


/**
 The block invoked in remote image fetch progress.
 
 @param receivedSize Current received size in bytes.
 @param expectedSize Expected total size in bytes (-1 means unknown).
 */
typedef void(^KCWebImageProgressBlock)(NSInteger receivedSize, NSInteger expectedSize);

/**
 The block invoked before remote image fetch finished to do additional image process.
 
 @discussion This block will be invoked before `KCWebImageCompletionBlock` to give
 you a chance to do additional image process (such as resize or crop). If there's
 no need to transform the image, just return the `image` parameter.
 
 @example You can clip the image, blur it and add rounded corners with these code:
 ^(UIImage *image, NSURL *url) {
 // Maybe you need to create an @autoreleasepool to limit memory cost.
 image = [image imageByResizeToSize:CGSizeMake(100, 100) contentMode:UIViewContentModeScaleAspectFill];
 image = [image imageByBlurRadius:20 tintColor:nil tintMode:kCGBlendModeNormal saturation:1.2 maskImage:nil];
 image = [image imageByRoundCornerRadius:5];
 return image;
 }
 
 @param image The image fetched from url.
 @param url   The image url (remote or local file path).
 @return The transformed image.
 */
typedef UIImage *(^KCWebImageTransformBlock)(UIImage *image, NSURL *url);

/**
 The block invoked when image fetch finished or cancelled.
 
 @param image       The image.
 @param url         The image url (remote or local file path).
 @param from        Where the image came from.
 @param error       Error during image fetching.
 @param finished    If the operation is cancelled, this value is NO, otherwise YES.
 */
typedef void (^KCWebImageCompletionBlock)(UIImage *image, NSURL *url, KCWebImageFromType from, KCWebImageStage stage, NSError *error);


@interface KCWebImageManager : NSObject

+ (instancetype)sharedManager;
- (instancetype)initWithCache:(KCImageCache *)cache queue:(NSOperationQueue *)queue NS_DESIGNATED_INITIALIZER;
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

- (KCWebImageOperation *)requestImageWithURL:(NSURL *)url
                                     options:(KCWebImageOptions)options
                                    progress:(KCWebImageProgressBlock)progress
                                   transform:(KCWebImageTransformBlock)transform
                                  completion:(KCWebImageCompletionBlock)completion;


/**
 The image cache used by image operation.
 You can set it to nil to avoid image cache.
 */
@property (nonatomic, strong) KCImageCache *cache;

/**
 The operation queue on which image operations are scheduled and run.
 You can set it to nil to make the new operation start immediately without queue.
 
 You can use this queue to control maximum number of concurrent operations, to obtain
 the status of the current operations, or to cancel all operations in this manager.
 */
@property (nonatomic, strong) NSOperationQueue *queue;

/**
 The shared transform block to process image. Default is nil.
 
 When called `requestImageWithURL:options:progress:transform:completion` and
 the `transform` is nil, this block will be used.
 */
@property (nonatomic, copy) KCWebImageTransformBlock sharedTransformBlock;

/**
 The image request timeout interval in seconds. Default is 15.
 */
@property (nonatomic, assign) NSTimeInterval timeout;

/**
 The username used by NSURLCredential, default is nil.
 */
@property (nonatomic, strong) NSString *username;

/**
 The password used by NSURLCredential, default is nil.
 */
@property (nonatomic, strong) NSString *password;

/**
 The image HTTP request header. Default is "Accept:image/webp,image/\*;q=0.8".
 */
@property (nonatomic, copy) NSDictionary *headers;

/**
 A block which will be invoked for each image HTTP request to do additional
 HTTP header process. Default is nil.
 
 Use this block to add or remove HTTP header field for a specified URL.
 */
@property (nonatomic, copy) NSDictionary *(^headersFilter)(NSURL *url, NSDictionary *header);

/**
 A block which will be invoked for each image operation. Default is nil.
 
 Use this block to provide a custom image cache key for a specified URL.
 */
@property (nonatomic, copy) NSString *(^cacheKeyFilter)(NSURL *url);

/**
 Returns the HTTP headers for a specified URL.
 
 @param url A specified URL.
 @return HTTP headers.
 */
- (NSDictionary *)headersForURL:(NSURL *)url;

/**
 Returns the cache key for a specified URL.
 
 @param url A specified URL
 @return Cache key used in YYImageCache.
 */
- (NSString *)cacheKeyForURL:(NSURL *)url;



@end
