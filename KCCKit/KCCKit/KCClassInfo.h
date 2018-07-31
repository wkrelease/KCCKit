//
//  KCClassInfo.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <objc/runtime.h>


typedef NS_OPTIONS(NSUInteger, KCEncodingType){
    
    KCEncodingTypeMask       = 0x1F, ///< mask of type value
    KCEncodingTypeUnknown    = 0, ///< unknown
    KCEncodingTypeVoid       = 1, ///< void
    KCEncodingTypeBool       = 2, ///< bool
    KCEncodingTypeInt8       = 3, ///< char / BOOL
    KCEncodingTypeUInt8      = 4, ///< unsigned char
    KCEncodingTypeInt16      = 5, ///< short
    KCEncodingTypeUInt16     = 6, ///< unsigned short
    KCEncodingTypeInt32      = 7, ///< int
    KCEncodingTypeUInt32     = 8, ///< unsigned int
    KCEncodingTypeInt64      = 9, ///< long long
    KCEncodingTypeUInt64     = 10, ///< unsigned long long
    KCEncodingTypeFloat      = 11, ///< float
    KCEncodingTypeDouble     = 12, ///< double
    KCEncodingTypeLongDouble = 13, ///< long double
    KCEncodingTypeObject     = 14, ///< id
    KCEncodingTypeClass      = 15, ///< Class
    KCEncodingTypeSEL        = 16, ///< SEL
    KCEncodingTypeBlock      = 17, ///< block
    KCEncodingTypePointer    = 18, ///< void*
    KCEncodingTypeStruct     = 19, ///< struct
    KCEncodingTypeUnion      = 20, ///< union
    KCEncodingTypeCString    = 21, ///< char*
    KCEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    KCEncodingTypeQualifierMask   = 0xFE0,  ///< mask of qualifier
    KCEncodingTypeQualifierConst  = 1 << 5, ///< const
    KCEncodingTypeQualifierIn     = 1 << 6, ///< in
    KCEncodingTypeQualifierInout  = 1 << 7, ///< inout
    KCEncodingTypeQualifierOut    = 1 << 8, ///< out
    KCEncodingTypeQualifierBycopy = 1 << 9, ///< bycopy
    KCEncodingTypeQualifierByref  = 1 << 10, ///< byref
    KCEncodingTypeQualifierOneway = 1 << 11, ///< oneway
    
    KCEncodingTypePropertyMask         = 0x1FF000, ///< mask of property
    KCEncodingTypePropertyReadonly     = 1 << 12, ///< readonly
    KCEncodingTypePropertyCopy         = 1 << 13, ///< copy
    KCEncodingTypePropertyRetain       = 1 << 14, ///< retain
    KCEncodingTypePropertyNonatomic    = 1 << 15, ///< nonatomic
    KCEncodingTypePropertyWeak         = 1 << 16, ///< weak
    KCEncodingTypePropertyCustomGetter = 1 << 17, ///< getter=
    KCEncodingTypePropertyCustomSetter = 1 << 18, ///< setter=
    KCEncodingTypePropertyDynamic      = 1 << 19, ///< @dynamic
    KCEncodingTypePropertyGarbage      = 1 << 20,
    
};


KCEncodingType KCEncodingGetType(const char *typeEncoding);


@interface KCClassIvarInfo : NSObject

@property (nonatomic,assign,readonly)Ivar ivar;
@property (nonatomic,strong,readonly)NSString *name;
@property (nonatomic,assign,readonly)ptrdiff_t offset;
@property (nonatomic,strong,readonly)NSString *typeEncoding;
@property (nonatomic,assign,readonly)KCEncodingType type;
- (instancetype)initWithIvar:(Ivar)ivar;

@end


@interface KCClassMethodInfo : NSObject

@property (nonatomic,assign,readonly)Method method;
@property (nonatomic,strong,readonly)NSString *name;
@property (nonatomic,assign,readonly)SEL sel;
@property (nonatomic,assign,readonly)IMP imp;
@property (nonatomic,strong,readonly)NSString *typeEncoding;
@property (nonatomic,strong,readonly)NSString *returnTypeEncoding;
@property (nonatomic,strong,readonly)NSArray *argumentTypeEncodings;
- (instancetype)initWithMethod:(Method)method;

@end


@interface KCClassPropertyInfo : NSObject

@property (nonatomic, assign, readonly) objc_property_t property;
@property (nonatomic, strong, readonly) NSString *name; ///< property's name
@property (nonatomic, assign, readonly) KCEncodingType type; ///< property's type
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< property's encoding value
@property (nonatomic, strong, readonly) NSString *ivarName; ///< property's ivar name
@property (nonatomic, assign, readonly) Class cls; ///< may be nil
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *protocols; ///< may nil
@property (nonatomic, assign, readonly) SEL getter; ///< getter (nonnull)
@property (nonatomic, assign, readonly) SEL setter; ///< setter (nonnull)
- (instancetype)initWithProperty:(objc_property_t)property;

@end






@interface KCClassInfo : NSObject

@property (nonatomic, assign, readonly) Class cls; ///< class object
@property (nullable, nonatomic, assign, readonly) Class superCls; ///< super class object
@property (nullable, nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object
@property (nonatomic, readonly) BOOL isMeta; ///< whether this class is meta class
@property (nonatomic, strong, readonly) NSString *name; ///< class name
@property (nullable, nonatomic, strong, readonly) KCClassInfo *superClassInfo; ///< super class's class info
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, KCClassIvarInfo *> *ivarInfos; ///< ivars
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, KCClassMethodInfo *> *methodInfos; ///< methods
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, KCClassPropertyInfo *> *propertyInfos; ///< properties


/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, you may call 'classInfoWithClass' or
 'classInfoWithClassName' to get the updated class info.
 */
- (void)setNeedUpdate;

- (BOOL)needUpdate;


/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClassName:(NSString *)className;





@end












































