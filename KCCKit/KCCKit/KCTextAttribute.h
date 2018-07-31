//
//  KCTextAttribute.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

#pragma mark - Enum Define

/// The attribute type
typedef NS_OPTIONS(NSInteger, KCTextAttributeType) {
    KCTextAttributeTypeNone     = 0,
    KCTextAttributeTypeUIKit    = 1 << 0, ///< UIKit attributes, such as UILabel/UITextField/drawInRect.
    KCTextAttributeTypeCoreText = 1 << 1, ///< CoreText attributes, used by CoreText.
    KCTextAttributeTypeKCText   = 1 << 2, ///< KCText attributes, used by KCText.
};

/// Get the attribute type from an attribute name.
extern KCTextAttributeType KCTextAttributeGetType(NSString *attributeName);

/**
 Line style in KCText (similar to NSUnderlineStyle).
 */
typedef NS_OPTIONS (NSInteger, KCTextLineStyle) {
    // basic style (bitmask:0xFF)
    KCTextLineStyleNone       = 0x00, ///< (        ) Do not draw a line (Default).
    KCTextLineStyleSingle     = 0x01, ///< (──────) Draw a single line.
    KCTextLineStyleThick      = 0x02, ///< (━━━━━━━) Draw a thick line.
    KCTextLineStyleDouble     = 0x09, ///< (══════) Draw a double line.
    
    // style pattern (bitmask:0xF00)
    KCTextLineStylePatternSolid      = 0x000, ///< (────────) Draw a solid line (Default).
    KCTextLineStylePatternDot        = 0x100, ///< (‑ ‑ ‑ ‑ ‑ ‑) Draw a line of dots.
    KCTextLineStylePatternDash       = 0x200, ///< (— — — —) Draw a line of dashes.
    KCTextLineStylePatternDashDot    = 0x300, ///< (— ‑ — ‑ — ‑) Draw a line of alternating dashes and dots.
    KCTextLineStylePatternDashDotDot = 0x400, ///< (— ‑ ‑ — ‑ ‑) Draw a line of alternating dashes and two dots.
    KCTextLineStylePatternCircleDot  = 0x900, ///< (••••••••••••) Draw a line of small circle dots.
};

/**
 Text vertical alignment.
 */
typedef NS_ENUM(NSInteger, KCTextVerticalAlignment) {
    KCTextVerticalAlignmentTop =    0, ///< Top alignment.
    KCTextVerticalAlignmentCenter = 1, ///< Center alignment.
    KCTextVerticalAlignmentBottom = 2, ///< Bottom alignment.
};

/**
 The direction define in KCText.
 */
typedef NS_OPTIONS(NSUInteger, KCTextDirection) {
    KCTextDirectionNone   = 0,
    KCTextDirectionTop    = 1 << 0,
    KCTextDirectionRight  = 1 << 1,
    KCTextDirectionBottom = 1 << 2,
    KCTextDirectionLeft   = 1 << 3,
};

/**
 The trunction type, tells the truncation engine which type of truncation is being requested.
 */
typedef NS_ENUM (NSUInteger, KCTextTruncationType) {
    /// No truncate.
    KCTextTruncationTypeNone   = 0,
    
    /// Truncate at the beginning of the line, leaving the end portion visible.
    KCTextTruncationTypeStart  = 1,
    
    /// Truncate at the end of the line, leaving the start portion visible.
    KCTextTruncationTypeEnd    = 2,
    
    /// Truncate in the middle of the line, leaving both the start and the end portions visible.
    KCTextTruncationTypeMiddle = 3,
};



#pragma mark - Attribute Name Defined in KCText

/// The value of this attribute is a `KCTextBackedString` object.
/// Use this attribute to store the original plain text if it is replaced by something else (such as attachment).
UIKIT_EXTERN NSString *const KCTextBackedStringAttributeName;

/// The value of this attribute is a `KCTextBinding` object.
/// Use this attribute to bind a range of text together, as if it was a single charactor.
UIKIT_EXTERN NSString *const KCTextBindingAttributeName;

/// The value of this attribute is a `KCTextShadow` object.
/// Use this attribute to add shadow to a range of text.
/// Shadow will be drawn below text glyphs. Use KCTextShadow.subShadow to add multi-shadow.
UIKIT_EXTERN NSString *const KCTextShadowAttributeName;

/// The value of this attribute is a `KCTextShadow` object.
/// Use this attribute to add inner shadow to a range of text.
/// Inner shadow will be drawn above text glyphs. Use KCTextShadow.subShadow to add multi-shadow.
UIKIT_EXTERN NSString *const KCTextInnerShadowAttributeName;

/// The value of this attribute is a `KCTextDecoration` object.
/// Use this attribute to add underline to a range of text.
/// The underline will be drawn below text glyphs.
UIKIT_EXTERN NSString *const KCTextUnderlineAttributeName;

/// The value of this attribute is a `KCTextDecoration` object.
/// Use this attribute to add strikethrough (delete line) to a range of text.
/// The strikethrough will be drawn above text glyphs.
UIKIT_EXTERN NSString *const KCTextStrikethroughAttributeName;

