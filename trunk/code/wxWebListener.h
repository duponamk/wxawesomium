///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : wxWebListener.h
//   Description :
//      [TODO: Write the purpose of wxWebListener.h.]
//
//   Created On: 9/18/2009 2:29:19 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifndef DESURA_WXWEBLISTENER_H
#define DESURA_WXWEBLISTENER_H
#ifdef _WIN32
#pragma once
#endif

#include "WebViewListener.h"
#include <vector>
#include "wx/wx.h"

class wxAwesomium;

class wxWebViewListener : public Awesomium::WebViewListener
{
public:
	wxWebViewListener(wxAwesomium* parent);

	void onBeginNavigation(const std::string& url, const std::wstring& frameName);
	void onBeginLoading(const std::string& url, const std::wstring& frameName, int statusCode, const std::wstring& mimeType);
	void onFinishLoading();
	void onCallback(const std::string& name, const Awesomium::JSArguments& args);
	void onReceiveTitle(const std::wstring& title, const std::wstring& frameName);
	void onChangeTooltip(const std::wstring& tooltip);
	void onChangeCursor(const HCURSOR& cursor);
	void onChangeKeyboardFocus(bool isFocused);
	void onChangeTargetURL(const std::string& url);

private:
	wxAwesomium* m_pParent;
};


#define DEF_EVENTTYPE( name ) typedef void (wxEvtHandler::* name##Function) ( name &);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_BEGINNAVIGATION, 1000)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_BEGINLOADING, 1001)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_FINISHLOADING, 1002)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_CALLBACK, 1003)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_RECEIVETITLE, 1004)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_CHANGETOOLTIP, 1005)
	DECLARE_LOCAL_EVENT_TYPE(wxAWS_CHANGETARGETURL, 1006)
END_DECLARE_EVENT_TYPES()

