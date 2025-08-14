#include "bigint.hpp"

bigint::bigint() : value("0") {}

bigint::bigint(int nb)
{
	if (nb == 0)
		this->value = "0";
	while (nb != 0)
	{
		value.insert(value.begin(), "0123456789"[nb % 10]);
		nb /= 10;
	}
}
bigint::bigint(const std::string& value) : value(value) 
{
	removeLeadingZeros(this->value);
}

bigint::bigint(const bigint& other) : value(other.value) {}

bigint&	bigint::operator=(const bigint& other)
{
	this->value = other.value;
	return (*this);
}

bigint::~bigint() {}

bigint	bigint::operator+(const bigint& other) const
{
	int result = 0;
	std::string	output;
	int	carry = 0;
	int	value1 = 0;
	int	value2 = 0;
	std::string::const_reverse_iterator it1 = this->value.rbegin();
	std::string::const_reverse_iterator it2 = other.value.rbegin();


	while (it1 != this->value.rend() || it2 != other.value.rend())
	{
		if (it1 == this->value.rend())
			value1 = 0;
		else
			value1 = *it1++ - '0';
		if (it2 == other.value.rend())
			value2 = 0;
		else
			value2 = *it2++ - '0';
		result = value1 + value2 + carry;
		if (result > 9)
			carry = 1;
		else
			carry = 0;
		output.insert(output.begin(), "0123456789"[result % 10]);
	}
	if (carry)
		output.insert(output.begin(), '1');
	return (bigint(output));
}

bigint	bigint::operator-(const bigint& other) const
{
	int result = 0;
	std::string	output;
	int	borrow = 0;
	int	value1 = 0;
	int	value2 = 0;
	std::string::const_reverse_iterator it1 = this->value.rbegin();
	std::string::const_reverse_iterator it2 = other.value.rbegin();

	if (this->value.size() < other.value.size())
		return (bigint());
	if (this->value.size() == other.value.size() && this->value < other.value)
		return (bigint());
	while (it1 != this->value.rend() || it2 != other.value.rend())
	{
		
		if (it1 == this->value.rend())
			return (bigint());
		else
			value1 = *it1++ - '0';
		if (it2 == other.value.rend())
			value2 = 0;
		else
			value2 = *it2++ - '0';
		
		value1 -= borrow;
		if (value1 < value2)
		{
			result = (value1 + 10) - value2;
			borrow = 1;
		}
		else
		{
			result = value1 - value2;
			borrow = 0;
		}
		output.insert(output.begin(), "0123456789"[result]);
	}
	return (bigint(output));
}

bigint&	bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	removeLeadingZeros(this->value);
	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint tmp(*this);
	*this = *this + bigint("1");
	return (tmp);
}

bigint&	bigint::operator++()
{
	*this = *this + bigint("1");
	return (*this);
}

bigint	bigint::operator<<(int move)
{
	std::string	result = this->value;

	for (int i = 0; i < move; i++)
		result.push_back('0');
	return(bigint(result));
}

bigint	bigint::operator>>(int move)
{
	if (move >= static_cast<int>(this->value.length()))
		return (bigint(0));
	size_t	i = this->value.length();

	while (move > 0)
	{
		i--;
		move--;
	}
	std::string	result = this->value.substr(0, i);
	return (bigint(result));
}

bigint&	bigint::operator<<=(int move)
{
	*this = *this << move;
	return (*this);
}

bigint&	bigint::operator>>=(int move)
{
	*this = *this >> move;
	return (*this);
}

bool	bigint::operator==(const bigint& other) const
{
	return (this->value == other.value);
}

bool	bigint::operator!=(const bigint& other) const
{
	return (this->value != other.value);
}

bool	bigint::operator<(const bigint& other) const
{
	if (this->value.length() == other.value.length())
		return (this->value < other.value);
	return (this->value.length() < other.value.length());
}

bool	bigint::operator>(const bigint& other) const
{
	if (this->value.length() == other.value.length())
		return (this->value > other.value);
	return (this->value.length() > other.value.length());
}


bool	bigint::operator>=(const bigint& other) const
{
	if (this->value.length() == other.value.length())
		return (this->value >= other.value);
	return (this->value.length() >= other.value.length());
}

bool	bigint::operator<=(const bigint& other) const
{
	if (this->value.length() == other.value.length())
		return (this->value <= other.value);
	return (this->value.length() <= other.value.length());
}

const std::string&	bigint::getValue() const
{
	return (this->value);
}

void	bigint::removeLeadingZeros(std::string& s)
{
	size_t	i = 0;

	while (s[i] == '0' && i < s.length() - 1)
		i++;

	s = s.substr(i);
}

std::ostream&	operator<<(std::ostream& out, const bigint& b)
{
	out << b.getValue();
	return (out);
}