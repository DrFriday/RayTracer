#include "RenderFrame.h"
#include "../Events/Events.h"
#include "RenderApp.h"

#include "main.xpm"
#include "bg.xpm"

BEGIN_EVENT_TABLE(RenderFrame, wxFrame)
	EVT_MENU(Menu_Render_Start, RenderFrame::OnRenderStart)
	EVT_MENU(Menu_Render_Pause, RenderFrame::OnRenderPause)
	EVT_MENU(Menu_Render_Resume, RenderFrame::OnRenderResume)
	EVT_MENU(Menu_File_Save, RenderFrame::OnSaveFile)
	EVT_MENU(Menu_File_Open, RenderFrame::OnOpenFile)
	EVT_MENU(Menu_File_Quit, RenderFrame::OnQuit)
	EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,
		RenderFrame::OnRenderCompleted)
END_EVENT_TABLE()

RenderFrame::RenderFrame(const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame *)NULL
	, -1
	, wxT("Ray Tracer")
	, pos
    , size)
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(Menu_File_Open, wxT("&Open..."));
	menuFile->Append(Menu_File_Save, wxT("&Save As..."));
	menuFile->AppendSeparator();
	menuFile->Append(Menu_File_Quit, wxT("E&xit"));

	menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), FALSE);

	wxMenu *menuRender = new wxMenu;

	menuRender->Append(Menu_Render_Start, wxT("&Start"));
	menuRender->Append(Menu_Render_Pause, wxT("&Pause"));
	menuRender->Append(Menu_Render_Resume, wxT("&Resume"));

	menuRender->Enable(menuRender->FindItem(wxT("&Start")), TRUE);
	menuRender->Enable(menuRender->FindItem(wxT("&Pause")), FALSE);
	menuRender->Enable(menuRender->FindItem(wxT("&Resume")), FALSE);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuRender, wxT("&Render"));

	SetMenuBar(menuBar);

	canvas = new RenderCanvas(this);

	CreateStatusBar();
	SetStatusText(wxT("Ready"));

	wxIcon icon(main_xpm);
	SetIcon(icon);

	wxStatusBar* statusBar = GetStatusBar();
	int widths[] = { 150,300 };
	statusBar->SetFieldsCount(2, widths);
}

void RenderFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void RenderFrame::OnSaveFile(wxCommandEvent& WXUNUSED(event))
{
	wxString caption = wxT("Save File");

	wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
		"PNG files (*.png)|*.png|"
		"JPEG files (*.jpg)|*.jpg|"
		"TIFF files (*.tif)|*.tif");

	wxString defaultDir = wxEmptyString;
	wxString defaultFilename = wxT("render.bmp");

	wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	dialog.SetPath(currentPath);

	if (dialog.ShowModal() == wxID_OK)
	{
		currentPath = dialog.GetPath();

		wxImage theImage = canvas->GetImage();
		theImage.SaveFile(currentPath);
	}
}

void RenderFrame::OnOpenFile(wxCommandEvent& WXUNUSED(event))
{
	wxString caption = wxT("Choose a file");

	wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
		"PNG files (*.png)|*.png|"
		"JPEG files (*.jpg)|*.jpg|"
		"TIFF files (*.tif)|*.tif");

	wxString defaultDir = wxEmptyString;
	wxString defaultFilename = wxEmptyString;

	wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog.SetPath(currentPath);

	if (dialog.ShowModal() == wxID_OK)
	{
		currentPath = dialog.GetPath();
		wxImage* theImage = new wxImage();
		theImage->LoadFile(currentPath);

		if (!theImage->IsOk())
		{
			delete theImage;
			wxMessageBox(wxT("Sorry, could not load file."));
		}
		else
		{
			canvas->SetImage(*theImage);
			wxMenu* menuFile = GetMenuBar()->GetMenu(0);
			menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), TRUE);
		}
	}
}

void RenderFrame::OnRenderStart(wxCommandEvent& WXUNUSED(event))
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	canvas->renderStart();

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(menuFile->FindItem(wxT("&Open...")), FALSE);
	menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), TRUE);
}

void RenderFrame::OnRenderCompleted(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Pause")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	wxMenu* menuFile = GetMenuBar()->GetMenu(0);
	menuFile->Enable(menuFile->FindItem(wxT("&Open...")), TRUE);

	wxGetApp().SetStatusText(wxT("Rendering complete"));
}

void RenderFrame::OnRenderPause(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Resume")), TRUE);

	canvas->renderPause();

	wxGetApp().SetStatusText(wxT("Rendering paused"));
}

void RenderFrame::OnRenderResume(wxCommandEvent& event)
{
	wxMenu* menu = GetMenuBar()->GetMenu(1);
	menu->Enable(menu->FindItem(wxT("&Start")), FALSE);
	menu->Enable(menu->FindItem(wxT("&Pause")), TRUE);
	menu->Enable(menu->FindItem(wxT("&Resume")), FALSE);

	canvas->renderResume();

	wxGetApp().SetStatusText(wxT("Rendering..."));
}
