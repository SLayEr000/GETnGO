//
//  SAPIMainManager.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-5.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassportKit/PassportKit.h>

@class SAPIMainManager;
@class PASSFaceIDService;

@protocol SAPIMainManagerDelegate <NSObject>

@required
/**
 *  登录成功回调
 *
 *  @param sapiManager SAPIMainManager实例
 *  @param loginModel  登录成功的帐号信息
 *  @param extraInfo   额外的信息，目前包含字段：
 *                          SAPILoginExtraInfoIncompleteUserKey: 用户帐号类型，为SAPIUserCompleteType类型(这个字段值可能会变，建议只在登录成功时使用)
 *                          SAPILoginExtraInfoSourceKey：目前仅在通过H5登录时返回该字段，value固定为SAPILoginExtraInfoSourceFromH5LoginValue
 *                          SAPILoginExtraInfoActionTypeKey：表示当前登录类型，value 为 SAPILoginExtraInfoActionTypeXXX
 *
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager
    didLoginSucceed:(SAPILoginModel *)loginModel
          extraInfo:(NSDictionary *)extraInfo;

/**
 *  登录失败时回调
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didLoginFail:(SAPILoginModel *)model;

/**
 *  退出成功时回调
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didLogOut:(SAPILoginModel *)model;

@optional
/**
 *  v6.7.4 新增
 *  静默互通登录成功时调用，仅供产品线用于统计静默互通
 *
 *  @param sapiManager SAPIMainManage
 *  @param options     可能包含有该静默帐号来源于哪个app的字段(sourceAppName)和该App的BundleID(sourceBundleID)。
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager silenceLoginSucceedWithOptions:(NSDictionary *)options;

/**
 *  在成功登录一个帐号前会回调此方法
 *
 *  @param sapiManager SAPIMainManage
 *  @param freshModel  将要登录成功的帐号信息
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager beforeLoginSucceed:(SAPILoginModel *)freshModel;

/**
 *  补填用户名成功时回调
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didFillUnameSucceed:(SAPILoginModel *)model;

// ============ Deprecated Methods ============

/**
 *  登录成功时回调
 *
 *  NOTE：请使用 sapiManager:didLoginSucceed:extraInfo: 替代。如果实现了 sapiManager:didLoginSucceed:extraInfo: 则回调 sapiManager:didLoginSucceed:extraInfo:，否则回调 sapiManager:didLoginSucceed: 。
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didLoginSucceed:(SAPILoginModel *)model DEPRECATED_MSG_ATTRIBUTE("replaced by sapiManager:didLoginSucceed:extraInfo:");

/**
 *  第三方登录成功时回调
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didOauthLoginSucceed:(SAPILoginModel *)model DEPRECATED_MSG_ATTRIBUTE("use sapiManager:didLoginSucceed:extraInfo: instead");

/**
 *  注册成功时回调，此回调只会在旧版上行短信注册成功时才会调用，其他通过webview注册的时候都是直接调用的登录成功。
 *
 *  @param sapiManager sapiManager实例
 *  @param model       登录模型
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager didRegistVerified:(SAPILoginModel *)model DEPRECATED_MSG_ATTRIBUTE("use -[SAPILoginService registerBySendSMS:timeout:success:failure:] instead");

@end

@interface SAPIMainManager : NSObject

// ====== SAPIMainManager Deprecated Properties ======

// those properties will be removed in a future release.

@property (nonatomic, copy) NSString* imei DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, copy) NSString* deviceIdEncryptKey DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, copy) NSString* packageSign DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, assign) BOOL showLeCaiLogin DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, assign) BOOL showLeCaiRegTip DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, assign) BOOL onePasswordEnabled DEPRECATED_MSG_ATTRIBUTE("Set this property is unnecessary, this property will be removed in a future release");

@property (nonatomic, readonly) NSURL *bindMobileUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *bindEmailUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *rebindMobileUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *rebindEmailUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *unbindMobileUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *unbindEmailUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadBindWidgetURLWithType:bduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *normalizeAccountUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadAccountNormalizationURLWithBduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *accountRecordIndexUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadRecordIndexURLWithBduss:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSURL *changePasswordUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIWebView loadModifyPasswordURLWithBduss:callback:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSString *sinaLoginUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIMainWebView loadThirdOauthLoginWithType:extraParams:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSString *qqLoginUrl DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIMainWebView loadThirdOauthLoginWithType:extraParams:] instead, this property will be removed in a future release and should be avoided");

@property (nonatomic, readonly) NSString *weixinLoginURLString DEPRECATED_MSG_ATTRIBUTE("Use -[SAPIMainWebView loadWeiXinBindURLWithCode:] instead, this property will be removed in a future release and should be avoided");

// ===================================================

// ======== 基础必配参数 ========
// 从6.17.18版本起，请通过-[SAPIMainManager setupTpl:appKey:appId:environmentType:]方法设置这四个基础参数。
@property (nonatomic, assign, readonly) SapiEnvironmentType environmentType;
@property (nonatomic, copy, readonly) NSString *appid;
@property (nonatomic, copy, readonly) NSString *tpl;
@property (nonatomic, copy, readonly) NSString *appkey;
// ============================

@property (nonatomic, copy) NSString* appName;
@property (nonatomic, readonly) NSString* version;
@property (nonatomic, readonly) NSString* voiceProductId;
@property (nonatomic, assign) SAPIShareBindMode shareBindMode;

@property (nonatomic, assign) SAPILoginShareMode loginShareMode;
@property (nonatomic, assign) SAPILoginShareDirection loginShareDirection;
@property (nonatomic, assign) BOOL webNavigationBarHidden;
@property (nonatomic, assign) BOOL cacheEnabled;
@property (nonatomic, assign) BOOL loginOptionHidden;
@property (nonatomic, assign) BOOL showFastRegLink;

// 游客登录，游客帐号不支持互通
@property (nonatomic, assign) BOOL supportGuestLogin;

// 快推登录，开启快推登录的帐号不支持互通
@property (nonatomic, assign) BOOL quickUserLogin;

// 关于声纹登录
@property (nonatomic, assign) BOOL showQuickLogin;
@property (nonatomic, copy) NSString *quickLoginUserName;
@property (nonatomic, assign) BOOL voicePrintLogining;

// 短信登录输入框默认手机号
@property (nonatomic, copy) NSString* inputPlaceholderPhoneNumber;
@property (nonatomic, copy) NSString* fastRegText;
@property (nonatomic, assign) BOOL showRegLink;
@property (nonatomic, assign) BOOL showIPlayout;

@property (nonatomic, strong) NSMutableArray<NSNumber *> *fastLoginOptionList;
@property (nonatomic, copy) NSString* skinUrl;

/**
 *  登录入口显示判断：短信登录页面是否显示普通登录入口 1 显示  0 隐藏
 */
