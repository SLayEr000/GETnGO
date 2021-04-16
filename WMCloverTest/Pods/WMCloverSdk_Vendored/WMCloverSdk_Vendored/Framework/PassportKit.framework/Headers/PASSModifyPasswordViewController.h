//
//  PASSModifyPasswordViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/4/4.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

/**
 修改密码页面
 */
@interface PASSModifyPasswordViewController : PASSWebViewController

/**
 执行修改密码操作的用户登录态，如果传空，则用当前登录帐号
 */
@property (nonatomic, copy) NSString *bduss;

/**
 完成时回调，回调中 userInfo 为扩展字段，暂未使用；
 修改密码成功时，回调中 loginModel 不为空，error 为空；修改密码成功 bduss 会变化，回调中的 loginModel 为新的登录信息，同时 -[SAPIMainManager currentLoginModel] 也相应变成新的登录信息；
 修改密码失败时，比如用户中途取消，loginModel 为空，error 不为空；
 */
@property (nonatomic, copy) void(^completionHandler)(SAPILoginModel *loginModel, NSDictionary *userInfo, NSError *error);

/**
 初始化

 @param bduss 登录态，如果传空，则用当前登录帐号
 @return 页面实例
 */
- (instancetype)initWithBduss:(NSString *)bduss;

@end
