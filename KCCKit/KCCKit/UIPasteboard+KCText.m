//
//  UIPasteboard+KCText.m
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "UIPasteboard+KCText.h"
#import "KCKitMacro.h"
#import "KCImage.h"
#import "NSAttributedString+KCText.h"
#import <MobileCoreServices/MobileCoreServices.h>

KCSYNTH_DUMMY_CLASS(UIPasteboard_KCText)

NSString *const KCPasteboardTypeAttributedString = @"com.ibireme.NSAttributedString";
NSString *const KCUTTypeWEBP = @"com.google.webp";


@implementation UIPasteboard (KCText)


- (void)setPNGData:(NSData *)PNGData {
    [self setData:PNGData forPasteboardType:(id)kUTTypePNG];
}

- (NSData *)PNGData {
    return [self dataForPasteboardType:(id)kUTTypePNG];
}

- (void)setJPEGData:(NSData *)JPEGData {
    [self setData:JPEGData forPasteboardType:(id)kUTTypeJPEG];
}

- (NSData *)JPEGData {
    return [self dataForPasteboardType:(id)kUTTypeJPEG];
}

- (void)setGIFData:(NSData *)GIFData {
    [self setData:GIFData forPasteboardType:(id)kUTTypeGIF];
}

- (NSData *)GIFData {
    return [self dataForPasteboardType:(id)kUTTypeGIF];
}

- (void)setWEBPData:(NSData *)WEBPData {
    [self setData:WEBPData forPasteboardType:KCUTTypeWEBP];
}

- (NSData *)WEBPData {
    return [self dataForPasteboardType:KCUTTypeWEBP];
}

- (void)setImageData:(NSData *)imageData {
    [self setData:imageData forPasteboardType:(id)kUTTypeImage];
}

- (NSData *)imageData {
    return [self dataForPasteboardType:(id)kUTTypeImage];
}

- (void)setAttributedString:(NSAttributedString *)attributedString {
    self.string = [attributedString plainTextForRange:NSMakeRange(0, attributedString.length)];
    NSData *data = [attributedString archiveToData];
    if (data) {
        NSDictionary *item = @{KCPasteboardTypeAttributedString : data};
        [self addItems:@[item]];
    }
    [attributedString enumerateAttribute:KCTextAttachmentAttributeName inRange:NSMakeRange(0, attributedString.length) options:NSAttributedStringEnumerationLongestEffectiveRangeNotRequired usingBlock:^(KCTextAttachment *attachment, NSRange range, BOOL *stop) {
        UIImage *img = attachment.content;
        if ([img isKindOfClass:[UIImage class]]) {
            NSDictionary *item = @{@"com.apple.uikit.image" : img};
            [self addItems:@[item]];
            
            
            if ([img isKindOfClass:[KCImage class]] && ((KCImage *)img).animatedImageData) {
                if (((KCImage *)img).animatedImageType == KCImageTypeGIF) {
                    NSDictionary *item = @{(id)kUTTypeGIF : ((KCImage *)img).animatedImageData};
                    [self addItems:@[item]];
                } else if (((KCImage *)img).animatedImageType == KCImageTypePNG) {
                    NSDictionary *item = @{(id)kUTTypePNG : ((KCImage *)img).animatedImageData};
                    [self addItems:@[item]];
                } else if (((KCImage *)img).animatedImageType == KCImageTypeWebP) {
                    NSDictionary *item = @{(id)KCUTTypeWEBP : ((KCImage *)img).animatedImageData};
                    [self addItems:@[item]];
                }
            }
            
            
            // save image
            UIImage *simpleImage = nil;
            if ([attachment.content isKindOfClass:[UIImage class]]) {
                simpleImage = attachment.content;
            } else if ([attachment.content isKindOfClass:[UIImageView class]]) {
                simpleImage = ((UIImageView *)attachment.content).image;
            }
            if (simpleImage) {
                NSDictionary *item = @{@"com.apple.uikit.image" : simpleImage};
                [self addItems:@[item]];
            }
            
            // save animated image
            if ([attachment.content isKindOfClass:[UIImageView class]]) {
                UIImageView *imageView = attachment.content;
                KCImage *image = (id)imageView.image;
                if ([image isKindOfClass:[KCImage class]]) {
                    NSData *data = image.animatedImageData;
                    KCImageType type = image.animatedImageType;
                    if (data) {
                        switch (type) {
                            case KCImageTypeGIF: {
                                NSDictionary *item = @{(id)kUTTypeGIF : data};
                                [self addItems:@[item]];
                            } break;
                            case KCImageTypePNG: { // APNG
                                NSDictionary *item = @{(id)kUTTypePNG : data};
                                [self addItems:@[item]];
                            } break;
                            case KCImageTypeWebP: {
                                NSDictionary *item = @{(id)KCUTTypeWEBP : data};
                                [self addItems:@[item]];
                            } break;
                            default: break;
                        }
                    }
                }
            }
            
        }
    }];
}

- (NSAttributedString *)attributedString {
    for (NSDictionary *items in self.items) {
        NSData *data = items[KCPasteboardTypeAttributedString];
        if (data) {
            return [NSAttributedString unarchiveFromData:data];
        }
    }
    return nil;
}



@end
