/*
    Irdeto Secure Apps for Automotive SDK interface definition
*/
#import <Foundation/Foundation.h>

@protocol ISAFASPIService <NSObject>
@required
-(NSDictionary<NSString*, NSString*>*)getDeviceInfo;
@end

@interface SAFAOption : NSObject
@property (nonatomic,strong) id<ISAFASPIService> spiService;
@end

@interface SAFAABNData : NSObject
@property (nonatomic,copy) NSData *ABNData;
@property (nonatomic,copy) NSString *sessionID;
@end

@interface SecureSDKManager : NSObject

-(NSString*)getSDKVersion;
-(void)initialize:(int*)outStatusCode safaOption:(SAFAOption*)safaOption;
-(void)cleanup:(int*)outStatusCode;
-(BOOL)isProvisioned:(int*)outStatusCode;
-(NSString*)getProvisionRequest:(int*)outStatusCode;
-(void)provisionResponse:(int*)outStatusCode response:(NSString*)response;
-(NSData*)getOADigest:(int*)outStatusCode id:(NSString*)id data:(NSData*)data;
-(BOOL)checkData:(int*)outStatusCode id:(NSString*)id data:(NSData*)data;
-(NSString*)storePut:(int*)outStatusCode id:(NSString*)id data:(NSData*)data safaDataOption:(int)option;
-(NSData*)storeGet:(int*)outStatusCode id:(NSString*)id;
-(void)storeDelete:(int*)outStatusCode id:(NSString*)id;
-(NSData*)cryptoOperate:(int*)outStatusCode type:(NSString*)type keyId:(NSString*)keyId iv:(NSString*)iv data:(NSData*)data;
-(NSData*)cryptoOperateA0:(int*)outStatusCode type:(NSString*)type keyId:(NSString*)keyId iv:(NSString*)iv data:(NSData*)data;
-(NSString*)getDeviceID:(int*)outStatusCode;
-(NSData*)generateChallengeCode:(int*)outStatusCode id:(NSString*)id randomNumber:(NSData*)randomNumber bookingID:(NSData*)bookingID data:(NSData*)data keyType:(int)keyType;
-(NSData*)getSecureInputSequence:(int*)outStatusCode originalSequence:(NSData*)originalSequence;
-(NSData*)getEncodedInput:(int*)outStatusCode type:(int)type inputSequence:(NSData*)inputSequence pkiObj:(id)pkiObj;
-(BOOL)localInputVerify:(int*)outStatusCode pinID:(NSString*)pinID inputSequence:(NSData*)inputSequence;
-(SAFAABNData*)getABNData:(int*)outStatusCode count:(int)count;
-(void)notifyABNDataPostStatus:(int*)outStatusCode abnObj:(SAFAABNData*)abnObj;
-(NSData*)getRandomNumber:(int*)outStatusCode length:(int)length;

@end