///////////////////////////////////////////////////////////////////////////////////////
// BeginNavigationEvent
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSBeginNavigationEvent : public wxNotifyEvent
{
public:
	wxAWSBeginNavigationEvent(const wxString& url = wxT(""), const wxString& frameName = wxT("")) : wxNotifyEvent(wxAWS_BEGINNAVIGATION, 0)
	{
		m_szUrl = url;
		m_szFrameName = frameName;
	}

	wxAWSBeginNavigationEvent(const wxAWSBeginNavigationEvent& event) : wxNotifyEvent(event)
	{
		m_szUrl = event.m_szUrl;
		m_szFrameName = event.m_szFrameName;
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSBeginNavigationEvent(*this);
	}


	wxString m_szUrl;
	wxString m_szFrameName;

	DECLARE_DYNAMIC_CLASS(wxAWSBeginNavigationEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// BeginLoading
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSBeginLoadingEvent : public wxNotifyEvent
{
public:
	wxAWSBeginLoadingEvent(const wxString& url = wxT(""), const wxString& frameName = wxT(""), int status = 0, const wxString& mimetype = wxT("")) : wxNotifyEvent(wxAWS_BEGINLOADING, 0)
	{
		m_szUrl = url;
		m_szFrameName = frameName;
		m_iStatus = status;
		m_szMimeType = mimetype;
	}

	wxAWSBeginLoadingEvent(const wxAWSBeginLoadingEvent& event) : wxNotifyEvent(event)
	{
		m_szUrl = event.m_szUrl;
		m_szFrameName = event.m_szFrameName;
		m_iStatus = event.m_iStatus;
		m_szMimeType = event.m_szMimeType;
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSBeginLoadingEvent(*this);
	}

	wxString m_szUrl;
	wxString m_szFrameName;
	wxString m_szMimeType;
	int m_iStatus;

	DECLARE_DYNAMIC_CLASS(wxAWSBeginLoadingEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// FinishLoading
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSFinishLoadingEvent : public wxNotifyEvent
{
public:
	wxAWSFinishLoadingEvent() : wxNotifyEvent(wxAWS_FINISHLOADING, 0)
	{
	}

	wxAWSFinishLoadingEvent(const wxAWSFinishLoadingEvent& event) : wxNotifyEvent(event)
	{
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSFinishLoadingEvent(*this);
	}

	DECLARE_DYNAMIC_CLASS(wxAWSFinishLoadingEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// CallBack
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSCallBackEvent : public wxNotifyEvent
{
public:
	wxAWSCallBackEvent(const wxString& name = wxT(""), const Awesomium::JSArguments& args = Awesomium::JSArguments()) : wxNotifyEvent(wxAWS_CALLBACK, 0)
	{
		m_szName = name;

		for (size_t x=0; x<args.size(); x++)
		{
			m_Args.push_back( wxString(args[x].toString().c_str()));
		}
	}

	wxAWSCallBackEvent(const wxAWSCallBackEvent& event) : wxNotifyEvent(event)
	{
		m_szName = event.m_szName;

		for (size_t x=0; x<event.m_Args.size(); x++)
		{
			m_Args.push_back( wxString(event.m_Args[x]));
		}
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSCallBackEvent(*this);
	}


	wxString m_szName;
	std::vector<wxString> m_Args;

	DECLARE_DYNAMIC_CLASS(wxAWSCallBackEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// ReceiveTitle
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSReceiveTitleEvent : public wxNotifyEvent
{
public:
	wxAWSReceiveTitleEvent(const wxString& title = wxT(""), const wxString& frameName = wxT("")) : wxNotifyEvent(wxAWS_RECEIVETITLE, 0)
	{
		m_szTitle = title;
		m_szFrameName = frameName;
	}

	wxAWSReceiveTitleEvent(const wxAWSReceiveTitleEvent& event) : wxNotifyEvent(event)
	{
		m_szTitle = event.m_szTitle;
		m_szFrameName = event.m_szFrameName;
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSReceiveTitleEvent(*this);
	}


	wxString m_szTitle;
	wxString m_szFrameName;

	DECLARE_DYNAMIC_CLASS(wxAWSReceiveTitleEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// ChangeTooltip 
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSChangeTooltipEvent : public wxNotifyEvent
{
public:
	wxAWSChangeTooltipEvent(const wxString& tooltip = wxT("")) : wxNotifyEvent(wxAWS_CHANGETOOLTIP, 0)
	{
		m_szToolTip = tooltip;
	}

	wxAWSChangeTooltipEvent(const wxAWSChangeTooltipEvent& event) : wxNotifyEvent(event)
	{
		m_szToolTip = event.m_szToolTip;
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSChangeTooltipEvent(*this);
	}


	wxString m_szToolTip;

	DECLARE_DYNAMIC_CLASS(wxAWSChangeTooltipEvent);
};

///////////////////////////////////////////////////////////////////////////////////////
// ChangeTargetURL
///////////////////////////////////////////////////////////////////////////////////////

class wxAWSChangeTargetURLEvent : public wxNotifyEvent
{
public:
	wxAWSChangeTargetURLEvent(const wxString& url = wxT("")) : wxNotifyEvent(wxAWS_CHANGETARGETURL, 0)
	{
		m_szUrl = url;
	}

	wxAWSChangeTargetURLEvent(const wxAWSChangeTargetURLEvent& event) : wxNotifyEvent(event)
	{
		m_szUrl = event.m_szUrl;
	}

	virtual wxEvent *Clone() const
	{
		return new wxAWSChangeTargetURLEvent(*this);
	}

	wxString m_szUrl;

	DECLARE_DYNAMIC_CLASS(wxAWSChangeTargetURLEvent);
};



DEF_EVENTTYPE(wxAWSBeginNavigationEvent);
#define EVT_BEGINNAVIGATION(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_BEGINNAVIGATION, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSBeginNavigationEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSBeginLoadingEvent);
#define EVT_BEGINLOADING(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_BEGINLOADING, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSBeginLoadingEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSFinishLoadingEvent);
#define EVT_FINISHLOADING(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_FINISHLOADING, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSFinishLoadingEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSCallBackEvent);
#define EVT_CALLBACK(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_CALLBACK, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSCallBackEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSReceiveTitleEvent);
#define EVT_RECEIVETITLE(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_RECEIVETITLE, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSReceiveTitleEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSChangeTooltipEvent);
#define EVT_CHANGETOOLTIP(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_CHANGETOOLTIP, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSChangeTooltipEventFunction) & fn, (wxObject *) NULL ),

DEF_EVENTTYPE(wxAWSChangeTargetURLEvent);
#define EVT_CHANGETARGETURL(fn)	DECLARE_EVENT_TABLE_ENTRY( wxAWS_CHANGETARGETURL, wxID_ANY, -1, (wxObjectEventFunction) (wxEventFunction) (wxAWSChangeTargetURLEventFunction) & fn, (wxObject *) NULL ),


#endif 