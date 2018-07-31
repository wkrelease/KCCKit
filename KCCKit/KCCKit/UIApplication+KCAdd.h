//
//  UIApplication+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIApplication (KCAdd)

@property (nonatomic,readonly)NSURL *documentsURL;
@property (nonatomic,readonly)NSString *documentsPath;

@property (nonatomic,readonly)NSURL *cachesURL;
@property (nonatomic,readonly)NSString *cachesPath;

@property (nonatomic,readonly)NSURL *libraryURL;
@property (nonatomic,readonly)NSString *libraryPath;

@property (nonatomic, readonly) NSString *appBundleName;

@property (nonatomic,readonly)NSString *appBundleID;

@property (nonatomic,readonly)NSString *appVersion;

@property (nonatomic,readonly)NSString *appBuildVersion;

//非 appstore
@property (nonatomic,readonly)BOOL isPirated;

@property (nonatomic,readonly)BOOL isBeingDebugged;

@property (nonatomic,readonly)int64_t memoryUsage;

@property (nonatomic,readonly)float cpuUsage;

- (void)incrementNetworkActivityCount;

- (void)decrementNetworkActivityCount;

+ (BOOL)isAppExtension;

+ (UIApplication *)sharedExtensionApplication;


@end
