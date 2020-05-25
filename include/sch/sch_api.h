#if defined WIN32 || defined __CYGWIN__
# ifdef sch_EXPORTS
#  define SCH_API __declspec(dllexport)
# elif defined schd_EXPORTS
#  define SCH_API __declspec(dllexport)
# else
#  define SCH_API __declspec(dllimport)
# endif
#else
# if __GNUC__ >= 4
#  define SCH_API __attribute__((visibility("default")))
# else
#  define SCH_API
# endif
#endif
