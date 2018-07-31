//
//  NSDate+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/27.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDate (KCAdd)

@property (nonatomic,readonly) NSInteger year;
@property (nonatomic,readonly) NSInteger month;
@property (nonatomic,readonly) NSInteger day;
@property (nonatomic,readonly) NSInteger hour;
@property (nonatomic,readonly) NSInteger minute;
@property (nonatomic,readonly) NSInteger second;
@property (nonatomic,readonly) NSInteger nanosecond;
@property (nonatomic,readonly) NSInteger weekday;
@property (nonatomic,readonly) NSInteger weekdayOrdinal;
@property (nonatomic,readonly) NSInteger weekOfMonth;
@property (nonatomic,readonly) NSInteger weekOfYear;
@property (nonatomic,readonly) NSInteger yearForWeekOfYear;
@property (nonatomic, readonly) NSInteger quarter; ///< Quarter component
@property (nonatomic, readonly) BOOL isLeapMonth; ///< Weather the month is leap month
@property (nonatomic, readonly) BOOL isLeapYear; ///< Weather the year is leap year
@property (nonatomic, readonly) BOOL isToday; ///< Weather date is today (based on current locale)
@property (nonatomic, readonly) BOOL isYesterday; ///< Weather date is yesterday (based on current locale)


- (NSDate *)dateByAddingYears:(NSInteger)years;

- (NSDate *)dateByAddingMonths:(NSInteger)months;

- (NSDate *)dateByAddingWeeks:(NSInteger)weeks;

- (NSDate *)dateByAddingDays:(NSInteger)days;

- (NSDate *)dateByAddingHours:(NSInteger)hours;

- (NSDate *)dateByAddingMinutes:(NSInteger)minutes;

- (NSDate *)dateByAddingSeconds:(NSInteger)seconds;

- (NSString *)stringWithFormat:(NSString *)format;

- (NSString *)stringWithFormat:(NSString *)format timeZone:(NSTimeZone *)timeZone locale:(NSLocale *)locale;

- (NSString *)stringWithISOFormat;

+ (NSDate *)dateWithString:(NSString *)dateString format:(NSString *)format;

+ (NSDate *)dateWithString:(NSString *)dateString format:(NSString *)format timeZone:(NSTimeZone *)timeZone locale:(NSLocale *)locale;

+ (NSDate *)dateWithISOFormatString:(NSString *)dateString;

@end
