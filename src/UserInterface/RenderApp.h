#include <wx/wx.h>

#include "RenderFrame.h"

class RenderApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
	virtual void SetStatusText(const wxString&  text, int number = 0);

private:
	RenderFrame* frame;
};

DECLARE_APP(RenderApp);