//
//  CCRadioMenu.h
//  cocos2dx
//
//  Created by Big Tent Entertainment on 2/19/14.
//  Copyright (c) 2014 厦门雅基软件有限公司. All rights reserved.
//

// -- custom extension --

#ifndef __cocos2dx__CCRadioMenu__
#define __cocos2dx__CCRadioMenu__

#include "CCMenu.h"
using namespace cocos2d;

NS_CC_BEGIN

class CC_DLL CCRadioMenu : public CCMenu
{
public:
	CCRadioMenu() :m_pLastSelectedItem(NULL){}
	virtual ~CCRadioMenu(){}
	virtual void onEnter();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    /** creates an empty CCRadioMenu */
    static CCRadioMenu* create();
    
    /** creates a CCRadioMenu with CCMenuItem objects
     * @lua NA
     */
    static CCRadioMenu* create(CCMenuItem* item, ...);
    
    /** creates a CCRadioMenu with a CCArray of CCMenuItem objects
     * @js NA
     */
    static CCRadioMenu* createWithArray(CCArray* pArrayOfItems);
    
    /** creates a CCRadioMenu with it's item, then use addChild() to add
     * other items. It is used for script, it can't init with undetermined
     * number of variables.
     * @js NA
     */
    static CCRadioMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCRadioMenu with CCMenuItem objects
     * @js NA
     * @lua NA
     */
    static CCRadioMenu* createWithItems(CCMenuItem *firstItem, va_list args);
    
    void setSelectedItem(CCMenuItem* item);
    CCMenuItem* getSelectedItem();
protected:
	CCMenuItem* m_pLastSelectedItem;
};

NS_CC_END

#endif /* defined(__cocos2dx__CCRadioMenu__) */
