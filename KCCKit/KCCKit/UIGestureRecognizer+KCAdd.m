//
//  UIGestureRecognizer+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "UIGestureRecognizer+KCAdd.h"

#import "KCKitMacro.h"

#import <objc/runtime.h>

static const int block_key;

@interface _KCUIGestureRecognizerBlockTarget : NSObject

@property (nonatomic,copy)void (^blcok)(id sender);

- (id)initWithBlock:(void (^)(id sender))block;
- (void)invoke:(id)sender;

@end

@implementation _KCUIGestureRecognizerBlockTarget

- (id)initWithBlock:(void (^)(id))block{
    
    self = [super init];
    if (self) {
        _blcok = [block copy];
    }
    return self;
}
- (void)invoke:(id)sender{
    
    if (_blcok) {
        _blcok(sender);
    }
    
}


@end


@implementation UIGestureRecognizer (KCAdd)

- (NSMutableArray *)_kc_allUIGestureRecognizerBlockTargets{
    
    NSMutableArray *targets = objc_getAssociatedObject(self, &block_key);
    if (!targets) {
        targets = [NSMutableArray array];
        objc_setAssociatedObject(self, &block_key, targets, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return targets;
    
}

- (instancetype)initWithActionBlock:(void (^)(id))block{
    
    self = [self init];
    [self addActionBlock:block];
    return self;
    
}
- (void)addActionBlock:(void (^)(id))block{
    
    _KCUIGestureRecognizerBlockTarget *target = [[_KCUIGestureRecognizerBlockTarget alloc]initWithBlock:block
                                                 ];
    [self addTarget:target action:@selector(invoke:)];
    NSMutableArray *targets = [self _kc_allUIGestureRecognizerBlockTargets];
    [targets addObject:target];
    
}

- (void)removeAllActionBlocks{
    
    NSMutableArray *targets = [self _kc_allUIGestureRecognizerBlockTargets];
    [targets enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
       
        [self removeTarget:targets action:@selector(invoke:)];
        
    }];
    [targets removeAllObjects];
    
}
























@end
