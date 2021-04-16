//
//  SAPILoginService.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-8.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SAPIDefine.h"

@class SAPILoginModel;
@class SAPIVoiceInfo;
@class SAPIFaceInfo;
@class PASSError;

@interface SAPILoginService : NSObject

/**
 *  根据BDUSS、tpl列表查询本地是否已存在所有对应的stoken
 *
 *  @param bduss         bduss
 *  @param targetTPLList 业务线tpl列表
 *
 *  @return 传入参数正确时，如果本地已有全部的与传入参数对应的stoken时返回YES，其他情况返回NO。
 */
- (BOOL)isStokenExistedForBduss:(NSString *)bduss targetTPLList:(NSArray *)targetTPLList;

/**
 *  根据BDUSS获取传入tpl列表对应的stoken列表
 *
 *  @param bduss         bduss
 *  @param targetTPLList 业务线tpl列表，用于获取tpl对应的stoken
 *  @param success       获取成功时的回调。返回一个键值对，其中key为传入的某一tpl，value为对应的stoken。
 *  @param failure       获取失败时的回调，返回一个NSError实例。若返回NSError code为8，产品线需要引导用户重新登录。返回错误码为8的原因有几种：1. 本地PTOKEN缺失；2. BDUSS失效；3. PTOKEN和BDUSS不对应。从NSError的userInfo中取SAPIBdussPtokenInvalidReasonKey对应的值可以区分具体的原因，上述三种原因对应的值分别为SAPIBdussPtokenInvalidReasonMissingPtoken，SAPIBdussPtokenInvalidReasonUserNotOnline，SAPIBdussPtokenInvalidReasonBdussPtokenNotMatch。
 *
 *  @return 本地有与传入参数对应的缓存数据时，返回相应缓存数据；否则返回nil。
 *
 */
- (NSDictionary *)getStokenForBduss:(NSString *)bduss
                      targetTPLList:(NSArray *)targetTPLList
                            success:(void (^)(NSDictionary *tplStokenPairs))success
                            failure:(void (^)(NSError *error))failure;

/**
 *  根据BDUSS+TPLList，删除本地对应的stoken
 *
 *  @param bduss bduss
 *  @param targetTPLList   业务线tpl列表
 *
 *  @return 参数不为空时，删除成功返回YES，否则返回失败。
 *
 */
- (BOOL)deleteStokenForBduss:(NSString *)bduss targetTPLList:(NSArray *)targetTPLList;

/**
 *  修改头像
 *
 *  @important 由于某些原因（大部分是政府要求），上传头像需要禁止使用，请直接使用返回的文案。
 *
 *  @param imageData       头像图片NSData
 *  @param mimeType        mime类型
 *  @param model           登录模型
 *  @param completionBlock 完成后的回调
 *  @param errorBlock      失败后的回调
 */
- (BOOL)uploadPortrait:(NSData *)imageData
              mimeType:(NSString *)mimeType
            loginModel:(SAPILoginModel *)model
          onCompletion:(SAPIRequestCompletionBlock)completionBlock
               onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  获取头像
 *
 *  @param model           登录模型
 *  @param completionBlock 完成后的回调
 *  @param errorBlock      失败后的回调
 */
- (BOOL)getPortraitInfo:(SAPILoginModel *)model
           onCompletion:(SAPIRequestCompletionBlock)completionBlock
                onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  批量获取头像，最多获取5个,内部会根据 bduss 去重
 *
 *  @param modelList       登录模型数组
 *  @param completionBlock 完成后的回调
 *  @param errorBlock      网络请求失败后的回调
 */
- (BOOL)getPortraitListInfo:(NSArray<SAPILoginModel *> *)modelList
           onCompletion:(SAPIRequestCompletionBlock)completionBlock
                onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  补填用户名
 *
 *  @important 由于某些原因（大部分是政府要求），补填用户名需要禁止使用，请直接使用返回的文案。
 *
 *  @param uname           用户名
 *  @param model           登录模型
 *  @param completionBlock 完成后的回调
 *  @param errorBlock      失败后的回调
 */
