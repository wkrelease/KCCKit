//
//  KCReachability.h
//  Jade
//
//  Created by king on 16/5/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <netinet/in.h>
@import Foundation;
@import SystemConfiguration;

typedef NS_ENUM(NSUInteger,KCReachabilityStates){
    KCReachabilityStatesNone,
    KCReachabilityStatesWWAN,
    KCReachabilityStatesWIFI,
};

typedef NS_ENUM(NSUInteger,KCReachabilityWWANStates){
    KCReachabilityWWANStatesNone,
    KCReachabilityWWANStates2G,
    KCReachabilityWWANStates3G,
    KCReachabilityWWANStates4G,
};


@interface KCReachability : NSObject

@property (nonatomic, assign, readonly) SCNetworkReachabilityFlags flags;                           ///< Current flags.
@property (nonatomic, assign, readonly) KCReachabilityStates status;                                ///< Current status.
@property (nonatomic, assign, readonly) KCReachabilityWWANStates wwanStatus NS_AVAILABLE_IOS(7_0);  ///< Current WWAN status.
@property (nonatomic, assign, readonly, getter=isReachable) BOOL reachable;
@property (nonatomic, copy) void (^notifyBlock)(KCReachability *reachability);

+ (instancetype)reachability;
+ (instancetype)reachabilityForLocalWifi;
+ (instancetype)reachabilityWithHostname:(NSString *)hostname;
+ (instancetype)reachabilityWithAddress:(const struct sockaddr_in *)hostAddress;

- (BOOL)startNotifier;
- (void)stopNotifier ;

@end
