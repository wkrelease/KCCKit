//
//  KCReachability.m
//  Jade
//
//  Created by king on 16/5/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "KCReachability.h"

#import <objc/message.h>

#import <CoreTelephony/CTTelephonyNetworkInfo.h>

static KCReachabilityStates KCReachabilityStatesFromFlags(SCNetworkReachabilityFlags flags,BOOL allowWWAN){
    if ((flags & kSCNetworkReachabilityFlagsReachable) == 0) {
        return KCReachabilityStatesNone;
    }
    
    if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) &&
        (flags & kSCNetworkReachabilityFlagsTransientConnection)) {
        return KCReachabilityStatesNone;
    }
    
    if ((flags & kSCNetworkReachabilityFlagsIsWWAN) && allowWWAN) {
        return KCReachabilityStatesWWAN;
    }
    
    return KCReachabilityStatesWIFI;
}

static void KCReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void *info) {
    KCReachability *self = ((__bridge KCReachability *)info);
    if (self.notifyBlock) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.notifyBlock(self);
        });
    }
}

@interface KCReachability ()

@property (nonatomic, assign) SCNetworkReachabilityRef ref;
@property (nonatomic, assign) BOOL scheduled;
@property (nonatomic, assign) BOOL allowWWAN;
@property (nonatomic, strong) CTTelephonyNetworkInfo *networkInfo;

@end

@implementation KCReachability

+ (dispatch_queue_t)shareQueueKC{
    
    static dispatch_queue_t queue;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        queue = dispatch_queue_create("com.kc.kckit.reachability", DISPATCH_QUEUE_SERIAL);
    });
    return queue;
    
}
- (instancetype)init {
    struct sockaddr_in zero_addr;
    bzero(&zero_addr, sizeof(zero_addr));
    zero_addr.sin_len = sizeof(zero_addr);
    zero_addr.sin_family = AF_INET;
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr *)&zero_addr);
    return [self initWithRef:ref];
}
- (instancetype)initWithRef:(SCNetworkReachabilityRef)ref {
    if (!ref) return nil;
    self = super.init;
    if (!self) return nil;
    _ref = ref;
    _allowWWAN = YES;
    if (NSFoundationVersionNumber >= NSFoundationVersionNumber_iOS_7_0) {
        _networkInfo = [CTTelephonyNetworkInfo new];
    }
    return self;
}
- (void)dealloc {
    self.notifyBlock = nil;
    self.scheduled = NO;
    CFRelease(self.ref);
}
- (void)setScheduled:(BOOL)scheduled {
    if (_scheduled == scheduled) return;
    _scheduled = scheduled;
    if (scheduled) {
        SCNetworkReachabilityContext context = { 0, (__bridge void *)self, NULL, NULL, NULL };
        SCNetworkReachabilitySetCallback(self.ref, KCReachabilityCallback, &context);
        SCNetworkReachabilitySetDispatchQueue(self.ref, [self.class shareQueueKC]);
    } else {
        SCNetworkReachabilitySetDispatchQueue(self.ref, NULL);
    }
}

- (SCNetworkReachabilityFlags)flags {
    SCNetworkReachabilityFlags flags = 0;
    SCNetworkReachabilityGetFlags(self.ref, &flags);
    return flags;
}
- (KCReachabilityStates)status {
    return KCReachabilityStatesFromFlags(self.flags, self.allowWWAN);
}
- (KCReachabilityWWANStates)wwanStatus {
    if (self.networkInfo) return KCReachabilityWWANStatesNone;
    NSString *status = self.networkInfo.currentRadioAccessTechnology;
    if (!status) return KCReachabilityWWANStatesNone;
    static NSDictionary *dic;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        dic = @{CTRadioAccessTechnologyGPRS : @(KCReachabilityWWANStates2G),  // 2.5G   171Kbps
                CTRadioAccessTechnologyEdge : @(KCReachabilityWWANStates2G),  // 2.75G  384Kbps
                CTRadioAccessTechnologyWCDMA : @(KCReachabilityWWANStates3G), // 3G     3.6Mbps/384Kbps
                CTRadioAccessTechnologyHSDPA : @(KCReachabilityWWANStates3G), // 3.5G   14.4Mbps/384Kbps
                CTRadioAccessTechnologyHSUPA : @(KCReachabilityWWANStates3G), // 3.75G  14.4Mbps/5.76Mbps
                CTRadioAccessTechnologyCDMA1x : @(KCReachabilityWWANStates3G), // 2.5G
                CTRadioAccessTechnologyCDMAEVDORev0 : @(KCReachabilityWWANStates3G),
                CTRadioAccessTechnologyCDMAEVDORevA : @(KCReachabilityWWANStates3G),
                CTRadioAccessTechnologyCDMAEVDORevB : @(KCReachabilityWWANStates3G),
                CTRadioAccessTechnologyeHRPD : @(KCReachabilityWWANStates3G),
                CTRadioAccessTechnologyLTE : @(KCReachabilityWWANStates4G)}; // LTE:3.9G 150M/75M  LTE-Advanced:4G 300M/150M
    });
    NSNumber *num = dic[status];
    if (num) return num.unsignedIntegerValue;
    else return KCReachabilityWWANStatesNone;
}

- (BOOL)isReachable {
    return self.status != KCReachabilityStatesNone;
}

+ (instancetype)reachability {
//    return self.new;
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithName(NULL, [@"www.baidu.com" UTF8String]);
    return [[self alloc] initWithRef:ref];
}

+ (instancetype)reachabilityForLocalWifi {
    struct sockaddr_in localWifiAddress;
    bzero(&localWifiAddress, sizeof(localWifiAddress));
    localWifiAddress.sin_len = sizeof(localWifiAddress);
    localWifiAddress.sin_family = AF_INET;
    localWifiAddress.sin_addr.s_addr = htonl(IN_LINKLOCALNETNUM);
    KCReachability *one = [self reachabilityWithAddress:&localWifiAddress];
    one.allowWWAN = NO;
    return one;
}
+ (instancetype)reachabilityWithHostname:(NSString *)hostname {
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithName(NULL, [hostname UTF8String]);
    return [[self alloc] initWithRef:ref];
}

+ (instancetype)reachabilityWithAddress:(const struct sockaddr_in *)hostAddress {
    SCNetworkReachabilityRef ref = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr *)hostAddress);
    return [[self alloc] initWithRef:ref];
}

- (void)setNotifyBlock:(void (^)(KCReachability *reachability))notifyBlock {
    _notifyBlock = [notifyBlock copy];
    self.scheduled = (self.notifyBlock != nil);
}


#pragma mark Notification Management Methods

static void ReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info) {
 
    @autoreleasepool {
        dispatch_async(dispatch_get_main_queue(), ^{

        });
    }
    
}
- (BOOL)startNotifier {
    
    SCNetworkReachabilityContext	context = {0, (__bridge void * _Nullable)(self), NULL, NULL, NULL};
    
    if(SCNetworkReachabilitySetCallback(_ref, ReachabilityCallback, &context)) {
        
        if(SCNetworkReachabilityScheduleWithRunLoop(_ref, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode)) {
            return YES;
        }
        
    }
    
    return NO;
    
}

- (void)stopNotifier {
    
    if(_ref) {
        SCNetworkReachabilityUnscheduleFromRunLoop(_ref, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    }
    
}




@end
