//
//  KCWebImageManager.m
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "KCWebImageManager.h"

#import "KCImageCache.h"

#import "KCWebImageOperation.h"

@implementation KCWebImageManager

+ (instancetype)sharedManager {
    static KCWebImageManager *manager;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        KCImageCache *cache = [KCImageCache sharedCache];
        NSOperationQueue *queue = [NSOperationQueue new];
        if ([queue respondsToSelector:@selector(setQualityOfService:)]) {
            queue.qualityOfService = NSQualityOfServiceBackground;
        }
        manager = [[self alloc] initWithCache:cache queue:queue];
    });
    return manager;
}

- (instancetype)init {
    @throw [NSException exceptionWithName:@"KCWebImageManager init error" reason:@"Use the designated initializer to init." userInfo:nil];
    return [self initWithCache:nil queue:nil];
}

- (instancetype)initWithCache:(KCImageCache *)cache queue:(NSOperationQueue *)queue{
    self = [super init];
    if (!self) return nil;
    _cache = cache;
    _queue = queue;
    _timeout = 15.0;
    _headers = @{ @"Accept" : @"image/webp,image/*;q=0.8" };
    return self;
}

- (KCWebImageOperation *)requestImageWithURL:(NSURL *)url
                                     options:(KCWebImageOptions)options
                                    progress:(KCWebImageProgressBlock)progress
                                   transform:(KCWebImageTransformBlock)transform
                                  completion:(KCWebImageCompletionBlock)completion {
    
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    request.timeoutInterval = _timeout;
    request.HTTPShouldHandleCookies = (options & KCWebImageOptionHandleCookies) != 0;
    request.allHTTPHeaderFields = [self headersForURL:url];
    request.HTTPShouldUsePipelining = YES;
    request.cachePolicy = (options & KCWebImageOptionUseNSURLCache) ?
    NSURLRequestUseProtocolCachePolicy : NSURLRequestReloadIgnoringLocalCacheData;
    
    KCWebImageOperation *operation = [[KCWebImageOperation alloc] initWithRequest:request
                                                                          options:options
                                                                            cache:_cache
                                                                         cacheKey:[self cacheKeyForURL:url]
                                                                         progress:progress
                                                                        transform:transform ? transform : _sharedTransformBlock
                                                                       completion:completion];
    
    if (_username && _password) {
        operation.credential = [NSURLCredential credentialWithUser:_username password:_password persistence:NSURLCredentialPersistenceForSession];
    }
    if (operation) {
        NSOperationQueue *queue = _queue;
        if (queue) {
            [queue addOperation:operation];
        } else {
            [operation start];
        }
    }
    return operation;
}

- (NSDictionary *)headersForURL:(NSURL *)url {
    if (!url) return nil;
    return _headersFilter ? _headersFilter(url, _headers) : _headers;
}

- (NSString *)cacheKeyForURL:(NSURL *)url {
    if (!url) return nil;
    return _cacheKeyFilter ? _cacheKeyFilter(url) : url.absoluteString;
}


@end
