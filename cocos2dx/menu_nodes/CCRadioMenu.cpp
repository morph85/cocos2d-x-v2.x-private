//
//  CCRadioMenu.cpp
//  cocos2dx
//
//  Created by Big Tent Entertainment on 2/19/14.
//  Copyright (c) 2014 厦门雅基软件有限公司. All rights reserved.
//

// -- custom extension --

#include "CCRadioMenu.h"

NS_CC_BEGIN

CCRadioMenu* CCRadioMenu::create()
{
	return CCRadioMenu::create(NULL, NULL);
}

CCRadioMenu * CCRadioMenu::create(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args, item);
    
	CCRadioMenu *pRet = CCRadioMenu::createWithItems(item, args);
    
	va_end(args);
    
	return pRet;
}

CCRadioMenu* CCRadioMenu::createWithArray(CCArray* pArrayOfItems)
{
	CCRadioMenu *pRet = new CCRadioMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
    
	return pRet;
}

CCRadioMenu* CCRadioMenu::createWithItems(CCMenuItem* item, va_list args)
{
	CCArray* pArray = NULL;
	if (item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while (i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}
    
	return CCRadioMenu::createWithArray(pArray);
}

CCRadioMenu* CCRadioMenu::createWithItem(CCMenuItem* item)
{
	return CCRadioMenu::create(item, NULL);
}

void CCRadioMenu::onEnter()
{
	CCMenu::onEnter();
	if (m_pChildren->count()>0)
	{
        // set the first CCMenuItem to selected
        if (!m_pLastSelectedItem)
        {
            CCMenuItem* pFirstItem=(CCMenuItem*)(m_pChildren->objectAtIndex(0));
            pFirstItem->selected();
            m_pLastSelectedItem = pFirstItem;
        }
	}
}

void CCRadioMenu::setSelectedItem(CCMenuItem* item)
{
    if(m_pChildren->indexOfObject(item) != CC_INVALID_INDEX)
    {
        m_pSelectedItem = item;
        m_pSelectedItem->selected();
        
        // unselect the previous selected CCMenuItem
		if (m_pLastSelectedItem&&m_pLastSelectedItem!=m_pSelectedItem)
		{
			m_pLastSelectedItem->unselected();
		}
        
        m_pLastSelectedItem = m_pSelectedItem;
    }
}

CCMenuItem* CCRadioMenu::getSelectedItem()
{
    return m_pSelectedItem;
}

bool CCRadioMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || !m_bVisible /*|| !m_bEnabled*/)
	{
		return false;
	}
    
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
    
	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
        // unselect the previous selected CCMenuItem
		if (m_pLastSelectedItem&&m_pLastSelectedItem!=m_pSelectedItem)
		{
			m_pLastSelectedItem->unselected();
		}
        
		return true;
	}
	return false;
}
void CCRadioMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
}

void CCRadioMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
		m_pSelectedItem->activate();
		m_pLastSelectedItem = m_pSelectedItem;
	}
	m_eState = kCCMenuStateWaiting;
}

NS_CC_END