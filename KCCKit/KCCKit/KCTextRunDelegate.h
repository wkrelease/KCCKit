//
//  KCTextRunDelegate.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreText/CoreText.h>


/**
 Wrapper for CTRunDelegateRef.
 
 Example:
 
 KCTextRunDelegate *delegate = [KCTextRunDelegate new];
 delegate.ascent = 20;
 delegate.descent = 4;
 delegate.width = 20;
 CTRunDelegateRef ctRunDelegate = delegate.CTRunDelegate;
 if (ctRunDelegate) {
 /// add to attributed string
 CFRelease(ctRunDelegate);
 }
 
 */
@interface KCTextRunDelegate : NSObject <NSCopying, NSCoding>

/**
 Creates and returns the CTRunDelegate.
 
 @discussion You need call CFRelease() after used.
 The CTRunDelegateRef has a strong reference to this KCTextRunDelegate object.
 In CoreText, use CTRunDelegateGetRefCon() to get this KCTextRunDelegate object.
 
 @return The CTRunDelegate object.
 */
- (CTRunDelegateRef)CTRunDelegate CF_RETURNS_RETAINED;

/**
 Additional information about the the run delegate.
 */
@property (nonatomic, strong) NSDictionary *userInfo;

/**
 The typographic ascent of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat ascent;

/**
 The typographic descent of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat descent;

/**
 The typographic width of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat width;

@end
