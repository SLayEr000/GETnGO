//
//  PassportKit.h
//  PassportKit
//
//  Created by jiangzhenjie on 2017/3/31.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <UIKit/UIKit.h>

FOUNDATION_EXPORT double PassportKitVersionNumber;

FOUNDATION_EXPORT const unsigned char PassportKitVersionString[];

// 工具 & 框架
#import <PassportKit/SAPIJSONUtility.h>
#import <PassportKit/SAPIInvokeCommand.h>
#import <PassportKit/SAPIPlugin.h>
#import <PassportKit/SAPIWebView.h>
#import <PassportKit/SAPIMainWebView.h>
#import <PassportKit/SAPIURLFactory.h>

// SAPI基本类型定义
#import <PassportKit/SAPIDefine.h>

// SAPI通用模型
#import <PassportKit/SAPILoginModel.h>
#import <PassportKit/SAPIOAuthInfo.h>

// SAPI管理组件
#import <PassportKit/SAPILoginService.h>
#import <PassportKit/SAPIRegisterService.h>
#import <PassportKit/SAPIMainManager.h>
#import <PassportKit/SAPILogService.h>

// WKWebView Cookie 同步
#import <PassportKit/WKUserContentController+SAPIH5LoginSyncAddition.h>

#import <PassportKit/SAPIWebView+SAPIConstantAddition.h>

// Utility
#import <PassportKit/NSString+SAPIStringAdditions.h>
#import <PassportKit/NSDictionary+SAPIDictionaryAddition.h>
#import <PassportKit/NSURL+SAPIURLAdditions.h>
#import <PassportKit/PASSViewControllerTerminator.h>

// Controller
#import <PassportKit/PASSBaseViewController.h>
#import <PassportKit/PASSWebViewController.h>
#import <PassportKit/PASSLoginViewController.h>
#import <PassportKit/PASSAccountCenterViewController.h>
#import <PassportKit/PASSAccountSecurityCenterViewController.h>
#import <PassportKit/PASSBindWidgetViewController.h>
#import <PassportKit/PASSModifyPasswordViewController.h>
#import <PassportKit/UIViewController+PASSConvenient.h>
#import <PassportKit/UINavigationController+PASSConvenient.h>
#import <PassportKit/PASSThirdLoginViewController.h>
#import <PassportKit/PASSUserAgreementViewController.h>
#import <PassportKit/PASSAccountRealNameViewController.h>
#import <PassportKit/PASSAccountRecordViewController.h>
#import <PassportKit/PASSAccountAppealViewController.h>
#import <PassportKit/PASSAccountDestroyViewController.h>
#import <PassportKit/PASSHelpCenterViewController.h>
#import <PassportKit/PASSAccountWebViewController.h>
#import <PassportKit/PASSQRCodeLoginViewController.h>
#import <PassportKit/PASSAccountDetectViewController.h>
#import <PassportKit/PASSGuestNormalizeViewController.h>
#import <PassportKit/PASSShareAuthorizeViewController.h>

//View
#import <PassportKit/PASSLoginInputView.h>

#import <PassportKit/PASSRouter.h>
#import <PassportKit/PASSLoginConfig.h>
#import <PassportKit/PASSError.h>

// FaceID
#import <PassportKit/PASSFaceIDService.h>

// PASS OpenURL Handler
#import <PassportKit/PASSOpenURLHandler.h>
#import <PassportKit/PASSShareLoginOpenURLHandler.h>

