//
//  KCImage.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCImageCoder.h"
#import "KCAnimatedImageView.h"

@interface KCImage : UIImage<KCAnimatedImage>

+ (KCImage *)imageNamed:(NSString *)name; // no cache!
+ (KCImage *)imageWithContentsOfFile:(NSString *)path;
+ (KCImage *)imageWithData:(NSData *)data;
+ (KCImage *)imageWithData:(NSData *)data scale:(CGFloat)scale;

/**
 If the image is created from data or file, then the value indicates the data type.
 */
@property (nonatomic, readonly) KCImageType animatedImageType;

/**
 If the image is created from animated image data (multi-frame GIF/APNG/WebP),
 this property stores the original image data.
 */
@property (nonatomic, readonly) NSData *animatedImageData;

/**
 The total memory usage (in bytes) if all frame images was loaded into memory.
 The value is 0 if the image is not created from a multi-frame image data.
 */
@property (nonatomic, readonly) NSUInteger animatedImageMemorySize;

/**
 Preload all frame image to memory.
 
 @discussion Set this property to `YES` will block the calling thread to decode
 all animation frame image to memory, set to `NO` will release the preloaded frames.
 If the image is shared by lots of image views (such as emoticon), preload all
 frames will reduce the CPU cost.
 
 See `animatedImageMemorySize` for memory cost.
 */
@property (nonatomic, assign) BOOL preloadAllAnimatedImageFrames;

@end
