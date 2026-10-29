#pragma once

#include "empty_object.h"
#include "../../graphics/mesh/mesh.h"

namespace Datatypes {
    struct MeshObject : EmptyObject {
        Flake::Mesh mesh;
    };
}