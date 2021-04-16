//
//  SAPIDefine.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-5.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#ifndef SAPILib_SAPIDefine_h
#define SAPILib_SAPIDefine_h

/**
 互通模式
 */
typedef NS_ENUM(NSInteger, SAPILoginShareMode) {
    SAPINoShareLoginMode = 0,
    SAPISilenceShareLoginMode = 2,
    SAPIChoiceShareLoginMode = 3,
};

/**
 可以互通的方向
 */
typedef NS_ENUM(NSInteger, SAPILoginShareDirection) {
    SAPILoginShareDirectionBoth = 0,  //可以读写互通列表
    SAPILoginShareDirectionImport,    //可以读取互通列表，但不能将帐号写入互通列表
    SAPILoginShareDirectionExport     //可以将帐号写入互通列表，但不能读取互通列表
};

/**
 第三方帐号与百度帐号的绑定方式
 */
typedef enum {
    SAPIShareBindMobileBindMode, // 强制绑定手机号 - 在注册（首次登录）时，强制绑定手机号，推荐产品线使用该方式
    SAPIShareExplicitBindMode, // 明绑
    SAPIShareSMSBindMode, // 明绑且只支持通过手机号绑定
} SAPIShareBindMode;

/**
 快速登录选项
 */
typedef enum {
    SAPILoginOptionTSina = 0,
    SAPILoginOptionTSinaSSO,  //notice: 由于新浪微博不支持迁移appid，目前产品线无法新接入新浪微博SSO登录。
    SAPILoginOptionTQQ,         // 腾讯微博，已下线，不再支持
    SAPILoginOptionQRCode,
    SAPILoginOptionDeviceLogin,
    SAPILoginOptionNuoMi,
    SAPILoginOptionVoicePrint,
    SAPILoginOptionWeiXinSSO,
    SAPILoginOptionFFan,
    SAPILoginOptionChuanke,   // 传课登录方式
    SAPILoginOptionQQSSO,     // QQ SSO 登录
} SAPILoginOptionType;

/**
 环境配置
 
 - SapiEnvironment_Online: 线上环境
 - SapiEnvironment_RD: RD开发环境
 - SapiEnvironment_QA: QA联调环境
 - SapiEnvironment_New_QA: 新QA联调环境
 
 由于 QA 环境 HTTPS 使用的是自签名证书，需要安装根证书，步骤如下：
 1. 手机或者模拟器用 Safari 打开 http://10.94.19.13:8235/cer/passportqa.cer
 2. 点击安装证书
 3. iOS 10.3开始默认不信任自签名根证书，需要到 设置-通用-关于本机-证书信任设置 中勾选
 
 （如上面地址不可用，请尝试http://gitlab.baidu.com/jiangzhenjie/passport-https/raw/master/passportqa.cer）
 
 */
typedef enum ESapiEnvironmentType
{
    SapiEnvironment_Online = 1,
    SapiEnvironment_RD,
    SapiEnvironment_QA,
    SapiEnvironment_New_QA,
} SapiEnvironmentType;

/**
 第3方登录相关操作返回errorcode信息
 */
typedef enum
{
    //登录返回errorcode
    Oauth_TypeNotAvailable = 10,
    Oauth_InvalidOsuid = 17,
    Oauth_InvalidAct = 18,
    Oauth_InvalidAccessToken = 19,
    Oauth_AccessCancel = 501,
    Oauth_NoUserInfo = 502,
    Oauth_PassLoginFail = 401,
    Oauth_BindError = 901,
    Oauth_OtherError = -1,
    
    //帐号正常化返回errorcode
    Oauth_UserNoLogin = 119990
}TOauthErrorCode;

/**
 登录类型
 
 - SAPILoginTypeDefault: 普通登录
 - SAPILoginTypeSMS: 短信登录
 - SAPILoginTypeReg: 短信注册
 - SAPILoginTypeJoinWithAccount: AI联合登录，第三方拥有帐号系统
 - SAPILoginTypeJoinWithoutAccount: AI联合登录，第三方没有帐号系统
 */
typedef NS_ENUM(NSInteger, SAPILoginType){
    SAPILoginTypeDefault,
    SAPILoginTypeSMS,
    SAPILoginTypeReg,
    SAPILoginTypeJoinWithAccount,
    SAPILoginTypeJoinWithoutAccount,
};

