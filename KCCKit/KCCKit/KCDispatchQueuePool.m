//
//  KCDispatchQueuePool.m
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "KCDispatchQueuePool.h"
#import <libkern/OSAtomic.h>
@import UIKit;


#define MAX_QUEUE_COUNT 32

static inline dispatch_queue_priority_t NSQualityOfServiceToDispatchPriority(NSQualityOfService qos) {
    switch (qos) {
        case NSQualityOfServiceUserInteractive: return DISPATCH_QUEUE_PRIORITY_HIGH;
        case NSQualityOfServiceUserInitiated: return DISPATCH_QUEUE_PRIORITY_HIGH;
        case NSQualityOfServiceUtility: return DISPATCH_QUEUE_PRIORITY_LOW;
        case NSQualityOfServiceBackground: return DISPATCH_QUEUE_PRIORITY_BACKGROUND;
        case NSQualityOfServiceDefault: return DISPATCH_QUEUE_PRIORITY_DEFAULT;
        default: return DISPATCH_QUEUE_PRIORITY_DEFAULT;
    }
}

static inline qos_class_t NSQualityOfServiceToQOSClass(NSQualityOfService qos) {
    switch (qos) {
        case NSQualityOfServiceUserInteractive: return QOS_CLASS_USER_INTERACTIVE;
        case NSQualityOfServiceUserInitiated: return QOS_CLASS_USER_INITIATED;
        case NSQualityOfServiceUtility: return QOS_CLASS_USER_INITIATED;
        case NSQualityOfServiceBackground: return QOS_CLASS_BACKGROUND;
        case NSQualityOfServiceDefault: return QOS_CLASS_DEFAULT;
        default: return QOS_CLASS_UNSPECIFIED;
    }
}

typedef struct {
    const char *name;
    void **queues;
    uint32_t queueCount;
    int32_t counter;
} KCDispatchContext;

static KCDispatchContext *KCDispatchContextCreate(const char *name,
                                                  uint32_t queueCount,
                                                  NSQualityOfService qos) {
    KCDispatchContext *context = calloc(1, sizeof(KCDispatchContext));
    if (!context) return NULL;
    context->queues =  calloc(queueCount, sizeof(void *));
    if (!context->queues) {
        free(context);
        return NULL;
    }
    if ([UIDevice currentDevice].systemVersion.floatValue >= 8.0) {
        dispatch_qos_class_t qosClass = NSQualityOfServiceToQOSClass(qos);
        for (NSUInteger i = 0; i < queueCount; i++) {
            dispatch_queue_attr_t attr = dispatch_queue_attr_make_with_qos_class(DISPATCH_QUEUE_SERIAL, qosClass, 0);
            dispatch_queue_t queue = dispatch_queue_create(name, attr);
            context->queues[i] = (__bridge_retained void *)(queue);
        }
    } else {
        long identifier = NSQualityOfServiceToDispatchPriority(qos);
        for (NSUInteger i = 0; i < queueCount; i++) {
            dispatch_queue_t queue = dispatch_queue_create(name, DISPATCH_QUEUE_SERIAL);
            dispatch_set_target_queue(queue, dispatch_get_global_queue(identifier, 0));
            context->queues[i] = (__bridge_retained void *)(queue);
        }
    }
    context->queueCount = queueCount;
    if (name) {
        context->name = strdup(name);
    }
    return context;
}

static void KCDispatchContextRelease(KCDispatchContext *context) {
    if (!context) return;
    if (context->queues) {
        for (NSUInteger i = 0; i < context->queueCount; i++) {
            void *queuePointer = context->queues[i];
            dispatch_queue_t queue = (__bridge_transfer dispatch_queue_t)(queuePointer);
            const char *name = dispatch_queue_get_label(queue);
            if (name) strlen(name); // avoid compiler warning
            queue = nil;
        }
        free(context->queues);
        context->queues = NULL;
    }
    if (context->name) free((void *)context->name);
}

static dispatch_queue_t KCDispatchContextGetQueue(KCDispatchContext *context) {
    int32_t counter = OSAtomicIncrement32(&context->counter);
    if (counter < 0) counter = -counter;
    void *queue = context->queues[counter % context->queueCount];
    return (__bridge dispatch_queue_t)(queue);
}


