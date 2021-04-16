//
//  WMCommon.m
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import "WMCommon.h"
#import <sys/utsname.h>
#import <objc/runtime.h>


@implementation WMCommon

BOOL isHasAMPM(void){
    NSString *formatStringForHours = [NSDateFormatter dateFormatFromTemplate:@"j" options:0 locale:[NSLocale currentLocale]];
    NSRange containsA = [formatStringForHours rangeOfString:@"a"];
    BOOL hasAMPM = containsA.location != NSNotFound;
    return hasAMPM;
}

+ (NSString*)GetOnlyUUID {
    NSString *onlyUuid = [JCKeychainTool readKeychainValue:@"wmf_only_uuid"];
    if (onlyUuid == nil || onlyUuid.length == 0) {
        onlyUuid = [[UIDevice currentDevice].identifierForVendor UUIDString];
        [JCKeychainTool saveKeychainValue:onlyUuid key:@"wmf_only_uuid"];
    }
    return onlyUuid;
}

+ (BOOL)isBlankObject:(id)targetObejct{
    if ([targetObejct isKindOfClass:[NSNull class]]) {
        return YES;
    }
    if (targetObejct == nil || targetObejct == NULL) {
        return YES;
    }
    if([targetObejct isKindOfClass:[NSString class]]){
        if ([[targetObejct stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]] length]==0) {
            return YES;
        }
        NSCharacterSet *characterSet = [NSCharacterSet characterSetWithCharactersInString:@"\0"];
        NSArray *setArr = [(NSString*)targetObejct componentsSeparatedByCharactersInSet:characterSet];
        NSString *result = [setArr componentsJoinedByString:@""];
        if (result.length == 0) {
            return YES;
        }
    }
    return NO;
}

+ (NSString *)GetNowTimeStamp{    
    NSDate * nowDate = [NSDate date];
    NSTimeInterval timeSp = [nowDate timeIntervalSince1970];
    //转为字符型
    NSString *timeSpStr = [NSString stringWithFormat:@"%lld", (long long int)timeSp];
    return timeSpStr;
}

+ (nullable id)convertModelsArrayToJSON:(NSArray<JSONModel *>*)modelsArray{
    if (modelsArray.count == 0) {
        return nil;
    }
    NSMutableArray *dictArr = [JSONModel arrayOfDictionariesFromModels:modelsArray];
    
    if (![NSJSONSerialization isValidJSONObject:dictArr]){
        return nil;
    }
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictArr options:NSJSONWritingPrettyPrinted error:&error];
    if (error) {
        NSLog(@"Error:%@" , error);
        return nil;
    }
    id retDict = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:NULL];
    
    return retDict;
    
}

+ (NSDictionary *)convertjsonStringToDict:(NSString *)jsonString{
    NSDictionary *retDict = nil;
    if ([jsonString isKindOfClass:[NSString class]]) {
        NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        retDict = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:NULL];
        return  retDict;
    }else{
        return retDict;
    }
    
}

+ (NSString *)dictToJOSNString:(NSDictionary *)dict{
    NSError *error = nil;
    // NSJSONWritingFragmentsAllowed
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONReadingAllowFragments error:&error];
    if (error) {
        return @"";
    }
    NSString *jsonStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    if (!jsonStr) {
        return @"";
    }
    return jsonStr;

    
}

+ (NSString *)changeToStringWithTimestamp:(long long)timestamp formatterStr:(NSString *)formatStr{
    if (WM_IS_BLANK_OBJ(formatStr)) {
        return @"";
    }
    NSTimeInterval second = timestamp / 1000.0;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:second];
    NSDateFormatter *fmt = [[NSDateFormatter alloc] init];
    fmt.dateFormat = formatStr;
    NSString *string = [fmt stringFromDate:date];
    return string;
}

+ (NSString *)changeTimeStampToDateString:(NSString *)ts {
    if (WM_IS_BLANK_OBJ(ts)) {
        return @"";
    }
    NSTimeInterval second = ts.longLongValue / 1000.0;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:second];
    NSDateFormatter *fmt = [[NSDateFormatter alloc] init];
    fmt.dateFormat = @"yyyy.M.d HH:mm";
    NSString *string = [fmt stringFromDate:date];
    
    return string;
}

