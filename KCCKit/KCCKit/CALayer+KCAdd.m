//
//  CALayer+KCAdd.m
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "CALayer+KCAdd.h"

#import "KCKitMacro.h"

#import "KCCGUtilities.h"


KCSYNTH_DUMMY_CLASS(CALayer_KCAdd)

@implementation CALayer (KCAdd)

//屏幕快照
- (UIImage *)snapshotImage{
    UIGraphicsBeginImageContextWithOptions(self.bounds.size, self.opaque, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    [self renderInContext:context];//把照片用到上下文
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}
//pdf快照
- (NSData *)snapshotPDF{
    
    CGRect bounds = self.bounds;
    NSMutableData *data = [NSMutableData data];
    CGDataConsumerRef consumer = CGDataConsumerCreateWithCFData((__bridge CFMutableDataRef)data);
    CGContextRef context = CGPDFContextCreate(consumer, &bounds, NULL);
    CGDataConsumerRelease(consumer);
    if (!context) {
        return nil;
    }
    CGPDFContextBeginPage(context, NULL);
    CGContextTranslateCTM(context, 0, bounds.size.height);
    CGContextScaleCTM(context, 1.0, -1.0);
    [self renderInContext:context];
    CGPDFContextEndPage(context);
    CGPDFContextClose(context);
    CGContextRelease(context);
    return data;
    
}
- (void)setLayerShadow:(UIColor *)color offset:(CGSize)offset radius:(CGFloat)radius{
    
    self.shadowColor = color.CGColor;
    self.shadowOffset = offset;
    self.shadowRadius = radius;
    self.shadowOpacity = 1;
    self.shouldRasterize = YES;
    self.rasterizationScale = [UIScreen mainScreen].scale;
    
}
- (void)removeAllSublayers{
    
    while (self.sublayers.count) {
        [self.sublayers.lastObject removeFromSuperlayer];
    }
    
}

- (CGFloat)left{
    return self.frame.origin.x;
}
- (void)setLeft:(CGFloat)x{
    CGRect frame = self.frame;
    frame.origin.x = x;
    self.frame = frame;
}
- (CGFloat)top{
    return self.frame.origin.y;
}
- (void)setTop:(CGFloat)y{
    CGRect frame = self.frame;
    frame.origin.y = y;
    self.frame = frame;
}
- (CGFloat)right{
    return self.frame.origin.x + self.frame.size.width;
}
- (void)setRight:(CGFloat)right{
    CGRect frame = self.frame;
    frame.origin.x = right - frame.size.width;
    self.frame = frame;
}
- (CGFloat)bottom{
    return self.frame.origin.y + self.frame.size.height;
}
- (void)setBottom:(CGFloat)bottom{
    CGRect frame = self.frame;
    frame.origin.y = bottom - frame.size.height;
    self.frame = frame;
}
- (CGFloat)width{
    return self.frame.size.width;
}
- (void)setWidth:(CGFloat)width{
    CGRect frame = self.frame;
    frame.size.width = width;
    self.frame = frame;
}
- (CGFloat)height{
    return self.frame.size.height;
}
- (void)setHeight:(CGFloat)height{
    CGRect frame = self.frame;
    frame.size.height = height;
    self.frame = frame;
    
}
- (CGPoint)center{
    return CGPointMake(self.frame.origin.x + self.frame.size.width * 0.5,
                       self.frame.origin.y + self.frame.size.height * 0.5);
}
- (void)setCenter:(CGPoint)center{
    CGRect frame = self.frame;
    frame.origin.x = center.x - frame.size.width * 0.5;
    frame.origin.y = center.y - frame.size.height * 0.5;
    self.frame = frame;
}
- (CGFloat)centerX{
    return self.frame.origin.x + self.frame.size.width * 0.5;
}
- (void)setCenterX:(CGFloat)centerX{
    CGRect frame = self.frame;
    frame.origin.x = centerX - frame.size.width * 0.5;
    self.frame = frame;
}
- (CGFloat)centerY{
    return self.frame.origin.y + self.frame.size.height * 0.5;
}
- (void)setCenterY:(CGFloat)centerY{
    CGRect frame = self.frame;
    frame.origin.y = centerY - frame.size.height * 0.5;
    self.frame = frame;
}
- (CGPoint)origin{
    return self.frame.origin;
}
- (void)setOrigin:(CGPoint)origin{
    CGRect frame = self.frame;
    frame.origin = origin;
    self.frame = frame;
}
- (CGSize)frameSize{
    return self.frame.size;
}
- (void)setFrameSize:(CGSize)size{
    CGRect frame = self.frame;
    frame.size = size;
    self.frame = frame;
}
- (CGFloat)transformRotation{
    NSNumber *v = [self valueForKeyPath:@"transform.rotation"];
    return v.doubleValue;
}
- (void)setTransformRotation:(CGFloat)v{
    [self setValue:@(v) forKey:@"transform.rotation"];
}
- (CGFloat)transformRotationX{
    NSNumber *v = [self valueForKeyPath:@"transform.rotation.x"];
    return v.doubleValue;
}
- (void)setTransformRotationX:(CGFloat)transformRotationX{
    [self setValue:@(transformRotationX) forKey:@"transform.rotation.x"];
}
- (CGFloat)transformRotationY{
    NSNumber *v = [self valueForKeyPath:@"transform.rotation.y"];
    return v.doubleValue;
}
- (void)setTransformRotationY:(CGFloat)transformRotationY{
    [self setValue:@(transformRotationY) forKey:@"transform.rotation.y"];
}
- (CGFloat)transformRotationZ{
    NSNumber *v = [self valueForKeyPath:@"transform.rotation.z"];
    return v.doubleValue;
}
- (void)setTransformRotationZ:(CGFloat)transformRotationZ{
    [self setValue:@(transformRotationZ) forKey:@"transform.rotation.z"];
}

- (CGFloat)transformScaleX{
    NSNumber *v = [self valueForKeyPath:@"transform.scale.x"];
    return [v doubleValue];
}
- (void)setTransformScaleX:(CGFloat)transformScaleX{
    [self setValue:@(transformScaleX) forKey:@"transform.scale.x"];
}
- (CGFloat)transformScaleY{
    NSNumber *v = [self valueForKeyPath:@"transform.scale.y"];
    return v.doubleValue;
}
- (void)setTransformScaleY:(CGFloat)transformScaleY{
    [self setValue:@(transformScaleY) forKeyPath:@"transform.scale.y"];
}
- (CGFloat)transformScaleZ{
    NSNumber *v = [self valueForKeyPath:@"transform.scale.z"];
    return v.doubleValue;
}
- (void)setTransformScaleZ:(CGFloat)transformScaleZ{
    [self setValue:@(transformScaleZ) forKeyPath:@"transform.scale.z"];
}

- (CGFloat)transformScale{
    NSNumber *v = [self valueForKeyPath:@"transform.scale"];
    return v.doubleValue;
}
- (void)setTransformScale:(CGFloat)transformScale{
    [self setValue:@(transformScale) forKeyPath:@"transform.scale"];
}

- (CGFloat)transformTranslationX{
    NSNumber *v = [self valueForKeyPath:@"transform.translation.x"];
    return v.doubleValue;
}
- (void)setTransformTranslationX:(CGFloat)transformTranslationX{
    [self setValue:@(transformTranslationX) forKeyPath:@"transform.translation.x"];
}
- (CGFloat)transformTranslationY{
    NSNumber *v = [self valueForKeyPath:@"transform.translation.y"];
    return v.doubleValue;
}
- (void)setTransformTranslationY:(CGFloat)transformTranslationY{
    [self setValue:@(transformTranslationY) forKeyPath:@"transform.translation.y"];
}

- (CGFloat)transformTranslationZ{
    NSNumber *v = [self valueForKeyPath:@"transform.translation.z"];
    return v.doubleValue;
}
- (void)setTransformTranslationZ:(CGFloat)transformTranslationZ{
    [self setValue:@(transformTranslationZ) forKeyPath:@"transform.translation.z"];
}

- (CGFloat)transformDepth{
    return self.transform.m34;
}
- (void)setTransformDepth:(CGFloat)transformDepth{
    CATransform3D d = self.transform;
    d.m34 = transformDepth;
    self.transform = d;
}

- (UIViewContentMode)contentMode{
    return KCCAGravityToUIViewContentMode(self.contentsGravity);
}
- (void)setContentMode:(UIViewContentMode)contentMode{
    self.contentsGravity = KCUIViewContentModeToCAGravity(contentMode);
}
- (void)addFadeAnimationWithDuration:(NSTimeInterval)duration curve:(UIViewAnimationCurve)curve{
    if (duration <= 0) {
        return;
    }
    NSString *mediaFunction;
    switch (curve) {
        case UIViewAnimationCurveEaseInOut:
            mediaFunction = kCAMediaTimingFunctionEaseOut;
            break;
        case UIViewAnimationCurveEaseIn:
            mediaFunction = kCAMediaTimingFunctionEaseIn;
            break;
        case UIViewAnimationCurveEaseOut:
            mediaFunction = kCAMediaTimingFunctionEaseOut;
            break;
        case UIViewAnimationCurveLinear:
            mediaFunction = kCAMediaTimingFunctionLinear;
            break;
        default:
            mediaFunction = kCAMediaTimingFunctionLinear;
            break;
    }
    
    CATransition *transition = [CATransition animation];
    transition.duration = duration;
    transition.timingFunction = [CAMediaTimingFunction functionWithName:mediaFunction];
    transition.type = kCATransitionFade;
    [self addAnimation:transition forKey:@"kckit.fade"];
    
}

- (void)removePreviousFadeAnimation{
    [self removeAnimationForKey:@"kckit.fade"];
}





@end


































