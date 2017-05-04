#pragma once
#include <string>

namespace matrixm
{
	namespace sys
	{
		class Algorithm
		{
		public:
			static std::string replace(const std::string& _s, const std::string _to_replace, std::string _replace)
			{
				std::string result = _s;

				std::string::size_type pos = 0;
				while ((pos = _s.find(_to_replace, pos)) != std::string::npos)
				{
					result.erase(pos, _to_replace.length());
					result.insert(pos, _replace);
					pos += _to_replace.length() + _replace.length();
				}

				return result;
			}
		};
	}
}