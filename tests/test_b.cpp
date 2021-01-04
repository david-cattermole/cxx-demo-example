#include <iostream>
#include <string>
#include "mmscenegraph.h"

namespace mmsg = mmscenegraph;

void read_write_buffer() {
    // Allocate C++ memory and pass it to Rust to be filled.
    std::vector<uint32_t> buffer;
    buffer.reserve(42);
    rust::Slice<uint32_t> slice_of_buffer(buffer.data(), buffer.capacity());
    mmsg::geom::read(slice_of_buffer);

    // Now print the buffer contents out (inside Rust).
    rust::Slice<const uint32_t> const_slice_of_buffer(buffer.data(), buffer.capacity());
    mmsg::geom::write(const_slice_of_buffer);
}

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

    auto write_op = mmsg::new_write_operation(42, 42);
    auto write_op_id = write_op->get_id();
    auto write_op_num = write_op->get_num();
    std::cout << "Write Op Id: " << write_op_id << std::endl;
    std::cout << "Write Op Num: " << write_op_num << std::endl;

    read_write_buffer();

    std::cout << "---- Finished Test B!" << std::endl;
    return 0;
}
