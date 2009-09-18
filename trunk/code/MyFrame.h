///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : MyFrame.h
//   Description :
//      [TODO: Write the purpose of MyFrame.h.]
//
//   Created On: 9/18/2009 2:17:14 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifndef DESURA_MYFRAME_H
#define DESURA_MYFRAME_H
#ifdef _WIN32
#pragma once
#endif


#include "wx/wx.h"
#include "wxAwesomium.h"

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
	~MyFrame();

protected:
	void onButClick( wxCommandEvent& event );
	void onKeyDown( wxKeyEvent& event );
	void onTitleChange(wxAWSReceiveTitleEvent& event);
	void onJSCallBack(wxAWSCallBackEvent& event);

private:
	wxAwesomium* m_pBrowser;
	wxTextCtrl* m_textCtrl2;
	wxButton* m_button2;

	DECLARE_EVENT_TABLE();
};


#endif //DESURA_MYFRAME_H
