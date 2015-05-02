//
//  ProtocolCocos2dxDefine.h
//  cocos2dx
//
//  Created by Ivan Gan on 12/5/13.
//  Copyright (c) 2013 厦门雅基软件有限公司. All rights reserved.
//

#ifndef cocos2dx_ProtocolCocos2dxDefine_h
#define cocos2dx_ProtocolCocos2dxDefine_h

// -- custom extension --

// for use in both Objective-C and C++ common definition

typedef enum {
    EVENT_ID_MOVIE_MAKER = 1,
} CustomContextEventId;

typedef enum {
    ACTION_ID_EMAIL = 1,
    ACTION_ID_GENERATE_VIDEO_TO_NOTEBOOK = 2,
} CustomContextActionId;

typedef enum {
    CONTEXT_ID_NOTEBOOK = 1,
	CONTEXT_ID_LOADING_DLG = 2,
} CustomContextId;

#endif
