#pragma once

#include "../datatypes.h"

namespace Datatypes {
    struct MeshObject : EmptyObject {
        Mesh mesh;
        Material material;
        bool rendered = false;
    };
}