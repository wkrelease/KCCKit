//
//  KCTextInput.m
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//

#import "KCTextInput.h"
#import "KCKitMacro.h"

@implementation KCTextPosition

+ (instancetype)positionWithOffset:(NSInteger)offset {
    return [self positionWithOffset:offset affinity:KCTextAffinityForward];
}

+ (instancetype)positionWithOffset:(NSInteger)offset affinity:(KCTextAffinity)affinity {
    KCTextPosition *p = [self new];
    p->_offset = offset;
    p->_affinity = affinity;
    return p;
}

- (instancetype)copyWithZone:(NSZone *)zone {
    return [self.class positionWithOffset:_offset affinity:_affinity];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p> (%@%@)", self.class, self, @(_offset), _affinity == KCTextAffinityForward ? @"F":@"B"];
}

- (NSUInteger)hash {
    return _offset * 2 + (_affinity == KCTextAffinityForward ? 1 : 0);
}

- (BOOL)isEqual:(KCTextPosition *)object {
    if (!object) return NO;
    return _offset == object.offset && _affinity == object.affinity;
}

- (NSComparisonResult)compare:(KCTextPosition *)otherPosition {
    if (!otherPosition) return NSOrderedAscending;
    if (_offset < otherPosition.offset) return NSOrderedAscending;
    if (_offset > otherPosition.offset) return NSOrderedDescending;
    if (_affinity == KCTextAffinityBackward && otherPosition.affinity == KCTextAffinityForward) return NSOrderedAscending;
    if (_affinity == KCTextAffinityForward && otherPosition.affinity == KCTextAffinityBackward) return NSOrderedDescending;
    return NSOrderedSame;
}

@end



@implementation KCTextRange {
    KCTextPosition *_start;
    KCTextPosition *_end;
}

- (instancetype)init {
    self = [super init];
    if (!self) return nil;
    _start = [KCTextPosition positionWithOffset:0];
    _end = [KCTextPosition positionWithOffset:0];
    return self;
}

- (KCTextPosition *)start {
    return _start;
}

- (KCTextPosition *)end {
    return _end;
}

- (BOOL)isEmpty {
    return _start.offset == _end.offset;
}

- (NSRange)asRange {
    return NSMakeRange(_start.offset, _end.offset - _start.offset);
}

+ (instancetype)rangeWithRange:(NSRange)range {
    return [self rangeWithRange:range affinity:KCTextAffinityForward];
}

+ (instancetype)rangeWithRange:(NSRange)range affinity:(KCTextAffinity)affinity {
    KCTextPosition *start = [KCTextPosition positionWithOffset:range.location affinity:affinity];
    KCTextPosition *end = [KCTextPosition positionWithOffset:range.location + range.length affinity:affinity];
    return [self rangeWithStart:start end:end];
}

+ (instancetype)rangeWithStart:(KCTextPosition *)start end:(KCTextPosition *)end {
    if (!start || !end) return nil;
    if ([start compare:end] == NSOrderedDescending) {
        KC_SWAP(start, end);
    }
    KCTextRange *range = [KCTextRange new];
    range->_start = start;
    range->_end = end;
    return range;
}

+ (instancetype)defaultRange {
    return [self new];
}

- (instancetype)copyWithZone:(NSZone *)zone {
    return [self.class rangeWithStart:_start end:_end];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p> (%@, %@)%@", self.class, self, @(_start.offset), @(_end.offset - _start.offset), _end.affinity == KCTextAffinityForward ? @"F":@"B"];
}

- (NSUInteger)hash {
    return (sizeof(NSUInteger) == 8 ? OSSwapInt64(_start.hash) : OSSwapInt32(_start.hash)) + _end.hash;
}

- (BOOL)isEqual:(KCTextRange *)object {
    if (!object) return NO;
    return [_start isEqual:object.start] && [_end isEqual:object.end];
}

@end



@implementation KCTextSelectionRect

@synthesize rect = _rect;
@synthesize writingDirection = _writingDirection;
@synthesize containsStart = _containsStart;
@synthesize containsEnd = _containsEnd;
@synthesize isVertical = _isVertical;

- (id)copyWithZone:(NSZone *)zone {
    KCTextSelectionRect *one = [self.class new];
    one.rect = _rect;
    one.writingDirection = _writingDirection;
    one.containsStart = _containsStart;
    one.containsEnd = _containsEnd;
    one.isVertical = _isVertical;
    return one;
}

@end
