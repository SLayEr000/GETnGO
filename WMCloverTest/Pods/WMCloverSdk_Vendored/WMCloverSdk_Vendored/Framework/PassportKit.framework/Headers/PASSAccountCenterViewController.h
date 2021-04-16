//
//  PASSAccountCenterViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/3/31.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import "PASSWebViewController.h"

/**
 帐号中心页面
 */
@interface PASSAccountCenterViewController : PASSWebViewController

/**
 启动微信授权回调。在此回调中应该拉起微信客户端进行授权，授权完成后调用 relateWeiXinWithCode:wxAppId:scope:relateWeiXinUString: 进行帐号关联
 */
@property (nonatomic, copy) BOOL(^startWeiXinAuthHandler)(NSDictionary *userInfo);

/**
 关联微信帐号

 @param code 授权码
 */
- (void)relateWeiXinWithCode:(NSString *)code;

@end
