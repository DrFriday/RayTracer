#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane 
{
public:
	int hres; // horizontal images resolution
	int vres; // vertical image resolution
	float s; // pixel size
	float gamma; // monitor gamma factor
	float inv_gamma; // one over gamma

	void set_hres(int newHres)
	{
		hres = newHres;
	}

	void set_vres(int newVres)
	{
		vres = newVres;
	}

	void set_pixel_size(float newSize)
	{
		s = newSize;
	}

	void set_gamma(float newGamma)
	{
		gamma = newGamma;
		inv_gamma = 1 / newGamma;
	}

};


#endif // __VIEWPLANE