+ (NSString *)changeDateStringToFormatterString:(NSString *)ts {
    NSDateFormatter *formatter1 = [[NSDateFormatter alloc] init];
    [formatter1 setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSDateFormatter *formatter2 = [[NSDateFormatter alloc] init];
    [formatter2 setDateFormat:@"yyyy.M.d HH:mm"];
    
    NSDate *date = [formatter1 dateFromString:ts];
    NSString *dateStr = [formatter2 stringFromDate:date];
    
    return dateStr;
}

+ (NSDate *)changeDateWithFormatterType:(NSString *)type originStr:(NSString *)originStr{
    @autoreleasepool {
        NSDateFormatter *formatter1 = [[NSDateFormatter alloc] init];
        [formatter1 setDateFormat:type];
        NSDate *date = [formatter1 dateFromString:originStr];
        return date;
    }
}

+ (void)logDataToHex:(NSData *)data info:(NSString *)info{

    printf("%s : ",[info cStringUsingEncoding:NSUTF8StringEncoding]);
    printf("[");
    uint8_t *bytes = (uint8_t *)data.bytes;
    for (int i = 0; i < data.length; i++) {
        uint8_t byte = bytes[i];
        printf("%d ",byte);
    }
    printf("]");
    printf("\n");
}

+ (NSNumber *)numberHexString:(NSString *)aHexString{
    if (nil == aHexString){
         return nil;
    }
    NSScanner * scanner = [NSScanner scannerWithString:aHexString];
    unsigned long long longlongValue;
    [scanner scanHexLongLong:&longlongValue];
    NSNumber * hexNumber = [NSNumber numberWithLongLong:longlongValue];
    return hexNumber;
}

+ (NSString *)getHexByDecimal:(NSInteger)decimal {
    
    NSString *hex =@"";
    NSString *letter;
    NSInteger number;
    for (int i = 0; i<9; i++) {
        
        number = decimal % 16;
        decimal = decimal / 16;
        switch (number) {
                
            case 10:
                letter =@"A"; break;
            case 11:
                letter =@"B"; break;
            case 12:
                letter =@"C"; break;
            case 13:
                letter =@"D"; break;
            case 14:
                letter =@"E"; break;
            case 15:
                letter =@"F"; break;
            default:
                letter = [NSString stringWithFormat:@"%ld", number];
        }
        hex = [letter stringByAppendingString:hex];
        if (decimal == 0) {
            
            break;
        }
    }
    return hex;
}

+ (NSString *)urlEncodeUsingUTF8:(NSString *)url{
    return [url stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
}

+ (NSTimeInterval)getMilliSecond{
    return [[NSDate date] timeIntervalSince1970] * 1000;
}

+ (int)differentDaysByDate:(NSDate *)endDate startDate:(NSDate *)startDate{
    NSUInteger sec = [endDate timeIntervalSinceDate:startDate];
    int days = (int)(sec/(60*60*24));
    return days;
}

+ (NSData *)hexDecode:(NSData *)inData {
    uint8_t *bytes = (uint8_t *)inData.bytes;
    int halfLength = (int)inData.length / 2;
    
    int inOff = 0;
    int outOff = 0;
    
    uint8_t newBytes[halfLength];
    
    for(int i = 0; i < halfLength; ++i) {
        uint8_t left = bytes[inOff + i * 2];
        uint8_t right = bytes[inOff + i * 2 + 1];
        if (left < 97) {
            newBytes[outOff] = (uint8_t)((left - 48) << 4);
        } else {
            newBytes[outOff] = (uint8_t)((left - 97 + 10) << 4);
        }
        
        if (right < 97) {
            newBytes[outOff] += (uint8_t)(right - 48);
        } else {
            newBytes[outOff] += (uint8_t)(right - 97 + 10);
        }
        
        ++outOff;
    }
    
    return [NSData dataWithBytes:newBytes length:sizeof(newBytes)];
}

+ (NSString *)hexStringWithData:(NSData *)data{
    const unsigned char *dataBuffer = (const unsigned char *)[data bytes];
    if (!dataBuffer) {
        return [NSString string];
    }
    NSUInteger  dataLength  = [data length];
    NSMutableString *hexString  = [NSMutableString stringWithCapacity:(dataLength * 2)];
    
    for (int i = 0; i < dataLength; ++i) {
        [hexString appendFormat:@"%02x", (unsigned char)dataBuffer[i]];
    }
    return [NSString stringWithString:hexString];
}

+ (UIViewController *)getCurrentPresentVC{
    UIWindow * window = [[UIApplication sharedApplication] keyWindow];
    if (window.windowLevel != UIWindowLevelNormal){
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(UIWindow * tmpWin in windows){
            if (tmpWin.windowLevel == UIWindowLevelNormal){
                window = tmpWin;
                break;
            }
        }
    }
    UIViewController *result = window.rootViewController;
    while (result.presentedViewController) {
        result = result.presentedViewController;
    }
    
    if ([result isKindOfClass:[UINavigationController class]]) {
        result = [(UINavigationController *)result topViewController];
    }
    VBLog(@"当前所在的视图：%@",result);
    return result;
}

+ (NSString *)iphoneType {
    struct utsname systemInfo;
    
    uname(&systemInfo);
    
    NSString *platform = [NSString stringWithCString:systemInfo.machine encoding:NSASCIIStringEncoding];
    
    if ([platform isEqualToString:@"iPhone1,1"]) return @"iPhone 2G";
    
    if ([platform isEqualToString:@"iPhone1,2"]) return @"iPhone 3G";
    
    if ([platform isEqualToString:@"iPhone2,1"]) return @"iPhone 3GS";
    
    if ([platform isEqualToString:@"iPhone3,1"]) return @"iPhone 4";
    
    if ([platform isEqualToString:@"iPhone3,2"]) return @"iPhone 4";
    
    if ([platform isEqualToString:@"iPhone3,3"]) return @"iPhone 4";
    
    if ([platform isEqualToString:@"iPhone4,1"]) return @"iPhone 4S";
    
    if ([platform isEqualToString:@"iPhone5,1"]) return @"iPhone 5";
    
    if ([platform isEqualToString:@"iPhone5,2"]) return @"iPhone 5";
    
    if ([platform isEqualToString:@"iPhone5,3"]) return @"iPhone 5c";
    
    if ([platform isEqualToString:@"iPhone5,4"]) return @"iPhone 5c";
    
    if ([platform isEqualToString:@"iPhone6,1"]) return @"iPhone 5s";
    
    if ([platform isEqualToString:@"iPhone6,2"]) return @"iPhone 5s";
    
    if ([platform isEqualToString:@"iPhone7,1"]) return @"iPhone 6 Plus";
    
    if ([platform isEqualToString:@"iPhone7,2"]) return @"iPhone 6";
    
    if ([platform isEqualToString:@"iPhone8,1"]) return @"iPhone 6s";
    
    if ([platform isEqualToString:@"iPhone8,2"]) return @"iPhone 6s Plus";
    
    if ([platform isEqualToString:@"iPhone8,4"]) return @"iPhone SE";
    
    if ([platform isEqualToString:@"iPhone9,1"]) return @"iPhone 7";//国行、日版、港行
    
    if ([platform isEqualToString:@"iPhone9,2"]) return @"iPhone 7 Plus";//港行、国行
    
    if ([platform isEqualToString:@"iPhone9,3"])    return @"iPhone 7";//美版、台版
    
    if ([platform isEqualToString:@"iPhone9,4"])    return @"iPhone 7 Plus";//美版、台版
    
    if ([platform isEqualToString:@"iPhone10,1"])   return @"iPhone 8";//国行(A1863)、日行(A1906)
    
    if ([platform isEqualToString:@"iPhone10,4"])   return @"iPhone 8";//美版(Global/A1905)
    
    if ([platform isEqualToString:@"iPhone10,2"])   return @"iPhone 8 Plus";//国行(A1864)、日行(A1898)
    
    if ([platform isEqualToString:@"iPhone10,5"])   return @"iPhone 8 Plus";//美版(Global/A1897)
    
    if ([platform isEqualToString:@"iPhone10,3"])   return @"iPhone X";//国行(A1865)、日行(A1902)
    
    if ([platform isEqualToString:@"iPhone10,6"])   return @"iPhone X";//美版(Global/A1901)
    
    if ([platform isEqualToString:@"iPhone11,2"])   return @"iPhone XS";
    
    if ([platform isEqualToString:@"iPhone11,4"])   return @"iPhone XS Max";
    
    if ([platform isEqualToString:@"iPhone11,6"])   return @"iPhone XS Max";
    
    if ([platform isEqualToString:@"iPhone11,8"])   return @"iPhone XR";
    
    if ([platform isEqualToString:@"iPod1,1"])   return @"iPod Touch 1G";
    
    if ([platform isEqualToString:@"iPod2,1"])   return @"iPod Touch 2G";
    
    if ([platform isEqualToString:@"iPod3,1"])   return @"iPod Touch 3G";
    
    if ([platform isEqualToString:@"iPod4,1"])   return @"iPod Touch 4G";
    
    if ([platform isEqualToString:@"iPod5,1"])   return @"iPod Touch 5G";
    
    if ([platform isEqualToString:@"iPad1,1"])   return @"iPad 1G";
    
    if ([platform isEqualToString:@"iPad2,1"])   return @"iPad 2";
    
    if ([platform isEqualToString:@"iPad2,2"])   return @"iPad 2";
    
    if ([platform isEqualToString:@"iPad2,3"])   return @"iPad 2";
    
    if ([platform isEqualToString:@"iPad2,4"])   return @"iPad 2";
    
    if ([platform isEqualToString:@"iPad2,5"])   return @"iPad Mini 1G";
    
    if ([platform isEqualToString:@"iPad2,6"])   return @"iPad Mini 1G";
    
    if ([platform isEqualToString:@"iPad2,7"])   return @"iPad Mini 1G";
    
    if ([platform isEqualToString:@"iPad3,1"])   return @"iPad 3";
    
    if ([platform isEqualToString:@"iPad3,2"])   return @"iPad 3";
    
    if ([platform isEqualToString:@"iPad3,3"])   return @"iPad 3";
    
    if ([platform isEqualToString:@"iPad3,4"])   return @"iPad 4";
    
    if ([platform isEqualToString:@"iPad3,5"])   return @"iPad 4";
    
    if ([platform isEqualToString:@"iPad3,6"])   return @"iPad 4";
    
    if ([platform isEqualToString:@"iPad4,1"])   return @"iPad Air";
    
    if ([platform isEqualToString:@"iPad4,2"])   return @"iPad Air";
    
    if ([platform isEqualToString:@"iPad4,3"])   return @"iPad Air";
    
    if ([platform isEqualToString:@"iPad4,4"])   return @"iPad Mini 2G";
    
    if ([platform isEqualToString:@"iPad4,5"])   return @"iPad Mini 2G";
    
    if ([platform isEqualToString:@"iPad4,6"])   return @"iPad Mini 2G";
    
    if ([platform isEqualToString:@"i386"])      return @"iPhone Simulator";
    
    if ([platform isEqualToString:@"x86_64"])    return @"iPhone Simulator";
    
    return platform;
    
}

+ (BOOL) checkAppVersion {
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *localAppVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
    NSString *latestAppVersion = WMGetUserDefaultUtil(@"k_app_latest_version");
    
    if (!WM_IS_BLANK_OBJ(latestAppVersion)) {
        if (![localAppVersion isEqualToString:latestAppVersion]) {
            return YES;
        } else {
            return NO;
        }
    } else {
        return NO;
    }
}

+ (UIViewController*)initControllerWithXib:(Class)controllerClass {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"WMCloverSDKResource" ofType:@"bundle"];
    NSBundle *SDKBundle = [NSBundle bundleWithPath:path];
    
    UIViewController *vc =nil;
    if(ColoverSDKEnable){
        vc = [[controllerClass alloc] initWithNibName:NSStringFromClass([controllerClass class]) bundle:SDKBundle];
    }else{
        vc = [[controllerClass alloc ] init];
    }
    return vc;
}

+ (void) checkJitLic {
    //文件类型
    NSString * docPath = [WMF_ResourceBundle pathForResource:@"license" ofType:@"lce"];
    // 沙盒Library目录
    NSString * appDir = [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) lastObject];
   
    NSString *createDir =  [appDir stringByAppendingString:@"/JitCerts"];
    NSString *filePath = [createDir stringByAppendingString:@"/license.lce"];
    if(![[NSFileManager defaultManager] fileExistsAtPath:filePath]){
        [self createFolder:createDir];
        [self copyMissingFile:docPath toPath:createDir];
    }
}

