//
//  NSArray+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (KCAdd)

+ (NSArray *)arrayWithPlistData:(NSData *)plist;

+ (NSArray *)arrayWithPlistString:(NSString *)plist;

- (NSData *)plistData;

- (NSString *)plistString;

- (id)randomObject;

- (id)objectOrNilAtIndex:(NSUInteger)index;

- (NSString *)jsonStringEncoded;

- (NSString *)jsonPrettyStringEncoded;

@end



@interface NSMutableArray (YYAdd)

+ (NSMutableArray *)arrayWithPlistData:(NSData *)plist;

+ (NSMutableArray *)arrayWithPlistString:(NSString *)plist;

- (id)randomObject;

- (id)objectOrNilAtIndex:(NSUInteger)index;

- (void)removeObjectOrNilAtIndex:(NSUInteger)index;

- (void)removeFirstObject;

- (void)removeLastObject;

- (id)popFirstObject;

- (id)popLastObject;

- (void)appendObject:(id)anObject;

- (void)prependObject:(id)anObject;

- (void)appendObjects:(NSArray *)objects;

- (void)prependObjects:(NSArray *)objects;

- (void)insertObjects:(NSArray *)objects atIndex:(NSUInteger)index;

- (void)reverse;

- (void)shuffle;



@end
