///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : wxAwesomium.h
//   Description :
//      [TODO: Write the purpose of wxAwesomium.h.]
//
//   Created On: 9/18/2009 2:17:56 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifndef DESURA_WXAWESOMIUM_H
#define DESURA_WXAWESOMIUM_H
#ifdef _WIN32
#pragma once
#endif

#include "wx/wx.h"
#include "wxWebListener.h"
#include "WebCore.h"

class wxAwesomium : public wxPanel
{
public:
	wxAwesomium(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS );
	~wxAwesomium();


	void loadHtml(const wxString& html);
	void loadFile(const wxString& file);
	void loadUrl(const wxString& url);

	void stop();
	void refresh();
	void back();
	void forward();

	bool AcceptsFocus();

	void registerJSCallBack(const wxString& callback);
	void addCookie(const wxString& url, const wxString& name, const wxString& value);

protected:
	void onKeyPressed( wxKeyEvent& event );
	void onKeyDown( wxKeyEvent& event );
	void onKeyUp( wxKeyEvent& event );

	void onMouseEvent( wxMouseEvent& event );
	void onResize( wxSizeEvent& event );

	void onBlur( wxFocusEvent& event );
	void onFocus( wxFocusEvent& event );
	void onPaint(wxPaintEvent& event);
	void onEraseBG( wxEraseEvent& event ){;}
	void onIdle( wxIdleEvent& event );

	bool wxMouseToAMouse(int mouse, Awesomium::MouseButton& res);
		

	void changeCursor(const HCURSOR& cursor);

private:
	Awesomium::WebView* m_pWebView;


	friend class wxWebViewListener;
	DECLARE_EVENT_TABLE();
};

#endif //DESURA_WXAWESOMIUM_H