@property (nonatomic, assign) BOOL showLoginLink;

/**
 *  登录入口显示判断：普通登录界面是否显示短信登录入口 1 显示 0 隐藏
 */
@property (nonatomic, assign) BOOL showSMSLoginLink;

/**
 *  简化账号正常化
 */
@property (nonatomic, assign) BOOL simplifyAccountNomailization;

/**
 *  新浪微博、人人等通过oauth认证的第三方登录，每次登录都强制用户输入帐号密码来登录
 */
@property (nonatomic, assign) BOOL isOauthForceLogin;

@property (nonatomic, strong, readonly) NSURL *enhancedShareLoginURL;

/**
 *  腾讯微博登录URL
 */
@property (nonatomic, readonly) NSString *qqWeiboLoginUrl;

/**
 *  新浪微博SSO登录URL
 */
@property (nonatomic, readonly) NSString *sinaSSOLoginUrl;

/**
 *  飞凡Oauth登录URL字符串
 */
@property (nonatomic, readonly) NSString *ffanOauthLoginURLString;

/**
 *  忘记密码URL
 */
@property (nonatomic, readonly) NSString *forgetPwdUrl;

/**
 *  强制绑定相关参数
 */
@property (nonatomic, assign) BOOL connect;

/**
 *   执行绑定、解绑、换绑等功能成功后，是否跳过提示页面
 */
