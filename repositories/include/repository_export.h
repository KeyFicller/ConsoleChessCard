#ifndef REPOSITORY_EXPORT_H
#define REPOSITORY_EXPORT_H

// 导出宏定义
// 在编译动态库时定义 REPOSITORY_EXPORTS 宏
#ifdef _WIN32
    #ifdef REPOSITORY_EXPORTS
        #define REPOSITORY_API __declspec(dllexport)
    #else
        #define REPOSITORY_API __declspec(dllimport)
    #endif
#else
    #define REPOSITORY_API
#endif

#endif // REPOSITORY_EXPORT_H

