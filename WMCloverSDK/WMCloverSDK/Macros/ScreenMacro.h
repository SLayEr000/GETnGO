//
//  ScreenMacro.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#ifndef ScreenMacro_h
#define ScreenMacro_h

///屏幕比例
#define SCALE_2X ([UIScreen mainScreen].bounds.size.width/375.0)


///判断iPhone 尺寸
#define iPhone35     480 == [UIScreen mainScreen].bounds.size.height
#define iPhone40     568 == [UIScreen mainScreen].bounds.size.height
#define iPhone47     667 == [UIScreen mainScreen].bounds.size.height
#define iPhone55     736 == [UIScreen mainScreen].bounds.size.height
#define iPhoneX      812 == [UIScreen mainScreen].bounds.size.height

#define Device_Is_iPhoneX ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), [[UIScreen mainScreen] currentMode].size) : NO)

///iPhone xs max
#define iPhone65     896 == [UIScreen mainScreen].bounds.size.height

///屏幕高度
#define kScreenHeight       [UIScreen mainScreen].bounds.size.height

///屏幕宽度
#define kScreenWidth        [UIScreen mainScreen].bounds.size.width

/// 状态栏高度
#define StatusBarHeight         [[UIApplication sharedApplication] statusBarFrame].size.height

/// 导航栏高度
#define NavigationBarHeight     (StatusBarHeight + 44)

#define kIs_iphone (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)

#define kIs_iPhoneX kScreenWidth >=375.0f && kScreenHeight >=812.0f&& kIs_iphone

#define kTabBarHeight (CGFloat)(kIs_iPhoneX?(49.0 + 34.0):(49.0))

#endif /* ScreenMacro_h */
