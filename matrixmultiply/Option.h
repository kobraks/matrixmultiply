#pragma once

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
			explicit Option(const std::string& _option_name);
			explicit Option(const sys::Vector2i& _position, const sys::ushort& _color = 7);
			Option(const int& _x, const int& _y, const sys::ushort& _color = 7);
			Option(const std::string& _option_name, const sys::Vector2i& _position, const sys::ushort& _color = 7);
			Option(const std::string& _option_name, const int& _x, const int& _y, const sys::ushort& _color = 7);

			virtual ~Option();

			sys::Vector2i get_position() const;
			std::string get_name() const;
			int get_color() const;

			void set_position(const sys::Vector2i& _position);
			void set_position(const int& _x, const int& _y);

			void set_name(const std::string& _option_name);

			void set_color(int _color);

			Option& operator= (const sys::Vector2i& _vector);

			std::ostream& write(std::ostream& _out) const;
			Option& wirte();
		private:
			std::string name_;
			sys::Vector2i position_;
			sys::ushort color_;
		};

		inline std::ostream& operator<< (std::ostream& _out, const Option& _option)
		{
			return _option.write(_out);
		}
	};
}
