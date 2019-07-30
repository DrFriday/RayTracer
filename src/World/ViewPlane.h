#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class ViewPlane {
public:
	int hres; // horizontal images resolution
	int vres; // vertical image resolution
	float s; // pixel size
	float gamma; // monitor gamma factor
	float inv_gamma; // one over gamma
};


#endif // __VIEWPLANE