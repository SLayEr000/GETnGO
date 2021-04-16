//
//  SAPIWebView.h
//  SAPIBridge
//
//  Created by Vinson.D.Warm on 9/3/13.
//  Copyright (c) 2013 SAPI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SAPIPlugin.h"
#import "SAPIDefine.h"

@class SAPIWebView;
@class SAPILoginModel;
@class PASSLoginConfig;
@protocol SAPIWebViewBridgeDelegate;
@protocol SAPIWebViewLogDelegate;

@protocol SAPIWebViewDelegate <NSObject>

@optional
- (BOOL)sapiWebView:(SAPIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
- (void)sapiWebViewDidStartLoad:(SAPIWebView *)webView;
- (void)sapiWebViewDidFinishLoad:(SAPIWebView *)webView;
- (void)sapiWebView:(SAPIWebView *)webView didFailLoadWithError:(NSError *)error;

@end

@interface SAPIWebView : UIWebView

@property (nonatomic, strong) SAPIPlugin *plugin;

@property (nonatomic, strong) NSMutableArray *plugins DEPRECATED_MSG_ATTRIBUTE("This property is deprecated, this property will be removed in a future release");

@property (nonatomic, weak) id<SAPIWebViewDelegate> webViewDelegate;

// DONT SETUP THIS PROPERTY
// DONT SETUP THIS PROPERTY
@property (nonatomic, weak) id<SAPIWebViewBridgeDelegate> bridgeDelegate;

// DONT SETUP THIS PROPERTY
// DONT SETUP THIS PROPERTY
@property (nonatomic, weak) id<SAPIWebViewLogDelegate> logDelegate;

/**
 SAPIWebView 外链处理回调。应在回调中打开SAPIWebViewController。
 回调中的 `userInfo` 字段中包含URL和Title等信息，可以在 `SAPIWebView+SAPIConstantAddition.h` 找到相应的 Key.
 
 Important 必须在调用 `-[SAPIWebView load:]` 之前设置，否则无效。
 
 */
@property (nonatomic, copy) void(^externalPageHandler)(NSDictionary *userInfo);

// 自定义 css 样式文件路径
@property (nonatomic, strong) NSURL *customCssStyleFileURL;

- (id)initWithPlugin:(SAPIPlugin *)plugin;

- (void)load:(NSURL *)url;

- (void)load:(NSURL *)url cookies:(NSArray *)cookies;

- (void)addPlugin:(SAPIPlugin *)plugin;

- (BOOL)historyBack;

- (NSURL *)currentURL;

- (void)addBlackListModule:(NSURL *)url;

- (void)clean;

/**
 *  在注册、登录界面采用native导航栏时，如果需要回退到上一个webview页面时可调用此方法
 *
 *  v6.7.10新增
 *
 *  调用时有以下两种情况：
 *  1.如果webview可以回退，则会回退到上一个页面；
 *  2.如果不能回退，则会调用注册到webview的SAPIControlPlugin中的finish:方法来关闭整个视图控制器（或执行其他操作）
 */
- (void)sapiWebViewGoBackIfPossible;

/**
 在登录页面填写用户名

 @param username 用户名
 */
- (void)fillLoginPageUsername:(NSString *)username;

@end

@interface SAPIWebView (SAPIWebViewLoadLoginAddtion)

/**
 加载登录 URL
 
 @param type 登录类型
 @param params 透传参数
 */
- (void)loadLoginWithType:(SAPILoginType)type extraParams:(NSDictionary *)params;

/**
 加载 SAPI 登录验证 URL
 
 @param urlString URL 字符串
 */
- (void)loadLoginVerifyWithURLString:(NSString *)urlString;

/**
 加载登录 URL

 @param config 登录参数
 @param params 透传参数
 */
- (void)loadLoginWithConfig:(PASSLoginConfig *)config extraParams:(NSDictionary *)params;

@end

@interface SAPIWebView (SAPIWebViewLoadAccountAddition)

/**
 对游客帐号进行正常化

 @param bduss 需要正常化帐号的bduss
 @param params 透传参数。键值为中文或特殊字符时需要URL Encode后传入。
 */
- (void)loadGuestNormalizationURLWithBduss:(NSString *)bduss extraParams:(NSDictionary *)params;

/**
 *  对半帐号进行正常化
 *
 *  @param bduss    需要正常化帐号的bduss
 *  @param callback 正常化以后的回调。正常化成功时会回传一个SAPILoginModel实例；失败时会回传一个NSError实例
 */
- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss callback:(void(^)(SAPILoginModel *model, NSError *error))callback;

/**
 *  对半帐号进行正常化
 *
 *  @param bduss      需要正常化帐号的bduss
 *  @param input      正常化时是否需要输入密码：YES表示需要输入密码；NO表示不需要输入密码
 *  @param callback   正常化以后的回调。正常化成功时会回传一个SAPILoginModel实例；失败时会回传一个NSError实例
 */
- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss shouldInputPassword:(BOOL)input callback:(void(^)(SAPILoginModel *model, NSError *error))callback;

/**
 *  修改密码
 *
 *  @param bduss      需要修改密码的bduss
 *  @param callback   修改密码回调。error为空，表明修改密码成功，否则修改密码失败。loginModel不为空，表明更新当前登录模型成功，否则更新当前登录模型失败。
 */
- (void)loadModifyPasswordURLWithBduss:(NSString *)bduss callback:(void (^)(SAPILoginModel *loginModel, NSError *error))callback;

/**
 *  修改密码
 *
 *  @param bduss      需要修改密码的bduss
 *  @param params     透传参数
 *  @param callback   修改密码回调。error为空，表明修改密码成功，否则修改密码失败。loginModel不为空，表明更新当前登录模型成功，否则更新当前登录模型失败。
 */
- (void)loadModifyPasswordURLWithBduss:(NSString *)bduss extraParams:(NSDictionary *)params callback:(void (^)(SAPILoginModel *loginModel, NSError *error))callback;

/**
 *  操作记录
 *
 *  @param bduss bduss
 */
- (void)loadRecordIndexURLWithBduss:(NSString *)bduss;

/**
 加载帐号中心

 @param bduss 用户BDUSS
 */
- (void)loadAccountCenterWithBduss:(NSString *)bduss;

/**
 加载帐号中心

 @param bduss 登录态
 @param params 透传参数。键值为中文或特殊字符时需要URL Encode后传入。
 */
- (void)loadAccountCenterWithBduss:(NSString *)bduss extraParams:(NSDictionary *)params;

/**
 加载帐号检测
 
 @param bduss 登录态
 @param params 透传参数。键值为中文或特殊字符时需要URL Encode后传入。
 */
- (void)loadAccountDetectWithBduss:(NSString *)bduss extraParams:(NSDictionary *)params;

/**
 加载帐号安全中心。帐号安全中心包括找回密码、帐号申诉和找回帐号功能

 @param params 额外的参数，没有时传 nil 即可。
 */
- (void)loadAccountSecurityCenterWithExtraParams:(NSDictionary *)params;

@end

@interface SAPIWebView (SAPIWebViewLoadBindManageAddition)

/**
 *  加载绑定控件。绑定手机、换绑手机、解绑手机、绑定邮箱、换绑邮箱、解绑邮箱都可以通过该方法调用
 *
 *  注意：通过该方法调用绑定控件，将不会显示WebView的导航栏，需要自行显示NavigationBar导航栏。
 *
 *  @param type     绑定控件类型
 *  @param bduss    bduss
 *  @param callback 回调
 */
- (void)loadBindWidgetURLWithType:(SAPIBindWidgetType)type
                            bduss:(NSString *)bduss
                         callback:(void (^)(NSError *error))callback;

/**
 *  加载绑定控件。绑定手机、换绑手机、解绑手机、绑定邮箱、换绑邮箱、解绑邮箱都可以通过该方法调用
 *
 *  注意：通过该方法调用绑定控件，将不会显示WebView的导航栏，需要自行显示NavigationBar导航栏。
 *
 *  @param type     绑定控件类型
 *  @param bduss    bduss
 *  @param extraParams 额外参数，没有时传 nil
 *  @param callback 回调
 */
- (void)loadBindWidgetURLWithType:(SAPIBindWidgetType)type
                            bduss:(NSString *)bduss
                      extraParams:(NSDictionary *)extraParams
                         callback:(void (^)(NSError *error))callback;

/**
 *  绑定手机时，如果该手机已被绑定，同时配置[SAPIMainManager sharedManager].handleBindMobileConflict为YES，
 *  在用户点击“手机号登录”选项时则会回调此代码块。
 *
 *  @param bindConflictBlock 回调代码块，当配置[SAPIMainManager sharedManager].handleBindMobileConflict为YES时，bindConflictBlock必须不能为空。
 */
- (void)setHandleBindConflictBlock:(void(^)(NSDictionary *params))bindConflictBlock;

@end

@interface SAPIWebView (SAPIWebViewDeprecatedCategory)

- (void)load:(NSURL *)url cookies:(NSArray *)cookies persistentBduss:(BOOL)persistent DEPRECATED_MSG_ATTRIBUTE("Use load:cookies: instead");

- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void(^)(SAPILoginModel *model, NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadAccountNormalizationURLWithBduss:callback: instead");

- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent shouldInputPassword:(BOOL)input callback:(void(^)(SAPILoginModel *model, NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadAccountNormalizationURLWithBduss:shouldInputPassword:callback: instead");

- (void)loadModifyPasswordURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(SAPILoginModel *loginModel, NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadModifyPasswordURLWithBduss:callback: instead");

- (void)loadBindMobileURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

- (void)loadRebindMobileURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

- (void)loadUnbindMobileURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

- (void)loadBindEmailURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

- (void)loadRebindEmailURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

- (void)loadUnbindEmailURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void (^)(NSError *error))callback DEPRECATED_MSG_ATTRIBUTE("Use loadBindWidgetURLWithType:bduss:callback: instead");

@end
