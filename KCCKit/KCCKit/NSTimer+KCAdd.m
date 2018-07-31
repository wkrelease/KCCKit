//
//  NSTimer+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "NSTimer+KCAdd.h"

#import "KCKitMacro.h"

KCSYNTH_DUMMY_CLASS(NSTimer_KCAdd)

@implementation NSTimer (KCAdd)


+ (void)_kc_ExecBlock:(NSTimer *)timer{
    
    if ([timer userInfo]) {
        void (^block)(NSTimer *timer) = (void (^)(NSTimer *timer))[timer userInfo];
        block(timer);
    }
    
}


+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)seconds block:(void (^)(NSTimer *timer))block repeats:(BOOL)repeats {
    return [NSTimer scheduledTimerWithTimeInterval:seconds target:self selector:@selector(_kc_ExecBlock:) userInfo:[block copy] repeats:repeats];
}

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)seconds block:(void (^)(NSTimer *timer))block repeats:(BOOL)repeats {
    return [NSTimer timerWithTimeInterval:seconds target:self selector:@selector(_kc_ExecBlock:) userInfo:[block copy] repeats:repeats];
}



@end
