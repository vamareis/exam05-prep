#include "bigint.hpp"

bool	bigint::all_digits(const std::string& s)
{
	for (size_t i = 0; i < s.length(); i++)
		if (!isdigit(s[i]))
			return (false);
	return (true);
}

std::string	bigint::remove_leading_zeros(const std::string& s)
{
	size_t	pos = s.find_first_not_of('0');
	std::string	newStr;

	if (pos == s.npos)
		newStr = "0";
	else
		newStr = s.substr(pos);
	return (newStr);
}

bigint::bigint() : value("0") {}

bigint::bigint(const std::string& nstr)
{
	if(nstr.empty() || !all_digits(nstr))
		throw (std::invalid_argument("Invalid string parameter"));
	this->value = remove_leading_zeros(nstr);
}

bigint::bigint(unsigned long long n)
{
    if (n == 0)
		this->value = "0";
	while (n != 0)
	{
		value.insert(value.begin(), (n % 10) + '0');
		n /= 10;
	}
}

bigint::bigint(const bigint& other) : value(other.value) {}

bigint&	bigint::operator=(const bigint& other)
{
	if (this != &other)
		this->value = other.value;
	return (*this);
}

bigint::~bigint() {}

const std::string&  bigint::getValue() const
{
	return (this->value);
}

bigint	bigint::operator+(const bigint& other) const
{
	std::string::const_reverse_iterator	it1 = this->value.rbegin();
	std::string::const_reverse_iterator	it2 = other.value.rbegin();
	int	carry = 0;
	std::string	result;

	while (it1 != this->value.rend() || it2 != other.value.rend() || carry)
	{
		int	digit1 = (it1 != this->value.rend()) ? *it1++ - '0' : 0;
		int	digit2 = (it2 != other.value.rend()) ? *it2++ - '0' : 0;

		int	sum = digit1 + digit2 + carry;
		if (sum > 9)
		{
			result.insert(result.begin(), sum % 10 + '0');
			carry = 1;
		}
		else
		{
			result.insert(result.begin(), sum % 10 + '0');
			carry = 0;
		}
	}
	return (bigint(result));
}

bigint&   bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return (*this);
}

bigint	bigint::operator-(const bigint& other) const
{
	std::string::const_reverse_iterator	it1 = this->value.rbegin();
	std::string::const_reverse_iterator	it2 = other.value.rbegin();
	int	borrow = 0;
	int	subtraction = 0;
	std::string	result;

	while (it1 != this->value.rend() || it2 != other.value.rend() || borrow)
	{
		int	digit1 = (it1 != this->value.rend()) ? *it1++ - '0' : 0;
		int	digit2 = (it2 != other.value.rend()) ? *it2++ - '0' : 0;

		if (digit1 < digit2)
		{
			subtraction = (digit1 + 10) - digit2 - borrow;
			borrow = 1;
		}
		else
		{
			subtraction = digit1 - digit2 - borrow;
			borrow = 0;
		}
		result.insert(result.begin(), subtraction + '0');
	}
	return (bigint(result));
}

bigint&   bigint::operator-=(const bigint& other)
{
	*this = *this - other;
	return (*this);
}

bigint&	bigint::operator++()
{
	*this += bigint(1);
	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint	tmp = *this;
	++(*this);
	return (tmp);
}

bigint	bigint::operator<<(int shift)
{
	std::string	new_value = this->value;
	for (int i = 0; i < shift; i++)
		new_value.push_back('0');
	return (bigint(new_value));
}

bigint	bigint::operator>>(int shift)
{
	std::string	new_value = this->value;

	if (shift >= (int)this->value.size())
		new_value = "0";
	else
		new_value = this->value.substr(0, this->value.length() - shift);
	return (bigint(new_value));
}

bigint&	bigint::operator<<=(int shift)
{
	*this = *this << shift;
	return (*this);
}

bigint&	bigint::operator>>=(int shift)
{
	*this =	*this >> shift;
	return (*this);
}

bool	bigint::operator==(const bigint& other) const
{
	return (this->value == other.value);
}

bool	bigint::operator>(const bigint& other) const
{
	if (this->value.size() > other.value.size())
		return (true);
	return (this->value > other.value);
}

bool	bigint::operator<(const bigint& other) const
{
	if (this->value.size() < other.value.size())
		return (true);
	return (this->value > other.value);
}

bool	bigint::operator>=(const bigint& other) const
{
	return (*this > other || *this == other);
}

bool	bigint::operator<=(const bigint& other) const
{
	return (*this < other || *this == other);
}

bool	bigint::operator!=(const bigint& other) const
{
	return (this->value != other.value);
}

std::ostream&  operator<<(std::ostream& out, const bigint& other)
{
	out << other.getValue();
	return (out);
}