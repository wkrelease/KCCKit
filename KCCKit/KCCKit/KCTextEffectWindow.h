//
//  KCTextEffectWindow.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCTextMagnifier.h"
#import "KCTextSelectionView.h"

@interface KCTextEffectWindow : UIWindow

+ (instancetype)sharedWindow;

/// Show the magnifier in this window with a 'popup' animation. @param mag A magnifier.
- (void)showMagnifier:(KCTextMagnifier *)mag;
/// Update the magnifier content and position. @param mag A magnifier.
- (void)moveMagnifier:(KCTextMagnifier *)mag;
/// Remove the magnifier from this window with a 'shrink' animation. @param mag A magnifier.
- (void)hideMagnifier:(KCTextMagnifier *)mag;


/// Show the selection dot in this window if the dot is clipped by the selection view.
/// @param selection A selection view.
- (void)showSelectionDot:(KCTextSelectionView *)selection;
/// Remove the selection dot from this window.
/// @param selection A selection view.
- (void)hideSelectionDot:(KCTextSelectionView *)selection;




- (CGFloat)_updateMagnifier:(KCTextMagnifier *)mag;


@end
