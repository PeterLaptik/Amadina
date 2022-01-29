#ifndef EXPORTS_H_INCLUDED
#define EXPORTS_H_INCLUDED

#ifdef _MSC_VER
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

#endif // EXPORTS_H_INCLUDED
