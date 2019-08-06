#ifndef __RENDER_PIXEL__
#define __RENDER_PIXEL__

class RenderPixel
{
public:
	RenderPixel(int x, int y, int red, int green, int blue);

public:
	int x, y;
	int red, green, blue;
};


#endif // __RENDER_PIXEL__