- (BOOL)fillUname:(NSString *)uname
       loginModel:(SAPILoginModel *)model
     onCompletion:(SAPIRequestCompletionBlock)completionBlock
          onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  用现有模型登录(含互通)
 *
 *  @param model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成
 *               功
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model;

/**
 *  用现有模型登录(含互通)

 @param model model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成功
 @param userInfo 透传参数，该参数将透传至 didLoginSuccess 方法的 extraInfo 字段中，Key 为 userInfo
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model userInfo:(NSDictionary *)userInfo;

/**
 *  用现有模型登录(不含互通)
 *  建议以下情况使用：
 *  1. web端登录状态同步到sdk里
 *  2. 兼容历史版本登录状态
 *
 *  @param model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成功。
 */
- (void)unsharedLoginWithLoginModel:(SAPILoginModel *)model;

/**
 *  退出登录
 *
 *  @param model 登录模型
 */
- (BOOL)logout:(SAPILoginModel *)model;

/**
 *  重登录
 *
 *  @param uid        用户uid
 *  @param completion 完成后的回调
 *  @param error      失败后的回调
 */
- (BOOL)reloginWithUid:(NSString *)uid
          onCompletion:(void (^)(void))completion
                 error:(void (^)(void))error DEPRECATED_MSG_ATTRIBUTE("replaced by reloginWithUid:success:failure:");

/**
 *  利用本地可能存在的登录信息来尝试重登录（第三方登录帐号不支持重登录）
 *  替代reloginWithUid:onCompletion:error:接口
 *
 *  @param uid     重登录用户的uid
 *  @param success 重登录成功时的回调，会返回一个SAPILoginModel实例
 *  @param failure 重登录失败时的回调，会返回一个NSError实例
 */
- (void)reloginWithUid:(NSString *)uid
               success:(void (^)(SAPILoginModel *model))success
               failure:(void (^)(NSError *error))failure DEPRECATED_MSG_ATTRIBUTE("deprecated in version 6.15.0, use reloginWithUid:bduss:success:failure: instead");

/**
 *  利用本地可能存在的登录信息来尝试重登录
 *
 *  @param uid     重登录用户的uid
 *  @param bduss   重登录用户的bdus
 *  @param success 重登录成功时的回调，会返回一个SAPILoginModel实例
 *  @param failure 重登录失败时的回调，会返回一个NSError实例
 */
- (void)reloginWithUid:(NSString *)uid
                 bduss:(NSString *)bduss
               success:(void (^)(SAPILoginModel *model))success
               failure:(void (^)(NSError *error))failure;

/**
 *  根据bduss同步loginModel到sdk（此接口同步的帐号不会互通），需网络请求
 *  如果是将Cookie中的BDUSS同步到SDK，请使用-[SAPILoginService web2NativeLoginSuccess:failure:]接口
 *
 *  @param bduss           bduss，不能为nil或空字符串
 *  @param ptoken          ptoken，没有时传入nil
 *  @param app             帐号来源app名字，不能为nil或空字符串
 *  @param completionBlock 同步成功时的回调
 *  @param errorBlock      同步失败时的回调
 *
 *  @return 传入参数格式是否正确，返回NO表示传入参数不合法
 */
- (BOOL)syncLoginModelWithBduss:(NSString *)bduss
                         ptoken:(NSString *)ptoken
                            app:(NSString *)app
                   onCompletion:(SAPIRequestCompletionBlock)completionBlock
                        onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  获取登录行为信息
 *
 *  @param uid 用户uid
 *
 *  @return 用户登录行为信息
 */
- (NSDictionary *)readLoginActionInfoByUid:(NSString *)uid;

