//
//  UIControl+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/28.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIControl (KCAdd)

- (void)removeAllTargets;

- (void)setTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

- (void)addBlockForControlEvents:(UIControlEvents)controlEvents block:(void (^)(id sender))block;

- (void)setBlockForControlEvents:(UIControlEvents)controlEvents block:(void (^)(id sender))block;

- (void)removeAllBlocksForControlEvents:(UIControlEvents)controlEvents;


@end