/// The value of this attribute is a `KCTextBorder` object.
/// Use this attribute to add cover border or cover color to a range of text.
/// The border will be drawn above the text glyphs.
UIKIT_EXTERN NSString *const KCTextBorderAttributeName;

/// The value of this attribute is a `KCTextBorder` object.
/// Use this attribute to add background border or background color to a range of text.
/// The border will be drawn below the text glyphs.
UIKIT_EXTERN NSString *const KCTextBackgroundBorderAttributeName;

/// The value of this attribute is a `KCTextBorder` object.
/// Use this attribute to add a code block border to one or more line of text.
/// The border will be drawn below the text glyphs.
UIKIT_EXTERN NSString *const KCTextBlockBorderAttributeName;

/// The value of this attribute is a `KCTextAttachment` object.
/// Use this attribute to add attachment to text.
/// It should be used in conjunction with a CTRunDelegate.
UIKIT_EXTERN NSString *const KCTextAttachmentAttributeName;

/// The value of this attribute is a `KCTextHighlight` object.
/// Use this attribute to add a touchable highlight state to a range of text.
UIKIT_EXTERN NSString *const KCTextHighlightAttributeName;

/// The value of this attribute is a `NSValue` object stores CGAffineTransform.
/// Use this attribute to add transform to each glyph in a range of text.
UIKIT_EXTERN NSString *const KCTextGlyphTransformAttributeName;



#pragma mark - String Token Define

UIKIT_EXTERN NSString *const KCTextAttachmentToken; ///< Object replacement character (U+FFFC), used for text attachment.
UIKIT_EXTERN NSString *const KCTextTruncationToken; ///< Horizontal ellipsis (U+2026), used for text truncation  "…".



#pragma mark - Attribute Value Define

/**
 The tap/long press action callback defined in KCText.
 
 @param containerView The text container view (such as YYLabel/KCTextView).
 @param text          The whole text.
 @param range         The text range in `text`.
 @param rect          The text frame in `containerView`.
 */
typedef void(^KCTextAction)(UIView *containerView, NSAttributedString *text, NSRange range, CGRect rect);


/**
 KCTextBackedString objects are used by the NSAttributedString class cluster
 as the values for text backed string attributes (stored in the attributed
 string under the key named KCTextBackedStringAttributeName).
 
 It may used for copy/paste plain text from attributed string.
 Example: If :) is replace by a custom emoji (such as😊), the backed string can be set to @":)".
 */
@interface KCTextBackedString : NSObject <NSCoding,NSCopying>
+ (instancetype)stringWithString:(NSString *)string;
@property (nonatomic, copy) NSString *string; ///< backed string
@end


/**
 KCTextBinding objects are used by the NSAttributedString class cluster
 as the values for shadow attributes (stored in the attributed string under
 the key named KCTextBindingAttributeName).
 
 Add this to a range of text will make the specified characters 'binding together'.
 KCTextView will treat the range of text as a single character during text
 selection and edit.
 */
@interface KCTextBinding : NSObject <NSCoding, NSCopying>
+ (instancetype)bindingWithDeleteConfirm:(BOOL)deleteConfirm;
@property (nonatomic, assign) BOOL deleteConfirm; ///< confirm the range when delete in KCTextView
@end


/**
 KCTextShadow objects are used by the NSAttributedString class cluster
 as the values for shadow attributes (stored in the attributed string under
 the key named KCTextShadowAttributeName or KCTextInnerShadowAttributeName).
 
 It's similar to `NSShadow`, but offers more options.
 */
@interface KCTextShadow : NSObject <NSCoding, NSCopying>
+ (instancetype)shadowWithColor:(UIColor *)color offset:(CGSize)offset radius:(CGFloat)radius;

@property (nonatomic, strong) UIColor *color;           ///< shadow color
@property (nonatomic, assign) CGSize offset;            ///< shadow offset
@property (nonatomic, assign) CGFloat radius;           ///< shadow blur radius
@property (nonatomic, assign) CGBlendMode blendMode;    ///< shadow blend mode
@property (nonatomic, strong) KCTextShadow *subShadow;  ///< a sub shadow which will be added above the parent shadow

+ (instancetype)shadowWithNSShadow:(NSShadow *)nsShadow; ///< convert NSShadow to KCTextShadow
- (NSShadow *)nsShadow; ///< convert KCTextShadow to NSShadow
@end


/**
 KCTextDecorationLine objects are used by the NSAttributedString class cluster
 as the values for decoration line attributes (stored in the attributed string under
 the key named KCTextUnderlineAttributeName or KCTextStrikethroughAttributeName).
 
 When it's used as underline, the line is drawn below text glyphs;
 when it's used as strikethrough, the line is drawn above text glyphs.
 */
