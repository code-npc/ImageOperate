﻿#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CImageOperateApp:
// 有关此类的实现，请参阅 ImageOperate.cpp
//

class ImageOperateApp : public CWinApp
{
public:
	ImageOperateApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern ImageOperateApp theApp;
