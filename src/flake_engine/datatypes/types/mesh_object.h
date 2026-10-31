#pragma once

#include "empty_object.h"

namespace Datatypes {
    struct MeshObject : EmptyObject {
        Mesh mesh;
        Material material;
    };
}