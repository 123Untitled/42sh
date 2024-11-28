#ifndef __42sh_cwd__
#define __42sh_cwd__

#include <string>
#include <unistd.h>
#include <limits.h>


// -- S H  N A M E S P A C E --------------------------------------------------

namespace sh {


	// -- C W D ---------------------------------------------------------------

	class cwd final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = sh::cwd;


			// -- private members ---------------------------------------------

			/* current working directory */
			std::string _path;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			cwd(void)
			: _path{} {

				// get current working directory
				char buf[PATH_MAX];

				if (::getcwd(buf, sizeof(buf)) != nullptr) {
					_path = buf;
				}
			}

			/* deleted copy constructor */
			cwd(const self&) = delete;

			/* deleted move constructor */
			cwd(self&&) = delete;

			/* destructor */
			~cwd(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static methods ---------------------------------------

			/* get current working directory */
			static auto get(void) -> std::string {
				return self::_shared()._path;
			}

	};  // class cwd

} // namespace sh

#endif
