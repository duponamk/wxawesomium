///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : MyFrame.cpp
//   Description :
//      [TODO: Write the purpose of MyFrame.cpp.]
//
//   Created On: 9/18/2009 2:48:33 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

//#include "common.h"
#include "MyFrame.h"


BEGIN_EVENT_TABLE( MyFrame, wxFrame )
	EVT_BUTTON( wxID_ANY, MyFrame::onButClick )
	EVT_RECEIVETITLE( MyFrame::onTitleChange )
	EVT_CALLBACK( MyFrame::onJSCallBack )
END_EVENT_TABLE()

MyFrame::MyFrame( const wxString& title) : wxFrame( NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxWANTS_CHARS )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 0 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxT("http://lodle.net/moddb/cookie.php"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl2, 0, wxALL|wxEXPAND, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, wxT("Go"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_button2, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	fgSizer1->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_pBrowser = new wxAwesomium( this );
	m_pBrowser->registerJSCallBack( "clearBreadCrumbs" );
	m_pBrowser->registerJSCallBack( "addBreadCrumb" );
	m_pBrowser->addCookie("http://lodle.net/moddb", "TestCookie", "Mmm Cookies!");

	fgSizer1->Add( m_pBrowser, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

MyFrame::~MyFrame()
{
}

void MyFrame::onButClick( wxCommandEvent& event )
{
	m_pBrowser->loadUrl(m_textCtrl2->GetValue());
}

void MyFrame::onTitleChange(wxAWSReceiveTitleEvent& event)
{
	this->SetTitle(event.m_szTitle);
}

void MyFrame::onJSCallBack(wxAWSCallBackEvent& event)
{
	
}