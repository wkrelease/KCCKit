//
//  KCTextContainerView.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCTextLayout.h"

@interface KCTextContainerView : UIView

@property (nonatomic, weak) UIView *hostView;

/// Debug option for layout debug. Set this property will let the view redraw it's contents.
@property (nonatomic, copy) KCTextDebugOption *debugOption;

/// Text vertical alignment.
@property (nonatomic, assign) KCTextVerticalAlignment textVerticalAlignment;

/// Text layout. Set this property will let the view redraw it's contents.
@property (nonatomic, strong) KCTextLayout *layout;

/// The contents fade animation duration when the layout's contents changed. Default is 0 (no animation).
@property (nonatomic, assign) NSTimeInterval contentsFadeDuration;

/// Convenience method to set `layout` and `contentsFadeDuration`.
/// @param layout  Same as `layout` property.
/// @param fadeDuration  Same as `contentsFadeDuration` property.
- (void)setLayout:(KCTextLayout *)layout withFadeDuration:(NSTimeInterval)fadeDuration;


@end
