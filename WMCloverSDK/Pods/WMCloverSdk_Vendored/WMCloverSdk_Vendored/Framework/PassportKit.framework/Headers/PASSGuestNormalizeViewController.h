//
//  PASSNormalizeGuestViewController.h
//  PassportKit
//
//  Created by Gang,Liu on 2018/6/5.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <PassportKit/PassportKit.h>

typedef NS_ENUM(NSInteger, PASSGuestNormalizeResult) {
    PASSGuestNormalizeResultSuccess = 0, //正常化成功
    PASSGuestNormalizeResultMerge,       //合并帐号
    PASSGuestNormalizeResultFailed,      //正常化失败
};

@interface PASSGuestNormalizeViewController : PASSAccountWebViewController

/**
 正常化以后的回调, 使用者需在此回调内自己关闭 PASSGuestNormalizeViewController 页面。
 result: 正常化结果 PASSNormalizeResult 类型
 model : 正常化成功、合并帐号后返回的 SAPILoginModel 实例
 error : 失败时会回传一个PASSError实例
 */
@property (nonatomic, copy) void(^normalizeCompolition)(PASSGuestNormalizeResult result, SAPILoginModel *model, PASSError *error);

@end
