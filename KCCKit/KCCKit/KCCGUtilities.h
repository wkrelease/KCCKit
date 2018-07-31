






#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#if __has_include(<KCKit/KCKit.h>)
#import <KCKit/KCKitMacro.h>
#else
#import "KCKitMacro.h"
#endif


KC_EXTERN_C_BEGIN


CGContextRef KCCGContextCreateARGBBitmapContext(CGSize size, BOOL opaque, CGFloat scale);

CGContextRef KCCGContextCreateGrayBitmapContext(CGSize size, CGFloat scale);

CGFloat KCScreenScale();

CGSize KCScreenSize();

static inline CGFloat DegreesToRadians(CGFloat degrees) {
    return degrees * M_PI / 180;
}
static inline CGFloat RadiansToDegrees(CGFloat radians) {
    return radians * 180 / M_PI;
}
static inline CGFloat CGAffineTransformGetRotation(CGAffineTransform transform) {
    return atan2(transform.b, transform.a);
}
static inline CGFloat CGAffineTransformGetScaleX(CGAffineTransform transform) {
    return  sqrt(transform.a * transform.a + transform.c * transform.c);
}
static inline CGFloat CGAffineTransformGetScaleY(CGAffineTransform transform) {
    return sqrt(transform.b * transform.b + transform.d * transform.d);
}
static inline CGFloat CGAffineTransformGetTranslateX(CGAffineTransform transform) {
    return transform.tx;
}
static inline CGFloat CGAffineTransformGetTranslateY(CGAffineTransform transform) {
    return transform.ty;
}

CGAffineTransform KCCGAffineTransformGetFromPoints(CGPoint before[3], CGPoint after[3]);

CGAffineTransform KCCGAffineTransformGetFromViews(UIView *from, UIView *to);

static inline CGAffineTransform CGAffineTransformMakeSkew(CGFloat x, CGFloat y){
  
    CGAffineTransform transform = CGAffineTransformIdentity;
    transform.c = -x;
    transform.b = y;
    return transform;
    
}
static inline UIEdgeInsets UIEdgeInsetsInvert(UIEdgeInsets insets) {
    return UIEdgeInsetsMake(-insets.top, -insets.left, -insets.bottom, -insets.right);
}
UIViewContentMode KCCAGravityToUIViewContentMode(NSString *gravity);

NSString *KCUIViewContentModeToCAGravity(UIViewContentMode contentMode);

CGRect KCCGRectFitWithContentMode(CGRect rect, CGSize size, UIViewContentMode mode);


static inline CGPoint CGRectGetCenter(CGRect rect) {
    return CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
}

static inline CGFloat CGRectGetArea(CGRect rect) {
    if (CGRectIsNull(rect)) return 0;
    rect = CGRectStandardize(rect);
    return rect.size.width * rect.size.height;
}

