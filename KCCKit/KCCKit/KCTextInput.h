//
//  KCTextInput.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//


#import <UIKit/UIKit.h>

/**
 Text position affinity. For example, the offset appears after the last
 character on a line is backward affinity, before the first character on
 the following line is forward affinity.
 */
typedef NS_ENUM(NSInteger, KCTextAffinity) {
    KCTextAffinityForward  = 0, ///< offset appears before the character
    KCTextAffinityBackward = 1, ///< offset appears after the character
};


/**
 A KCTextPosition object represents a position in a text container; in other words,
 it is an index into the backing string in a text-displaying view.
 
 KCTextPosition has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface KCTextPosition : UITextPosition <NSCopying>

@property (nonatomic, readonly) NSInteger offset;
@property (nonatomic, readonly) KCTextAffinity affinity;

+ (instancetype)positionWithOffset:(NSInteger)offset;
+ (instancetype)positionWithOffset:(NSInteger)offset affinity:(KCTextAffinity) affinity;

- (NSComparisonResult)compare:(id)otherPosition;

@end


/**
 A KCTextRange object represents a range of characters in a text container; in other words,
 it identifies a starting index and an ending index in string backing a text-displaying view.
 
 KCTextRange has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface KCTextRange : UITextRange <NSCopying>

@property (nonatomic, readonly) KCTextPosition *start;
@property (nonatomic, readonly) KCTextPosition *end;
@property (nonatomic, readonly, getter=isEmpty) BOOL empty;

+ (instancetype)rangeWithRange:(NSRange)range;
+ (instancetype)rangeWithRange:(NSRange)range affinity:(KCTextAffinity) affinity;
+ (instancetype)rangeWithStart:(KCTextPosition *)start end:(KCTextPosition *)end;
+ (instancetype)defaultRange; ///< <{0,0} Forward>

- (NSRange)asRange;

@end


/**
 A KCTextSelectionRect object encapsulates information about a selected range of
 text in a text-displaying view.
 
 KCTextSelectionRect has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface KCTextSelectionRect : UITextSelectionRect <NSCopying>

@property (nonatomic, readwrite) CGRect rect;
@property (nonatomic, readwrite) UITextWritingDirection writingDirection;
@property (nonatomic, readwrite) BOOL containsStart;
@property (nonatomic, readwrite) BOOL containsEnd;
@property (nonatomic, readwrite) BOOL isVertical;

@end