/**
 *  获取用户信息
 *
 *  @param bduss           用户的bduss
 *
 *
 *  @param completionBlock 获取成功时的回调。可能包含以下字段：
 *                          displayname：用户显示名称，用于产品线展示。
 *
 *                          have_psw：是否设置了密码。
 *
 *                          incomplete_user：是否为半帐号。为1时即为半帐号，半帐号需要绑定手机或者正常化后才能调用其他接口。
 *
 *                          portrait：头像地址拼接串。
 *                          portrait_tag：头像id的md5值，为 0 时表示用户尚未设置头像。
 *                          可根据portrait和portrait_tag拼接出头像地址：
 *                          NSString *portraitUrl = [NSString stringWithFormat:@"http://himg.bdimg.com/sys/portrait/item/%@.jpg?%@", [info objectForKey:@"portrait"], [info objectForKey:@"portrait_tag"]];
 *                          头像地址若也需HTTPS，可按如下方式拼接：
 *                          NSString *portraitUrl = [NSString stringWithFormat:@"https://gss0.bdstatic.com/7Ls0a8Sm1A5BphGlnYG/sys/portrait/item/%@.jpg?%@", [info objectForKey:@"portrait"], [info objectForKey:@"portrait_tag"]];
 *
 *
 *                          secureemail：打码后的邮箱，用户已绑定邮箱时会返回此字段。
 *
 *                          securemobil：打码后的手机，用户已绑定手机时会返回此字段。
 *
 *                          userid：用户id。
 *
 *                          username：用户名（可能为空）。显示用户名请使用displayname字段。
 *
 *
 *  @param errorBlock      获取失败时的回调。最常见的错误情况为传入bduss已失效,此时返回errno:400021，errmsg: "user not
 *                          online, status = 2"
 *
 *  @return 传入bduss为空时返回NO，其他返回YES
 *
 */
- (BOOL)getUserInfo:(NSString *)bduss
       onCompletion:(SAPIRequestCompletionBlock)completionBlock
            onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  用加密密码和 uid 登录
 *
 *  @param uid             uid
 *  @param pass            加密密码
 *  @param completionBlock 完成时回调
 *  @param errorBlock      失败时回调
 *
 *  @return 传入uid或pass为空时返回NO，其他返回YES
 */
- (BOOL)loginWithUid:(NSString *)uid
       encryptedPass:(NSString *)pass
        onCompletion:(SAPIRequestCompletionBlock)completionBlock
             onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  获取热门推荐头像列表
 *
 *  v6.7.0新增
 *
 *  @param bduss           bduss
 *  @param completionBlock 获取成功时回调
 *  @param errorBlock      获取失败时回调
 */
- (void)getHotAvatarListWithBduss:(NSString *)bduss
                     onCompletion:(SAPIRequestCompletionBlock)completionBlock
                          onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  设置用户头像为热门推荐头像的某个头像 (与用户自定义修改头像的接口不同，请注意区分)
 *
 *  v6.7.0新增
 *
 *  @param bduss           bduss
 *  @param serie           所选热门头像的系列
 *  @param number          所选热门头像的序号
 *  @param completionBlock 设置成功时的回调
 *  @param errorBlock      设置失败时的回调
 */
- (void)setHotAvatarWithBduss:(NSString *)bduss
                        serie:(NSString *)serie
                       number:(NSUInteger)number
                 onCompletion:(SAPIRequestCompletionBlock)completionBlock
                      onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  微信登录时先获取mkey防止csrf攻击
 *  v6.7.1新增
 *
 *  @param wxAppId         微信的AppId
 *  @param scope           微信的授权范围，默认请填写snsapi_userinfo
 *  @param completionBlock 获取成功时的回调，成功时会返回一个mkey字段，请作为参数传入微信登录的state字段
 *  @param errorBlock      获取失败时的回调
 */
- (void)getMkeyWithWeiXinAppId:(NSString *)wxAppId
                         scope:(NSString *)scope
                  OnCompletion:(SAPIRequestCompletionBlock)completionBlock
                       onError:(SAPIRequestErrorBlock)errorBlock;

- (void)getMkeyWithWeiXinAppId:(NSString *)wxAppId
                         scope:(NSString *)scope
                     bindValue:(NSString *)bindValue
                   extraParams:(NSDictionary *)extra
                  OnCompletion:(SAPIRequestCompletionBlock)completionBlock
                       onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  根据用户名、明文密码尝试重登录（仅支持百度帐号，第三方帐号不支持重登录）
 *  仅在没有触发反作弊、用户帐号类型不明确等各类其他情况时才能重登录成功
 *  没有用户名、明文密码或已接入SAPI SDK登录的帐号，可调用reloginWithUid:success:failure:接口来尝试重登录
 *
 *  v6.7.7新增
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param success  登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure  登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 */
- (void)reloginWithUsername:(NSString *)username
                   password:(NSString *)password
                    success:(void (^)(SAPILoginModel *loginModel))success
                    failure:(void (^)(NSError *error))failure;

