#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

class	bigint
{
	private:
		std::string value;
	public:
		bigint();
		bigint(int nb);
		bigint(const std::string& nb);
		bigint(const bigint& other);
		bigint&	operator=(const bigint& other);
		~bigint();

		bigint	operator+(const bigint& other) const;
		bigint	operator-(const bigint& other) const;
		bigint&	operator+=(const bigint& other);

		bigint	operator++(int);
		bigint&	operator++();

		bigint	operator<<(int move);
		bigint	operator>>(int move);
		bigint&	operator<<=(int move);
		bigint&	operator>>=(int move);

		bool	operator==(const bigint& other) const;
		bool	operator!=(const bigint& other) const;
		bool	operator<(const bigint& other) const;
		bool	operator>(const bigint& other) const;
		bool	operator<=(const bigint& other) const;
		bool	operator>=(const bigint& other) const;

		const std::string&	getValue() const;
		void	removeLeadingZeros(std::string& s);
};

std::ostream&	operator<<(std::ostream& out, const bigint& b);

#endif