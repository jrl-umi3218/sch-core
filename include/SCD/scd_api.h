#ifdef WIN32
# ifdef scd_EXPORTS
#  define SCD_API __declspec(dllexport)
# elif defined scdd_EXPORTS
#  define SCD_API __declspec(dllexport)
# else
#  define SCD_API __declspec(dllimport)
# endif
#else
# define SCD_API
#endif
