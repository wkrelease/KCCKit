//
//  UIScrollView+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "UIScrollView+KCAdd.h"

#import "KCKitMacro.h"

KCSYNTH_DUMMY_CLASS(UIScrollView_KCAdd)

@implementation UIScrollView (KCAdd)

- (void)scrollToTop {
    [self scrollToTopAnimated:YES];
}

- (void)scrollToBottom {
    [self scrollToBottomAnimated:YES];
}

- (void)scrollToLeft {
    [self scrollToLeftAnimated:YES];
}

- (void)scrollToRight {
    [self scrollToRightAnimated:YES];
}

- (void)scrollToTopAnimated:(BOOL)animated{
    
    CGPoint off = self.contentOffset;
    off.y = 0 - self.contentInset.top;
    [self setContentOffset:off animated:animated];
    
}
- (void)scrollToBottomAnimated:(BOOL)animated{
    
    CGPoint off = self.contentOffset;
    off.y = self.contentSize.height - self.bounds.size.height + self.contentInset.bottom;
    [self setContentOffset:off animated:animated];
    
}
- (void)scrollToLeftAnimated:(BOOL)animated{
    
    CGPoint off = self.contentOffset;
    off.x = 0 - self.contentInset.left;
    [self setContentOffset:off animated:animated];
    
}
- (void)scrollToRightAnimated:(BOOL)animated{
    
    CGPoint off = self.contentOffset;
    off.x = self.contentSize.width - self.bounds.size.width + self.contentInset.right;
    [self setContentOffset:off animated:animated];
    
}






















@end
