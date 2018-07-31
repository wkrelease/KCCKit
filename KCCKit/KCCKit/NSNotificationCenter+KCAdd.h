//
//  NSNotificationCenter+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSNotificationCenter (KCAdd)

- (void)postNotificationOnMainThread:(NSNotification *)notification;

- (void)postNotificationOnMainThread:(NSNotification *)notification waitUntilDone:(BOOL)wait;

- (void)postNotificationOnMainThreadWithName:(NSString *)name object:(id)object;

- (void)postNotificationOnMainThreadWithName:(NSString *)name object:(id)object userInfo:(NSDictionary *)userInfo;

- (void)postNotificationOnMainThreadWithName:(NSString *)name object:(id)object userInfo:(NSDictionary *)userInfo waitUntilDone:(BOOL)wait;

@end



























