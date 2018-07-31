//
//  NSObject+KCAddForARC.m
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "NSObject+KCAddForARC.h"


@implementation NSObject (KCAddForARC)

- (instancetype)arcDebugRetain{
    
    return [self retain];
    
}

- (oneway void)arcDebugRelease{
    
    [self release];
    
}

- (instancetype)arcDebugAutorelease{
    
    return [self autorelease];
    
}

- (NSUInteger)arcDebugRetainCount{
    
    return [self retainCount];
    
}


@end
