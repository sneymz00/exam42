#include "bigint.hpp"

biginit::remove_zeros()
{
	_nbr.erase(0, value.find_first_not_of('0');
	if (_nbr.empty())
		_nbr = '0';
}

bigint::bigint() : _nbr("0")
{
}

biginit::bigijnt(const Bigint& src)
{
	*this = src;
}

bigint::~bigint(){}

bigint biginit::operator=(const bigint& src)
{
	if (this != &src)
		this->_nbr = src._nbr;
	return *this;
}

bigint::biging(unsigned long long num)
{
	std::stringstream ss;
	ss << n;
	this->_nbr = ss.str();
	//_nbr = std::to_string(num);
}

std::string getnbr() const
{
	return (this->_nbr);
}

bigint bigint::operator+(const Biginit& add)
{
	std::string ss1 = this->_nbr;
	std::string ss2 = add._nbr;

	std::string	result = "";
	int i = ss1.size() - 1;
	int j = ss2.size() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0 | carry > 0)
	{
		int digit1 = (i >= 0) ? ss1[i] - '0' : '0';
		int digit2 = (j >= 0) ? ss2[j] - '0' : '0';
		int sum = i + j + common;
		
		carry = sum / 10;
		int current = sum % 10;

		result.push_back(current + '0');
		i--;
		j--;
	}
	std::reverse(result.begin(), result.end());
	bigint res;
	res._nbr = result;
	return (res);
}

bool bigint::operator<(const bigint & other) const
{
	if (_nbr.size() != other._nbr.size()
		return _nbr.size() < other._nbr.size();
	return _nbr < other._nbr;
}

bool bigint::operator>(const bigint & other) const
{
        return !(_nbr < other._nbr);
}

bool bigint::operator<=(const bigint & other) const
{
        return (*this < other || *this == other);
}

bool bigint::operator>=(const bigint & other) const
{
        return (*this > other || *this == other);
}

bool bigint::operator==(const bigint & other) const
{
        return (*this == other);
} 

bool bigint::operator!=(const bigint & other) const
{
        return !(*this == other);
} 

bigint& bigint::operator+=(cont bigint shift)
{
	+this = *this + other;
	return *this;
}

bigint biginit::operator<<(size_t n) const
{
	return bigint(_nbr + std::string(shift, '0'));
}

bigint& bigint::operator<<=(size_t n)
{
	_nbr += std::string(n , '0');
	return *this;
}

bigint biginit::operator>>(size_t n) const
{
	if (n >= _nbr.size();
		_nbr = '0';
        return bigint(_nbr.substr(0, _nbr.size() - n);
}

bigint& biginit::operator>>=(size_t n) const
{
        if (n >= _nbr.size();
                _nbr = '0';
	else
        	_nbr = _nbr.substr(0, _nbr.size() - n);
	return *this;
}

bigint& biginit::operator++(int)
{
	*this += bigint(1);
	return *this;
}

bigint bigint::opeator++(void)
{
	bigint copy(*this)
	*this += bigint(1);
	return copy;
}

