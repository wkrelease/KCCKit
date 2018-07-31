//
//  UIPasteboard+KCText.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

UIKIT_EXTERN NSString *const KCPasteboardTypeAttributedString;
UIKIT_EXTERN NSString *const KCUTTypeWEBP;


@interface UIPasteboard (KCText)

@property (nonatomic, copy) NSData *PNGData;    ///< PNG file data
@property (nonatomic, copy) NSData *JPEGData;   ///< JPEG file data
@property (nonatomic, copy) NSData *GIFData;    ///< GIF file data
@property (nonatomic, copy) NSData *WEBPData;   ///< WebP file data
@property (nonatomic, copy) NSData *imageData;  ///< image file data
@property (nonatomic, copy) NSAttributedString *attributedString;


@end