@interface KCTextDecoration : NSObject <NSCoding, NSCopying>
+ (instancetype)decorationWithStyle:(KCTextLineStyle)style;
+ (instancetype)decorationWithStyle:(KCTextLineStyle)style width:(NSNumber *)width color:(UIColor *)color;
@property (nonatomic, assign) KCTextLineStyle style; ///< line style
@property (nonatomic, strong) NSNumber *width;       ///< line width (nil means automatic width)
@property (nonatomic, strong) UIColor *color;        ///< line color (nil means automatic color)
@property (nonatomic, strong) KCTextShadow *shadow;  ///< line shadow
@end


/**
 KCTextBorder objects are used by the NSAttributedString class cluster
 as the values for border attributes (stored in the attributed string under
 the key named KCTextBorderAttributeName or KCTextBackgroundBorderAttributeName).
 
 It can be used to draw a border around a range of text, or draw a background
 to a range of text.
 
 Example:
 ╭──────╮
 │ Text │
 ╰──────╯
 */
@interface KCTextBorder : NSObject <NSCoding, NSCopying>
+ (instancetype)borderWithLineStyle:(KCTextLineStyle)lineStyle lineWidth:(CGFloat)width strokeColor:(UIColor *)color;
+ (instancetype)borderWithFillColor:(UIColor *)color cornerRadius:(CGFloat)cornerRadius;
@property (nonatomic, assign) KCTextLineStyle lineStyle; ///< border line style
@property (nonatomic, assign) CGFloat strokeWidth;       ///< border line width
@property (nonatomic, strong) UIColor *strokeColor;      ///< border line color
@property (nonatomic, assign) CGLineJoin lineJoin;       ///< border line join
@property (nonatomic, assign) UIEdgeInsets insets;       ///< border insets for text bounds
@property (nonatomic, assign) CGFloat cornerRadius;      ///< border corder radius
@property (nonatomic, strong) KCTextShadow *shadow;      ///< border shadow
@property (nonatomic, strong) UIColor *fillColor;        ///< inner fill color
@end


/**
 KCTextAttachment objects are used by the NSAttributedString class cluster
 as the values for attachment attributes (stored in the attributed string under
 the key named KCTextAttachmentAttributeName).
 
 When display an attributed string which contains `KCTextAttachment` object,
 the content will be placed in text metric. If the content is `UIImage`,
 then it will be drawn to CGContext; if the content is `UIView` or `CALayer`,
 then it will be added to the text container's view or layer.
 */
@interface KCTextAttachment : NSObject<NSCoding, NSCopying>
+ (instancetype)attachmentWithContent:(id)content;
@property (nonatomic, strong) id content;                    ///< Supported type: UIImage, UIView, CALayer
@property (nonatomic, assign) UIViewContentMode contentMode; ///< Content display mode.
@property (nonatomic, assign) UIEdgeInsets contentInsets;    ///< The insets when drawing content.
@property (nonatomic, strong) NSDictionary *userInfo;        ///< The user information dictionary.
@end


/**
 KCTextHighlight objects are used by the NSAttributedString class cluster
 as the values for touchable highlight attributes (stored in the attributed string
 under the key named KCTextHighlightAttributeName).
 
 When display an attributed string in `YYLabel` or `KCTextView`, the range of
 highlight text can be toucheds down by users. If a range of text is turned into
 highlighted state, the `attributes` in `KCTextHighlight` will be used to modify
 (set or remove) the original attributes in the range for display.
 */
@interface KCTextHighlight : NSObject <NSCoding, NSCopying>
/**
 Attributes that you can apply to text in an attributed string when highlight.
 Key:   Same as CoreText/KCText Attribute Name.
 Value: Modify attribute value when highlight (NSNull for remove attribute).
 */
@property (nonatomic, copy) NSDictionary *attributes;

+ (instancetype)highlightWithAttributes:(NSDictionary *)attributes;

// Convenience methods below to set the `attributes`.
- (void)setFont:(UIFont *)font;
- (void)setColor:(UIColor *)color;
- (void)setStrokeWidth:(NSNumber *)width;
- (void)setStrokeColor:(UIColor *)color;
- (void)setShadow:(KCTextShadow *)shadow;
- (void)setInnerShadow:(KCTextShadow *)shadow;
- (void)setUnderline:(KCTextDecoration *)underline;
- (void)setStrikethrough:(KCTextDecoration *)strikethrough;
- (void)setBackgroundBorder:(KCTextBorder *)border;
- (void)setBorder:(KCTextBorder *)border;
- (void)setAttachment:(KCTextAttachment *)attachment;

/**
 The user information dictionary, default is nil.
 */
@property (nonatomic, copy) NSDictionary *userInfo;

/**
 Tap action when user tap the highlight, default is nil.
 If the value is nil, KCTextView or YYLabel will ask it's delegate to deal with tap action.
 */
@property (nonatomic, copy) KCTextAction tapAction;

/**
 Long press action when user long press the highlight, default is nil.
 If the value is nil, KCTextView or YYLabel will ask it's delegate to deal with long press action.
 */
@property (nonatomic, copy) KCTextAction longPressAction;

@end

