//
//  KCTextParser.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//


@protocol KCTextParser <NSObject>
@required
/**
 When text is changed in KCTextView or YYLabel, this method will be called.
 
 @param text  The original attributed string. This method may parse the text and
 change the text attributes or content.
 
 @param selectedRange  Current selected range in `text`.
 This method should correct the range if the text content is changed. If there's
 no selected range (such as YYLabel), this value is NULL.
 
 @return If the 'text' is modified in this method, returns `YES`, otherwise returns `NO`.
 */
- (BOOL)parseText:(NSMutableAttributedString *)text selectedRange:(NSRangePointer)selectedRange;
@end






@interface KCTextSimpleMarkdownParser : NSObject <KCTextParser>
@property (nonatomic, assign) CGFloat fontSize;         ///< default is 14
@property (nonatomic, assign) CGFloat headerFontSize;   ///< default is 20

@property (nonatomic, strong) UIColor *textColor;
@property (nonatomic, strong) UIColor *controlTextColor;
@property (nonatomic, strong) UIColor *headerTextColor;
@property (nonatomic, strong) UIColor *inlineTextColor;
@property (nonatomic, strong) UIColor *codeTextColor;
@property (nonatomic, strong) UIColor *linkTextColor;

- (void)setColorWithBrightTheme; ///< reset the color properties to pre-defined value.
- (void)setColorWithDarkTheme;   ///< reset the color properties to pre-defined value.
@end



/**
 A simple emoticon parser.
 
 Use this parser to map some specified piece of string to image emoticon.
 Example: "Hello :smile:"  ->  "Hello 😀"
 
 It can also be used to extend the "unicode emoticon".
 */
@interface KCTextSimpleEmoticonParser : NSObject <KCTextParser>

/**
 The custom emoticon mapper.
 The key is a specified plain string, such as @":smile:".
 The value is a UIImage which will replace the specified plain string in text.
 */
@property (copy) NSDictionary *emoticonMapper;
@end