/**
 上次用户成功登录方式
 
 - PASSLastLoginTypeNone:         无
 - PASSLastLoginTypePWD:          帐号密码登录
 - PASSLastLoginTypeSMS:          帐号短信登录
 - PASSLastLoginTypeFace:         刷脸登录
 - PASSLastLoginTypeWechat:       微信登录
 - PASSLastLoginTypeWeibo:        微博登录
 - PASSLastLoginTypeQQ:           QQ登录
 - PASSLastLoginTypeSilentShare:  静默互通登录
 - PASSLastLoginTypeChoiceShare:  选择互通登录
 */
typedef NS_ENUM(NSInteger, PASSLastLoginType){
    PASSLastLoginTypeNone = 0,
    PASSLastLoginTypePWD,
    PASSLastLoginTypeSMS,
    PASSLastLoginTypeFace,
    PASSLastLoginTypeWechat,
    PASSLastLoginTypeWeibo,
    PASSLastLoginTypeQQ,
    PASSLastLoginTypeSilentShare,
    PASSLastLoginTypeChoiceShare
};

/**
 第三方Oauth登录类型
 
 - SAPIThirdOauthLoginTypeWeibo: 第三方 Weibo Oauth 登录
 */
typedef NS_ENUM(NSUInteger, SAPIThirdOauthLoginType) {
    SAPIThirdOauthLoginTypeWeibo,
};

/**
 *  登录帐号类型，用在确认用户输入的登录帐号是手机还是用户名
 */
typedef NS_ENUM(NSInteger, SAPILoginAccountType){
    /**
     *  默认情况
     */
    SAPILoginAccountTypeDefault = 0,
    /**
     *  用户输入的登录帐号为手机号
     */
    SAPILoginAccountTypeMobile = 1,
    /**
     *  用户输入的登录帐号为用户名
     */
    SAPILoginAccountTypeUsername = 2,
};

/**
 *  绑定控件类型
 */
typedef NS_ENUM(NSUInteger, SAPIBindWidgetType){
    /**
     *  绑定手机
     */
    SAPIBindWidgetTypeBindMobile,
    /**
     *  换绑手机
     */
    SAPIBindWidgetTypeRebindMobile,
    /**
     *  解绑手机
     */
    SAPIBindWidgetTypeUnbindMobile,
    /**
     *  绑定邮箱
     */
    SAPIBindWidgetTypeBindEmail,
    /**
     *  换绑邮箱
     */
    SAPIBindWidgetTypeRebindEmail,
    /**
     *  解绑邮箱
     */
    SAPIBindWidgetTypeUnbindEmail,
};

/**
 *  用户帐号类型
 */
typedef NS_ENUM(NSUInteger, SAPIUserCompleteType) {
    /**
     *  完整帐号
     */
    SAPIUserCompleteTypeNormalUser,
    /**
     *  半帐号
     */
    SAPIUserCompleteTypeIncompleteUser,
    /**
     *  未知类型，产品线需要自行查询
     */
    SAPIUserCompleteTypeUnknown,
};

/**
 *  NA与H5登录态同步策略
 *  当NA Bduss和H5 Bduss出现不一致时，根据以下策略决定最终登录状态<br/>
 *  1.SAPINativeH5SyncStrategyNativePriority —— NA优先，直接使用NA登录态覆盖H5登录态<br/>
 *  2.SAPINativeH5SyncStrategyH5Priority —— H5优先，亦即最后一次登录的帐号优先，将H5登录状态同步到NA<br/>
 */
typedef NS_ENUM(NSUInteger, SAPINativeH5SyncStrategy) {
    SAPINativeH5SyncStrategyNativePriority,
    SAPINativeH5SyncStrategyH5Priority,
};

/**
 *  @brief NA和H5登录态同步成功回调策略
 *
 *  @since 6.15.15
 */
typedef NS_ENUM(NSUInteger, SAPINativeH5SyncCallbackStrategy) {
    /**
     *  登录态同步成功后立刻回调
     *
     *  @since 6.15.15
     */
    SAPINativeH5SyncCallbackStrategyImmediately,
    /**
     *  登录态同步成功后，先对STOKEN进行预取，预取成功后回调；预取失败回调同步失败。
     *
     *  @since 6.15.15
     */
    SAPINativeH5SyncCallbackStrategyAfterStokenRetrieved,
};

/**
 *  @brief 国际化
 */
typedef NS_ENUM(NSUInteger, SAPII18NType) {
    /**
     *  中文
     */
    SAPII18NZh_Cn,
    /**
     *  英文
     */
    SAPII18NEng,
};

