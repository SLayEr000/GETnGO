/**
 * v2.2.8
 */

#import <Foundation/Foundation.h>

/**
 *  getZInfoWithEvent方法需要 传入 的参数字典中的Key
 */
__attribute__((visibility("default")))
extern NSString * const kSSDKEventIdentifier; // eventID

__attribute__((visibility("default")))
extern NSString * const kSSDKAccountIdentifier; // accountID
/**
 *  getZInfoWithEvent方法 返回 的参数字典中的Key
 */
__attribute__((visibility("default")))
extern NSString * const kSSDKZToken; // ztoken

__attribute__((visibility("default")))
@interface SSDKLib : NSObject

/**
 *  iOS安全SDK单一实例
 */
+ (id)sharedInstance;

/**
 * iOS安全SDK初始化接口，宿主App通过集成Passport调用
 @param passportCUID:       Passport CUID
 @param hostAppCUID:        宿主APP CUID
 @param AppKey:             申请的AppKey
 @param secretKey:          申请的secretKey
 @param ZInfoReadyHandle:   调用者提供的回调函数，调起时zid在服务端可查。可传空
 */
- (void)startSDKEngineWithCUID:(NSString *)passportCUID
                   hostAppCUID:(NSString *)hostAppCUID
                        appKey:(NSString *)appKey
                     secretKey:(NSString *)secretKey
             ZInfoReadyHandler:(void (^)(NSError *error))ZInfoReadyHandler;

/**
 * iOS安全SDK初始化接口，宿主App直接调用
 @param deviceID:           唯一设备标识
 @param AppKey:             申请的AppKey
 @param secretKey:          申请的secretKey
 @param ZInfoReadyHandle:   调用者提供的回调函数，调起时zid在服务端可查。可传空
 */
- (void)startSDKEngineWithDeviceID:(NSString *)deviceID
                            appKey:(NSString *)appKey
                         secretKey:(NSString *)secretKey
                 ZInfoReadyHandler:(void (^)(NSError *error))ZInfoReadyHandler;

/**
 * 特定事件（如支付、登录）发生时查询zid的接口
 @param eventInfo: 包含eventID和accountID信息的字典:{ kSSDKEventIdentifier: (NSString*)eventID, kSSDKAccountIdentifier:(NSString*)accountID}
 
 eventID：
 涉及重要的安全操作（如支付、登录等），eventID 传非0的数字字面的字符串，如@"1", @"2"等；
 若不涉及到安全性操作，仅期望简单获取zid时，eventID 传@"0"；
 
 accountID: 没有可传@""；
 
 @return: 包含ztoken信息的字典：@{ kSSDKZToken: ztoken }，ztoken为NSString类型
 */
- (NSDictionary *)getZInfoWithEvent:(NSDictionary *)eventInfo;


/**
 JS对特定事件（如支付、登录）发生时查询zid的接口
 
 @param paramDict 传入的字典参数
 @return 包含zid信息的字典：@{kSSDKZToken : ztoken}，ztoken为NSString *类型
 */
- (NSDictionary *)getZInfoWithBridgeEvent:(NSDictionary *)paramDict;


@end
