//
//  UIDevice+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIDevice (KCAdd)

#pragma mark - Device Information

+ (float)systemVersion;

@property (nonatomic,readonly)BOOL isPad;

@property (nonatomic,readonly)BOOL isSimulator;

@property (nonatomic,readonly) BOOL isJailbroken;

@property (nonatomic, readonly) BOOL canMakePhoneCalls NS_EXTENSION_UNAVAILABLE_IOS("");

@property (nonatomic, readonly) NSString *machineModel;

@property (nonatomic, readonly) NSString *machineModelName;

@property (nonatomic, readonly) NSDate *systemUptime;


#pragma mark - Network Information

@property (nonatomic, readonly) NSString *ipAddressWIFI;

@property (nonatomic, readonly) NSString *ipAddressCell;




/**
 Network traffic type:
 
 WWAN: Wireless Wide Area Network.
 For example: 3G/4G.
 
 WIFI: Wi-Fi.
 
 AWDL: Apple Wireless Direct Link (peer-to-peer connection).
 For exmaple: AirDrop, AirPlay, GameKit.
 */
typedef NS_OPTIONS(NSUInteger, KCNetworkTrafficType) {
    KCNetworkTrafficTypeWWANSent     = 1 << 0,
    KCNetworkTrafficTypeWWANReceived = 1 << 1,
    KCNetworkTrafficTypeWIFISent     = 1 << 2,
    KCNetworkTrafficTypeWIFIReceived = 1 << 3,
    KCNetworkTrafficTypeAWDLSent     = 1 << 4,
    KCNetworkTrafficTypeAWDLReceived = 1 << 5,
    
    KCNetworkTrafficTypeWWAN = KCNetworkTrafficTypeWWANSent | KCNetworkTrafficTypeWWANReceived,
    KCNetworkTrafficTypeWIFI = KCNetworkTrafficTypeWIFISent | KCNetworkTrafficTypeWIFIReceived,
    KCNetworkTrafficTypeAWDL = KCNetworkTrafficTypeAWDLSent | KCNetworkTrafficTypeAWDLReceived,
    
    KCNetworkTrafficTypeALL = KCNetworkTrafficTypeWWAN |
    KCNetworkTrafficTypeWIFI |
    KCNetworkTrafficTypeAWDL,
};

/**
 Get device network traffic bytes.
 
 @discussion This is a counter since the device's last boot time.
 Usage:
 
 uint64_t bytes = [[UIDevice currentDevice] getNetworkTrafficBytes:KCNetworkTrafficTypeALL];
 NSTimeInterval time = CACurrentMediaTime();
 
 uint64_t bytesPerSecond = (bytes - _lastBytes) / (time - _lastTime);
 
 _lastBytes = bytes;
 _lastTime = time;
 
 
 @param type traffic types
 @return bytes counter.
 */
- (uint64_t)getNetworkTrafficBytes:(KCNetworkTrafficType)types;


#pragma mark - Disk Space
///=============================================================================
/// @name Disk Space
///=============================================================================

/// Total disk space in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t diskSpace;

/// Free disk space in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t diskSpaceFree;

/// Used disk space in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t diskSpaceUsed;


#pragma mark - Memory Information
///=============================================================================
/// @name Memory Information
///=============================================================================

/// Total physical memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryTotal;

/// Used (active + inactive + wired) memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryUsed;

/// Free memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryFree;

/// Acvite memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryActive;

/// Inactive memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryInactive;

/// Wired memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryWired;

/// Purgable memory in byte. (-1 when error occurs)
@property (nonatomic, readonly) int64_t memoryPurgable;

#pragma mark - CPU Information
///=============================================================================
/// @name CPU Information
///=============================================================================

/// Avaliable CPU processor count.
@property (nonatomic, readonly) NSUInteger cpuCount;

/// Current CPU usage, 1.0 means 100%. (-1 when error occurs)
@property (nonatomic, readonly) float cpuUsage;

/// Current CPU usage per processor (array of NSNumber), 1.0 means 100%. (nil when error occurs)
@property (nonatomic, readonly) NSArray *cpuUsagePerProcessor;

@end


#ifndef kSystemVersion
#define kSystemVersion [UIDevice systemVersion]
#endif

#ifndef kiOS6Later
#define kiOS6Later (kSystemVersion >= 6)
#endif

#ifndef kiOS7Later
#define kiOS7Later (kSystemVersion >= 7)
#endif

#ifndef kiOS8Later
#define kiOS8Later (kSystemVersion >= 8)
#endif

#ifndef kiOS9Later
#define kiOS9Later (kSystemVersion >= 9)
#endif

