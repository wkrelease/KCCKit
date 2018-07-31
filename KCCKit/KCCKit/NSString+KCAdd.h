//
//  NSString+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

@interface NSString (KCAdd)

#pragma mark - Hash

- (NSString *)md2String;

- (NSString *)md4String;

- (NSString *)md5String;

- (NSString *)sha1String;

- (NSString *)sha224String;

- (NSString *)sha256String;

- (NSString *)sha384String;

- (NSString *)sha512String;

- (NSString *)hmacMD5StringWithKey:(NSString *)key;

- (NSString *)hmacSHA1StringWithKey:(NSString *)key;

- (NSString *)hmacSHA224StringWithKey:(NSString *)key;

- (NSString *)hmacSHA256StringWithKey:(NSString *)key;

- (NSString *)hmacSHA384StringWithKey:(NSString *)key;

- (NSString *)hmacSHA512StringWithKey:(NSString *)key;

- (NSString *)crc32String;

#pragma mark - Encode and decode

- (NSString *)base64EncodedString;

+ (NSString *)stringWithBase64EncodedString:(NSString *)base64EncodedString;

- (NSString *)stringByURLEncode;

- (NSString *)stringByURLDecode;

- (NSString *)stringByEscapingHTML;

#pragma mark - Drawing

- (CGSize)sizeForFont:(UIFont *)font size:(CGSize)size mode:(NSLineBreakMode)lineBreakMode;

- (CGFloat)widthForFont:(UIFont *)font;

- (CGFloat)heightForFont:(UIFont *)font width:(CGFloat)width;

#pragma mark - Regular Expression

- (BOOL)matchesRegex:(NSString *)regex options:(NSRegularExpressionOptions)options;

- (void)enumerateRegexMatches:(NSString *)regex options:(NSRegularExpressionOptions)options usingBlock:(void (^)(NSString *match, NSRange matchRange,BOOL *stop))block;

- (NSString *)stringByReplacingRegex:(NSString *)regex options:(NSRegularExpressionOptions)options withString:(NSString *)replacement;

#pragma mark -Emoji

- (BOOL)containsEmoji;

- (BOOL)containsEmojiForSystemVersion:(float)systemVersion;

#pragma mark - NSNumber Compatible

@property (readonly) char charValue;
@property (readonly) unsigned char unsignedCharValue;
@property (readonly) short shortValue;
@property (readonly) unsigned short unsignedShortValue;
@property (readonly) unsigned int unsignedIntValue;
@property (readonly) long longValue;
@property (readonly) unsigned long unsignedLongValue;
@property (readonly) unsigned long long unsignedLongLongValue;
@property (readonly) NSUInteger unsignedIntegerValue;

#pragma mark - Utilities

+ (NSString *)stringWithUUID;

+ (NSString *)stringWithUTF32Char:(UTF32Char)char32;

+ (NSString *)stringWithUTF32Chars:(const UTF32Char *)char32 length:(NSUInteger)length;

- (void)enumerateUTF32CharInRange:(NSRange)range usingBlock:(void (^)(UTF32Char char32, NSRange range, BOOL *stop))block;

- (NSString *)stringByTrim;

- (NSString *)stringByAppendingNameScale:(CGFloat)scale;

- (NSString *)stringByAppendingPathScale:(CGFloat)scale;

- (CGFloat)pathScale;

- (BOOL)isNotBlank;

- (BOOL)containsString:(NSString *)string;

- (BOOL)containsCharacterSet:(NSCharacterSet *)set;

- (NSNumber *)numberValue;

- (NSData *)dataValue;

- (NSRange)rangeofAll;

- (id)jsonValueDecoded;

+ (NSString *)stringNamed:(NSString *)name;

+ (NSString *)dateStringWithTime:(NSString *)string;



+ (NSString *)ServiceStr:(NSString *)url;

+ (NSString *)stringByReversedForPay:(NSString *)str;

+ (NSString *)getMoneyStringDecimal:(NSString *)string;

@end
