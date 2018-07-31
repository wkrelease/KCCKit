//
//  KCTextView.h
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "KCTextParser.h"
#import "KCTextLayout.h"
#import "KCTextAttribute.h"

@class KCTextView;

@protocol KCTextViewDelegate <NSObject, UIScrollViewDelegate>
@optional
- (BOOL)textViewShouldBeginEditing:(KCTextView *)textView;
- (BOOL)textViewShouldEndEditing:(KCTextView *)textView;
- (void)textViewDidBeginEditing:(KCTextView *)textView;
- (void)textViewDidEndEditing:(KCTextView *)textView;
- (BOOL)textView:(KCTextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(KCTextView *)textView;
- (void)textViewDidChangeSelection:(KCTextView *)textView;

- (BOOL)textView:(KCTextView *)textView shouldTapHighlight:(KCTextHighlight *)highlight inRange:(NSRange)characterRange;
- (void)textView:(KCTextView *)textView didTapHighlight:(KCTextHighlight *)highlight inRange:(NSRange)characterRange rect:(CGRect)rect;
- (BOOL)textView:(KCTextView *)textView shouldLongPressHighlight:(KCTextHighlight *)highlight inRange:(NSRange)characterRange;
- (void)textView:(KCTextView *)textView didLongPressHighlight:(KCTextHighlight *)highlight inRange:(NSRange)characterRange rect:(CGRect)rect;
@end




@interface KCTextView : UIScrollView<UITextInput>


#pragma mark - Accessing the Delegate

@property (nonatomic, weak) id<KCTextViewDelegate> delegate;

@property (nonatomic, copy) NSString *text;

@property (nonatomic, strong) UIFont *font;

@property (nonatomic, strong) UIColor *textColor;

@property (nonatomic, assign) NSTextAlignment textAlignment;

@property (nonatomic, assign) KCTextVerticalAlignment textVerticalAlignment;

@property (nonatomic, assign) UIDataDetectorTypes dataDetectorTypes;

@property (nonatomic, copy) NSDictionary *linkTextAttributes;

@property (nonatomic, copy) NSDictionary *highlightTextAttributes;

@property (nonatomic, copy) NSDictionary *typingAttributes;

@property (nonatomic, copy) NSAttributedString *attributedText;

@property (nonatomic, strong) id<KCTextParser> textParser;

@property (nonatomic, strong, readonly) KCTextLayout *textLayout;


#pragma mark - Configuring the Placeholder

@property (nonatomic, copy) NSString *placeholderText;

@property (nonatomic, strong) UIFont *placeholderFont;

@property (nonatomic, strong) UIColor *placeholderTextColor;

@property (nonatomic, copy) NSAttributedString *placeholderAttributedText;

#pragma mark - Configuring the Text Container

@property (nonatomic, assign) UIEdgeInsets textContainerInset;

@property (nonatomic, copy) NSArray *exclusionPaths;

@property (nonatomic, assign, getter=isVerticalForm) BOOL verticalForm;

@property (nonatomic, copy) id<KCTextLinePositionModifier> linePositionModifier;

@property (nonatomic, copy) KCTextDebugOption *debugOption;

#pragma mark - Working with the Selection and Menu

- (void)scrollRangeToVisible:(NSRange)range;

@property (nonatomic, assign) NSRange selectedRange;

@property (nonatomic, assign) BOOL clearsOnInsertion;

@property (nonatomic, getter=isSelectable) BOOL selectable;

@property (nonatomic, getter=isHighlightable) BOOL highlightable;

@property (nonatomic, getter=isEditable) BOOL editable;

@property (nonatomic, assign) BOOL allowsPasteImage;

@property (nonatomic, assign) BOOL allowsPasteAttributedString;

@property (nonatomic, assign) BOOL allowsCopyAttributedString;


#pragma mark - Manage the undo and redo

@property (nonatomic, assign) BOOL allowsUndoAndRedo;

@property (nonatomic, assign) NSUInteger maximumUndoLevel;

#pragma mark - Replacing the System Input Views

@property (readwrite, retain) UIView *inputView;

@property (readwrite, retain) UIView *inputAccessoryView;

@property (nonatomic, assign) CGFloat extraAccessoryViewHeight;



@end




// Notifications, see UITextView's documentation for more information.
UIKIT_EXTERN NSString *const KCTextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSString *const KCTextViewTextDidChangeNotification;
UIKIT_EXTERN NSString *const KCTextViewTextDidEndEditingNotification;