//拷贝文件
+ (BOOL)copyMissingFile:(NSString *)sourcePath toPath:(NSString *)toPath{
    BOOL retVal = YES;
    NSString * finalLocation = [toPath stringByAppendingPathComponent:[sourcePath lastPathComponent]];
    if (![[NSFileManager defaultManager] fileExistsAtPath:finalLocation])
    {
        retVal = [[NSFileManager defaultManager] copyItemAtPath:sourcePath toPath:finalLocation error:NULL];
    }
    return retVal;
}

//创建文件夹
+ (void)createFolder:(NSString *)createDir{
    BOOL isDir = NO;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL existed = [fileManager fileExistsAtPath:createDir isDirectory:&isDir];
    if ( !(isDir == YES && existed == YES) )
    {
        [fileManager createDirectoryAtPath:createDir withIntermediateDirectories:YES attributes:nil error:nil];
    }
}

static NSUInteger backgroundTaskId = 0;
#pragma mark - 申请后台常驻时间
+ (NSUInteger)applyBackgroundTimeInterval:(NSTimeInterval)timeInterval{
    __block NSUInteger backgroundTaskIdentifier = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:^(void) {
        [[UIApplication sharedApplication] endBackgroundTask:backgroundTaskIdentifier];
    }];
    backgroundTaskId = backgroundTaskIdentifier;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(timeInterval * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[UIApplication sharedApplication] endBackgroundTask:backgroundTaskId];
    });
    return backgroundTaskId;
}

