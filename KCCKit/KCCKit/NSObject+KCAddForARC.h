//
//  NSObject+KCAddForARC.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *debug method for nsobject when using arc
 */
@interface NSObject (KCAddForARC)

- (instancetype)arcDebugRetain;

- (oneway void)arcDebugRelease;

- (instancetype)arcDebugAutorelease;

- (NSUInteger)arcDebugRetainCount;

@end
