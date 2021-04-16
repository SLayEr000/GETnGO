//
//  WMCommon.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import <Foundation/Foundation.h>


@interface WMCommon : NSObject

///判断是否手机系统的是否是12小时制 yes为12小时制 no为24小时制
BOOL isHasAMPM(void);

///获取唯一uuid
+ (NSString *_Nullable)GetOnlyUUID;

///判断对象是否为空
+ (BOOL)isBlankObject:(id _Nullable )targetObejct;

///获取当前时间戳
+ (NSString *_Nullable)GetNowTimeStamp;

///字典转为json字符串
+ (NSString *_Nullable)dictToJOSNString:(NSDictionary *_Nullable)dict;

///json string转为对象
+ (NSDictionary *_Nullable)convertjsonStringToDict:(NSString *_Nullable)jsonString;

///[model] ----> json
+ (nullable id)convertModelsArrayToJSON:(NSArray<JSONModel *> *_Nullable)modelsArray;


+ (NSString *_Nullable)changeToStringWithTimestamp:(long long)timestamp formatterStr:(NSString *_Nullable)formatStr;

///字符串 根据格式 转date
+ (NSDate *_Nullable)changeDateWithFormatterType:(NSString *_Nullable)type originStr:(NSString *_Nullable)originStr;

///16进制转10进制
+ (NSNumber *_Nullable)numberHexString:(NSString *_Nullable)aHexString;


///十进制转换十六进制
+ (NSString *_Nullable)getHexByDecimal:(NSInteger)decimal;

///url encode
+ (NSString *_Nullable)urlEncodeUsingUTF8:(NSString *_Nullable)url;

///获取当前时间 - 毫秒
+ (NSTimeInterval)getMilliSecond;

///计算两个时间的天数差
+ (int)differentDaysByDate:(NSDate *_Nullable)endDate startDate:(NSDate *_Nonnull)startDate;

///字符转字节
+ (NSData *_Nullable)hexDecode:(NSData *_Nullable)inData;

+ (NSString *_Nullable)hexStringWithData:(NSData *_Nullable)data;

///获取到当前所在的视图
+ (UIViewController *_Nullable)getCurrentPresentVC;

///iphone机型
+ (NSString *_Nullable)iphoneType;

///检查版本
+ (BOOL)checkAppVersion;

///吉大证书验证
+ (void)checkJitLic;

///申请后_Nullable台常驻时间
+ (NSUInteger)applyBackgroundTimeInterval:(NSTimeInterval)timeInterval;

///通过颜色来生成一个纯色图片
+ (UIImage *_Nullable)buttonImageFromColor:(UIColor *_Nullable)color rect:(CGRect)rect;

///对象转换为字典
+ (NSDictionary*_Nullable)getObjectData:(id _Nullable )obj;

///手机是否越狱
+ (BOOL)isJailBreak;

// 获取文件或者文件夹大小(单位：M)
+ (double)sizeAtPath:(NSString *_Nullable)path;

/**
 格式化16进制打印 NSData 对象

 @param data data
 @param info 其他需要打印的提示信息
 */
+ (void)logDataToHex:(NSData *_Nullable)data info:(NSString *_Nullable)info;


/**
 时间戳转换成固定格式日期字符串

 @param ts 时间戳
 @return 日期字符串
 */
+ (NSString *_Nullable)changeTimeStampToDateString:(NSString *_Nullable)ts;

/**
 时间字符串转换成固定格式日期字符串
 
 @param ts 时间字符串
 @return 日期字符串
 */
+ (NSString *_Nullable)changeDateStringToFormatterString:(NSString *_Nullable)ts;

@end

