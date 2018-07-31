//
//  KCTextMagnifier.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCTextAttribute.h"

typedef NS_ENUM(NSUInteger,KCTextMagnifierType){
    KCTextMagnifierTypeCaret,
    KCTextMagnifierTypeRanged,
};



@interface KCTextMagnifier : UIView

+ (id)magnifierWithType:(KCTextMagnifierType)type;

@property (nonatomic, readonly) KCTextMagnifierType type; ///< Type of magnifier
@property (nonatomic, readonly) CGSize fitSize;           ///< The 'best' size for magnifier view.
@property (nonatomic, readonly) CGSize snapshotSize;      ///< The 'best' snapshot image size for magnifier.
@property (nonatomic, strong) UIImage *snapshot;          ///< The image in magnifier (readwrite).

@property (nonatomic, weak) UIView *hostView;             ///< The coordinate based view.
@property (nonatomic, assign) CGPoint hostCaptureCenter;  ///< The snapshot capture center in `hostView`.
@property (nonatomic, assign) CGPoint hostPopoverCenter;  ///< The popover center in `hostView`.
@property (nonatomic, assign) BOOL hostVerticalForm;      ///< The host view is vertical form.
@property (nonatomic, assign) BOOL captureDisabled;       ///< A hint for `YYTextEffectWindow` to disable capture.
@property (nonatomic, assign) BOOL captureFadeAnimation;  ///< Show fade animation when the snapshot image changed.



@end