typedef NS_OPTIONS(NSUInteger, SAPIBiometricOptions) {
    SAPIBiometricOptionLivenessRecog = 1 << 0,
    SAPIBiometricOptionVoiceVerify = 1 << 1,
};

typedef NS_ENUM(NSUInteger, SAPINativeURLType) {
    SAPINativeURLTypeNone,
    SAPINativeURLTypeAppeal,
    SAPINativeURLTypeLiveness,
    SAPINativeURLTypeQRCodeLogin,
};

//Service方法回调
typedef void (^SAPIRequestCompletionBlock)(NSDictionary *info);
typedef void (^SAPIRequestErrorBlock)(NSDictionary *errorInfo);

//登录相关Notification
// SAPI中相关行为所产生的Notification

/**
 *  支持互通帐号登陆成功消息 notification中的userInfo中会有登录成功后的json字典
 */
#define kLoginSucceedNotification        @"kLoginSucceedNotification"

/**
 *  不支持互通帐号登陆成功消息 notification中的userInfo中会有登录成功后的json字典
 */
#define kUnsharedLoginSucceedNotification @"kUnsharedLoginSucceedNotification"

/**
 *  登陆失败消息
 */
#define kLoginFailNotification           @"kLoginFailNotification"

/**
 *  注册验证成功消息 notification中的userInfo中会有注册成功后的json字典
 */
#define kRegistVerifiedNotification      @"kRegistVerifiedNotification"

/**
 *  补填用户名成功消息 notification中的userInfo中会有注册成功后的json字典
 */
#define kFillUnameSucceedNotification    @"kFillUnameSucceedNotification"

/**
 *  第3方页面登录返回信息
 */
#define kOauthLoginNotification          @"kOauthLoginNotification"

/**
 *  帐号完整化返回信息
 */
#define kFillAccountNotification         @"kFillAccountNotification"

/**
 *  退出返回信息
 */
#define kLogOutNotification              @"kLogOutNotification"

// ==== Login Extra Info Key ====
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoIncompleteUserKey;
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoSourceKey;
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoActionTypeKey;
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoUserInfoKey;
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoKey;

// ==== Login Extra Info Value ====
// 登录来源：H5登录
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoSourceFromH5LoginValue;
// 登录来源：静默登录
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoSourceFromSilenceLoginValue;
// 登录类型：登录
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoActionTypeLogin;
// 登录类型：注册
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoActionTypePhoneReg;
// 登录类型：命中风控登录
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoActionTypeLoginProtect;
// 登录类型：选择互通
FOUNDATION_EXPORT NSString * const SAPILoginExtraInfoActionTypeChoiceShareLogin;

// ==== SAPI NSError UserInfo Keys and Values ====
FOUNDATION_EXPORT NSString * const SAPIBdussPtokenInvalidReasonKey;
/**
 *  @brief 本地PTOKEN缺失
 */
FOUNDATION_EXPORT NSString * const SAPIBdussPtokenInvalidReasonMissingPtoken;
/**
 *  @brief BDUSS无效
 */
FOUNDATION_EXPORT NSString * const SAPIBdussPtokenInvalidReasonUserNotOnline;
/**
 *  @brief PTOKEN和BDUSS不匹配
 */
FOUNDATION_EXPORT NSString * const SAPIBdussPtokenInvalidReasonBdussPtokenNotMatch;

// ==== Cookie Synchronization Notification ====
FOUNDATION_EXPORT NSString * const SAPICookieSyncH5CookieClearedNotification;

// ==== 第三方登录绑定授权信息Key ====
FOUNDATION_EXPORT NSString * const PASSThirdBindAccessTokenKey;
FOUNDATION_EXPORT NSString * const PASSThirdBindOpenIdKey;
FOUNDATION_EXPORT NSString * const PASSThirdBindUnionIdKey;
FOUNDATION_EXPORT NSString * const PASSThirdBindAuthCodeKey;

// ==== PASSRouter Defines ====
FOUNDATION_EXPORT NSString * const PASSRouterResultKey;
FOUNDATION_EXPORT NSString * const PASSRouterSuccessKey;
FOUNDATION_EXPORT NSString * const PASSRouterCancelKey;

// ==== 新浪微博第三方登录绑定授权信息Key ====
FOUNDATION_EXPORT NSString * const PASSThirdBindUserIDKey;
FOUNDATION_EXPORT NSString * const PASSThirdBindRefreshTokenKey;

#endif
