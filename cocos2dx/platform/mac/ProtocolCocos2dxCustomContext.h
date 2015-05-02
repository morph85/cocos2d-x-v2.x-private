//
//  ProtocolCocos2dxCustomContext.h
//  cocos2dx
//
//  Created by Ivan Gan on 12/4/13.
//  Copyright (c) 2013 厦门雅基软件有限公司. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProtocolCocos2dxDefine.h"

// -- custom extension --

// for use in Objective-C protocol only

@protocol ProtocolCocos2dxCustomContext <NSObject>
@required
- (void)callbackPopViewIos;
@optional
- (float)callbackMicLevel;
- (void)callbackNativeViewControllerWithContextId:(int)contextId;
- (void)callbackPerformActionWithEventId:(int)eventId andActionId:(int)actionId andFilePath:(NSString *)filePath;
- (void)callbackPerformActionWithEventId:(int)eventId andActionId:(int)actionId andFolderPath:(NSString *)folderPath;
- (NSString *)callbackJsonEvent:(NSString *)callbackJson;
@end
