#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

class   bigint
{
    private:
        std::string value;

    public:
        bigint();
        bigint(unsigned int n);
        bigint(const std::string& n);
        bigint(const bigint& other);
        bigint& operator=(const bigint& other);
        ~bigint();

        bigint operator+(const bigint& other) const;
        bigint operator-(const bigint& other) const;

        bigint& operator+=(const bigint& other);
        /* bigint& operator-=(const bigint& other); */

        bigint  operator++(int);
        bigint&  operator++();
        /* bigint  operator--(int);
        bigint&  operator--(); */

        bigint  operator<<(unsigned int move) const;
        bigint  operator>>(unsigned int move) const;
        bigint& operator<<=(unsigned int move);
        bigint& operator>>=(unsigned int move);

        bool    operator==(const bigint& other) const;
        bool    operator!=(const bigint& other) const;
        bool    operator>(const bigint& other) const;
        bool    operator<(const bigint& other) const;
        bool    operator<=(const bigint& other) const;
        bool    operator>=(const bigint& other) const;

        std::string    removeLeadingZeros(const std::string& s) const;
        const std::string&  getValue() const;
};

std::ostream&   operator<<(std::ostream& out, const bigint& b);

#endif