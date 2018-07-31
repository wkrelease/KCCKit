//
//  KCGestureRecognizer.h
//  Jade
//
//  Created by king on 16/5/16.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger,KCGestureRecognizerState){
    KCGestureRecognizerStateBegan, ///< gesture start
    KCGestureRecognizerStateMoved, ///< gesture moved
    KCGestureRecognizerStateEnded, ///< gesture end
    KCGestureRecognizerStateCancelled, ///< gesture cancel
};

@interface KCGestureRecognizer : UIGestureRecognizer

@property (nonatomic, readonly) CGPoint startPoint; ///< start point
@property (nonatomic, readonly) CGPoint lastPoint; ///< last move point.
@property (nonatomic, readonly) CGPoint currentPoint; ///< current move point.

@property (nonatomic, copy) void (^action)(KCGestureRecognizer *gesture, KCGestureRecognizerState state);

- (void)cancel;

@end
