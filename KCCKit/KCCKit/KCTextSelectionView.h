//
//  KCTextSelectionView.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCTextAttribute.h"
#import "KCTextInput.h"

@interface KCSelectionGrabberDot : UIView
/// Dont't access this property. It was used by `KCTextEffectWindow`.
@property (nonatomic, strong) UIView *mirror;
@end
@interface KCSelectionGrabber : UIView


@property (nonatomic, readonly) KCSelectionGrabberDot *dot; ///< the dot view
@property (nonatomic, assign) KCTextDirection dotDirection; ///< don't support composite direction
@property (nonatomic, strong) UIColor *color; ///< tint color, default is nil
@end




@interface KCTextSelectionView : UIView

@property (nonatomic, weak) UIView *hostView; ///< the holder view
@property (nonatomic, strong) UIColor *color; ///< the tint color
@property (nonatomic, assign, getter = isCaretBlinks) BOOL caretBlinks; ///< whether the caret is blinks
@property (nonatomic, assign, getter = isCaretVisible) BOOL caretVisible; ///< whether the caret is visible
@property (nonatomic, assign, getter = isVerticalForm) BOOL verticalForm; ///< weather the text view is vertical form

@property (nonatomic, assign) CGRect caretRect; ///< caret rect (width==0 or height==0)
@property (nonatomic, copy) NSArray *selectionRects; ///<  array of KCTextSelectionRect, default is nil

@property (nonatomic, readonly) UIView *caretView;
@property (nonatomic, readonly) KCSelectionGrabber *startGrabber;
@property (nonatomic, readonly) KCSelectionGrabber *endGrabber;

- (BOOL)isGrabberContainsPoint:(CGPoint)point;
- (BOOL)isStartGrabberContainsPoint:(CGPoint)point;
- (BOOL)isEndGrabberContainsPoint:(CGPoint)point;
- (BOOL)isCaretContainsPoint:(CGPoint)point;
- (BOOL)isSelectionRectsContainsPoint:(CGPoint)point;


@end
