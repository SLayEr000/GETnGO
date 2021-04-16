//
//  PASSWebViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/3/31.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import "PASSBaseViewController.h"
#import "SAPIMainWebView.h"

@class PASSWebViewController;
@protocol PASSWebViewControllerNavigationDelegate <NSObject>

@optional
- (void)webViewController:(PASSWebViewController *)webViewController didReceivedParams:(NSDictionary *)params;

@end

/**
 加载动画代理
 */
@protocol PASSWebViewControllerLoadingDelegate <NSObject>

@optional

/**
 显示 Loading，需要在回调中创建或者显示 loading 视图，并且启动 loading 动画

 @param webViewController controller实例
 @param view loadingView 的父视图，一般回传为 controller 的 root view
 */
- (void)passWebViewController:(PASSWebViewController *)webViewController startLoadingInView:(UIView *)view;

/**
 隐藏 Loading，需要在回调中停止 loading 动画，并且移除或者隐藏 loading 视图

 @param webViewController controller实例
 */
- (void)passWebViewController:(PASSWebViewController *)webViewController endLoadingInView:(UIView *)view;

@end

// 接入方可以使用该Tag标记LoadingView，防止Tag重复
FOUNDATION_EXPORT NSInteger const kPASSWebViewControllerLoadingViewTag;

/**
 WebView控制器基类
 */
@interface PASSWebViewController : PASSBaseViewController <SAPIMainWebViewDelegate>

/**
 控制器持有的WebView实例
 */
@property (nonatomic, strong, readonly) SAPIMainWebView *webView;

/**
 页面加载路径
 */
@property (nonatomic, strong) NSURL *url;

/**
 是否显示进度条，默认为YES
 */
@property (nonatomic, assign) BOOL showProgress;

/**
 是否允许在WebView加载完成后动态更新标题，默认为YES
 */
@property (nonatomic, assign) BOOL enableUpdateTitle;

/**
 额外的查询字符串参数，这些参数将直接拼接在URL后面
 注意：key 和 value 如果是非 URL 允许字符，需要 URL Encode 后传入
 */
@property (nonatomic, strong) NSDictionary *extraQueryParams;

/**
 导航代理
 */
@property (nonatomic, weak) id<PASSWebViewControllerNavigationDelegate> navigationDelegate;

/**
 打开登录页回调，产品线在该回调中调起自己的登录页面。
 <p>
 某些流程可能触发登录，建议产品线实现该回调。
 注意，如不实现该回调，将打开默认的登录页。
 </p>
 */
@property (nonatomic, copy) void(^presentLoginVCHandler)(NSDictionary *userInfo);

/**
 加载动画代理
 */
@property (nonatomic, weak) id<PASSWebViewControllerLoadingDelegate> loadingDelegate;

/**
 页面当前URL Request
 */
@property (nonatomic, strong, readonly) NSURLRequest *currentRequest;

/**
 日志打点透传字段
 
 字段规范：
 1. 字段格式为 json，需要 URL Encode 后传入；
 2. URL Encode 后的长度不能超过 100 字节。
 */
@property (nonatomic, copy) NSString *statExtra;

/**
 初始化页面

 @param url 路径
 @return WebView 控制器实例
 */
- (instancetype)initWithURL:(NSURL *)url;

/**
 初始化页面
 
 @param urlString 路径字符串
 @return WebView 控制器实例
 */
- (instancetype)initWithURLString:(NSString *)urlString;

/**
 加载WebView，子类可重写该方法自定义加载行为
 */
- (void)loadWebView;

/**
 重新加载当前URL
 */
- (void)reloadWebView;

/**
 是否支持侧滑返回
 
 @return YES 表示支持，NO 表示不支持
 */
- (BOOL)supportInteractivePopGesture;

/**
 页面是否可以回退

 @return YES 表示可以回退，NO表示不可以
 */
- (BOOL)pageCanGoBack;

@end
