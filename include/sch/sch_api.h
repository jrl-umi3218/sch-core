#ifdef WIN32
# ifdef sch_EXPORTS
#  define SCH_API __declspec(dllexport)
# elif defined schd_EXPORTS
#  define SCH_API __declspec(dllexport)
# else
#  define SCH_API __declspec(dllimport)
# endif
#else
# define SCH_API
#endif
