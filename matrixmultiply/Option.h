#pragma once

#include <functional>
#include <string>
#include <ostream>

#include "TypeDefs.h"
#include "Vector2.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class Option
		{
		public:
			Option();
			explicit Option(const std::string& _option_name, bool _selectable = true, std::function<void()> _on_click = nullptr);
			explicit Option(const sys::Vector2i& _position, const sys::ushort& _color = 7, bool selectable_ = true,
				std::function<void()> _on_click = nullptr);
			Option(const int& _x, const int& _y, const sys::ushort& _color = 7, bool selectable_ = true,
				std::function<void()> _on_click = nullptr);
			Option(const std::string& _option_name, const sys::Vector2i& _position, const sys::ushort& _color = 7,
				bool selectable_ = true, std::function<void()> _on_click = nullptr);
			Option(const std::string& _option_name, const int& _x, const int& _y, const sys::ushort& _color = 7,
				bool selectable_ = true, std::function<void()> _on_click = nullptr);

			virtual ~Option();

			sys::Vector2i get_position() const;
			std::string get_name() const;
			int get_color() const;

			void set_position(const sys::Vector2i& _position);
			void set_position(const int& _x, const int& _y);

			void set_name(const std::string& _option_name);

			void set_color(int _color);

			void set_on_click_action(std::function<void()> _on_click);
			void delete_on_click_action();
			std::function<void()> get_on_click_action() const;

			void on_click();

			Option& operator= (const sys::Vector2i& _vector);

			std::ostream& write(std::ostream& _out) const;
			Option& wirte();

			bool is_selectable();
			void is_selectable(bool _selectable);
		private:
			bool selectable_;
			std::string name_;
			sys::Vector2i position_;
			sys::ushort color_;

			std::function<void()> on_click_;
		};

		inline std::ostream& operator<< (std::ostream& _out, const Option& _option)
		{
			return _option.write(_out);
		}
	};
}
