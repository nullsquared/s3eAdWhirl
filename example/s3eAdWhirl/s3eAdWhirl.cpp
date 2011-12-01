/*
 * This file is part of the s3eAdWhirl Marmalade extension
 *
 * Copyright (C) 2001-2011 Agop Shirinian
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ExamplesMain.h"

#include "s3eAdWhirl.h"

namespace
{
	const char* g_LastMessage = NULL;

	bool g_AdShowing = true;

	float GetAdScale()
	{
		// the banners are 320x50 but they may be scaled up depending on the screen size
		float adScale = s3eSurfaceGetInt(S3E_SURFACE_WIDTH) / 320.0f;
		return adScale;
	}

	int32 AdLoad(void* system, void* user)
	{
		g_LastMessage = "`x666666Ad loaded";
		return 0;
	}

	int32 AdFail(void* system, void* user)
	{
		g_LastMessage = "`x666666Ad failed";
		return 0;
	}

	int32 AdFullscreenBegin(void* system, void* user)
	{
		g_LastMessage = "`x666666Fullscreen ad began";
		return 0;
	}

	int32 AdFullscreenEnd(void* system, void* user)
	{
		g_LastMessage = "`x666666Fullscreen ad ended";
		return 0;
	}

	// avoid bringing in conflicting SC++L implementations
	int iabs(int x)
	{
		return x < 0 ? -x : x;
	}
}

void ExampleInit()
{
	// initialise s3eAdWhirl
	s3eDeviceOSID osid = (s3eDeviceOSID)s3eDeviceGetInt(S3E_DEVICE_OS);
	if (osid == S3E_OS_ID_IPHONE)
	{
		// this ID is specifically made for testing s3eAdWhirl
		// make sure you change this ID to your iPhone app AdWhirl ID when building your own app
		s3eAdWhirlStart("c9791d39bd5b4157b2d3f7912d345c52");
	}
	else if (osid == S3E_OS_ID_ANDROID)
	{
		// this ID is specifically made for testing s3eAdWhirl
		// make sure you change this ID to your Android app AdWhirl ID when building your own app
		s3eAdWhirlStart("c705a7e8711b4aafb845d18d390976b0");
	}
	else
	{
	}

	s3eAdWhirlRegister(S3E_ADWHIRL_CALLBACK_AD_LOAD, &AdLoad, NULL);
	s3eAdWhirlRegister(S3E_ADWHIRL_CALLBACK_AD_FAIL, &AdFail, NULL);
	s3eAdWhirlRegister(S3E_ADWHIRL_CALLBACK_FULLSCREEN_BEGIN, &AdFullscreenBegin, NULL);
	s3eAdWhirlRegister(S3E_ADWHIRL_CALLBACK_FULLSCREEN_END, &AdFullscreenEnd, NULL);
}

void ExampleTerm()
{
}

bool ExampleUpdate()
{
	if (!s3eAdWhirlAvailable())
		return true;

	s3ePointerState pointerState = s3ePointerGetState(S3E_POINTER_BUTTON_SELECT);

	if ((pointerState & S3E_POINTER_STATE_RELEASED) != 0)
	{
		int screenH = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
		int y = s3ePointerGetY();

		if (iabs(screenH - 300 - y) < 50)
		{
			if (g_AdShowing)
			{
				s3eAdWhirlHide();
				g_AdShowing = false;
			}
			else
			{
				s3eAdWhirlShow();
				g_AdShowing = true;
			}
		}
		else if (iabs(screenH - 200 - y) < 50)
		{
			s3eAdWhirlRequestFreshAd();
		}
	}

	return true;
}

void ExampleRender()
{
	int screenW = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int screenH = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	if (!s3eAdWhirlAvailable())
	{
		s3eDebugPrint(screenW / 3, screenH / 2, "`xff0000s3eAdWhirl extension not found.", 1);
		return;
	}

	if (g_AdShowing)
	{
		s3eDebugPrintf(10, screenH - 300, S3E_FALSE, "`x666666Tap here to hide ad");
	}
	else
	{
		s3eDebugPrintf(10, screenH - 300, S3E_FALSE, "`x666666Tap here to show ad");
	}

	s3eDebugPrintf(10, screenH - 200, S3E_FALSE, "`x666666Tap here to refresh ad");

	if (g_LastMessage != NULL)
	{
		s3eDebugPrintf(10, screenH - 100, S3E_FALSE, g_LastMessage);
	}

	if (g_AdShowing)
	{
		float adScale = GetAdScale();
		int adW = (int)(320 * adScale);
		int adH = (int)(50 * adScale);
		// draw a fake ad for the simulator
		DrawRect(0, 0, adW, adH, 255, 128, 128);
		s3eDebugPrintf(adW / 3, adH / 2, S3E_FALSE, "`x666666Loading ad...");
	}
}
