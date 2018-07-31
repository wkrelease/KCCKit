//
//  KCSentinel.h
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KCSentinel : NSObject

@property (atomic, readonly) int32_t value;

- (int32_t)increase;

@end
