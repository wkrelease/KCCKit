//
//  NSThread+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "NSThread+KCAdd.h"

#import <CoreFoundation/CoreFoundation.h>

@interface NSThread_KCAdd : NSObject

@end

@implementation NSThread_KCAdd

@end


#if __has_feature(objc_arc)
#error This file must be compiled without ARC. Specify the -fno-objc-arc flag to this file.
#endif


static NSString *const KCNSThreadAutoleasePoolKey = @"KCNSThreadAutoleasePoolKey";
static NSString *const KCNSthreadAutoleasePoolStackKey = @"KCNSthreadAutoleasePoolStackKey";
static inline void KCAutoleasePoolPush(){
    
    NSMutableDictionary *dic = [NSThread currentThread].threadDictionary;
    NSMutableArray *poolStack = dic[KCNSthreadAutoleasePoolStackKey];
    
    if (!poolStack) {
        CFArrayCallBacks callBacks = {0};
        poolStack = (id)CFArrayCreateMutable(CFAllocatorGetDefault(), 0, &callBacks);
        dic[KCNSthreadAutoleasePoolStackKey] = poolStack;
        CFRelease(poolStack);
    }
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    [poolStack addObject:pool];
    
}

static inline void KCAutoreleasePoolPop() {
 
    NSMutableDictionary *dic = [NSThread currentThread].threadDictionary;
    NSMutableArray *poolStack = dic[KCNSthreadAutoleasePoolStackKey];
    NSAutoreleasePool *pool = [poolStack lastObject];
    [poolStack removeLastObject];
    [pool release];
    
}

static void KCRunLoopAutoreleasePoolObserverCallBack(CFRunLoopObserverRef observer,CFRunLoopActivity activity,void *info){
    
    switch (activity) {
        case kCFRunLoopEntry:
            KCAutoleasePoolPush();
            break;
        case kCFRunLoopBeforeWaiting:
            KCAutoreleasePoolPop();
            KCAutoleasePoolPush();
            break;
        case kCFRunLoopExit:
            KCAutoreleasePoolPop();
            break;
        default:
            break;
    }
    
}
static void KCRunloopAutoreleasePoolSetup() {
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
       
        CFRunLoopRef runloop = CFRunLoopGetCurrent();
        CFRunLoopObserverRef pushObserver;
        pushObserver = CFRunLoopObserverCreate(CFAllocatorGetDefault(), kCFRunLoopExit, true, -0x7FFFFFFF, KCRunLoopAutoreleasePoolObserverCallBack, NULL);
        CFRunLoopObserverRef popObserver;
        popObserver = CFRunLoopObserverCreate(CFAllocatorGetDefault(), kCFRunLoopBeforeWaiting|kCFRunLoopExit, true, 0x7FFFFFFF, KCRunLoopAutoreleasePoolObserverCallBack, NULL);
        CFRunLoopAddObserver(runloop, popObserver, kCFRunLoopCommonModes);
        CFRelease(popObserver);
        
    });
    
}


@implementation NSThread (KCAdd)

+ (void)addAutoreleasePoolToCurrentRunloop {
    
    if ([NSThread isMainThread]) return; // The main thread already has autorelease pool.
    NSThread *thread = [self currentThread];
    if (!thread) return;
    if (thread.threadDictionary[KCNSThreadAutoleasePoolKey]) return; // already added
    KCRunloopAutoreleasePoolSetup();
    thread.threadDictionary[KCNSThreadAutoleasePoolKey] = KCNSThreadAutoleasePoolKey; // mark the state
    
}



@end
