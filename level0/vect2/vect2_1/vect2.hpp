#ifndef VECT2
#define VECT2

#include <iostream>

class	vect2
{
	private:
		int	x;
		int	y;

	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		vect2&	operator=(const vect2& other);
		~vect2();

		vect2	operator+(const vect2& other) const;
		vect2	operator-(const vect2& other) const;
		vect2	operator*(int scalar) const;

		vect2&	operator+=(const vect2& other);
		vect2&	operator-=(const vect2& other);
		vect2&	operator*=(int scalar);

		vect2	operator-() const;

		vect2&	operator++();
		vect2	operator++(int);
		vect2&	operator--();
		vect2	operator--(int);

		int&	operator[](int index);
		const int&	operator[](int index) const;
		
		bool	operator==(const vect2& other) const;
		bool	operator!=(const vect2& other) const;

		int	getX() const;
		int	getY() const;


};

std::ostream&	operator<<(std::ostream& out, const vect2& v);
vect2	operator*(int scalar, const vect2& v);

#endif