//
//  UIImage+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/28.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (KCAdd)

+ (UIImage *)imageWithSmallGIFData:(NSData *)data scale:(CGFloat)scale;

+ (BOOL)isAnimatedGIFData:(NSData *)data;

+ (BOOL)isAnimatedGIFFile:(NSString *)path;

+ (UIImage *)imageWithPDF:(id)dataOrPath;

+ (UIImage *)imageWithPDF:(id)dataOrPath size:(CGSize)size;

+ (UIImage *)imageWithEmoji:(NSString *)emoji size:(CGFloat)size;

+ (UIImage *)imageWithColor:(UIColor *)color;

+ (UIImage *)imageWithColor:(UIColor *)color size:(CGSize)size;

+ (UIImage *)imageWithSize:(CGSize)size drawBlock:(void (^)(CGContextRef context))drawBlock;


#pragma mark - Image Info

- (BOOL)hasAlphaChannel;

#pragma mark - Modify Image

- (void)drawInRect:(CGRect)rect withContentMode:(UIViewContentMode)contentMode clipsToBounds:(BOOL)clips;

- (UIImage *)imageByResizeToSize:(CGSize)size;

- (UIImage *)imageByResizeToSize:(CGSize)size contentMode:(UIViewContentMode)contentMode;

- (UIImage *)imageByCropToRect:(CGRect)rect;

- (UIImage *)imageByInsetEdge:(UIEdgeInsets)insets withColor:(UIColor *)color;

- (UIImage *)imageByRoundCornerRadius:(CGFloat)radius;

- (UIImage *)imageByRoundCornerRadius:(CGFloat)radius
                          borderWidth:(CGFloat)borderWidth
                          borderColor:(UIColor *)borderColor;


- (UIImage *)imageByRoundCornerRadius:(CGFloat)radius
                              corners:(UIRectCorner)corners
                          borderWidth:(CGFloat)borderWidth
                          borderColor:(UIColor *)borderColor
                       borderLineJoin:(CGLineJoin)borderLineJoin;


- (UIImage *)imageByRotate:(CGFloat)radians fitSize:(BOOL)fitSize;

- (UIImage *)imageByRotateLeft90;

- (UIImage *)imageByRotateRight90;

- (UIImage *)imageByRotate180;

- (UIImage *)imageByFlipVertical;

- (UIImage *)imageByFlipHorizontal;

#pragma mark - Image Effect

- (UIImage *)imageByTintColor:(UIColor *)color;

- (UIImage *)imageByGrayscale;

- (UIImage *)imageByBlurSoft;

- (UIImage *)imageByBlurLight;

- (UIImage *)imageByBlurExtraLight;

- (UIImage *)imageByBlurDark;

- (UIImage *)imageByBlurWithTint:(UIColor *)tintColor;

- (UIImage *)imageByBlurRadius:(CGFloat)blurRadius
                     tintColor:(UIColor *)tintColor
                      tintMode:(CGBlendMode)tintBlendMode
                    saturation:(CGFloat)saturation
                     maskImage:(UIImage *)maskImage;





@end
