//
//  NSObject+KCModel.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provide some data-model method:
 
 * Convert json to any object, or convert any object to json.
 * Set object properties with a key-value dictionary (like KVC).
 * Implementations of `NSCoding`, `NSCopying`, `-hash` and `-isEqual:`.
 
 See `YYModel` protocol for custom methods.
 
 
 Sample Code:
 
 ********************** json convertor *********************
 @code
 @interface YYAuthor : NSObject
 @property (nonatomic, strong) NSString *name;
 @property (nonatomic, assign) NSDate *birthday;
 @end
 @implementation YYAuthor
 @end
 
 @interface YYBook : NSObject
 @property (nonatomic, copy) NSString *name;
 @property (nonatomic, assign) NSUInteger pages;
 @property (nonatomic, strong) YYAuthor *author;
 @end
 @implementation YYBook
 @end
 
 int main() {
 // create model from json
 YYBook *book = [YYBook modelWithJSON:@"{\"name\": \"Harry Potter\", \"pages\": 256, \"author\": {\"name\": \"J.K.Rowling\", \"birthday\": \"1965-07-31\" }}"];
 
 // convert model to json
 NSString *json = [book modelToJSONString];
 // {"author":{"name":"J.K.Rowling","birthday":"1965-07-31T00:00:00+0000"},"name":"Harry Potter","pages":256}
 }
 @endcode
 
 
 ********************** Coding/Copying/hash/equal *********************
 @code
 @interface YYShadow :NSObject <NSCoding, NSCopying>
 @property (nonatomic, copy) NSString *name;
 @property (nonatomic, assign) CGSize size;
 @end
 
 @implementation YYShadow
 - (void)encodeWithCoder:(NSCoder *)aCoder { [self modelEncodeWithCoder:aCoder]; }
 - (id)initWithCoder:(NSCoder *)aDecoder { self = [super init]; return [self modelInitWithCoder:aDecoder]; }
 - (id)copyWithZone:(NSZone *)zone { return [self modelCopy]; }
 - (NSUInteger)hash { return [self modelHash]; }
 - (BOOL)isEqual:(id)object { return [self modelIsEqual:object]; }
 @end
 @endcode
 
 */
@interface NSObject (KCModel)

+ (nullable instancetype)modelWithJSON:(id)json;

+ (nullable instancetype)modelWithDictionary:(NSDictionary *)dictionary;

- (BOOL)modelSetWithJSON:(id)json;

- (BOOL)modelSetWithDictionary:(NSDictionary *)dic;

- (nullable id)modelToJSONObject;

- (nullable NSData *)modelToJSONData;

- (nullable NSString *)modelToJSONString;

- (nullable id)modelCopy;

- (void)modelEncodeWithCoder:(NSCoder *)aCoder;

- (id)modelInitWithCoder:(NSCoder *)aDecoder;

- (NSUInteger)modelHash;

- (BOOL)modelIsEqual:(id)model;

- (NSString *)modelDescription;

@end


@interface NSArray (KCModel)

+ (nullable NSArray *)modelArrayWithClass:(Class)cls json:(id)json;

@end



@interface NSDictionary (KCModel)

+ (nullable NSDictionary *)modelDictionaryWithClass:(Class)cls json:(id)json;
@end


@protocol KCModel <NSObject>
@optional

+ (nullable NSDictionary<NSString *, id> *)modelCustomPropertyMapper;

+ (nullable NSDictionary<NSString *, id> *)modelContainerPropertyGenericClass;

+ (nullable Class)modelCustomClassForDictionary:(NSDictionary *)dictionary;

+ (nullable NSArray<NSString *> *)modelPropertyBlacklist;

+ (nullable NSArray<NSString *> *)modelPropertyWhitelist;


- (NSDictionary *)modelCustomWillTransformFromDictionary:(NSDictionary *)dic;


- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic;


- (BOOL)modelCustomTransformToDictionary:(NSMutableDictionary *)dic;

@end

NS_ASSUME_NONNULL_END