//通过颜色来生成一个纯色图片
+ (UIImage *)buttonImageFromColor:(UIColor *)color rect:(CGRect)rect{
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

///对象转换为字典
+ (NSDictionary*)getObjectData:(id)obj {
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
    unsigned int propsCount;
    
    objc_property_t *props = class_copyPropertyList([obj class], &propsCount);
    
    for(int i = 0;i < propsCount; i++) {
        
        objc_property_t prop = props[i];
        NSString *propName = [NSString stringWithUTF8String:property_getName(prop)];
        id value = [obj valueForKey:propName];
        if(value == nil) {
            
            value = [NSNull null];
        } else {
            value = [self getObjectInternal:value];
        }
        [dic setObject:value forKey:propName];
    }
    
    return dic;
}

+ (id)getObjectInternal:(id)obj {
    
    if([obj isKindOfClass:[NSString class]]
       ||
       [obj isKindOfClass:[NSNumber class]]
       ||
       [obj isKindOfClass:[NSNull class]]) {
        
        return obj;
        
    }
    if([obj isKindOfClass:[NSArray class]]) {
        
        NSArray *objarr = obj;
        NSMutableArray *arr = [NSMutableArray arrayWithCapacity:objarr.count];
        
        for(int i = 0; i < objarr.count; i++) {
            
            [arr setObject:[self getObjectInternal:[objarr objectAtIndex:i]] atIndexedSubscript:i];
        }
        return arr;
    }
    if([obj isKindOfClass:[NSDictionary class]]) {
        
        NSDictionary *objdic = obj;
        NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:[objdic count]];
        
        for(NSString *key in objdic.allKeys) {
            
            [dic setObject:[self getObjectInternal:[objdic objectForKey:key]] forKey:key];
        }
        return dic;
    }
    return [self getObjectData:obj];
    
}

