//
//  PASSAccountWebViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/1/17.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

@interface PASSAccountWebViewController : PASSWebViewController

/**
 登录态，如果传空，则用当前登录帐号
 */
@property (nonatomic, copy) NSString *bduss;

/**
 构造方法

 @param bduss 登录态，如果传空，则使用当前登录帐号
 @return PASSAccountWebViewController 实例
 */
- (instancetype)initWithBduss:(NSString *)bduss;

@end
