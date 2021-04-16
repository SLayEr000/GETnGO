//
//  PASSBaseViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/3/31.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 这是一个空的协议，加入的初始目的是为了区分PASS SDK自己的ViewController
 */
@protocol PASSViewControllerCloseDelegate <NSObject>

@end

@class PASSBaseViewController;

/**
 自定义回调代理
 
 SDK 内部可能存在新开页面的情况，这些方法可能回调多次，建议这些方法实现时动态创建 View 而不是使用实例变量
 
 建议：
 @code
 - (UILabel *)passViewControllerCustomTitleLabel:(PASSBaseViewController *)viewController {
     UILabel *label = [[UILabel alloc] init];
     // ....
     return label;
 }
 @endcode
 
 不建议：
 @code
 - (UILabel *)passViewControllerCustomTitleLabel:(PASSBaseViewController *)viewController {
     return self.customTitleLabel;
 }
 @endcode
 
 */
@protocol PASSViewControllerUIDelegate <NSObject>

@optional

/**
 自定义 View 背景颜色，默认为白色
 
 <p>
 有一点需要注意：
 登录页使用 Web 自带导航栏时（默认使用 Web 导航栏，除非将 preferredNavigationBarShown 设置成 YES），可通过 sapi-custom-style.css 文件修改导航栏的背景颜色，状态栏颜色由 View 颜色控制，为保持状态栏和导航栏颜色一致，应该实现该方法并针对登录页设置 View 的背景颜色，且背景颜色和 sapi-custom-style.css 中 pass-header 的 background 属性保持一致。参考代码：
 @code
 - (UIColor *)passViewControllerCustomViewBackgroundColor:(PASSBaseViewController *)viewController {
     if ([viewController isKindOfClass:[PASSLoginViewController class]]) {
         return [UIColor sapi_colorWithHex:0xf8f8f8];   // 0xf8f8f8 为 sapi-custom-style.css 中 pass-header 的 background 属性值
     }
     return nil;     // 其他返回 nil 表示使用默认的颜色，即白色
 }
 @endcode
 </p>
 
 @param viewController 当前 viewController 实例
 @return 返回 View 的自定义背景颜色，返回 nil 表示使用默认的
 */
- (UIColor *)passViewControllerCustomViewBackgroundColor:(PASSBaseViewController *)viewController;

/**
 自定义导航栏标题
 
 @param viewController 当前 viewController 实例
 @return 返回自定义标题栏，返回 nil 表示使用默认的
 */
- (UILabel *)passViewControllerCustomTitleLabel:(PASSBaseViewController *)viewController;

/**
 自定义导航栏标题颜色

 @param viewController 当前 viewController 实例
 @return 返回自定义标题栏字体颜色，返回 nil 表示使用默认的
 */
- (UIColor *)passViewControllerCustomTitleLabelTextColor:(PASSBaseViewController *)viewController;

/**
 自定义返回按钮
 
 自定义的返回按钮按下时调用 handleBackAction 方法处理返回行为，如：
 
 @code
 [btn addTarget:viewController action:@selector(handleBackAction) forControlEvents:UIControlEventTouchUpInside];
 @endcode
 
 如需要自定义返回行为，建议对 ViewController 进行扩展
 
 如需要自定义右边按钮，请通过 rightBarButtonItem 实现，如：
 @code
 PASSLoginViewController *loginVC = [[PASSLoginViewController alloc] initWithLoginWay:PASSLoginWayAccount];
 loginVC.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(handleRightItem)];
 @endcode
 
 @param viewController 当前 ViewController 实例
 @return UIBarButtonItem 实例，返回 nil 时表示使用默认的
 
 */
- (UIBarButtonItem *)passViewControllerCustomBackBarButtonItem:(PASSBaseViewController *)viewController;

/**
 自定义返回按钮图片

 @param viewController 当前 ViewController 实例
 @return 按钮图片实例，返回 nil 表示使用默认的
 */
- (UIImage *)passViewControllerBackBarButtonImage:(PASSBaseViewController *)viewController;

