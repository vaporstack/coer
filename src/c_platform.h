//
//  c_platform.h
//  coer-ios
//
//  Created by vs on 2/19/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef c_platform_h
#define c_platform_h


#ifdef _WIN64
#define CPLATFORM_WIN
#elif _WIN32
#define CPLATFORM_WIN

#elif __APPLE__
#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#define CPLATFORM_IOS
//#define CPLATFORM_IOS
#elif TARGET_IPHONE_SIMULATOR
#define CPLATFORM_IOS_SIM
//#define CPLATFORM_IOS
//#define CPLATFORM_IOS

#ifndef PATH_MAX
#define PATH_MAX 2048
#endif

#else

#define CPLATFORM_DARWIN 1
#undef CPLATFORM_IOS_SIM
#undef CPLATFORM_IOS
#endif

#elif __linux
#define CPLATFORM_LINUX

#elif __linux__
#define CPLATFORM_LINUX
#elif __unix // all unices not caught above

#define CPLATFORM_UNIX
#error unix
#elif __posix

#define CPLATFORM_POSIX
#error posix

#elif __ANDROID__
#define CPLATFORM_ANDROID
#else

#error unable to determine platform
#endif

#ifdef CPLATFORM_LINUX
#include <linux/limits.h>
#include <stdbool.h>
#endif

#ifdef CPLATFORM_WIN

#include <windows.h>
#define PATH_MAX 2048
typedef short bool;
#define true 1
#define false 0
#endif

#ifdef CPLATFORM_DARWIN
#include <limits.h>
#include <stdbool.h>
#endif

//  usage
/*
 //  big ugly switch
 #ifdef CPLATFORM_WIN_64
 #define ROS_SEP '\\'
 #define RGL_GL
 
 #elif   CPLATFORM_WIN_32
 #define ROS_SEP '\\'
 #define RGL_GL
 
 #elif   CPLATFORM_IOS
 #define ROS_SEP '/'
 #define RGL_GLES
 #elif   CPLATFORM_IOS_SIM
 #define ROS_SEP '/'
 #define RGL_GLES
 #elif	CPLATFORM_DARWIN
 #define ROS_SEP '/'
 
 #elif   CPLATFORM_LINUX
 #define ROS_SEP '/'
 #define RGL_GL 1
 #elif   RTARGET_LINUX
 #define ROS_SEP '/'
 #define RGL_GL 1
 #elif   RTARGET_UNIX
 #define ROS_SEP '/'
 #define RGL_GL 1
 
 #elif   RTARGET_POSIX
 #define ROS_SEP '/'
 #define RGL_GL 1
 
 #endif
 */


#endif /* c_platform_h */
