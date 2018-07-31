//
//  UIBarButtonItem+KCAdd.h
//  KCKit
//
//  Created by king on 16/2/29.
//  Copyright © 2016年 KC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIBarButtonItem (KCAdd)

@property (nonatomic,copy)void (^actionBlock)(id);

@end
