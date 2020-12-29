#ifndef MMSCENEGRAPH_CPP_H
#define MMSCENEGRAPH_CPP_H

#include <cxx.h>
#include <memory>
#include <string>
#include "symbol_export.h"

namespace mmscenegraph {

    class ThingC {
    public:
        MMSCENEGRAPH_SYMBOL_EXPORT
        ThingC(std::string appname);

        MMSCENEGRAPH_SYMBOL_EXPORT
        ~ThingC();

        std::string appname;
    };

    struct SharedThing;

    MMSCENEGRAPH_SYMBOL_EXPORT
    std::unique_ptr <ThingC> make_demo(rust::Str appname);

    MMSCENEGRAPH_SYMBOL_EXPORT
    const std::string &get_name(const ThingC &thing);

    MMSCENEGRAPH_SYMBOL_EXPORT
    void do_thing(SharedThing state);

} // namespace mmscenegraph

#endif // MMSCENEGRAPH_CPP_H
