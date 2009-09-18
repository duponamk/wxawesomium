///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : wxWebListener.cpp
//   Description :
//      [TODO: Write the purpose of wxWebListener.cpp.]
//
//   Created On: 9/18/2009 2:29:51 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

//#include "common.h"
#define _CRT_SECURE_NO_WARNINGS
#include "wxWebListener.h"
#include "wxAwesomium.h"

wxWebViewListener::wxWebViewListener(wxAwesomium* parent)
{
	m_pParent = parent;
}

void wxWebViewListener::onChangeCursor(const HCURSOR& cursor)
{
	m_pParent->changeCursor(cursor);
}

void wxWebViewListener::onChangeKeyboardFocus(bool isFocused)
{

}


DEFINE_EVENT_TYPE(wxAWS_BEGINNAVIGATION)
IMPLEMENT_DYNAMIC_CLASS(wxAWSBeginNavigationEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_BEGINLOADING)
IMPLEMENT_DYNAMIC_CLASS(wxAWSBeginLoadingEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_FINISHLOADING)
IMPLEMENT_DYNAMIC_CLASS(wxAWSFinishLoadingEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_CALLBACK)
IMPLEMENT_DYNAMIC_CLASS(wxAWSCallBackEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_RECEIVETITLE)
IMPLEMENT_DYNAMIC_CLASS(wxAWSReceiveTitleEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_CHANGETOOLTIP)
IMPLEMENT_DYNAMIC_CLASS(wxAWSChangeTooltipEvent, wxNotifyEvent)

DEFINE_EVENT_TYPE(wxAWS_CHANGETARGETURL)
IMPLEMENT_DYNAMIC_CLASS(wxAWSChangeTargetURLEvent, wxNotifyEvent)


void wxWebViewListener::onBeginNavigation(const std::string& url, const std::wstring& frameName)
{
	m_pParent->GetEventHandler()->AddPendingEvent(wxAWSBeginNavigationEvent(wxString(url), wxString(frameName)));
}

void wxWebViewListener::onBeginLoading(const std::string& url, const std::wstring& frameName, int statusCode, const std::wstring& mimeType)
{
	wxAWSBeginLoadingEvent event(wxString(url), wxString(frameName), statusCode, wxString(mimeType));
	m_pParent->GetEventHandler()->AddPendingEvent(event);
}

void wxWebViewListener::onFinishLoading()
{
	m_pParent->GetEventHandler()->AddPendingEvent(wxAWSFinishLoadingEvent());
}

void wxWebViewListener::onCallback(const std::string& name, const Awesomium::JSArguments& args)
{
	wxAWSCallBackEvent event(wxString(name), args);
	m_pParent->GetEventHandler()->AddPendingEvent(event);
}

void wxWebViewListener::onReceiveTitle(const std::wstring& title, const std::wstring& frameName)
{
	m_pParent->GetEventHandler()->AddPendingEvent(wxAWSReceiveTitleEvent(wxString(title), wxString(frameName)));
}

void wxWebViewListener::onChangeTooltip(const std::wstring& tooltip)
{
	m_pParent->GetEventHandler()->AddPendingEvent(wxAWSChangeTooltipEvent(wxString(tooltip)));
}

void wxWebViewListener::onChangeTargetURL(const std::string& url)
{
	m_pParent->GetEventHandler()->AddPendingEvent(wxAWSChangeTargetURLEvent(wxString(url)));
}