@property (nonatomic, assign) BOOL quickCallbackAfterExecuteBind;

@property (nonatomic, strong) SAPILoginService *loginService;
@property (nonatomic, strong) SAPIRegisterService *registerService;

@property (nonatomic, weak) id<SAPIMainManagerDelegate> delegate;

/**
 *  v6.7.4 新增
 *  当产品线的App版本升级时，是否重新开启一次静默互通。
 *  此参数的设置只在App每个版本第一次启动时有效。
 *  默认为NO。
 */
@property (nonatomic, assign) BOOL silentShareOnUpgrade;

/**
 *  v6.7.6 新增
 *  是否支持无密码注册
 */
@property (nonatomic, assign) BOOL supportNoPwdRegister;

@property (nonatomic, copy) NSString *fastRegSMSChannel;

/**
 *  v6.8.4  新增
 *
 *  短信登录界面是否显示第三方登录入口
 */
@property (nonatomic, assign) BOOL showThirdLoginOnSMSLogin;

/**
 *  v6.8.4  新增
 *
 *  绑定手机时，如果手机号已经被绑定，是否跳转到短信登录界面
 *  如果设置为YES，则在绑定手机冲突时，如果用户点击了手机号登录则会回调SAPIControlPlugin的action_bind_widget_phone_number_exist:方法
 */
@property (nonatomic, assign) BOOL handleBindMobileConflict;

@property (nonatomic, strong, readonly) NSString *SAPICUID;

/**
 *  是否支持海外手机号登录。默认为NO，不支持。
 */
@property (nonatomic, assign) BOOL supportForeignMobile;

/**
 *  短信登录是否支持通过语音验证码登录。默认为YES
 */
@property (nonatomic, assign) BOOL supportVoiceVerifyOnSMSLogin;

/**
 *  线下环境HTTPS开关，默认是YES。
 *  由于线下环境证书为自签名证书，请用Safari打开 http://10.94.19.13:8235/cer/passportqa.cer 安装QA环境根证书
 *
 */
@property (nonatomic, assign) BOOL enabledHTTPSOffline;

/**
 *  是否开启H5登录状态同步，默认为NO。
 * 
 *  @discussion 开启此字段后，将使用如下策略同步Native和H5登录态：
     1. NA为空，H5为空 —— 帐号已同步，不处理
     2. NA为空，H5不为空 —— H5已登录，需要同步到NA，请求getUserInfo，成功H5->NA，失败不处理
     3. NA不为空，H5为空 —— H5退出或Cookie被清空，将NA登录态写回Cookie（如果是H5退出登录，BDUSS失效，需要产品线调logout接口。为方便产品线处理这种情况，SDK 会在这种情况下发送 SAPICookieSyncH5CookieClearedNotification 通知，产品线可监听该通知来触发查询 BDUSS 是否失效，查询 BDUSS 是否有效请用产品线业务接口）
     4. NA不为空，H5不为空
         4.1 NA == H5 —— 帐号已同步，不处理，即同1
         4.2 NA != H5，帐号不同步（可认为H5换号登录），根据策略决定最终状态。若使用NA优先策略，则直接使用NA登录态覆盖H5，若使用H5优先策略，则用H5 BDUSS请求getUserInfo，成功H5->NA，BDUSS失效NA->H5，其他不处理
 *
 */
@property (nonatomic, assign) BOOL enableSyncH5LoginStatus;

/**
 *  NA与H5登录态同步策略
 * 
 *  @see SAPINativeH5SyncStrategy
 */
@property (nonatomic, assign) SAPINativeH5SyncStrategy naH5SyncStrategy;

/**
 *  @brief NA和H5登录态同步成功回调策略
 *
 *  NA和H5登录态同步成功后，按策略回调登录成功。
 *
 *  @see SAPINativeH5SyncCallbackStrategy
 *
 *  @since 6.15.15
 */
@property (nonatomic, assign) SAPINativeH5SyncCallbackStrategy naH5SyncCallbackStrategy;

/**
 *  @brief Native与Webview的通信方式是否使用iframe，默认为NO。
 */
@property (nonatomic, assign) BOOL useIFrame;

