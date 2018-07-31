//
//  NSKeyedUnarchiver+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSKeyedUnarchiver (KCAdd)

+ (id)unarchiveObjectWithData:(NSData *)data exception:(__autoreleasing NSException **)exception;

+ (id)unarchiveObjectWithFile:(NSString *)path exception:(__autoreleasing NSException **)exception;


@end
