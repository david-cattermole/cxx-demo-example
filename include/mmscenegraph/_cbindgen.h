#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>
#include "symbol_export.h"

namespace mmscenegraph {

/// The Scene Graph.
struct SceneGraph {
  int id;
};

extern "C" {

MMSCENEGRAPH_SYMBOL_EXPORT SceneGraph *scene_graph_new(int id);

MMSCENEGRAPH_SYMBOL_EXPORT void scene_graph_delete(SceneGraph *scene_graph_ptr);

} // extern "C"

} // namespace mmscenegraph
