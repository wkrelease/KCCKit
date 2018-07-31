//
//  UIFont+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <CoreGraphics/CoreGraphics.h>

#import <CoreText/CoreText.h>

@interface UIFont (KCAdd)<NSCoding>


#pragma mark - Font Traits
@property (nonatomic, readonly) BOOL isBold NS_AVAILABLE_IOS(7_0); ///< Whether the font is bold.
@property (nonatomic, readonly) BOOL isItalic NS_AVAILABLE_IOS(7_0); ///< Whether the font is italic.
@property (nonatomic, readonly) BOOL isMonoSpace NS_AVAILABLE_IOS(7_0); ///< Whether the font is mono space.
@property (nonatomic, readonly) BOOL isColorGlyphs NS_AVAILABLE_IOS(7_0); ///< Whether the font is color glyphs (such as Emoji).
@property (nonatomic, readonly) CGFloat fontWeight NS_AVAILABLE_IOS(7_0); ///< Font weight from -1.0 to 1.0. Regular weight is 0.0.

- (UIFont *)fontWithBold NS_AVAILABLE_IOS(7_0);
- (UIFont *)fontWithItalic NS_AVAILABLE_IOS(7_0);
- (UIFont *)fontWithBoldItalic NS_AVAILABLE_IOS(7_0);
- (UIFont *)fontWithNormal NS_AVAILABLE_IOS(7_0);

#pragma mark - Create font
+ (UIFont *)fontWithCTFont:(CTFontRef)CTFont;
+ (UIFont *)fontWithCGFont:(CGFontRef)CGFont size:(CGFloat)size;
- (CTFontRef)CTFontRef CF_RETURNS_RETAINED;
- (CGFontRef)CGFontRef CF_RETURNS_RETAINED;

#pragma mark - Load and unload font
+ (BOOL)loadFontFromPath:(NSString *)path;
+ (void)unloadFontFromPath:(NSString *)path;
+ (UIFont *)loadFontFromData:(NSData *)data;
+ (BOOL)unloadFontFromData:(UIFont *)font;

#pragma mark - Dump font data
+ (NSData *)dataFromFont:(UIFont *)font;
+ (NSData *)dataFromCGFont:(CGFontRef)cgFont;





@end