/**
 自定义错误页

 错误页的重试按钮调用 handleErrorRetry 方法进行重试处理
 
 @code
 - (UIView *)passViewControllerCustomErrorView:(PASSBaseViewController *)viewController {
    UIView *errorView = [[UIView alloc] init];
    // ...
    UIButton *retryBtn = [[UIButton alloc] init];
    [retryBtn addTarget:viewController action:@selector(handleErrorRetry) forControlEvents:UIControlEventTouchUpInside];
    // ...
    return errorView;
 }
 @endcode
 
 如需要自定义重试行为，建议对 ViewController 进行扩展
 
 如需要显示不同的文案，可以创建一个 UILabel 实例并赋值 tag 为 kPASSViewControllerErrorViewTipsLabelTag

 @param viewController 当前 ViewController 实例
 @return 自定义错误页实例，返回 nil 表示使用默认的
 */
- (UIView *)passViewControllerCustomErrorView:(PASSBaseViewController *)viewController;

/**
 自定义 StatusBar 样式

 @param viewController 当前 ViewController 实例
 @return StatusBar 样式
 */
- (UIStatusBarStyle)passViewControllerPreferredStatusBarStyle:(PASSBaseViewController *)viewController;

@end

FOUNDATION_EXPORT NSInteger const kPASSViewControllerErrorViewTipsLabelTag;

/**
 ViewController基类
 */
@interface PASSBaseViewController : UIViewController <PASSViewControllerCloseDelegate>

/**
 UI 代理，可实现代理方法进行自定义 View
 */
@property (nonatomic, weak) id<PASSViewControllerUIDelegate> uiDelegate;

/**
 导航栏标题
 */
@property (nonatomic, strong, readonly) UILabel *titleLabel;

/**
 导航栏返回按钮
 */
@property (nonatomic, strong, readonly) UIBarButtonItem *backBarButtonItem;

/**
 导航栏返回按钮图片
 */
@property (nonatomic, strong, readonly) UIImage *backBarButtonImage;

/**
 错误提示页
 */
@property (nonatomic, strong, readonly) UIView *errorView;

/**
 背景颜色，默认为白色
 */
@property (nonatomic, strong) UIColor *backgroundColor DEPRECATED_MSG_ATTRIBUTE("Implement -[PASSViewControllerUIDelegate passViewControllerCustomViewBackgroundColor:] instead");

/**
 页面关闭回调
 
 userInfo：页面关闭相关回调参数，目前包含以下字段：
 isAccountDestroyed：BOOL 值，表示是否帐号注销
 isAccountFrozen: BOOL 值，表示是否帐号冻结
 */
@property (nonatomic, copy) void(^finishHandler)(NSDictionary *userInfo) DEPRECATED_MSG_ATTRIBUTE("use closeHandler and return YES instead");

/**
 页面关闭回调，注意：只有使用 closeViewController 及其重载方法关闭页面时才有回调。
 
 @params userInfo：页面关闭相关回调参数，目前包含以下字段：
            isAccountDestroyed：BOOL 值，表示是否帐号注销
            isAccountFrozen: BOOL 值，表示是否帐号冻结
 
 @return 返回YES时表示关闭页面；返回NO时表示不关闭页面，产品线自行关闭
 */
@property (nonatomic, copy) BOOL(^closeHandler)(NSDictionary *userInfo);

/**
 发生错误时回调
 block 返回 YES 表示显示错误页，返回 NO 表示不显示错误页，默认显示
 */
@property (nonatomic, copy) BOOL(^errorHandler)(NSError *error);

/**
 设置子视图
 该方法会在 viewDidLoad 方法内调用，子类可重写该方法增加其他布局，并根据需要决定是否调用 [super setupViews]
 */
- (void)setupViews;

/**
 显示错误提示页

 @param message 错误提示文案
 */
- (void)showErrorViewWithMessage:(NSString *)message;

/**
 隐藏错误提示页
 */
- (void)hideErrorView;

/**
 关闭当前页面
 */
- (void)closeViewController;

/**
 关闭页面

 @param userInfo 透传参数，该参数会被透传到 finishHandler 的回调参数中
 */
- (void)closeViewControllerWithUserInfo:(NSDictionary *)userInfo;

/**
 处理返回按钮，子类可重写该方法自定义返回按钮行为
 */
- (void)handleBackAction;

/**
 处理重试行为
 */
- (void)handleErrorRetry;

/**
 更新底返回框架
 */
- (void)updateBottomNavigator;

@end
