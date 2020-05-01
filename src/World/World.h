#pragma once

#include "../GeometricObjects/Sphere.h"
#include "../Tracers/Tracer.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "ViewPlane.h"

#include <memory>
#include <vector>
#include <wx/wx.h>

class RenderThread;

class World
{
  public:
    ViewPlane vp;
    RGBColor background_color;
    Tracer* tracer_prt;
    Sphere sphere;
    std::vector<GeometricObject*> objects;

    World();

    void
    build();

    void
    render_scene() const;

    void
    open_window(const int hres, const int vres) const;

    void
    display_pixel(const int row, const int column, const RGBColor& color) const;

    void
    setPaintArea(RenderThread* paintArea);

    void
    add_object(GeometricObject* object_ptr);

    ShadeRec
    hit_bare_bones_objects(const Ray& ray) const;

  private:
    RenderThread* paintArea;
};
