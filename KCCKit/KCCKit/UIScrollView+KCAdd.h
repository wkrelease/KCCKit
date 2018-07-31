//
//  UIScrollView+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIScrollView (KCAdd)

- (void)scrollToTop;

- (void)scrollToBottom;

- (void)scrollToLeft;

- (void)scrollToRight;

- (void)scrollToTopAnimated:(BOOL)animated;


- (void)scrollToBottomAnimated:(BOOL)animated;


- (void)scrollToLeftAnimated:(BOOL)animated;


- (void)scrollToRightAnimated:(BOOL)animated;


@end
