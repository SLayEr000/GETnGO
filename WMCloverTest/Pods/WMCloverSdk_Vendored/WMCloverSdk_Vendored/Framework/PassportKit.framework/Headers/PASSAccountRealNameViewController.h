//
//  PASSAccountRealNameViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/11/1.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

@interface PASSAccountRealNameViewController : PASSWebViewController

/**
 登录态，如果传空，则用当前登录帐号
 */
@property (nonatomic, copy) NSString *bduss;

@end