///手机是否越狱
+ (BOOL)isJailBreak{
    BOOL isJail = NO;
    /// 根据是否能打开cydia判断
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"cydia://"]]) {
        isJail = YES;
    }
    /// 根据是否能获取所有应用的名称判断 没有越狱的设备是没有读取所有应用名称的权限的。
    if ([[NSFileManager defaultManager] fileExistsAtPath:@"User/Applications/"]) {
        isJail = YES;
    }
    
    NSArray *jailbreak_tool_paths = @[
        @"/Applications/Cydia.app",
        @"/Library/MobileSubstrate/MobileSubstrate.dylib",
        @"/bin/bash",
        @"/usr/sbin/sshd",
        @"/etc/apt"
    ];
    
    /// 判断这些文件是否存在，只要有存在的，就可以认为手机已经越狱了。
    for (int i=0; i<jailbreak_tool_paths.count; i++) {
        if ([[NSFileManager defaultManager] fileExistsAtPath:jailbreak_tool_paths[i]]) {
            isJail = YES;
        }
    }
    
    return isJail;
}

// 获取文件或者文件夹大小(单位：M)
+ (double)sizeAtPath:(NSString *)path {
    NSFileManager *fm = [NSFileManager defaultManager];
    BOOL isDir = YES;
    if (![fm fileExistsAtPath:path isDirectory:&isDir]) {
        return 0;
    };
    unsigned long long fileSize = 0;
    if (isDir) {
        NSDirectoryEnumerator *enumerator = [fm enumeratorAtPath:path];
        while (enumerator.nextObject) {
            fileSize += enumerator.fileAttributes.fileSize;
        }
    } else {
        fileSize = [fm attributesOfItemAtPath:path error:nil].fileSize;
    }
    double size = fileSize/(1000.0*1000.0);
    return size;
}

@end
