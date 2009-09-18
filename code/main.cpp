
#include "wx/wx.h"

#include "MyFrame.h"

extern void updateAwesomium();

class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)

	virtual bool OnInit()
	{
		// call the base class initialization method, currently it only parses a
		// few common command-line options but it could be do more in the future
		if ( !wxApp::OnInit() )
			return false;

		// create the main application window
		MyFrame *frame = new MyFrame("Minimal wxWidgets App");

		// and show it (the frames, unlike simple controls, are not shown when
		// created initially)
		frame->Show(true);

		// success: wxApp::OnRun() will be called which will enter the main message
		// loop and the application will run. If we returned false here, the
		// application would exit immediately.
		return true;
	}

	bool Dispatch()
	{
		updateAwesomium();
		return wxApp::Dispatch();
	}
};

IMPLEMENT_APP(MyApp)