static KCDispatchContext *KCDispatchContextGetForQOS(NSQualityOfService qos) {
    static KCDispatchContext *context[5] = {0};
    switch (qos) {
        case NSQualityOfServiceUserInteractive: {
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                int count = (int)[NSProcessInfo processInfo].activeProcessorCount;
                count = count < 1 ? 1 : count > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : count;
                context[0] = KCDispatchContextCreate("com.ibireme.kckit.user-interactive", count, qos);
            });
            return context[0];
        } break;
        case NSQualityOfServiceUserInitiated: {
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                int count = (int)[NSProcessInfo processInfo].activeProcessorCount;
                count = count < 1 ? 1 : count > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : count;
                context[1] = KCDispatchContextCreate("com.ibireme.kckit.user-initiated", count, qos);
            });
            return context[1];
        } break;
        case NSQualityOfServiceUtility: {
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                int count = (int)[NSProcessInfo processInfo].activeProcessorCount;
                count = count < 1 ? 1 : count > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : count;
                context[2] = KCDispatchContextCreate("com.ibireme.kckit.utility", count, qos);
            });
            return context[2];
        } break;
        case NSQualityOfServiceBackground: {
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                int count = (int)[NSProcessInfo processInfo].activeProcessorCount;
                count = count < 1 ? 1 : count > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : count;
                context[3] = KCDispatchContextCreate("com.ibireme.kckit.background", count, qos);
            });
            return context[3];
        } break;
        case NSQualityOfServiceDefault:
        default: {
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                int count = (int)[NSProcessInfo processInfo].activeProcessorCount;
                count = count < 1 ? 1 : count > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : count;
                context[4] = KCDispatchContextCreate("com.ibireme.kckit.default", count, qos);
            });
            return context[4];
        } break;
    }
}


@implementation KCDispatchQueuePool {
@public
    KCDispatchContext *_context;
}

- (void)dealloc {
    if (_context) {
        KCDispatchContextRelease(_context);
        _context = NULL;
    }
}

- (instancetype)initWithContext:(KCDispatchContext *)context {
    self = [super init];
    if (!context) return nil;
    self->_context = context;
    _name = context->name ? [NSString stringWithUTF8String:context->name] : nil;
    return self;
}

- (instancetype)initWithName:(NSString *)name queueCount:(NSUInteger)queueCount qos:(NSQualityOfService)qos {
    if (queueCount == 0 || queueCount > MAX_QUEUE_COUNT) return nil;
    self = [super init];
    _context = KCDispatchContextCreate(name.UTF8String, (uint32_t)queueCount, qos);
    if (!_context) return nil;
    _name = name;
    return self;
}

- (dispatch_queue_t)queue {
    return KCDispatchContextGetQueue(_context);
}

+ (instancetype)defaultPoolForQOS:(NSQualityOfService)qos {
    switch (qos) {
        case NSQualityOfServiceUserInteractive: {
            static KCDispatchQueuePool *pool;
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                pool = [[KCDispatchQueuePool alloc] initWithContext:KCDispatchContextGetForQOS(qos)];
            });
            return pool;
        } break;
        case NSQualityOfServiceUserInitiated: {
            static KCDispatchQueuePool *pool;
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                pool = [[KCDispatchQueuePool alloc] initWithContext:KCDispatchContextGetForQOS(qos)];
            });
            return pool;
        } break;
        case NSQualityOfServiceUtility: {
            static KCDispatchQueuePool *pool;
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                pool = [[KCDispatchQueuePool alloc] initWithContext:KCDispatchContextGetForQOS(qos)];
            });
            return pool;
        } break;
        case NSQualityOfServiceBackground: {
            static KCDispatchQueuePool *pool;
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                pool = [[KCDispatchQueuePool alloc] initWithContext:KCDispatchContextGetForQOS(qos)];
            });
            return pool;
        } break;
        case NSQualityOfServiceDefault:
        default: {
            static KCDispatchQueuePool *pool;
            static dispatch_once_t onceToken;
            dispatch_once(&onceToken, ^{
                pool = [[KCDispatchQueuePool alloc] initWithContext:KCDispatchContextGetForQOS(NSQualityOfServiceDefault)];
            });
            return pool;
        } break;
    }
}

@end

dispatch_queue_t KCDispatchQueueGetForQOS(NSQualityOfService qos) {
    return KCDispatchContextGetQueue(KCDispatchContextGetForQOS(qos));
}
