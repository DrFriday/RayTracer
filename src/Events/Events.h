#ifndef __EVENTS__
#define __EVENTS__

#include<wx/wx.h>

wxDECLARE_EVENT(wxEVT_RENDER, wxCommandEvent);
constexpr auto ID_RENDER_COMPLETED = 100;
constexpr auto ID_RENDER_NEWPIXEL = 101;
constexpr auto ID_RENDER_UPDATE = 102;
constexpr auto RENDER_START = 103;

#endif // __EVENTS__