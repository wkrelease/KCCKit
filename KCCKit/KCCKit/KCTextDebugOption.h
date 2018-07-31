//
//  KCTextDebugOption.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KCTextDebugOption;

@protocol KCTextDebugTarget <NSObject>
@required
- (void)setDebugOption:(KCTextDebugOption *)option;
@end



@interface KCTextDebugOption : NSObject

@property (nonatomic, strong) UIColor *baselineColor;      ///< baseline color
@property (nonatomic, strong) UIColor *CTFrameBorderColor; ///< CTFrame path border color
@property (nonatomic, strong) UIColor *CTFrameFillColor;   ///< CTFrame path fill color
@property (nonatomic, strong) UIColor *CTLineBorderColor;  ///< CTLine bounds border color
@property (nonatomic, strong) UIColor *CTLineFillColor;    ///< CTLine bounds fill color
@property (nonatomic, strong) UIColor *CTLineNumberColor;  ///< CTLine line number color
@property (nonatomic, strong) UIColor *CTRunBorderColor;   ///< CTRun bounds border color
@property (nonatomic, strong) UIColor *CTRunFillColor;     ///< CTRun bounds fill color
@property (nonatomic, strong) UIColor *CTRunNumberColor;   ///< CTRun number color
@property (nonatomic, strong) UIColor *CGGlyphBorderColor; ///< CGGlyph bounds border color
@property (nonatomic, strong) UIColor *CGGlyphFillColor;   ///< CGGlyph bounds fill color

- (BOOL)needDrawDebug; ///< `YES`: at least one debug color is visible. `NO`: all debug color is invisible/nil.
- (void)clear; ///< Set all debug color to nil.

+ (void)addDebugTarget:(id<KCTextDebugTarget>)target;

+ (void)removeDebugTarget:(id<KCTextDebugTarget>)target;

+ (KCTextDebugOption *)sharedDebugOption;

+ (void)setSharedDebugOption:(KCTextDebugOption *)option;

@end
