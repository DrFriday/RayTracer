#include "RenderApp.h"

IMPLEMENT_APP(RenderApp)

bool
RenderApp::OnInit()
{
	wxInitAllImageHandlers();

	frame = new RenderFrame(wxPoint(200, 200), wxSize(700, 500));
	frame->Centre();
	frame->Show(true);
	SetTopWindow(frame.get());
	return true;
}

int 
RenderApp::OnExit()
{
	return 0;
}

void 
RenderApp::SetStatusText(const wxString&  text, int number)
{
	frame->SetStatusText(text, number);
}