#include "bigint.hpp"

bigint::bigint() : value("0") {}

bigint::bigint(unsigned int n)
{
    if (n == 0)
        value = "0";
    while (n != 0)
    {
        value.insert(value.begin(), "0123456789"[n % 10]);
        n /= 10;
    }
}

bigint::bigint(const std::string& n)
{
    value = removeLeadingZeros(n);
}

bigint::bigint(const bigint& other) : value(other.value) {}

bigint& bigint::operator=(const bigint& other)
{
    if (this != &other)
        this->value = other.value;
    return (*this);
}

bigint::~bigint() {}

bigint bigint::operator+(const bigint& other) const
{
    int result = 0;
    int value1 = 0;
    int value2 = 0;
    int carry = 0;
    std::string answer;
    std::string::const_reverse_iterator it1 = this->value.rbegin();
    std::string::const_reverse_iterator it2 = other.value.rbegin();

    while (it1 != this->value.rend() || it2 != other.value.rend())
    {
        if (it1 != this->value.rend())
            value1 = *it1++ - '0';
        else
            value1 = 0;
        if (it2 != other.value.rend())
            value2 = *it2++ - '0';
        else
            value2 = 0;

        result = value1 + value2 + carry;
        if (result > 9)
        {
            answer.insert(answer.begin(), "0123456789"[result % 10]);
            carry = 1;
        }
        else
        {
            answer.insert(answer.begin(), "0123456789"[result]);
            carry = 0;
        }
    }
    if (carry)
        answer.insert(answer.begin(), '1');
    return(bigint(removeLeadingZeros(answer)));
}

bigint  bigint::operator-(const bigint& other) const
{
    return (bigint("0"));
}

bigint& bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return (*this);
}

bigint  bigint::operator++(int)
{
    bigint  tmp(*this);
    *this += bigint(1);
    return (tmp);
}

bigint&  bigint::operator++()
{
    *this += bigint(1);
    return (*this);
}

bigint  bigint::operator<<(unsigned int move) const
{
    std::string result = this->value;
    for (int i = 0; i < move; i++)
        result.push_back('0');
    return (bigint(removeLeadingZeros(result)));
}

bigint  bigint::operator>>(unsigned int move) const
{
    if (move >= this->value.length())
        return (bigint());
    size_t  i = this->value.length();
    while (move)
    {
        i--;
        move--;
    }
    return (bigint(this->value.substr(0, i)));
}

bigint& bigint::operator<<=(unsigned int move)
{
    *this = *this << move;
    return (*this);
}

bigint& bigint::operator>>=(unsigned int move)
{
    *this = *this >> move;
    return (*this);
}

bool    bigint::operator==(const bigint& other) const
{
    return (this->value == other.value);
}

bool    bigint::operator!=(const bigint& other) const
{
    return (this->value != other.value);
}

bool    bigint::operator<(const bigint& other) const
{
    if (this->value.length() == other.value.length())
        return (this->value < other.value);
    else
        return (this->value.length() < other.value.length());
}


bool    bigint::operator>(const bigint& other) const
{
    if (this->value.length() == other.value.length())
        return (this->value > other.value);
    else
        return (this->value.length() > other.value.length());
}

bool    bigint::operator<=(const bigint& other) const
{
    if (this->value.length() == other.value.length())
        return (this->value <= other.value);
    else
        return (this->value.length() <= other.value.length());
}

bool    bigint::operator>=(const bigint& other) const
{
    if (this->value.length() == other.value.length())
        return (this->value >= other.value);
    else
        return (this->value.length() >= other.value.length());
}

std::string bigint::removeLeadingZeros(const std::string& s) const
{
    size_t  i = 0;
    while (i < s.length() - 1 && s[i] == '0')
        i++;
    return (s.substr(i));
}

const std::string&  bigint::getValue() const
{
    return (this->value);
}

std::ostream&   operator<<(std::ostream& out, const bigint& b)
{
    out << b.getValue();
    return (out);
}
