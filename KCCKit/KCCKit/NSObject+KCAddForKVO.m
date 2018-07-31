//
//  NSObject+KCAddForKVO.m
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "NSObject+KCAddForKVO.h"

#import "KCKitMacro.h"
#import <objc/objc.h>
#import <objc/runtime.h>

KCSYNTH_DUMMY_CLASS(NSObject_KCAddForKVO)

static const int block_key;

@interface _KCNSObjectKVOBlockTarget : NSObject

@property (nonatomic,copy)void (^block)(__weak id obj,id oldVal,id newVal);

- (id)initWithBlock:(void (^)(__weak id obj, id oldVal, id newVal))block;

@end

@implementation _KCNSObjectKVOBlockTarget

- (id)initWithBlock:(void (^)(__weak id, id, id))block{
    
    self = [super init];
    if (self) {
        self.block = block;
    }
    return self;
}
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context{
    
    if (!self.block) {
        return;
    }
    BOOL isPrior = [[change objectForKey:NSKeyValueChangeNotificationIsPriorKey]boolValue];
    
    if (isPrior) {
        return;
    }
    
    NSKeyValueChange changeKind = [[change objectForKey:NSKeyValueChangeKindKey]integerValue];
    
    if (changeKind != NSKeyValueChangeSetting) {
        return;
    }
    
    id oldVal = [change objectForKey:NSKeyValueChangeOldKey];
    if (oldVal == [NSNull null]) {
        oldVal = nil;
    }
    
    id newVal = [change objectForKey:NSKeyValueChangeNewKey];
    if (newVal == [NSNull null]) {
        newVal = nil;
    }
    
    self.block(object,oldVal,newVal);
    
}

@end

@implementation NSObject (KCAddForKVO)


- (void)addObserverBlockForKeyPath:(NSString *)keyPath block:(void (^)(__weak id, id, id))block{
    
    if (!keyPath || !block) {
        return;
    }
    _KCNSObjectKVOBlockTarget *target = [[_KCNSObjectKVOBlockTarget alloc]initWithBlock:block];
    NSMutableDictionary *dic = [self _kc_allNSObjectObserverBlocks];
    NSMutableArray *arr = dic[keyPath];
    if (!arr) {
        arr = [NSMutableArray new];
        dic[keyPath] = arr;
    }
    [arr addObject:target];
    [self addObserver:target forKeyPath:keyPath options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:NULL];
}













- (void)removeObserverBlocksForKeyPath:(NSString *)keyPath{
    
    if (!keyPath) {
        return;
    }
    NSMutableDictionary *dic = [self _kc_allNSObjectObserverBlocks];
    NSMutableArray *arr = dic[keyPath];
    [arr enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
       
        [self removeObserver:obj forKeyPath:keyPath];
        
    }];
    
}


- (void)removeObserverBlocks{
    
    NSMutableDictionary *dic = [self _kc_allNSObjectObserverBlocks];
    
    [dic enumerateKeysAndObjectsUsingBlock: ^(NSString *key, NSArray *arr, BOOL *stop) {
        [arr enumerateObjectsUsingBlock: ^(id obj, NSUInteger idx, BOOL *stop) {
            [self removeObserver:obj forKeyPath:key];
        }];
    }];
    
}



- (NSMutableDictionary *)_kc_allNSObjectObserverBlocks{
    
    NSMutableDictionary *targets = objc_getAssociatedObject(self, &block_key);
    if (!targets) {
        targets = [NSMutableDictionary new];
        objc_setAssociatedObject(self, &block_key, targets, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return targets;
    
}























@end