/**
 *  根据用户名、明文密码尝试重登录（仅支持百度帐号，第三方帐号不支持重登录）
 *
 *  此接口不会回调SAPIMainManagerDelegate相关方法。
 *
 *  重登录成功后，如果得到的uid与当前已登录帐号的uid不一致，则会回调失败，错误码为-710；如果uid一致或当前未登录，则会用重登录得到的信息更新本地信息并回调成功。
 *
 *  仅在没有触发反作弊、用户帐号类型不明确等各类其他情况时才能重登录成功。
 *
 *  没有用户名、明文密码或已接入SAPI SDK登录的帐号，可调用reloginWithUid:bduss:success:failure:接口来尝试重登录。
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param success  登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure  登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 *
 */
- (void)reloginIfNeededWithUsername:(NSString *)username
                           password:(NSString *)password
                            success:(void (^)(SAPILoginModel *model))success
                            failure:(void (^)(NSError *error))failure;

/**
 *  通过手机号获取动态密码，然后根据手机号、动态密码登录。
 *  如果命中反作弊策略，需要输入验证码，验证码为数字字母组合。
 *
 *  @param mobile  手机号
 *  @param captcha 验证码，没有时传nil
 *  @param success 获取成功时的回调，返回一个内容格式如@{ @"errCode": @"0", @"errMsg": @"" }的键值对
 *  @param failure 获取失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码；
 *                                  如果需要输入验证码，则返回一个UIImage实例，否则返回nil。
 */
- (void)getDpassWithMobile:(NSString *)mobile
                   captcha:(NSString *)captcha
                   success:(void (^)(NSDictionary *info))success
                   failure:(void (^)(UIImage *captchaImage, NSError *error))failure;

/**
 *  短信登录获取动态密码需要输入验证码时，可通过此方法刷新验证码
 *
 *  @param completion 完成时回调
 */
- (void)refreshCaptchaForSMSLoginOnCompletion:(void (^)(UIImage *captchaImage))completion;

/**
 *  根据手机号、动态密码登录
 *  先调用getDpassWithMobile:success:failure:接口获取动态密码
 *
 *  v6.7.8新增
 *
 *  @param mobile  手机号
 *  @param dpass   动态密码，通过getDpassWithMobile:success:failure:获取
 *  @param success 登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure 登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 */
- (void)loginWithMobile:(NSString *)mobile
                  dpass:(NSString *)dpass
                success:(void (^)(SAPILoginModel *loginModel))success
                failure:(void (^)(NSError *error))failure;

/**
 *  生成短信内容，用于上行短信注册、登录等操作
 *
 *  v6.7.8新增
 *
 *  @return 生成的短信内容
 */
- (NSString *)getUpwardSMSContentForRegister;

/**
 *  通过上行短信注册并登录帐号
 *  需先调用getUpwardSMSContentForRegister接口获取短信内容并成功发送该短信后再调用本接口
 *
 *  v6.7.8新增
 *
 *  @param sms     上行短信的内容，通过getUpwardSMSContentForRegister接口获取
 *  @param timeout 本次注册、登录操作的超时时间
 *  @param success 注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure 注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerBySendSMS:(NSString *)sms
                  timeout:(NSTimeInterval)timeout
                  success:(void (^)(SAPILoginModel *loginModel))success
                  failure:(void (^)(NSError *error))failure;

- (void)clearAllRequest;

#pragma mark - Native & H5 Share Login
/**
 *  H5登录态同步到Native
 *
 *  @discussion 该方法会自动从Cookie中获取bduss及其他信息，然后同步到Native。同步成功时，回调登录成功以及success；同步失败时，回调登录失败以及failure。同步策略请参考[SAPIMainManager sharedManager].naH5SyncStrategy配置项。
 *
 *  使用场景：H5登录完成，需要将H5登录态同步到Native端时调用
 *
 *  @param success 登录成功回调，若cookie中包含登录态，则返回一个loginModel，否则登录失败
 *  @param failure 登录失败回调
 */
