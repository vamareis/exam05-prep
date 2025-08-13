#include <iostream>
#include <cctype>
#include <algorithm>

class   bigint
{
    private:
        std::string value;

    public:
        bigint();
        bigint(const std::string& nstr);
        bigint(unsigned long long n);
        bigint(const bigint& other);
        bigint&	operator=(const bigint& other);
        ~bigint();

        const std::string&  getValue() const;
        bool	all_digits(const std::string& s);
        std::string	remove_leading_zeros(const std::string& s);

        bigint	operator+(const bigint& other) const;
        bigint&	operator+=(const bigint& other);
        bigint	operator-(const bigint& other) const;
        bigint&	operator-=(const bigint& other);
        bigint&	operator++();
		bigint	operator++(int);
		bigint	operator<<(int shift);
		bigint	operator>>(int shift);
		bigint&	operator<<=(int shift);
		bigint&	operator>>=(int shift);
		bool	operator==(const bigint& other) const;
		bool	operator>(const bigint& other) const;
		bool	operator<(const bigint& other) const;
		bool	operator>=(const bigint& other) const;
		bool	operator<=(const bigint& other) const;
		bool	operator!=(const bigint& other) const;
};

std::ostream&  operator<<(std::ostream& out, const bigint& other);