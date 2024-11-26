#ifndef ___42SH_DIAGNOSTICS_EXCEPTION___
#define ___42SH_DIAGNOSTICS_EXCEPTION___


// -- S H  N A M E S P A C E --------------------------------------------------

namespace sh {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = sh::exception;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			exception(void) noexcept = default;

			/* copy constructor */
			exception(const self&) noexcept = default;

			/* move constructor */
			exception(self&&) noexcept = default;

			/* destructor */
			virtual ~exception(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* move assignment operator */
			auto operator=(self&&) -> self& = delete;


			// -- public interface --------------------------------------------

			/* what */
			virtual auto what(void) const noexcept -> const char* = 0;

	}; // class exception

} // namespace sh

#endif // ___42SH_DIAGNOSTICS_EXCEPTION___
