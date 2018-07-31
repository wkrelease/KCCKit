//
//  UITextField+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UITextField (KCAdd)

/**
 Set all text selected.
 */
- (void)selectAllText;

/**
 Set text in range selected.
 
 @param range  The range of selected text in a document.
 */
- (void)setSelectedRange:(NSRange)range;

@end
