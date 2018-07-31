//
//  KCWebImageOperation.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KCImageCache.h"
#import "KCWebImageManager.h"

@interface KCWebImageOperation : NSOperation

@property (nonatomic, strong, readonly) NSURLRequest *request;     ///< The image URL request.
@property (nonatomic, strong, readonly) NSURLResponse *response;   ///< The response for request.
@property (nonatomic, assign, readonly) KCWebImageOptions options; ///< The operation's option.
@property (nonatomic, strong, readonly) KCImageCache *cache;       ///< The image cache.
@property (nonatomic, strong, readonly) NSString *cacheKey;        ///< The image cache key.

/**
 Whether the URL connection should consult the credential storage for authenticating
 the connection. Default is YES.
 
 @discussion This is the value that is returned in the `NSURLConnectionDelegate`
 method `-connectionShouldUseCredentialStorage:`.
 */
@property (nonatomic, assign) BOOL shouldUseCredentialStorage;

/**
 The credential used for authentication challenges in `-connection:didReceiveAuthenticationChallenge:`.
 
 @discussion This will be overridden by any shared credentials that exist for the
 username or password of the request URL, if present.
 */
@property (nonatomic, strong) NSURLCredential *credential;

/**
 Creates and returns a new operation.
 
 You should call `start` to execute this operation, or you can add the operation
 to an operation queue.
 
 @param request    The Image request. This value should not be nil.
 @param options    A mask to specify options to use for this operation.
 @param cache      An image cache. Pass nil to avoid image cache.
 @param cacheKey   An image cache key. Pass nil to avoid image cache.
 @param progress   A block invoked in image fetch progress.
 The block will be invoked in background thread. Pass nil to avoid it.
 @param transform  A block invoked before image fetch finished to do additional image process.
 The block will be invoked in background thread. Pass nil to avoid it.
 @param completion A block invoked when image fetch finished or cancelled.
 The block will be invoked in background thread. Pass nil to avoid it.
 
 @return The image request opeartion, or nil if an error occurs.
 */
- (instancetype)initWithRequest:(NSURLRequest *)request
                        options:(KCWebImageOptions)options
                          cache:(KCImageCache *)cache
                       cacheKey:(NSString *)cacheKey
                       progress:(KCWebImageProgressBlock)progress
                      transform:(KCWebImageTransformBlock)transform
                     completion:(KCWebImageCompletionBlock)completion NS_DESIGNATED_INITIALIZER;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;



@end
