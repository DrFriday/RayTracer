#ifndef __RENDER_FRAME__
#define __RENDER_FRAME__

#include <wx/wx.h>
#include "RenderCanvas.h"

class RenderFrame : public wxFrame
{
public:
	RenderFrame(const wxPoint& pos, const wxSize& size);

	//event handlers
	void OnQuit(wxCommandEvent& event);
	void OnOpenFile(wxCommandEvent& event);
	void OnSaveFile(wxCommandEvent& event);
	void OnRenderStart(wxCommandEvent& event);
	void OnRenderCompleted(wxCommandEvent& event);
	void OnRenderPause(wxCommandEvent& event);
	void OnRenderResume(wxCommandEvent& event);

private:
	RenderCanvas *canvas; //where the rendering takes place
	wxString currentPath; //for file dialogues
	DECLARE_EVENT_TABLE()
};

//IDs for menu items
enum
{
	Menu_File_Quit = 100,
	Menu_File_Open,
	Menu_File_Save,
	Menu_Render_Start,
	Menu_Render_Pause,
	Menu_Render_Resume
};

#endif // __RENDER_FRAME__