/**
 *  @brief 国际化配置项，默认为中文
 */
@property (nonatomic, assign) SAPII18NType i18nType;

/**
 支持生物认证类型
 从8.7.0起，该配置项失效，默认都接入活体能力
 */
@property (nonatomic, assign) SAPIBiometricOptions biometricOptions;

/**
 百度地图CUID，用于数据打通
 */
@property (nonatomic, copy) NSString *baiduMapCuid;

/**
 App Group，给该字段赋值时，会将本地登录帐号与Widget共享。使用SAPIWidget库从Widget中读取当前登录帐号。
 */
@property (nonatomic, copy) NSString *appGroupID;

/**
 微信AppId
 使用微信登录或者帐号中心使用微信关联时需要赋值
 */
@property (nonatomic, copy) NSString *wxAppId;

/**
 微信Scope，默认为snsapi_userinfo
 使用微信登录或者帐号中心使用微信关联时需要赋值
 */
@property (nonatomic, copy) NSString *wxScope;

/**
 安全SDK APPKey，申请请到 http://dev.passport.baidu.com/authorize/safesdk
 */
@property (nonatomic, copy, readonly) NSString *ssdkAppKey;

/**
 安全SDK APPSecretKey，申请请到 http://dev.passport.baidu.com/authorize/safesdk
 */
@property (nonatomic, copy, readonly) NSString *ssdkSecretKey;

/**
 安全SDK初始化完成后回调，会固定在主线程中回调，请使用ssdkInitializeCompletion替代
 */
@property (nonatomic, copy) void(^ssdkInitalCompletion)(void) DEPRECATED_MSG_ATTRIBUTE("replaced by void(^ssdkInitializeCompletion)(NSError *error)");

/**
 安全SDK初始化完成后回调，会固定在主线程中回调，error不为空说明ssdk初始化失败
 */
@property (nonatomic, copy) void(^ssdkInitializeCompletion)(NSError *error);

/**
 安全SDK 初始化参数 hostAppCUID（由宿主产品线提供的CUID）
 产品线如在自己业务中用到安全 SDK，务必传递该参数
 */
@property (nonatomic, copy) NSString *hostAppCUID;

/**
 *  是否校验APP是否是备份恢复安装，若是备份恢复将清除登录信息，用户需要从新登录。默认为NO（不校验）。
 *  注：请在初始化 PASS SDK统一入口之前设置，否则无效
 */
@property (nonatomic, assign) BOOL shouldCheckAppRestored;

/**
 从8.7.0起，该配置项失效，默认接入刷脸登录。请参考文档：http://wiki.baidu.com/pages/viewpage.action?pageId=369625380
 */
@property (nonatomic, assign) BOOL supportFaceLogin;

/**
 是否开启个性化登录，默认为YES
 个性化登录：登录方式展现层级：互通登录>用户自主设置刷脸方式（刷脸登录）>个性化登录（用户上次成功登录的方式）>默认登录方式 
 */
@property (nonatomic, assign) BOOL supportPersonalizedLogin;

/**
 QQ 登录 AppId，接入 QQ SSO 登录时需要赋值
 */
@property (nonatomic, copy) NSString *qqAppId;

/**
 新浪微博 登录 AppKey，接入 新浪微博 SSO 登录时需要赋值
 */
@property (nonatomic, copy) NSString *sinaWeiboAppKey;

/**
 新浪微博 登录 redirectURI，默认设置为 https://passport.baidu.com，若与申请时填写的不一样请重新赋值，否则会报 redirect_uri_mismatch 错误
 */
@property (nonatomic, copy) NSString *sinaRedirectURI;

/**
 宿主App的Scheme
 */
@property (nonatomic, copy) NSString *appScheme;

@property (nonatomic, strong) PASSFaceIDService *faceIDService;

/**
 上次用户成功登录方式
 */
@property (nonatomic, assign, readonly) PASSLastLoginType lastLoginType;

/**
 当前是否登录
 */
@property (nonatomic, assign, readonly) BOOL isLogin;

