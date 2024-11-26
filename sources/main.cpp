#include "42sh/diagnostics/system_error.hpp"
#include "42sh/environment.hpp"
#include <termios.h>
#include <unistd.h>

#include "42sh/memory/malloc.hpp"

namespace sh {



	// -- T E R M I N A L -----------------------------------------------------

	class terminal final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = sh::terminal;


			// -- private members ---------------------------------------------

			/* original terminal */
			const struct ::termios _origin;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			terminal(void)
			: _origin{self::_get_attributes()} {
			}

			/* deleted copy constructor */
			terminal(const self&) = delete;

			/* deleted move constructor */
			terminal(self&&) = delete;

			/* destructor */
			~terminal(void) noexcept {

				// restore terminal settings
				static_cast<void>(::tcsetattr(STDIN_FILENO, TCSAFLUSH, &_origin));
			}


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self& {
				static self instance;
				return instance;
			}

			/* get attributes */
			static auto _get_attributes(void) -> struct ::termios {

				struct ::termios attr;

				// get terminal attributes
				if (::tcgetattr(STDIN_FILENO, &attr) == -1)
					throw sh::system_error("tcgetattr failed");

				return attr;
			}


		public:

			// -- public static methods ---------------------------------------

			/* raw */
			static auto raw(void) -> void {

				// get instance
				auto& ins = self::_shared();

				// copy original attributes
				struct ::termios attr{ins._origin};

				/* disable canonical mode */
				attr.c_lflag &= ~static_cast<::tcflag_t>(ICANON);

				/* disable echo */
				attr.c_lflag &= ~static_cast<::tcflag_t>(ECHO);

				///* non-blocking */
				attr.c_cc[VMIN] = 0;
				attr.c_cc[VTIME] = 0;

				/* set new attributes */
				if (::tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) == -1)
					throw sh::system_error("tcsetattr failed");
			}


			/* restore */
			static auto restore(void) -> void {

				// get instance
				auto& ins = self::_shared();

				// restore terminal settings
				if (::tcsetattr(STDIN_FILENO, TCSAFLUSH, &ins._origin) == -1)
					throw sh::system_error("tcsetattr failed");
			}

	}; // class terminal

}



auto main(int ac, char** av) -> int {

	sh::terminal::raw();

	sh::malloc<int>(10U);

	sh::environment::print();

	return 0;
}
