#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}

searchable_tree_bag::~searchable_tree_bag() {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
    tree_bag::operator=(other);
    return (*this);
}

bool searchable_tree_bag::has(int value) const
{
    return (search_value(value, this->tree));
}

bool    searchable_tree_bag::search_value(int value, node *n) const
{
    if (value == n->value)
        return (true);
    if (value < n->value && n->l)
        return (search_value(value, n->l));
    else if (value > n->value && n->r)
        return (search_value(value, n->r));
    return (false);
}
