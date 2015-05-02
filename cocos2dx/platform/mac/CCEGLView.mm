/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "CCEGLView.h"
#include "EAGLView.h"
#include "CCDirectorCaller.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

NS_CC_BEGIN

CCEGLView* CCEGLView::s_sharedView = NULL;

CCEGLView* CCEGLView::sharedOpenGLView(void)
{
    if (!s_sharedView)
    {
        s_sharedView = new CCEGLView();
    }
    return s_sharedView;
}

CCEGLView::CCEGLView(void)
{
}

CCEGLView::~CCEGLView(void)
{
    CCLOG("cocos2d: deallocing CCEGLView %p", this);
    s_sharedView = NULL;
}

bool CCEGLView::isOpenGLReady(void)
{
    return [EAGLView sharedEGLView] != NULL;
}

bool CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    return false;
}

void CCEGLView::end(void)
{
    [[CCDirectorCaller sharedDirectorCaller] end];
    
    // destroy EAGLView
    [[EAGLView sharedEGLView] removeFromSuperview];
    
    delete this;
}

void CCEGLView::swapBuffers()
{
	[[EAGLView sharedEGLView] swapBuffers];
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        [[EAGLView sharedEGLView] becomeFirstResponder];
    }
    else
    {
        [[EAGLView sharedEGLView] resignFirstResponder];
    }
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[EAGLView sharedEGLView] frameZoomFactor];
    
    glViewport((GLint)(x * m_fScaleX * frameZoomFactor + m_obViewPortRect.origin.x * frameZoomFactor),
               (GLint)(y * m_fScaleY * frameZoomFactor + m_obViewPortRect.origin.y * frameZoomFactor),
               (GLsizei)(w * m_fScaleX * frameZoomFactor),
               (GLsizei)(h * m_fScaleY * frameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[EAGLView sharedEGLView] frameZoomFactor];
    
    glScissor((GLint)(x * m_fScaleX * frameZoomFactor + m_obViewPortRect.origin.x * frameZoomFactor),
              (GLint)(y * m_fScaleY * frameZoomFactor + m_obViewPortRect.origin.y * frameZoomFactor),
              (GLsizei)(w * m_fScaleX * frameZoomFactor),
              (GLsizei)(h * m_fScaleY * frameZoomFactor));
}

void CCEGLView::setMultiTouchMask(bool mask)
{
	//EAGLView *glView = [EAGLView sharedEGLView];
	//glView.multipleTouchEnabled = mask ? YES : NO;
}

// -- custom extension start --
void CCEGLView::callbackPopViewIos()
{
    [[EAGLView sharedEGLView] callbackPopViewIos];
}

void CCEGLView::callbackNativeActivityOrViewController(int contextId)
{
    [[EAGLView sharedEGLView] callbackNativeViewControllerWithContextId:contextId];
}

void CCEGLView::callbackPerformActionWithFilePath(int eventId, int actionId, const char *filePath)
{
    [[EAGLView sharedEGLView] callbackPerformActionWithEventId:eventId andActionId:actionId andFilePath:[NSString stringWithUTF8String:filePath]];
}

void CCEGLView::callbackPerformActionWithFolderPath(int eventId, int actionId, const char *folderPath)
{
    [[EAGLView sharedEGLView] callbackPerformActionWithEventId:eventId andActionId:actionId andFolderPath:[NSString stringWithUTF8String:folderPath]];
}

std::string CCEGLView::callbackJsonEvent(std::string callbackJson)
{
    NSString *returnJson = [[EAGLView sharedEGLView] callbackJsonEvent:[NSString stringWithUTF8String:callbackJson.c_str()]];
    std::string returnJsonString = "";
    if (returnJson != NULL)
    {
        returnJsonString = std::string([returnJson UTF8String]);
    }
    return returnJsonString;
}
// -- custom extension end --

NS_CC_END // end of namespace cocos2d;
