//
//  UIGestureRecognizer+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIGestureRecognizer (KCAdd)

- (instancetype)initWithActionBlock:(void (^)(id sender))block;

- (void)addActionBlock:(void (^)(id sender))block;

- (void)removeAllActionBlocks;

@end
