//
//  PASSLoginViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/3/31.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import "PASSWebViewController.h"

@class PASSLoginConfig;

/**
 登录方式

 - PASSLoginWayAccount: 帐号密码登录
 - PASSLoginWaySMS: 短信登录
 - PASSLoginWayReg: 注册
 - PASSLoginWayJoinWithAccount: AI联合登录，第三方拥有帐号系统
 - PASSLoginWayJoinWithoutAccount: AI联合登录，第三方没有帐号系统
 */
typedef NS_ENUM(NSInteger, PASSLoginWay) {
    PASSLoginWayAccount,
    PASSLoginWaySMS,
    PASSLoginWayReg,
    PASSLoginWayJoinWithAccount,
    PASSLoginWayJoinWithoutAccount,
};

/**
 第三方 SSO 登录类型

 - PASSThirdSSOTypeWeiXin: 微信登录
 - PASSThirdSSOTypeQQ: QQ登录
 - PASSThirdSSOTypeSina: 新浪微博登录
 */
typedef NS_ENUM(NSUInteger, PASSThirdSSOType) {
    PASSThirdSSOTypeWeiXin = 1,
    PASSThirdSSOTypeQQ,
    PASSThirdSSOTypeSina,
};


/**
 第三方 OAuth 登录类型

 - PASSThirdOAuthTypeWeibo: 新浪微博登录
 */
typedef NS_ENUM(NSUInteger, PASSThirdOAuthType) {
    PASSThirdOAuthTypeWeibo = 1,
};

/**
 登录页面
 */
@interface PASSLoginViewController : PASSWebViewController

/**
 预设用户名
 */
@property (nonatomic, copy) NSString *presetUsername;

/**
 默认为NO
 */
@property (nonatomic, assign) BOOL preferredNavigationBarShown;

/**
 第三方SSO登录授权回调。在回调中应该拉起第三方客户端进行授权，授权完成后调用 bindThirdPartySSOLoginWithType:authCode: 进行百度帐号绑定
 */
@property (nonatomic, copy) void(^startThirdPartySSOAuthHandler)(NSDictionary *userInfo, PASSThirdSSOType type);

/**
 初始化登录页面

 @param loginWay 登录方式
 @return 登录页面实例
 */
- (instancetype)initWithLoginWay:(PASSLoginWay)loginWay;

/**
 初始化登录页面

 @param config 登录相关参数，可定制化登录页，具体内容见 PASSLoginConfig 说明
 @return 登录页面实例
 */
- (instancetype)initWithLoginConfig:(PASSLoginConfig *)config;

/**
 第三方登录绑定。在完成第三方授权后，调用此方法进行百度帐号绑定操作。
 
 @param type 第三方类型
 @param authCode 授权码
 */
- (void)bindThirdPartySSOLoginWithType:(PASSThirdSSOType)type authCode:(NSString *)authCode;

/**
 第三方登录绑定。在完成第三方授权后，调用此方法进行百度帐号绑定操作。

 @param type 第三方类型
 @param authInfo 授权信息，根据不同类型传入不同值，字典 Key 可在 SAPIDefine.h 中找到。一般而言使用 Wrapper 返回的授权信息即可。
 
 对于 微信SSO 登录来说，需要以下字段：
 PASSThirdBindAuthCodeKey
 
 对于 QQ SSO 登录来说，需要以下字段：
 PASSThirdBindAccessTokenKey
 PASSThirdBindOpenIdKey
 PASSThirdBindUnionIdKey
 
 @return 当 authInfo 中包含的授权信息和 type 符合时，返回YES，否则返回 NO。
 */
- (BOOL)bindThirdPartySSOLoginWithType:(PASSThirdSSOType)type authInfo:(NSDictionary *)authInfo;

@end