/**
 初始化 PASS SDK 统一入口

 申请TPL，APPKEY，APPID参数请到 http://dev.passport.baidu.com/authorize/index
 
 @param tpl 产品线标识
 @param appKey APPKey
 @param appId APPID
 @param environmentType 环境类型
 */
- (void)setupTpl:(NSString *)tpl appKey:(NSString *)appKey appId:(NSString *)appId environmentType:(SapiEnvironmentType)environmentType ssdkAppKey:(NSString *)ssdkAppKey ssdkSecretKey:(NSString *)ssdkSecretKey;

/**
 *  当前登录Model
 *
 *  @return 如果为nil，则当前没有登录账号
 */
- (SAPILoginModel *)currentLoginModel;

/**
 *  登录帐号列表
 *
 *  @return 帐号列表
 */
- (NSArray *)localLoginModelList;

/**
 *  互通帐号列表
 *
 *  @return 帐号列表
 */
- (NSArray *)sharedLoginModelList;

/**
 *  用现有模型登录(含互通)， 若需要保存本次登录类型，请使用 loginWithLoginModel:loginType:
 *
 *  @param model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成功。
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model;

/**
 用现有模型登录(含互通)，若不需要保存本次登录类型，请使用 loginWithLoginModel:

 @param model     构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成功。
 @param Type      需要保存的本次登录类型
 @param userInfo  透传参数，该参数将透传至 didLoginSuccess 方法的 extraInfo 字段中，Key 为 userInfo
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model loginType:(PASSLastLoginType)Type userInfo:(NSDictionary *)userInfo;

/**
 *  清除所用快捷登录选项
 */
- (void)clearLoginOptions;

/**
 *  添加快捷登录选项
 *
 *  @param optionType 快捷登录选项
 */
- (void)addLoginOption:(SAPILoginOptionType)optionType;

/**
 *  取消当前SAPI所有网络请求
 */
- (void)clearAllRequest;

/**
 *  云端同步 (回调)
 *
 *  @param completion 完成时回调
 *  @param error      失败时回调
 */
- (void)syncCacheOnCompletion:(void (^)(void))completion error:(void (^)(void))error;

/**
 *  清除内存中缓存的登录页
 */
- (void)clearCachePage;

/**
 *  pass cookies可信任domain
 */
- (NSArray *)getCookiesAuthorizedDomainList;

/**
 *  获取糯米强制绑定地址
 */
- (NSURL *)enforceBindingURLWithToken:(NSString *)token
                               adtext:(NSString *)adtext
                               adhref:(NSString *)adhref
                            returnURL:(NSString *)returnURLStr;

/**
 *  获取强制绑定地址
 */
- (NSURL *)accountBindingURLWithToken:(NSString *)token
                               adtext:(NSString *)adtext
                               adhref:(NSString *)adhref
                            returnURL:(NSString *)returnURLStr;

/**
 *  安全验证url
 */
- (NSURL *)getAuthWidgetUrlWithToken:(NSString *)token
                           returnURL:(NSString *)returnUrl;

/**
 *  v6.7.8 新增
 *  重置静默互通状态
 *  重置后可以再次开启一次静默互通
 */
- (void)resetSilentShareLogin;

/**
 *  SAPIMainManger单例
 */
+ (SAPIMainManager *)sharedManager;

/**
 获取安全 SDK ZID
 该接口返回一个字典，Key 为 @"0" 表示 ZID，ZID 可能会变，产品线不应该缓存 ZID，而是每次需要时调用接口获取
 
 @param eventID 事件ID，由安全SDK分配
 若不涉及到安全性操作，仅期望简单获取zid时，eventID 传@"0"
 
 @important 从8.5.0版本起，产品线自身业务如需接入安全SDK，强烈建议直接调用安全SDK相关接口，无需通过PASS SDK调用，具体接入方式参考SSDKLib.h。该接口在未来可能会被废弃，建议尽量避免使用。
 
 return 返回数据
 
 */
- (NSDictionary *)activeSSDKWithEventID:(NSInteger)eventID;

@end

@interface SAPIMainManager (SAPIRedirect)

/**
 判断url字符串类型

 @param urlString url字符串
 @return 类型
 */
- (SAPINativeURLType)checkNativeURLType:(NSString *)urlString;

@end
