//
//  NSParagraphStyle+KCText.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NSParagraphStyle (KCText)

+ (NSParagraphStyle *)styleWithCTStyle:(CTParagraphStyleRef)CTStyle;

- (CTParagraphStyleRef)CTStyle CF_RETURNS_RETAINED;

@end
