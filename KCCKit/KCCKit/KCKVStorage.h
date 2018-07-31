//
//  KCKVStorage.h
//  KCKit
//
//  Created by king on 16/3/31.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KCKVStorageItem : NSObject

/**  注释  **/
@property (nonatomic,strong)NSString *key;
/**  注释  **/
@property (nonatomic,strong)NSData *value;
/**  注释  **/
@property (nonatomic,strong)NSString *filename;
/**  注释  **/
@property (nonatomic,assign)int size;
/**  注释  **/
@property (nonatomic,assign)int modTime;
/**  注释  **/
@property (nonatomic,assign)int accessTime;
/**  注释  **/
@property (nonatomic,strong)NSData *extendedData;

@end

typedef NS_ENUM(NSUInteger,KCKVStorageType){
    
    /// The `value` is stored as a file in file system.
    KCKVStorageTypeFile = 0,
    
    /// The `value` is stored in sqlite with blob type.
    KCKVStorageTypeSQLite = 1,
    
    /// The `value` is stored in file system or sqlite based on your choice.
    KCKVStorageTypeMixed = 2,
    
};

@interface KCKVStorage : NSObject

#pragma mark - Attribute
@property (nonatomic, readonly) NSString *path;        ///< The path of this storage.
@property (nonatomic, readonly) KCKVStorageType type;  ///< The type of this storage.
@property (nonatomic, assign) BOOL errorLogsEnabled;   ///< Set `YES` to enable error logs for debug.

#pragma mark - Initializer
///=============================================================================
/// @name Initializer
///=============================================================================
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

- (instancetype)initWithPath:(NSString *)path type:(KCKVStorageType)type NS_DESIGNATED_INITIALIZER;

- (BOOL)saveItem:(KCKVStorageItem *)item;

- (BOOL)saveItemWithKey:(NSString *)key value:(NSData *)value;

- (BOOL)saveItemWithKey:(NSString *)key
                  value:(NSData *)value
               filename:(NSString *)filename
           extendedData:(NSData *)extendedData;

- (BOOL)removeItemForKey:(NSString *)key;

- (BOOL)removeItemForKeys:(NSArray *)keys;

- (BOOL)removeItemsLargerThanSize:(int)size;

- (BOOL)removeItemsEarlierThanTime:(int)time;

- (BOOL)removeItemsToFitSize:(int)maxSize;

- (BOOL)removeItemsToFitCount:(int)maxCount;

- (BOOL)removeAllItems;

- (void)removeAllItemsWithProgressBlock:(void(^)(int removedCount, int totalCount))progress
                               endBlock:(void(^)(BOOL error))end;



- (KCKVStorageItem *)getItemForKey:(NSString *)key;

- (KCKVStorageItem *)getItemInfoForKey:(NSString *)key;

- (NSData *)getItemValueForKey:(NSString *)key;

- (NSArray *)getItemForKeys:(NSArray *)keys;

- (NSArray *)getItemInfoForKeys:(NSArray *)keys;

- (NSDictionary *)getItemValueForKeys:(NSArray *)keys;


- (BOOL)itemExistsForKey:(NSString *)key;

- (int)getItemsCount;

- (int)getItemsSize;



@end





























