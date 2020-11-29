#include <iostream>
#include <mmscenegraph.h>

namespace mmsg = mmscenegraph;

int test_a() {
    std::cout << "---- Start Test A..." << std::endl;

    int scene_id = 42;
    mmsg::SceneGraph *scene_graph = mmsg::scene_graph_new(scene_id);
    mmsg::scene_graph_delete(scene_graph);

    std::cout << "---- Finished Test A!" << std::endl;
    return 0;
}
