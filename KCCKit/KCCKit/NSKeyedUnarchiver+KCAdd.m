//
//  NSKeyedUnarchiver+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "NSKeyedUnarchiver+KCAdd.h"

#import "KCKitMacro.h"

KCSYNTH_DUMMY_CLASS(NSKeyedUnarchiver_KCAdd)

@implementation NSKeyedUnarchiver (KCAdd)


+ (id)unarchiveObjectWithData:(NSData *)data exception:(__autoreleasing NSException **)exception {
    id object = nil;
    @try {
        object = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    }
    @catch (NSException *e)
    {
        if (exception) *exception = e;
    }
    @finally
    {
    }
    return object;
}

+ (id)unarchiveObjectWithFile:(NSString *)path exception:(__autoreleasing NSException **)exception {
    id object = nil;
    
    @try {
        object = [NSKeyedUnarchiver unarchiveObjectWithFile:path];
    }
    @catch (NSException *e)
    {
        if (exception) *exception = e;
    }
    @finally
    {
    }
    return object;
}


@end
