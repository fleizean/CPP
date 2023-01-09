/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleizean <fleizean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:37:12 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/09 19:08:16 by fleizean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T> { // T'nin yanına , koy ve göster
public:
    MutantStack() : std::stack<T>() { };
    MutantStack(MutantStack const &src) : std::stack<T>(src) { };
    ~MutantStack() { this->c.clear(); }

    MutantStack &operator=(MutantStack const& mstack) {
        if (mstack != *this)
            this->c = mstack.c;
        return *this;
    };

    typedef typename std::stack<T>::container_type::iterator iterator;
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

#endif