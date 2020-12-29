#ifndef MMSCENEGRAPH_SYMBOL_EXPORT_H
#define MMSCENEGRAPH_SYMBOL_EXPORT_H

// Cross-platform symbol visibility macro.
#if defined(_MSC_VER)
    #define MMSCENEGRAPH_SYMBOL_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
    #define MMSCENEGRAPH_SYMBOL_EXPORT __attribute__((visibility("default")))
#else
    #define MMSCENEGRAPH_SYMBOL_EXPORT
#endif

#endif // MMSCENEGRAPH_SYMBOL_EXPORT_H
