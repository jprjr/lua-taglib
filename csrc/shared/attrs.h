#ifndef LTAGLIB_ATTRS_INCLUDE_GUARD
#define LTAGLIB_ATTRS_INCLUDE_GUARD

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(_MSC_VER)
#define LTAGLIB_PUBLIC __declspec(dllexport)
#define LTAGLIB_PRIVATE
#elif (defined(__GNUC__) && (__GNUC__ >= 4))
#define LTAGLIB_PUBLIC __attribute__((visibility("default")))
#define LTAGLIB_PRIVATE __attribute__((visibility("hidden")))
#else
#define LTAGLIB_PUBLIC
#define LTAGLIB_PRIVATE
#endif

#if __cplusplus >= 201103L
#define LTAGLIB_OVERRIDE override
#define LTAGLIB_CONSTEXPR constexpr
#else
#define LTAGLIB_OVERRIDE
#define LTAGLIB_CONSTEXPR
#endif

#endif

