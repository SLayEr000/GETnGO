//
//  PASSPopLoginInputView.h
//  popLogin
//
//  Created by Gang,Liu on 2018/4/27.
//  Copyright © 2018年 Gang,Liu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PASSError.h"

@class PASSLoginInputView;
@protocol PASSLoginInputViewDelegate <NSObject>

@required
/**
 登录成功 事件

 @param inputView  回传的控件
 @param loginModel 登陆成功后的 model
 */
- (void)passLoginInputView:(PASSLoginInputView *)inputView didLoginSuccess:(SAPILoginModel *)loginModel;

/**
 回退 事件

 @param inputView 回传的控件
 @param phoneNum  回传的手机号
 */
- (void)passLoginInputView:(PASSLoginInputView *)inputView needBackWithPhoneNum:(NSString *)phoneNum error:(PASSError *)error;

@optional
/**
 将要发起登录 事件
 
 @param inputView  回传的控件
 */
- (void)passLoginInputViewWillLogin:(PASSLoginInputView *)inputView;

/**
 登录失败 事件

 @param inputView 回传的控件
 @param error     登陆失败的 error
 */
- (void)passLoginInputView:(PASSLoginInputView *)inputView didLoginFailed:(PASSError *)error;

/**
 获取验证码成功 事件
 
 @param inputView 回传的控件
 @param info      获取验证码成功返回的 info
 */
- (void)passLoginInputView:(PASSLoginInputView *)inputView getDpassSuccess:(NSDictionary *)info;

/**
 获取验证码失败 事件

 @param inputView 回传的控件
 @param error     获取验证码失败的 error
 */
- (void)passLoginInputView:(PASSLoginInputView *)inputView getDpassFailed:(PASSError *)error;

/**
 验证码输入框展示 事件

 @param inputView 回传的控件
 */
- (void)passLoginInputViewWillShowVerifyCodeField:(PASSLoginInputView *)inputView;

/**
 验证码输入框隐藏 事件
 
 @param inputView 回传的控件
 */
- (void)passLoginInputViewWillHideVerifyCodeField:(PASSLoginInputView *)inputView;

@end

/**
 需要回退的错误码枚举

 - PASSLoginBackErrorCodeUnreg: 账号未注册
 - PASSLoginBackErrorCodeSecondCard: 二次卡
 */
typedef NS_ENUM(NSInteger, PASSLoginBackErrorCode) {
    PASSLoginBackErrorCodeUnreg = 12,
    PASSLoginBackErrorCodeSecondCard = 30,
};

@interface PASSLoginInputView : UIView

@property (nonatomic, weak) id<PASSLoginInputViewDelegate> delegate;

/**
 手机号输入框
 */
@property (nonatomic, strong, readonly) UITextField *acountField;

/**
 验证码输入框
 */
@property (nonatomic, strong, readonly) UITextField *verifyCodeField;

/**
 * 短信框登录，登录时候产品线透传字段
 *
 * 字段规范：
 *  1. 字段格式为 json，需要 URL Encode 后传入；
 *  2. URL Encode 后的长度不能超过 100 字节。
 *
 * 如需上传UA、产品线CUID，请通过该字段传递
 */
@property (nonatomic, copy) NSString *smsLoginStatExtra;

/**
 可传入控件内的适配因子，默认为屏幕宽度比例

 @param scaledFactor 适配因子,大于0
 @return PASSLoginInputView
 */
- (instancetype)initWithScaledFactor:(CGFloat)scaledFactor;

/**
 清空手机号输入框内容并且隐藏验证码输入框
 */
- (void)clearAccountField;

@end
