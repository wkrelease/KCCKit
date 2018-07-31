//
//  KCDispatchQueuePool.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef KCDispatchQueuePool_h
#define KCDispatchQueuePool_h

/**X
 A dispatch queue pool holds multiple serial queues.
 Use this class to control queue's thread count (instead of concurrent queue).
 */
@interface KCDispatchQueuePool : NSObject
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

/**
 Creates and returns a dispatch queue pool.
 @param name       The name of the pool.
 @param queueCount Maxmium queue count, should in range (1, 32).
 @param qos        Queue quality of service (QOS).
 @return A new pool, or nil if an error occurs.
 */
- (instancetype)initWithName:(NSString *)name queueCount:(NSUInteger)queueCount qos:(NSQualityOfService)qos;

/// Pool's name.
@property (nonatomic, readonly) NSString *name;

/// Get a serial queue from pool.
- (dispatch_queue_t)queue;

+ (instancetype)defaultPoolForQOS:(NSQualityOfService)qos;

@end

/// Get a serial queue from global queue pool with a specified qos.
extern dispatch_queue_t KCDispatchQueueGetForQOS(NSQualityOfService qos);

#endif

