//
//  KCImageCache.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KCMemoryCache,KCDiskCache;

typedef NS_OPTIONS(NSUInteger, KCImageCacheType){
    
    KCImageCacheTypeNone = 0,
    KCImageCacheTypeMemory = 1 << 0,
    KCImageCacheTypeDisk = 1 << 1,
    KCImageCacheTypeAll = KCImageCacheTypeMemory | KCImageCacheTypeDisk,
    
};

@interface KCImageCache : NSObject


/** The name of the cache. Default is nil. */
@property (copy) NSString *name;

@property (strong, readonly) KCMemoryCache *memoryCache;

@property (strong, readonly) KCDiskCache *diskCache;



@property (assign) BOOL allowAnimatedImage;

/**
 Whether decode the image to memory bitmap. Default is YES.
 
 @discussion If the value is YES, then the image will be decoded to memory bitmap
 for better display performance, but may cost more memory.
 */
@property (assign) BOOL decodeForDisplay;


#pragma mark - Initializer
///=============================================================================
/// @name Initializer
///=============================================================================
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;


+ (instancetype)sharedCache;

/**
 The designated initializer. Multiple instances with the same path will make the
 cache unstable.
 
 @param path Full path of a directory in which the cache will write data.
 Once initialized you should not read and write to this directory.
 @result A new cache object, or nil if an error occurs.
 */
- (instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;


#pragma mark - Access Methods
///=============================================================================
/// @name Access Methods
///=============================================================================

/**
 Sets the image with the specified key in the cache (both memory and disk).
 This method returns immediately and executes the store operation in background.
 
 @param image The image to be stored in the cache. If nil, this method has no effect.
 @param key   The key with which to associate the image. If nil, this method has no effect.
 */
- (void)setImage:(UIImage *)image forKey:(NSString *)key;



- (void)setImage:(UIImage *)image imageData:(NSData *)imageData forKey:(NSString *)key withType:(KCImageCacheType)type;

/**
 Removes the image of the specified key in the cache (both memory and disk).
 This method returns immediately and executes the remove operation in background.
 
 @param key The key identifying the image to be removed. If nil, this method has no effect.
 */
- (void)removeImageForKey:(NSString *)key;

/**
 Removes the image of the specified key in the cache.
 This method returns immediately and executes the remove operation in background.
 
 @param key  The key identifying the image to be removed. If nil, this method has no effect.
 @param type The cache type to remove image.
 */
- (void)removeImageForKey:(NSString *)key withType:(KCImageCacheType)type;

/**
 Returns a Boolean value that indicates whether a given key is in cache.
 If the image is not in memory, this method may blocks the calling thread until
 file read finished.
 
 @param key A string identifying the image. If nil, just return NO.
 @return Whether the image is in cache.
 */
- (BOOL)containsImageForKey:(NSString *)key;


- (BOOL)containsImageForKey:(NSString *)key withType:(KCImageCacheType)type;

/**
 Returns the image associated with a given key.
 If the image is not in memory, this method may blocks the calling thread until
 file read finished.
 
 @param key A string identifying the image. If nil, just return nil.
 @return The image associated with key, or nil if no image is associated with key.
 */
- (UIImage *)getImageForKey:(NSString *)key;



- (UIImage *)getImageForKey:(NSString *)key withType:(KCImageCacheType)type;

/**
 Asynchronously get the image associated with a given key.
 
 @param key   A string identifying the image. If nil, just return nil.
 @param type  The cache type.
 @param block A completion block which will be called on main thread.
 */
- (void)getImageForKey:(NSString *)key withType:(KCImageCacheType)type withBlock:(void(^)(UIImage *image, KCImageCacheType type))block;

/**
 Returns the image data associated with a given key.
 This method may blocks the calling thread until file read finished.
 
 @param key A string identifying the image. If nil, just return nil.
 @return The image data associated with key, or nil if no image is associated with key.
 */
- (NSData *)getImageDataForKey:(NSString *)key;

/**
 Asynchronously get the image data associated with a given key.
 
 @param key   A string identifying the image. If nil, just return nil.
 @param block A completion block which will be called on main thread.
 */
- (void)getImageDataForKey:(NSString *)key withBlock:(void(^)(NSData *imageData))block;



@end
