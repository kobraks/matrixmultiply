#pragma once
#include <string>

#include "Option.h"
#include "Options.h"
#include "TypeDefs.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class Menu : public Options
		{
		public:
			Menu(Options *_parent, std::initializer_list<std::string> _options, const sys::uint& _start_selected);
			Menu(std::initializer_list<std::string> _options, const sys::uint& _start_selected);

			virtual void show();
			virtual void close();
			virtual int selected() const;

			int count() const;

			virtual Option* get_options() const;
			virtual Option* get_selected();

			virtual Options* parent();

			virtual ~Menu();
		protected:
			void draw() const;

			void select(const int& _key, const int& _min_value, const int& _max_value);
			void color_selected(const sys::ushort& _selected_color, const sys::ushort& _unselected_color);
		private:
			bool execute_;
			int selected_;

			Option* options_;
			sys::uint amount_options_;
			Options* parent_;
		};
	};
}