//
//  KCTextKeyboardManager.h
//  Jade
//
//  Created by king on 16/5/31.
//  Copyright © 2016年 KC. All rights reserved.
//


@import UIKit;

/**
 System keyboard transition information.
 Use -[YYTextKeyboardManager convertRect:toView:] to convert frame to specified view.
 */
typedef struct{
    BOOL fromVisible;
    BOOL toVisible;
    CGRect fromFrame;
    CGRect toFrame;
    NSTimeInterval animationDuration;
    UIViewAnimationCurve animationCurve;
    UIViewAnimationOptions animationOption;
}KCTextKeyboardTransition;

@protocol KCTextKeyboardObserver <NSObject>

@optional
- (void)keyboardChangedWithTransition:(KCTextKeyboardTransition)transition;
@end


@interface KCTextKeyboardManager : NSObject

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new  UNAVAILABLE_ATTRIBUTE;
+ (instancetype)defaultManager;
@property (nonatomic, readonly) UIWindow *keyboardWindow;
@property (nonatomic, readonly) UIView *keyboardView;
@property (nonatomic, readonly, getter=isKeyboardVisible) BOOL keyboardVisible;
@property (nonatomic, readonly) CGRect keyboardFrame;
- (void)addObserver:(id<KCTextKeyboardObserver>)observer;
- (void)removeObserver:(id<KCTextKeyboardObserver>)observer;
- (CGRect)convertRect:(CGRect)rect toView:(UIView *)view;


@end
