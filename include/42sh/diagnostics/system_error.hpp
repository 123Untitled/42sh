#ifndef ___42SH_DIAGNOSTICS_SYSTEM_ERROR___
#define ___42SH_DIAGNOSTICS_SYSTEM_ERROR___

#include "42sh/diagnostics/exception.hpp"

#include <string>
#include <cstring>
#include <cerrno>


// -- S H  N A M E S P A C E --------------------------------------------------

namespace sh {


	// -- S Y S T E M  E R R O R ----------------------------------------------

	class system_error : public sh::exception {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = sh::system_error;


			// -- private members ---------------------------------------------

			/* where */
			const char* _where;

			/* what */
			const char* _what;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			system_error(void) noexcept
			: sh::exception{}, _where{"unknown location"}, _what{::strerror(errno)} {
			}

			/* where constructor */
			system_error(const char* where) noexcept
			: sh::exception{}, _where{where != nullptr ? where : "unknown location"},
			  _what{::strerror(errno)} {
			}

			/* copy constructor */
			system_error(const self&) noexcept = default;

			/* move constructor */
			system_error(self&&) noexcept = default;

			/* destructor */
			~system_error(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public interface --------------------------------------------

			/* what */
			auto what(void) const noexcept -> const char* override {
				static std::string msg{};
				msg.append(_where);
				msg.append(": ");
				msg.append(_what);
				return msg.data();
			}

	}; // class system_error

} // namespace sh

#endif // ___42SH_DIAGNOSTICS_SYSTEM_ERROR___
