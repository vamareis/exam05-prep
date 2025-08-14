#include "set.hpp"

set::set(searchable_bag& bag) : bag(bag) {}

set::set(const set& other) : bag(other.bag) {}

set::~set() {}

set&    set::operator=(const set& other) 
{
    (void)other;
    return (*this);
}

void    set::insert(int value)
{
    if (!bag.has(value))
        bag.insert(value);
}

void set::insert(int *a, int s)
{
    for (int i = 0; i < s; i++)
        insert(a[i]);
}

void set::print() const
{
    bag.print();
}

void set::clear()
{
    bag.clear();
}

 bool set::has(int value) const
 {
    return (bag.has(value));
 }

searchable_bag& set::get_bag()
{
    return (this->bag);
}