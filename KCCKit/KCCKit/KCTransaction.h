//
//  KCTransaction.h
//  Jade
//
//  Created by king on 16/6/15.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KCTransaction : NSObject

+ (KCTransaction *)transactionWithTarget:(id)target selector:(SEL)selector;

- (void)commit;

@end
