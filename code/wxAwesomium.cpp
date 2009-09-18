///////////// Copyright © 2009 DesuraNet. All rights reserved. /////////////
//
//   Project     : wxAwesomium
//   File        : wxAwesomium.cpp
//   Description :
//      [TODO: Write the purpose of wxAwesomium.cpp.]
//
//   Created On: 9/18/2009 2:17:58 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

//#include "common.h"
#include "wxAwesomium.h"
#include "wxWebListener.h"


Awesomium::WebCore* g_pWebCore = NULL;

void updateAwesomium()
{
	if (g_pWebCore)
		g_pWebCore->update();
}

BEGIN_EVENT_TABLE( wxAwesomium, wxPanel )
	EVT_CHAR( wxAwesomium::onKeyPressed )
	EVT_KEY_DOWN( wxAwesomium::onKeyDown )
	EVT_KEY_UP( wxAwesomium::onKeyUp )
	EVT_MOUSE_EVENTS( wxAwesomium::onMouseEvent )
	EVT_SIZE( wxAwesomium::onResize )
	EVT_SET_FOCUS( wxAwesomium::onFocus )
	EVT_KILL_FOCUS( wxAwesomium::onBlur )
	EVT_IDLE( wxAwesomium::onIdle )
END_EVENT_TABLE()

wxAwesomium::wxAwesomium(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	if (!g_pWebCore)
		g_pWebCore = new Awesomium::WebCore(Awesomium::LOG_NORMAL, true, Awesomium::PF_RGBA);

	m_pWebView = g_pWebCore->createWebView(size.GetWidth(), size.GetHeight());
	m_pWebView->setListener(new wxWebViewListener(this));

	Connect( wxEVT_PAINT, wxPaintEventHandler( wxAwesomium::onPaint ));
	Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( wxAwesomium::onEraseBG ) );
}

wxAwesomium::~wxAwesomium()
{
	m_pWebView->destroy();
}

bool wxAwesomium::AcceptsFocus()
{
	return true;
}

void wxAwesomium::registerJSCallBack(const wxString& callback)
{
	m_pWebView->setCallback(std::string( callback.c_str() ));
}

void wxAwesomium::addCookie(const wxString& url, const wxString& name, const wxString& value)
{

}

void wxAwesomium::loadHtml(const wxString& html)
{
	m_pWebView->loadHTML(std::string( html.c_str() ));
}

void wxAwesomium::loadFile(const wxString& file)
{
	m_pWebView->loadFile(std::string( file.c_str() ));
}

void wxAwesomium::loadUrl(const wxString& url)
{
	std::string stdUrl( url.c_str() );

	if (!url.StartsWith("http://"))
		stdUrl = std::string("http://") + stdUrl;

	m_pWebView->loadURL(stdUrl);
}

void wxAwesomium::stop()
{
}

void wxAwesomium::refresh()
{
}

void wxAwesomium::back()
{
	m_pWebView->goToHistoryOffset(-1);
}

void wxAwesomium::forward()
{
	m_pWebView->goToHistoryOffset(1);
}



void wxAwesomium::onKeyPressed( wxKeyEvent& event )
{
	HWND hwnd = (HWND)this->GetHWND();
	UINT message = WM_CHAR;
	WPARAM wparam = event.m_rawCode;
	LPARAM lparam = event.m_rawFlags;

	m_pWebView->injectKeyboardEvent(hwnd, message, wparam, lparam);
	event.Skip();
}

void wxAwesomium::onKeyDown( wxKeyEvent& event )
{
	HWND hwnd = (HWND)this->GetHWND();
	UINT message = WM_KEYDOWN;
	WPARAM wparam = event.m_rawCode;
	LPARAM lparam = event.m_rawFlags;

	m_pWebView->injectKeyboardEvent(hwnd, message, wparam, lparam);
	event.Skip();
}

void wxAwesomium::onKeyUp( wxKeyEvent& event )
{
	HWND hwnd = (HWND)this->GetHWND();
	UINT message = WM_KEYUP;
	WPARAM wparam = event.m_rawCode;
	LPARAM lparam = event.m_rawFlags;

	m_pWebView->injectKeyboardEvent(hwnd, message, wparam, lparam);
	event.Skip();
}

void wxAwesomium::onMouseEvent( wxMouseEvent& event )
{
	if (event.Moving() || event.Dragging())
	{
		int x,y;
		event.GetPosition(&x,&y);
		m_pWebView->injectMouseMove(x,y);
	}

	if (event.ButtonDown())
	{
		SetFocus();
		Awesomium::MouseButton but;

		if (wxMouseToAMouse(event.GetButton(), but) == true)
			m_pWebView->injectMouseDown(but);
	}

	if (event.ButtonUp())
	{
		Awesomium::MouseButton but;

		if (wxMouseToAMouse(event.GetButton(), but) == true)
			m_pWebView->injectMouseUp(but);
	}

	m_pWebView->injectMouseWheel(event.GetWheelRotation());
}

void wxAwesomium::onResize( wxSizeEvent& event )
{
	m_pWebView->resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void wxAwesomium::onBlur( wxFocusEvent& event )
{
	m_pWebView->unfocus();
}

void wxAwesomium::onFocus( wxFocusEvent& event )
{
	m_pWebView->focus();
}

void wxAwesomium::onIdle( wxIdleEvent& event )
{
	g_pWebCore->update();
	Refresh();
}

void wxAwesomium::onPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	int x = this->GetSize().GetWidth();
	int y = this->GetSize().GetHeight();

	unsigned char *buff = (unsigned char*)malloc(sizeof(unsigned char*)*x*y*3);
	memset(buff, 0, x*y*3);

	m_pWebView->render(buff, x*3, 3);

	wxImage render(x, y);
	render.SetData(buff);

	wxBitmap temp(render);

	//temp.SaveFile("E:\\wxBrowserTest\\wxAwesomium\\Debug\\RenderImage.bmp", wxBITMAP_TYPE_BMP);
	dc.DrawBitmap(temp, 0, 0, true);
}

bool wxAwesomium::wxMouseToAMouse(int mouse, Awesomium::MouseButton& res)
{
	switch (mouse)
	{
		case wxMOUSE_BTN_LEFT:
			res = Awesomium::LEFT_MOUSE_BTN;
			break;

		case wxMOUSE_BTN_MIDDLE: 
			res = Awesomium::MIDDLE_MOUSE_BTN; 
			break;

		case wxMOUSE_BTN_RIGHT: 
			res = Awesomium::RIGHT_MOUSE_BTN; 
			break;

		default:
			return false;
	};

	return true;
}

void wxAwesomium::changeCursor(const HCURSOR& cursor)
{
	wxCursor c;
	c.SetHCURSOR((WXHCURSOR)cursor);
	this->SetCursor( c );
}