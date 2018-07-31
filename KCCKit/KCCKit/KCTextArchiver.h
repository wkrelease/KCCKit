//
//  KCTextArchiver.h
//  Jade
//
//  Created by king on 16/6/7.
//  Copyright © 2016年 KC. All rights reserved.
//


@import UIKit;

@interface KCTextArchiver : NSKeyedArchiver<NSKeyedArchiverDelegate>
@end


@interface KCTextUnarchiver : NSKeyedUnarchiver <NSKeyedUnarchiverDelegate>
@end