static inline CGFloat CGPointGetDistanceToPoint(CGPoint p1, CGPoint p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

static inline CGFloat CGPointGetDistanceToRect(CGPoint p, CGRect r) {
    r = CGRectStandardize(r);
    if (CGRectContainsPoint(r, p)) return 0;
    CGFloat distV, distH;
    if (CGRectGetMinY(r) <= p.y && p.y <= CGRectGetMaxY(r)) {
        distV = 0;
    } else {
        distV = p.y < CGRectGetMinY(r) ? CGRectGetMinY(r) - p.y : p.y - CGRectGetMaxY(r);
    }
    if (CGRectGetMinX(r) <= p.x && p.x <= CGRectGetMaxX(r)) {
        distH = 0;
    } else {
        distH = p.x < CGRectGetMinX(r) ? CGRectGetMinX(r) - p.x : p.x - CGRectGetMaxX(r);
    }
    return MAX(distV, distH);
}

static inline CGFloat CGFloatToPixel(CGFloat value) {
    return value * KCScreenScale();
}
static inline CGFloat CGFloatFromPixel(CGFloat value) {
    return value / KCScreenScale();
}
static inline CGFloat CGFloatPixelFloor(CGFloat value) {
    CGFloat scale = KCScreenScale();
    return floor(value * scale) / scale;
}
static inline CGFloat CGFloatPixelRound(CGFloat value) {
    CGFloat scale = KCScreenScale();
    return round(value * scale) / scale;
}
static inline CGFloat CGFloatPixelCeil(CGFloat value) {
    CGFloat scale = KCScreenScale();
    return ceil(value * scale) / scale;
}
static inline CGFloat CGFloatPixelHalf(CGFloat value) {
    CGFloat scale = KCScreenScale();
    return (floor(value * scale) + 0.5) / scale;
}
static inline CGPoint CGPointPixelFloor(CGPoint point) {
    CGFloat scale = KCScreenScale();
    return CGPointMake(floor(point.x * scale) / scale,
                       floor(point.y * scale) / scale);
}
static inline CGPoint CGPointPixelRound(CGPoint point) {
    CGFloat scale = KCScreenScale();
    return CGPointMake(round(point.x * scale) / scale,
                       round(point.y * scale) / scale);
}
static inline CGPoint CGPointPixelCeil(CGPoint point) {
    CGFloat scale = KCScreenScale();
    return CGPointMake(ceil(point.x * scale) / scale,
                       ceil(point.y * scale) / scale);
}
static inline CGPoint CGPointPixelHalf(CGPoint point) {
    CGFloat scale = KCScreenScale();
    return CGPointMake((floor(point.x * scale) + 0.5) / scale,
                       (floor(point.y * scale) + 0.5) / scale);
}
static inline CGSize CGSizePixelFloor(CGSize size) {
    CGFloat scale = KCScreenScale();
    return CGSizeMake(floor(size.width * scale) / scale,
                      floor(size.height * scale) / scale);
}
static inline CGSize CGSizePixelRound(CGSize size) {
    CGFloat scale = KCScreenScale();
    return CGSizeMake(round(size.width * scale) / scale,
                      round(size.height * scale) / scale);
}
static inline CGSize CGSizePixelCeil(CGSize size) {
    CGFloat scale = KCScreenScale();
    return CGSizeMake(ceil(size.width * scale) / scale,
                      ceil(size.height * scale) / scale);
}
static inline CGSize CGSizePixelHalf(CGSize size) {
    CGFloat scale = KCScreenScale();
    return CGSizeMake((floor(size.width * scale) + 0.5) / scale,
                      (floor(size.height * scale) + 0.5) / scale);
}

static inline CGRect CGRectPixelFloor(CGRect rect) {
    CGPoint origin = CGPointPixelCeil(rect.origin);
    CGPoint corner = CGPointPixelFloor(CGPointMake(rect.origin.x + rect.size.width,
                                                   rect.origin.y + rect.size.height));
    CGRect ret = CGRectMake(origin.x, origin.y, corner.x - origin.x, corner.y - origin.y);
    if (ret.size.width < 0) ret.size.width = 0;
    if (ret.size.height < 0) ret.size.height = 0;
    return ret;
}

static inline CGRect CGRectPixelRound(CGRect rect) {
    CGPoint origin = CGPointPixelRound(rect.origin);
    CGPoint corner = CGPointPixelRound(CGPointMake(rect.origin.x + rect.size.width,
                                                   rect.origin.y + rect.size.height));
    return CGRectMake(origin.x, origin.y, corner.x - origin.x, corner.y - origin.y);
}

static inline CGRect CGRectPixelCeil(CGRect rect) {
    CGPoint origin = CGPointPixelFloor(rect.origin);
    CGPoint corner = CGPointPixelCeil(CGPointMake(rect.origin.x + rect.size.width,
                                                  rect.origin.y + rect.size.height));
    return CGRectMake(origin.x, origin.y, corner.x - origin.x, corner.y - origin.y);
}

static inline CGRect CGRectPixelHalf(CGRect rect) {
    CGPoint origin = CGPointPixelHalf(rect.origin);
    CGPoint corner = CGPointPixelHalf(CGPointMake(rect.origin.x + rect.size.width,
                                                  rect.origin.y + rect.size.height));
    return CGRectMake(origin.x, origin.y, corner.x - origin.x, corner.y - origin.y);
}

static inline UIEdgeInsets UIEdgeInsetPixelFloor(UIEdgeInsets insets) {
    insets.top = CGFloatPixelFloor(insets.top);
    insets.left = CGFloatPixelFloor(insets.left);
    insets.bottom = CGFloatPixelFloor(insets.bottom);
    insets.right = CGFloatPixelFloor(insets.right);
    return insets;
}

static inline UIEdgeInsets UIEdgeInsetPixelCeil(UIEdgeInsets insets) {
    insets.top = CGFloatPixelCeil(insets.top);
    insets.left = CGFloatPixelCeil(insets.left);
    insets.bottom = CGFloatPixelCeil(insets.bottom);
    insets.right = CGFloatPixelCeil(insets.right);
    return insets;
}



// main screen's scale
#ifndef kScreenScale
#define kScreenScale KCScreenScale()
#endif

// main screen's size (portrait)
#ifndef kScreenSize
#define kScreenSize KCScreenSize()
#endif

// main screen's width (portrait)
#ifndef kScreenWidth
#define kScreenWidth KCScreenSize().width
#endif

// main screen's height (portrait)
#ifndef kScreenHeight
#define kScreenHeight KCScreenSize().height
#endif

KC_EXTERN_C_END




