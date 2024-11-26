#ifndef __42sh_memory_malloc__
#define __42sh_memory_malloc__

#include "42sh/config.hpp"
#include "42sh/types.hpp"

#if !__42sh_has_builtin(__builtin_malloc)
 || !__42sh_has_builtin(__builtin_realloc)
 || !__42sh_has_builtin(__builtin_free)
#	include <stdlib.h>
#endif


// -- S H  N A M E S P A C E --------------------------------------------------

namespace sh {


	/* malloc */
	template <typename T>
	auto malloc(sh::size_t size) -> T* {

		// allocate memory
		#if __42sh_has_builtin(__builtin_malloc)
			void* ptr = __builtin_malloc(size * sizeof(T));
		#else
			void* ptr = ::malloc(size * sizeof(T));
		#endif

		// return pointer
		return static_cast<T*>(ptr);
	}

	/* realloc */
	template <typename T>
	auto realloc(T* ptr, sh::size_t size) -> T* {

		// reallocate memory
		#if __42sh_has_builtin(__builtin_realloc)
			void* new_ptr = __builtin_realloc(ptr, size * sizeof(T));
		#else
			void* new_ptr = ::realloc(ptr, size * sizeof(T));
		#endif

		// return pointer
		return static_cast<T*>(new_ptr);
	}

	/* free */
	template <typename T>
	auto free(T* ptr) -> void {

		// free memory
		#if __42sh_has_builtin(__builtin_free)
			__builtin_free(ptr);
		#else
			::free(ptr);
		#endif
	}

} // namespace sh

#endif // __42sh_memory_malloc__
