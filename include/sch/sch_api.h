#ifdef WIN32
# ifdef sch_EXPORTS
#  define sch_API __declspec(dllexport)
# elif defined schd_EXPORTS
#  define sch_API __declspec(dllexport)
# else
#  define sch_API __declspec(dllimport)
# endif
#else
# define sch_API
#endif
