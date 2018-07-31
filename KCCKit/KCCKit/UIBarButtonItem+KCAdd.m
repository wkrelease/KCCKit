//
//  UIBarButtonItem+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "UIBarButtonItem+KCAdd.h"

#import "KCKitMacro.h"

#import <objc/runtime.h>

KCSYNTH_DUMMY_CLASS(UIBarButtonItem_KCAdd)

static const int block_key;

@interface _KCUIBarButtonItemBlockTarget : NSObject

@property (nonatomic,copy)void (^block)(id sender);

- (id)initWithBlock:(void (^)(id sender))block;
- (void)invoke:(id)sender;

@end

@implementation _KCUIBarButtonItemBlockTarget

- (id)initWithBlock:(void (^)(id sender))block{
    self = [super init];
    if (self) {
        _block = [block copy];
    }
    return self;
}

- (void)invoke:(id)sender {
    if (self.block) self.block(sender);
}

@end



@implementation UIBarButtonItem (KCAdd)

- (void)setActionBlock:(void (^)(id sender))block{
    
    _KCUIBarButtonItemBlockTarget *target = [[_KCUIBarButtonItemBlockTarget alloc]initWithBlock:block];
    objc_setAssociatedObject(self, &block_key, target, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    [self setTarget:target];
    [self setAction:@selector(invoke:)];
    
}

- (void (^)(id)) actionBlock {
    _KCUIBarButtonItemBlockTarget *target = objc_getAssociatedObject(self, &block_key);
    return target.block;
}

@end
