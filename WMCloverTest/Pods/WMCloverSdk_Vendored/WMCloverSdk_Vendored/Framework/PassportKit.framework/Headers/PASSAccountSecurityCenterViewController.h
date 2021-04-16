//
//  PASSAccountSecurityCenterViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/4/2.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

/**
 帐号安全中心页面
 */
@interface PASSAccountSecurityCenterViewController : PASSWebViewController

/**
 通过扫描二维码拿到的URL
 */
@property (nonatomic, copy) NSString *qrcodeURLString;

/**
 额外的参数，没有时传nil即可
 */
@property (nonatomic, strong) NSDictionary *extraParams;

/**
 检查当前URL是否满足跳转帐号申诉
 
 @param urlString url字符串
 @return 满足跳转申诉时返回YES，其他情况返回NO
 */
+ (BOOL)checkWhetherAccountSecurityCenterURLString:(NSString *)urlString;

@end
