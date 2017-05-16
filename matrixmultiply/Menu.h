#pragma once
#include <string>
#include <vector>

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
			explicit Menu(Options*  _parent = nullptr);
			Menu(Options *_parent, std::initializer_list<std::string> _options, const sys::uint& _start_selected);
			Menu(std::initializer_list<std::string> _options, const sys::uint& _start_selected);

			virtual void show();
			virtual void close();
			virtual int selected() const;
			void select(const int& _index);

			void show_selected_option(bool _show);
			bool show_selected_option() const;

			int count() const;

			virtual std::vector<matrixm::menu::Option*> get_options() const;
			virtual Option* get_selected();
			Option* get_option(int _index);

			virtual Options* parent();

			virtual ~Menu();

			void add_option(Option* option);
			void remove_option(int _index);
		protected:
			void draw() const;

			virtual void select(const int& _key, const int& _min_value, const int& _max_value);
			void select_down(const int& _min_value, const int& _max_value);
			void select_up(const int& _min_value, const int& _max_value);
			void color_selected(const sys::ushort& _selected_color, const sys::ushort& _unselected_color);
		private:
			bool execute_, show_selected_;
			int selected_;

			std::vector<Option*> options_;
			Options* parent_;
		};
	};
}