//
//  NSDictionary+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (KCAdd)


+ (NSDictionary *)dictionaryWithPlistData:(NSData *)plist;

+ (NSDictionary *)dictionaryWithPlistString:(NSString *)plist;

//安全取键
- (id)safeObj:(id)key;


- (NSData *)plistData;

- (NSString *)plistString;

- (NSArray *)allKeysSorted;

- (NSArray *)allValuesSortedByKeys;

- (BOOL)containsObjectForKey:(id)key;

- (NSDictionary *)entriesForKeys:(NSArray *)keys;

- (NSString *)jsonStringEncoded;

- (NSString *)jsonPrettyStringEncoded;

+ (NSDictionary *)dictionaryWithXML:(id)xmlDataOrString;

- (BOOL)boolValueForKey:(NSString *)key default:(BOOL)def;

- (char)charValueForKey:(NSString *)key default:(char)def;
- (unsigned char)unsignedCharValueForKey:(NSString *)key default:(unsigned char)def;

- (short)shortValueForKey:(NSString *)key default:(short)def;
- (unsigned short)unsignedShortValueForKey:(NSString *)key default:(unsigned short)def;

- (int)intValueForKey:(NSString *)key default:(int)def;
- (unsigned int)unsignedIntValueForKey:(NSString *)key default:(unsigned int)def;

- (long)longValueForKey:(NSString *)key default:(long)def;
- (unsigned long)unsignedLongValueForKey:(NSString *)key default:(unsigned long)def;

- (long long)longLongValueForKey:(NSString *)key default:(long long)def;
- (unsigned long long)unsignedLongLongValueForKey:(NSString *)key default:(unsigned long long)def;

- (float)floatValueForKey:(NSString *)key default:(float)def;
- (double)doubleValueForKey:(NSString *)key default:(double)def;

- (NSInteger)integerValueForKey:(NSString *)key default:(NSInteger)def;
- (NSUInteger)unsignedIntegerValueForKey:(NSString *)key default:(NSUInteger)def;

- (NSNumber *)numverValueForKey:(NSString *)key default:(NSNumber *)def;
- (NSString *)stringValueForKey:(NSString *)key default:(NSString *)def;



@end


@interface NSMutableDictionary (KCAdd)


+ (NSMutableDictionary *)dictionaryWithPlistData:(NSData *)plist;

+ (NSMutableDictionary *)dictionaryWithPlistString:(NSString *)plist;

- (id)popObjectForKey:(id)aKey;

- (NSDictionary *)popEntriesForKeys:(NSArray *)keys;


@end














