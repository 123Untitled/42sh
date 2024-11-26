#ifndef ___42SH_ENVIRONMENT___
#define ___42SH_ENVIRONMENT___

#include <string>
#include <unordered_map>
#include <iostream>

#include <unistd.h>


// -- S H  N A M E S P A C E --------------------------------------------------

namespace sh {


	// -- E N V I R O N M E N T -----------------------------------------------

	class environment final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using self = sh::environment;


			// -- private members ---------------------------------------------

			/* variables */
			std::unordered_map<std::string, std::string> _vars;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) -> self& {
				static self instance;
				return instance;
			}


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			environment(void)
			: _vars{} {

				if (environ == nullptr)
					return;

				// loop over environment variables
				for (unsigned i = 0U; environ[i] != nullptr; ++i) {

					// get variable
					std::string var{environ[i]};

					// find delimiter
					auto pos = var.find('=');

					// get key
					std::string key{var.substr(0U, pos)};

					// get value
					std::string val{var.substr(pos + 1U)};

					// insert variable
					_vars.emplace(std::move(key), std::move(val));
				}

			}

			/* deleted copy constructor */
			environment(const self&) = delete;

			/* deleted move constructor */
			environment(self&&) = delete;

			/* destructor */
			~environment(void) noexcept = default;


			// -- private assignment operators --------------------------------

			/* deleted copy assignment operator */
			auto operator=(const self&) -> self& = delete;

			/* deleted move assignment operator */
			auto operator=(self&&) -> self& = delete;


		public:

			// -- public static accessors -------------------------------------

			/* get */
			static auto get(const std::string& key) -> std::string {

				// get instance
				auto& instance = self::_shared();

				// find variable
				auto it = instance._vars.find(key);

				// return value
				return it != instance._vars.end() ? it->second : std::string{};
			}

			/* set */
			static auto set(const std::string& key,
							const std::string& val) -> void {

				// get instance
				auto& instance = self::_shared();

				// set variable
				instance._vars[key] = val;
			}

			/* print */
			static auto print(void) -> void {

				// get instance
				auto& instance = self::_shared();

				// loop over variables
				for (const auto& [key, val] : instance._vars) {
					std::cout << key << " = " << val << std::endl;
				}
			}


	}; // class environment

} // namespace sh

#endif // ___42SH_ENVIRONMENT___
