//
//  UIColor+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

extern void KC_RGB2HSL(CGFloat R,CGFloat G,CGFloat B,CGFloat *H,CGFloat *S,CGFloat *L);
extern void KC_HSL2RGB(CGFloat H,CGFloat S,CGFloat L,CGFloat *R,CGFloat *G,CGFloat *B);
extern void KC_RGB2HSB(CGFloat R,CGFloat G,CGFloat B,CGFloat *H,CGFloat *S,CGFloat *B_);
extern void KC_HSB2RGB(CGFloat H,CGFloat S,CGFloat B,CGFloat *R,CGFloat *G,CGFloat *B_);
extern void KC_RGB2CMYK(CGFloat R,CGFloat G,CGFloat B,CGFloat *C,CGFloat *M,CGFloat *Y,CGFloat *K);
extern void KC_CMYK2RGB(CGFloat C,CGFloat M,CGFloat Y,CGFloat K,CGFloat *R,CGFloat *G,CGFloat *B);
extern void KC_HSB2HSL(CGFloat H,CGFloat S,CGFloat B,CGFloat *H_,CGFloat *S_,CGFloat *L_);
extern void KC_HSL2HSB(CGFloat H,CGFloat S,CGFloat L,CGFloat *H_,CGFloat *S_,CGFloat *B);


/*
 Create UIColor with a hex string.
 Example: UIColorHex(0xF0F), UIColorHex(66ccff), UIColorHex(#66CCFF88)
 
 Valid format: #RGB #RGBA #RRGGBB #RRGGBBAA 0xRGB ...
 The `#` or "0x" sign is not required.
 */
#ifndef UIColorHex
#define UIColorHex(_hex_)   [UIColor colorWithHexString:((__bridge NSString *)CFSTR(#_hex_))]
#endif





@interface UIColor (KCAdd)



+ (UIColor *)colorWithHue:(CGFloat)hue
               saturation:(CGFloat)saturation
                lightness:(CGFloat)lightness
                    alpha:(CGFloat)alpha;

+ (UIColor *)colorWithCyan:(CGFloat)cyan
                   magenta:(CGFloat)magenta
                    yellow:(CGFloat)yellow
                     black:(CGFloat)black
                     alpha:(CGFloat)alpha;

+ (UIColor *)colorWithRGB:(uint32_t)rgbValue;

+ (UIColor *)colorWithRGBA:(uint32_t)rgbaValue;

+ (UIColor *)colorWithRGB:(uint32_t)rgbValue alpha:(CGFloat)alpha;

+ (UIColor *)colorWithHexString:(NSString *)hexStr;

- (UIColor *)colorByAddColor:(UIColor *)add blendMode:(CGBlendMode)blendMode;

- (UIColor *)colorByChangeHue:(CGFloat)hueDelta
                   saturation:(CGFloat)saturationDelta
                   brightness:(CGFloat)brightnessDelta
                        alpha:(CGFloat)alphaDelta;



#pragma mark - Get color's description

- (uint32_t)rgbValue;
- (uint32_t)rgbaValue;
- (NSString *)hexString;
- (NSString *)hexStringWithAlpha;


#pragma mark - Retrieving Color Information

- (BOOL)getHue:(CGFloat *)hue
    saturation:(CGFloat *)saturation
     lightness:(CGFloat *)lightness
         alpha:(CGFloat *)alpha;

- (BOOL)getCyan:(CGFloat *)cyan
        magenta:(CGFloat *)magenta
         yellow:(CGFloat *)yellow
          black:(CGFloat *)black
          alpha:(CGFloat *)alpha;


@property (nonatomic, readonly) CGFloat red;

@property (nonatomic, readonly) CGFloat green;

@property (nonatomic, readonly) CGFloat blue;

@property (nonatomic, readonly) CGFloat hue;

@property (nonatomic, readonly) CGFloat saturation;

@property (nonatomic, readonly) CGFloat brightness;

@property (nonatomic, readonly) CGFloat alpha;

@property (nonatomic, readonly) CGColorSpaceModel colorSpaceModel;

@property (nonatomic, readonly) NSString *colorSpaceString;






@end
