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

#ifndef __CC_COMMON_H__
#define __CC_COMMON_H__

#include "CCPlatformMacros.h"

// -- custom extension start --
#include "CCFileUtils.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
// -- custom extension end --

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/// The max length of CCLog message.
static const int kMaxLogLen = 16*1024;

// -- custom extension start --
typedef enum LogLevel
{
	LOG_DEBUG = 1,
	LOG_INFO = 2,
	LOG_WARN = 3,
	LOG_ERROR = 4,
} ccLogLevel;
// -- custom extension end --

/**
@brief Output Debug message.
*/
void CC_DLL CCLog(const char * pszFormat, ...) CC_FORMAT_PRINTF(1, 2);

// -- custom extension start --
void CC_DLL CCLog(ccLogLevel logLevel, const char *tag, const char *pszFormat, ...);

// custom logging
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
inline void CC_DLL DDLog(ccLogLevel logLevel, const char *cppName, const char *funcName, int lineNum, const char *pszFormat, ...)
{
	static FILE *logFile = NULL; // static global file
	long int logFileMaxSize = 10 * 1024 * 1024; // 10MB
	std::string logFilePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "log-cocos2dx.txt";
    
	char buf[cocos2d::kMaxLogLen + 1];
    
	va_list args;
	va_start(args, pszFormat);
	vsnprintf(buf, cocos2d::kMaxLogLen + 1, pszFormat, args);
	va_end(args);
    
	std::string logPriorityString = "";
	switch (logLevel)
	{
		case LOG_DEBUG:
    		logPriorityString = "[DEBUG]";
    		break;
		case LOG_INFO:
    		logPriorityString = "[INFO]";
    		break;
		case LOG_WARN:
    		logPriorityString = "[WARN]";
    		break;
		case LOG_ERROR:
    		logPriorityString = "[ERROR]";
    		break;
		default:
    		break;
	}
    
	std::ostringstream tag;
    
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	tag << cppName << ":" << funcName << ":" << lineNum;
	#else
	tag << logPriorityString << "[" << cppName << ":" << funcName << ":" << lineNum << "]";
	#endif
	CCLog(logLevel, tag.str().c_str(), buf);
    
	#ifdef LOG_WRITE_TO_FILE
	std::ostringstream logInfo;
	logInfo << "[" << __DATE__ << " " << __TIME__ << "]" << logPriorityString << "[" << cppName << ":" << funcName << ":" << lineNum << "]" << buf << "\r\n";
    
	// open and write to file
	if (logFile == NULL)
	{
		logFile = fopen(logFilePath.c_str(), "a+");
		if (!logFile)
		{
    		CCLog(LOG_ERROR, "CCCommon.h:DLog()", "Error creating log file:%s", logFilePath.c_str());
    		return;
		}
	}

	// check if file size exceed max file size, recreate
	long int logFileSize = ftell(logFile);
	if (logFileSize > logFileMaxSize)
	{
		CCLog(LOG_INFO, "CCCommon.h:DLog()", "Generate new log file:%s", logFilePath.c_str());
		fclose(logFile);

		logFile = fopen(logFilePath.c_str(), "w+");
		if (!logFile)
		{
			CCLog(LOG_ERROR, "CCCommon.h:DLog()", "Error creating new log file:%s", logFilePath.c_str());
			return;
		}
	}
    
	fputs(logInfo.str().c_str(), logFile);
	fflush(logFile);

	// do not close the file, always open
	#endif
}
#else
	inline void CC_DLL DDLog(ccLogLevel logLevel, const char *cppName, const char *funcName, int lineNum, const char *pszFormat, ...)
	{
		// do nothing
	}
#endif
// -- custom extension end --

/**
 * lua can not deal with ...
 */
void CC_DLL CCLuaLog(const char * pszFormat);

/**
@brief Pop out a message box
*/
void CC_DLL CCMessageBox(const char * pszMsg, const char * pszTitle);

/**
@brief Enum the language type supported now
*/
typedef enum LanguageType
{
    kLanguageEnglish = 0,
    kLanguageChinese,
    kLanguageFrench,
    kLanguageItalian,
    kLanguageGerman,
    kLanguageSpanish,
    kLanguageDutch,
    kLanguageRussian,
    kLanguageKorean,
    kLanguageJapanese,
    kLanguageHungarian,
    kLanguagePortuguese,
    kLanguageArabic
} ccLanguageType;

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_COMMON_H__