- (void)web2NativeLoginSuccess:(void (^)(SAPILoginModel *loginModel))success
                       failure:(void (^)(NSError *error))failure;

/**
 *  H5登录态同步到Native
 *
 *  @discussion 该方法会自动从Cookie中获取bduss及其他信息，然后同步到Native。同步成功时，回调登录成功以及success；同步失败时，回调登录失败以及failure。同步策略请参考[SAPIMainManager sharedManager].naH5SyncStrategy配置项。
 *
 *  使用场景：H5登录完成，需要将H5登录态同步到Native端时调用
 *
 *  @param source  登录来源，该字段会透传到登录成功回调中，以 SAPILoginExtraInfoSourceKey 作为 Key
 *  @param oauthType 第三方登录类型
 *  @param success 登录成功回调，若cookie中包含登录态，则返回一个loginModel，否则登录失败
 *  @param failure 登录失败回调
 */
- (void)web2NativeLoginWithSource:(NSString *)source
              loginModelOauthType:(NSString *)oauthType
                            success:(void (^)(SAPILoginModel *loginModel))success
                            failure:(void (^)(NSError *error))failure;

/**
 *  H5登录态同步到Native
 *
 *  @discussion 该方法会将传入的登录模型同步到Native。同步成功时，回调登录成功；同步失败时，回调登录失败。同步策略请参考[SAPIMainManager sharedManager].naH5SyncStrategy配置项。
 *
 *  使用场景：H5登录完成且产品线已获取到完整的登录模型（uid，displayname，bduss不能为nil或空字符串），需要将H5登录态同步到Native端时调用。若产品线没有获取完整的登录模型，可调用-[SAPILoginService web2NativeLoginSuccess:failure:]方法同步H5登录态到Native。
 *
 *  @param loginModel 登录模型。uid，displayname，bduss不能为nil或空字符串
 */
- (void)web2NativeLoginWithLoginModel:(SAPILoginModel *)loginModel;

/**
 *  Native登录态同步到H5
 *
 *  使用场景：需要主动将Native登录状态同步到H5时调用。SAPI在登录完成时会自动同步Native登录态到H5。
 *
 *  @discussion 当前未登录时，会删除cookie中的bduss；当前已登录时，会将当前登录态写到cookie中。
 */
- (void)native2WebLogin;

/**
 *  将bduss写入cookie
 *  <li>所有白名单域名都写(如 .baidu.com, .nuomi.com, .hao123.com)</li>
 *  <li>非SessionOnly，过期时间8年</li>
 *  <li>非Secure</li>
 *
 *  @param bduss bduss
 */
- (void)setBdussToCookie:(NSString *)bduss;

/**
 *  获取cookie中的bduss
 *
 *  @return 如果存在返回baidu域下的bduss，否则返回nil
 */
- (NSString *)getBdussFromCookie;

#pragma mark - 二维码联合登录
/**
 获取二维码联合登录授权文案

 @param text 扫码后得到的百度侧二维码文本
 @return 授权文案。如果二维码合法，则返回相应的文案；否则将返回 nil。
 */
- (NSString *)qrcodeAuthCopywritingWithQRCodeText:(NSString *)text;

/**
 二维码登录，将App登录态同步到其他设备端。注意：该接口仅提供外部厂商联合登录百度帐号使用，内部产品线不可使用
 
 @param text 扫码后得到的百度侧二维码文本
 @param success 成功时回调
 @param failure 失败时回调
 */
- (void)qrcodeLoginWithQRCodeText:(NSString *)text
                   successHandler:(void(^)(NSDictionary *info))success
                   failureHandler:(void(^)(PASSError *error))failure;

@end

@class SAPIOAuthInfo;
@interface SAPILoginService (PASSAIJoinLogin)

/**
 *  通过openPlatformId换取百度开放平台accesstoken
 *
 *  @param openPlatformId  调用时传入，不能为空。
 *  @param success 成功回调，返回一个SAPIOAuthInfo实例。
 *  @param failure 失败回调，返回一个NSError实例。
 */
- (void)getAccessTokenWithOpenPlatformId:(NSString *)openPlatformId
                                 success:(void (^)(SAPIOAuthInfo *oauthInfo))success
                                 failure:(void (^)(NSError *error))failure;
@end
