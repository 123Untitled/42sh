#ifndef ___42SH_CONFIG___
#define ___42SH_CONFIG___


// check for has_builtin
#ifndef __42sh_has_builtin
#	ifndef __has_builtin
#		define __42sh_has_builtin(_) 0
#	else
#		define __42sh_has_builtin(_) __has_builtin(_)
#	endif
#endif // __has_builtin


#endif // ___42SH_CONFIG___
