//
//  KCSentinel.m
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "KCSentinel.h"
#import <libkern/OSAtomic.h>

@implementation KCSentinel{
    
    int32_t _value;
    
}

- (int32_t)value {
    return _value;
}

- (int32_t)increase {
    return OSAtomicIncrement32(&_value);
}

@end
