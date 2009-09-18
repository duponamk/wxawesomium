///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : userAgent.cpp
//   Description :
//      [TODO: Write the purpose of userAgent.cpp.]
//
//   Created On: 9/18/2009 7:17:03 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifdef max
#undef max
#endif

#include "PlatformString.h"
#include "detours.h"

class TUserAgent
{
public:
	WebCore::String getUserAgent(const WebCore::String& appName)
	{
		const char* wOsVer = "TestUserAgent";
		const char* appidStr = "100";
		const char* buildStr = "1";

		return WebCore::String::format("Desura/%d.%d (%s)", atoi(appidStr), atoi(buildStr), wOsVer);
	}
};

typedef WebCore::String (__thiscall TUserAgent::* UserAgentFN)(const WebCore::String&);


bool g_bHookStatus = false;
UserAgentFN originalFunction = NULL;
UserAgentFN newFunction = &TUserAgent::getUserAgent;



bool isHooked()
{
	return g_bHookStatus;
}

void doHook()
{
	//debug sub_11084400
	//release loc_101D0E50

//#ifdef _DEBUG
//	originalFunction = (UserAgentFN)DetourFunction((PBYTE)0x11084400, static_cast<PBYTE>(newFunction));
//#else
//	originalFunction = (UserAgentFN)DetourFunction((PBYTE)0x101D0E50, static_cast<PBYTE>(newFunction));
//#endif

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID*)0x11084400, (PVOID*)&newFunction);
	DetourTransactionCommit();

	g_bHookStatus = true;
}

void releaseHook()
{
//#ifdef _DEBUG
//	DetourRemove((PBYTE)0x11084400, (PBYTE)originalFunction);
//#else
//	DetourRemove((PBYTE)0x101D0E50, (PBYTE)originalFunction);
//#endif

	g_bHookStatus = false;
}