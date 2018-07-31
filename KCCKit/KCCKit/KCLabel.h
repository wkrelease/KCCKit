//
//  KCLabel.h
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCTextParser.h"
#import "KCTextLayout.h"
#import "KCTextAttribute.h"

@interface KCLabel : UIView<NSCoding>

@property (nonatomic, copy) NSString *text;

@property (nonatomic, retain) UIFont *font;

@property (nonatomic, retain) UIColor *textColor;

@property (nonatomic, retain) UIColor *shadowColor;

@property (nonatomic, assign) CGSize shadowOffset;

@property (nonatomic, assign) CGFloat shadowBlurRadius;

@property (nonatomic, assign) NSTextAlignment textAlignment;

@property (nonatomic, assign) KCTextVerticalAlignment textVerticalAlignment;

@property (nonatomic, copy) NSAttributedString *attributedText;

@property (nonatomic, assign) NSLineBreakMode lineBreakMode;

@property (nonatomic, copy) NSAttributedString *truncationToken;

@property (nonatomic, assign) NSUInteger numberOfLines;

@property (nonatomic, strong) id<KCTextParser> textParser;

@property (nonatomic, strong) KCTextLayout *textLayout;


#pragma mark - Configuring the Text Container


@property (nonatomic, copy) UIBezierPath *textContainerPath;

@property (nonatomic, copy) NSArray *exclusionPaths;

@property (nonatomic, assign) UIEdgeInsets textContainerInset;

@property (nonatomic, assign, getter=isVerticalForm) BOOL verticalForm;

@property (nonatomic, copy) id<KCTextLinePositionModifier> linePositionModifier;

@property (nonatomic, copy) KCTextDebugOption *debugOption;


#pragma mark - Interacting with Text Data

@property (nonatomic, copy) KCTextAction highlightTapAction;

@property (nonatomic, copy) KCTextAction highlightLongPressAction;



#pragma mark - Configuring the Display Mode

@property (nonatomic, assign) BOOL displaysAsynchronously;

@property (nonatomic, assign) BOOL clearContentsBeforeAsynchronouslyDisplay;

@property (nonatomic, assign) BOOL fadeOnAsynchronouslyDisplay;

@property (nonatomic, assign) BOOL fadeOnHighlight;

@property (nonatomic, assign) BOOL ignoreCommonProperties;





/*
 Tips:
 
 1. If you only need a UILabel alternative to display rich text and receive link touch event,
 you do not need to adjust the display mode properties.
 
 2. If you have performance issues, you may enable the asynchronous display mode
 by setting the `displaysAsynchronously` to YES.
 
 3. If you want to get the highest performance, you should do text layout with
 `YYTextLayout` class in background thread. Here's an example:
 
 YYLabel *label = [YYLabel new];
 label.displaysAsynchronously = YES;
 label.ignoreCommonProperties = YES;
 
 dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
 
 // Create attributed string.
 NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Some Text"];
 text.font = [UIFont systemFontOfSize:16];
 text.color = [UIColor grayColor];
 [text setColor:[UIColor redColor] range:NSMakeRange(0, 4)];
 
 // Create text container
 YYTextContainer *container = [YYTextContainer new];
 container.size = CGSizeMake(100, CGFLOAT_MAX);
 container.maximumNumberOfRows = 0;
 
 // Generate a text layout.
 YYTextLayout *layout = [YYTextLayout layoutWithContainer:container text:text];
 
 dispatch_async(dispatch_get_main_queue(), ^{
 label.size = layout.textBoundingSize;
 label.textLayout = layout;
 });
 });
 
 */









@end
