//
//  AppConfig.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#ifndef AppConfig_h
#define AppConfig_h

///登录状态
#define Login_type @"1"

///环境参数
#define Production @"1"

#define BaseUrl  @"http://10.31.6.130:8070/icps"

#define kBaseURL @"http://10.31.5.65/base"

#define BannerURL @"http://10.31.5.66/"


///默认字体
#define DEFAULT_FONT(a) \
({\
UIFont *font = [UIFont fontWithName:@"PingFangSC-Regular" size:a*SCALE_2X];\
if (!font)\
font =  [UIFont systemFontOfSize:a*SCALE_2X];\
font;\
})\


///状态栏样式
#define kStatusBarStyle UIStatusBarStyleDefault

///界面View背景颜色
#define kViewBackgroundColor RGB(245, 246, 247)

#define kPublicGreen RGB(0, 167, 84)

#define kLineColor RGB(233, 241, 252)

///友盟别名
#define UMTokenName @"UMENGTEST"

#endif /* AppConfig_h */
