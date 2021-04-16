//
//  PASSThirdLoginViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/4/4.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

/**
 第三方登录页面
 */
@interface PASSThirdLoginViewController : PASSWebViewController

/**
 第三方 SSO 授权登录类型（如微信登录），如果使用 SSO 授权登录，authCode 或 authInfo 不能为空。
 */
@property (nonatomic, assign) PASSThirdSSOType ssoType;

/**
 第三方 SSO 授权登录码。
 */
@property (nonatomic, copy) NSString *authCode;

/**
 第三方 SSO 授权信息。Key定义可在 SAPIDefine.h 中找到
 */
@property (nonatomic, copy) NSDictionary *authInfo;

/**
 第三方 OAuth 授权登录类型（如微博登录）
 */
@property (nonatomic, assign) PASSThirdOAuthType oauthType;

/**
 检测 authInfo 中的授权信息是否和类型匹配

 @param authInfo 授权信息
 @param type 登录类型
 @return 当 authInfo 中包含的授权信息和 type 符合时，返回YES，否则返回 NO。
 */
+ (BOOL)checkAuthInfoAvailable:(NSDictionary *)authInfo forType:(PASSThirdSSOType)type;

@end
