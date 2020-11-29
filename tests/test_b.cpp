#include <iostream>
#include <string>
#include "mmscenegraph.h"

namespace mmsg = mmscenegraph;

int test_b() {
    std::cout << "---- Start Test B..." << std::endl;

    auto app_name = std::string("my awesome demo");
    auto x = mmsg::make_demo(app_name);
    auto name = mmsg::get_name(*x);
    std::cout << name << std::endl;

    auto read_op = mmsg::new_read_operation(42, 42);
    auto read_op_id = read_op->get_id();
    auto read_op_num = read_op->get_num();
    std::cout << "Read Op Id: " << read_op_id << std::endl;
    std::cout << "Read Op Num: " << read_op_num << std::endl;

    std::cout << "---- Finished Test B!" << std::endl;
    return 0;
}
