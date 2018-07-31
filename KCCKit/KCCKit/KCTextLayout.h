//
//  KCTextLayout.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>
#import "KCTextDebugOption.h"
#import "KCTextLine.h"
#import "KCTextInput.h"

@protocol KCTextLinePositionModifier;
extern const CGSize KCTextContainerMaxSize;



@interface KCTextContainer : NSObject <NSCoding, NSCopying>

+ (instancetype)containerWithSize:(CGSize)size;
+ (instancetype)containerWithSize:(CGSize)size insets:(UIEdgeInsets)insets;
+ (instancetype)containerWithPath:(UIBezierPath *)path;
@property (assign) CGSize size;
@property (assign) UIEdgeInsets insets;
@property (copy) UIBezierPath *path;
@property (copy) NSArray *exclusionPaths;
@property (assign) CGFloat pathLineWidth;
@property (assign, getter=isPathFillEvenOdd) BOOL pathFillEvenOdd;
@property (assign, getter=isVerticalForm) BOOL verticalForm;
@property (assign) NSUInteger maximumNumberOfRows;
@property (assign) KCTextTruncationType truncationType;
@property (copy) NSAttributedString *truncationToken;
@property (copy) id<KCTextLinePositionModifier> linePositionModifier;
@end


@protocol KCTextLinePositionModifier <NSObject, NSCopying>
@required
- (void)modifyLines:(NSArray *)lines fromText:(NSAttributedString *)text inContainer:(KCTextContainer *)container;
@end




@interface KCTextLinePositionSimpleModifier : NSObject <KCTextLinePositionModifier>
@property (assign) CGFloat fixedLineHeight; ///< The fixed line height (distance between two baseline).
@end





@interface KCTextLayout : NSObject


+ (KCTextLayout *)layoutWithContainerSize:(CGSize)size text:(NSAttributedString *)text;
+ (KCTextLayout *)layoutWithContainer:(KCTextContainer *)container text:(NSAttributedString *)text;
+ (KCTextLayout *)layoutWithContainer:(KCTextContainer *)container text:(NSAttributedString *)text range:(NSRange)range;
+ (NSArray *)layoutWithContainers:(NSArray *)containers text:(NSAttributedString *)text;
+ (NSArray *)layoutWithContainers:(NSArray *)containers text:(NSAttributedString *)text range:(NSRange)range;
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;
#pragma mark - Text layout attributes

@property (nonatomic, readonly) KCTextContainer *container;    ///< The text contaner
@property (nonatomic, readonly) NSAttributedString *text;      ///< The full text
@property (nonatomic, readonly) CTFramesetterRef frameSetter;  ///< CTFrameSetter
@property (nonatomic, readonly) CTFrameRef frame;              ///< CTFrame
@property (nonatomic, readonly) NSArray *lines;                ///< Array of `KCTextLine`, no truncated
@property (nonatomic, readonly) KCTextLine *truncatedLine;     ///< KCTextLine with truncated token, or nil
@property (nonatomic, readonly) NSArray *attachments;          ///< Array of `KCTextAttachment`
@property (nonatomic, readonly) NSArray *attachmentRanges;     ///< Array of NSRange(wrapped by NSValue) in text
@property (nonatomic, readonly) NSArray *attachmentRects;      ///< Array of CGRect(wrapped by NSValue) in container
@property (nonatomic, readonly) NSSet *attachmentContentsSet;  ///< Set of Attachment (UIImage/UIView/CALayer)
@property (nonatomic, readonly) NSUInteger rowCount;           ///< Number of rows
@property (nonatomic, readonly) NSRange visibleRange;          ///< Visible text range
@property (nonatomic, readonly) CGRect textBoundingRect;       ///< Text bounding rect (only contains text glyph)
@property (nonatomic, readonly) CGSize textBoundingSize;       ///< Text bounding size (encompasses all text and insets)
@property (nonatomic, readonly) BOOL containsHighlight;        ///< Has highlight attribute
@property (nonatomic, readonly) BOOL needDrawBlockBorder;      ///< Has block border attribute
@property (nonatomic, readonly) BOOL needDrawBackgroundBorder; ///< Has background border attribute
@property (nonatomic, readonly) BOOL needDrawShadow;           ///< Has shadow attribute
@property (nonatomic, readonly) BOOL needDrawUnderline;        ///< Has underline attribute
@property (nonatomic, readonly) BOOL needDrawText;             ///< Has visible text
@property (nonatomic, readonly) BOOL needDrawAttachment;       ///< Has attachment attribute
@property (nonatomic, readonly) BOOL needDrawInnerShadow;      ///< Has inner shadow attribute
@property (nonatomic, readonly) BOOL needDrawStrikethrough;    ///< Has strickthrough attribute
@property (nonatomic, readonly) BOOL needDrawBorder;

#pragma mark - Query information from text layout
- (NSUInteger)lineIndexForRow:(NSUInteger)row;
- (NSUInteger)lineCountForRow:(NSUInteger)row;
- (NSUInteger)rowIndexForLine:(NSUInteger)line;
- (NSUInteger)lineIndexForPoint:(CGPoint)point;
- (NSUInteger)closestLineIndexForPoint:(CGPoint)point;
- (CGFloat)offsetForTextPosition:(NSUInteger)position lineIndex:(NSUInteger)lineIndex;
- (NSUInteger)textPositionForPoint:(CGPoint)point lineIndex:(NSUInteger)lineIndex;
- (KCTextPosition *)closestPositionToPoint:(CGPoint)point;
- (KCTextPosition *)positionForPoint:(CGPoint)point
                         oldPosition:(KCTextPosition *)oldPosition
                       otherPosition:(KCTextPosition *)otherPosition;
- (KCTextRange *)textRangeAtPoint:(CGPoint)point;
- (KCTextRange *)closestTextRangeAtPoint:(CGPoint)point;
- (KCTextRange *)textRangeByExtendingPosition:(KCTextPosition *)position;
- (KCTextRange *)textRangeByExtendingPosition:(KCTextPosition *)position
                                  inDirection:(UITextLayoutDirection)direction
                                       offset:(NSInteger)offset;
- (NSUInteger)lineIndexForPosition:(KCTextPosition *)position;
- (CGPoint)linePositionForPosition:(KCTextPosition *)position;
- (CGRect)caretRectForPosition:(KCTextPosition *)position;
- (CGRect)firstRectForRange:(KCTextRange *)range;
- (CGRect)rectForRange:(KCTextRange *)range;
- (NSArray *)selectionRectsForRange:(KCTextRange *)range;
- (NSArray *)selectionRectsWithoutStartAndEndForRange:(KCTextRange *)range;
- (NSArray *)selectionRectsWithOnlyStartAndEndForRange:(KCTextRange *)range;
#pragma mark - Draw text layout
- (void)drawInContext:(CGContextRef)context
                 size:(CGSize)size
                point:(CGPoint)point
                 view:(UIView *)view
                layer:(CALayer *)layer
                debug:(KCTextDebugOption *)debug
               cancel:(BOOL (^)(void))cancel;
- (void)drawInContext:(CGContextRef)context size:(CGSize)size debug:(KCTextDebugOption *)debug;
- (void)addAttachmentToView:(UIView *)view layer:(CALayer *)layer;
- (void)removeAttachmentFromViewAndLayer;


@end
