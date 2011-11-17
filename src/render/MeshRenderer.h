#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <tr1/memory>

#include "../GridData.h"

using std::tr1::shared_ptr;

class MeshRenderer
{
public:
    MeshRenderer(shared_ptr<GridData> grid);

    void glRender();

private:
    shared_ptr<GridData> grid;
};

#endif // MESHRENDERER_H
