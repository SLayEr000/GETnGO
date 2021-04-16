//
//  WMEnvironmentManager.m
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import "WMEnvironmentManager.h"

NSAttributedStringKey const _Nonnull NotificationName_WMEnvironmentChanged  = @"NotificationName_WMEnvironmentChanged";

@interface WMEnvironmentManager ()

@property (nonatomic , assign) WMFEnvironment env;
@property (nonatomic , strong) NSMutableDictionary *envDictionary;

@end


@implementation WMEnvironmentManager

+ (WMEnvironmentManager *)defaultManager{
    static WMEnvironmentManager *WMEnvironmentManager_default = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        WMEnvironmentManager_default = [[self alloc] init];
    });
    return WMEnvironmentManager_default;
}

- (instancetype)init{
    self = [super init];
    if (self) {
        self.envDictionary = [[NSMutableDictionary alloc] init];
        self.env = -1;

        WMFEnvironment envT = WMFEnvironment_QA;
        
#ifdef TARGET_DEV
        envT = WMFEnvironment_DEV;
#elif defined TARGET_QA
        envT = WMFEnvironment_QA;
#elif defined TARGET_PP
        envT = WMFEnvironment_PP;
#elif defined TARGET_P
        envT = WMFEnvironment_P;
#elif defined TARGET_DEMO
        envT = WMFEnvironment_DEMO;
#else
        envT = WMFEnvironment_QA;
#endif
        VBLog(@"%ld",envT);
        [self changeEnvironment:envT];

    }
    return self;
}

#pragma mark ==================================================
#pragma mark == 外部调用变量
#pragma mark ==================================================
- (WMFEnvironment)currentEnvironment{
    return self.env;
}

- (NSString*)currentEnvironmentString{
    NSString *envKey = @"XX";
    switch (self.env) {
        case WMFEnvironment_DEV:{
            envKey = @"DEV";
            break;
        }
        case WMFEnvironment_QA:{
            envKey = @"QA";
            break;
        }
        case WMFEnvironment_PP:{
            envKey = @"PP";
            break;
        }
        case WMFEnvironment_P:{
            envKey = @"P";
            break;
        }
        case WMFEnvironment_DEMO:{
            envKey = @"DEMO";
            break;
        }
        default:
            break;
    }
    return envKey;
}

- (NSDictionary *)currentEnvironmentDictionary{
    return self.envDictionary;
}

#pragma mark ==================================================
#pragma mark == 外部接口
#pragma mark ==================================================
- (void)changeEnvironment:(WMFEnvironment)aEnvironment{
    if(aEnvironment == WMFEnvironment_P){
        [[NSUserDefaults standardUserDefaults] setObject:@(1) forKey:@"Environment_Is_P"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }else{
        [[NSUserDefaults standardUserDefaults] setObject:@(0) forKey:@"Environment_Is_P"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    if (aEnvironment==self.env) {
        return;
    }
    self.env = aEnvironment;
    [self.envDictionary removeAllObjects];
    
    NSString *envPlistPath = [WMF_ResourceBundle pathForResource:@"WMEnvironment.plist" ofType:nil];
    NSDictionary *envPlist = [NSDictionary dictionaryWithContentsOfFile:envPlistPath];
    if (envPlist==nil || [envPlist count]<=0) {
//        NSString *message = [NSString stringWithFormat:@"%@",envPlistPath];
//        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Alert Title"
//                                                                                     message:message
//                                                                              preferredStyle:UIAlertControllerStyleAlert];
//        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
//            NSLog(@"Cancel Action");
//        }];
//        [alertController addAction:cancelAction];
//        UIWindow *window = [[UIApplication.sharedApplication windows] objectAtIndex:0];
//        [window.rootViewController presentViewController:alertController animated:YES completion:nil];
//        [WMToast showWithText:@"envPlist为空"];
        return;
    }
//    [WMToast showWithText:@"envPlist不为空------"];
    
    NSString *envKey = nil;
    switch (self.env) {
        case WMFEnvironment_DEV:{
//            envKey = @"ENV_DEV";
            envKey = @"ENV_P";
            break;
        }
        case WMFEnvironment_QA:{
            envKey = @"ENV_QA";
            break;
        }
        case WMFEnvironment_PP:{
            envKey = @"ENV_PP";
            break;
        }
        case WMFEnvironment_P:{
            envKey = @"ENV_P";
            break;
        }
        case WMFEnvironment_DEMO:{
            envKey = @"ENV_DEMO";
            break;
        }
        default:
            break;
    }
    
    if (envKey==nil) {
        return;
    }
    
    NSDictionary *envDic = [envPlist objectForKey:envKey];
    if (envDic && [envDic isKindOfClass:[NSDictionary class]]) {
        [self.envDictionary setValuesForKeysWithDictionary:envDic];
        [[NSNotificationCenter defaultCenter] postNotificationName:NotificationName_WMEnvironmentChanged object:nil];
    }
    
}

#pragma mark ==================================================
#pragma mark == 资源
#pragma mark ==================================================
- (NSString* _Nullable)wmf_sourcePath_WMCA_plist{
    NSString *fileName = [self.envDictionary objectForKey:@"wmca_plist"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        NSString *path = [WMF_ResourceBundle pathForResource:fileName ofType:nil];
        return path;
    }
    else{
        return nil;
    }
}

#pragma mark ==================================================
#pragma mark == URL
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_Base_URL{
    NSString *fileName = [self.envDictionary objectForKey:@"BASE_URL"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_PKI_URL{
    NSString *fileName = [self.envDictionary objectForKey:@"PKI_URL"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_QRCODE_URL{
    NSString *fileName = [self.envDictionary objectForKey:@"QRCODE_URL"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_BURYPOINT_URL{
    NSString *fileName = [self.envDictionary objectForKey:@"BURYPOINT_URL"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_SAFA_URL{
    NSString *fileName = [self.envDictionary objectForKey:@"SAFA_URL"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

#pragma mark ==================================================
#pragma mark == UUID
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_uuid_identifier{
    NSString *fileName = [self.envDictionary objectForKey:@"UDID_identifier"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_uuid_env{
    NSString *fileName = [self.envDictionary objectForKey:@"UDID_env"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

#pragma mark ==================================================
#pragma mark == 第三方平台的Key
#pragma mark ==================================================
- (NSString*_Nonnull)wmf_WXShareAppKey{
    NSString *fileName = [self.envDictionary objectForKey:@"WXShareAppKey"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_WXShareAppId{
    NSString *fileName = [self.envDictionary objectForKey:@"WXShareAppId"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_WXUniversalLink{
    NSString *fileName = [self.envDictionary objectForKey:@"WXUniversalLink"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_BaiduMapAppKey{
    NSString *fileName = [self.envDictionary objectForKey:@"BaiduMapAppKey"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}

- (NSString*_Nonnull)wmf_JPushAppKey{
    NSString *fileName = [self.envDictionary objectForKey:@"JPushAppKey"];
    if (fileName && [fileName isKindOfClass:[NSString class]] && fileName.length>0) {
        return fileName;
    }
    else{
        return @"";
    }
}


@end
