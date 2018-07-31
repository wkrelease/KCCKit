//
//  KCFileHash.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//


#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, KCFileHashType){
    KCFileHashTypeMD2     = 1 << 0, ///< MD2 hash
    KCFileHashTypeMD4     = 1 << 1, ///< MD4 hash
    KCFileHashTypeMD5     = 1 << 2, ///< MD5 hash
    KCFileHashTypeSHA1    = 1 << 3, ///< SHA1 hash
    KCFileHashTypeSHA224  = 1 << 4, ///< SHA224 hash
    KCFileHashTypeSHA256  = 1 << 5, ///< SHA256 hash
    KCFileHashTypeSHA384  = 1 << 6, ///< SHA384 hash
    KCFileHashTypeSHA512  = 1 << 7, ///< SHA512 hash
    KCFileHashTypeCRC32   = 1 << 8, ///< crc32 checksum
    KCFileHashTypeAdler32 = 1 << 9, ///< adler32 checksum
};

@interface KCFileHash : NSObject


@property (nonatomic, assign, readonly) KCFileHashType types; ///< hash type

@property (nonatomic, strong, readonly) NSString *md2String; ///< md2 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *md4String; ///< md4 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *md5String; ///< md5 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *sha1String; ///< sha1 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *sha224String; ///< sha224 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *sha256String; ///< sha256 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *sha384String; ///< sha384 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *sha512String; ///< sha512 hash string in lowercase
@property (nonatomic, strong, readonly) NSString *crc32String; ///< crc32 checksum string in lowercase
@property (nonatomic, strong, readonly) NSString *adler32String; ///< adler32 checksum string in lowercase

@property (nonatomic, strong, readonly) NSData *md2Data; ///< md2 hash
@property (nonatomic, strong, readonly) NSData *md4Data; ///< md4 hash
@property (nonatomic, strong, readonly) NSData *md5Data; ///< md5 hash
@property (nonatomic, strong, readonly) NSData *sha1Data; ///< sha1 hash
@property (nonatomic, strong, readonly) NSData *sha224Data; ///< sha224 hash
@property (nonatomic, strong, readonly) NSData *sha256Data; ///< sha256 hash
@property (nonatomic, strong, readonly) NSData *sha384Data; ///< sha384 hash
@property (nonatomic, strong, readonly) NSData *sha512Data; ///< sha512 hash
@property (nonatomic, assign, readonly) uint32_t crc32; ///< crc32 checksum
@property (nonatomic, assign, readonly) uint32_t adler32; ///< adler32 checksum



+ (KCFileHash *)hashForFile:(NSString *)filePath types:(KCFileHashType)types;

+ (KCFileHash *)hashForFile:(NSString *)filePath
                      types:(KCFileHashType)types
                 usingBlock:(void(^)(UInt64 totalSize, UInt64 processedSize, BOOL *stop))block;

@end
