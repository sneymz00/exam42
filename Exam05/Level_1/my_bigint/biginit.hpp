#ifndef _BIGINT_HPP_
#definde _BIGINT_HPP_

#include <iostream>
#include <sstream>i
#include <algorithm>

class bigint
{
	private:
		std::string _nbr;

	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& src);
		bigint	operator=(const bigint& src);
		~bigint();

		std:string getnbr() const;
		bigint operator*(const bigint& add);
}

std::ostream& operator<<(std::ostream& ss, const Bigint& src)
{
	ss << src.getnbr();
	return ss;
}

#endinf
