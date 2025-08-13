#include "set.hpp"

set::set(searchable_bag& bag) : bag(bag) {}

set::set(const set& other) : bag(other.bag) {}

set&    set::operator=(const set& other)
{
    (void)other;
    return (*this);
}

set::~set() {}

void	set::insert(int value)
{
	if (!this->bag.has(value))
		bag.insert(value);
}

void	set::insert(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		this->insert(arr[i]);
}

void	set::print() const
{
	this->bag.print();
}

void set::clear()
{
	this->bag.clear();
}

bool    set::has(int value)
{
	return (this->bag.has(value));
}

searchable_bag& set::get_bag() const
{
	return (this->bag);
}