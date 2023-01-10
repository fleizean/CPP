/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:37:12 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/10 18:13:48 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T> { // T'nin yanına , koy ve göster
public:
    MutantStack() : std::stack<T>() { }; // stack statik dinamik olmadığı için iterator ile dinamik yapıyoruz
    MutantStack(MutantStack const &src) : std::stack<T>(src) { };
    ~MutantStack() { this->c.clear(); }

    MutantStack &operator=(MutantStack const& mstack) {
        if (mstack != *this)
            this->c = mstack.c;
        return *this;
    };
    // iterator
    typedef typename std::stack<T>::container_type::iterator iterator; // stackin içeriğine git oradan protected kısmındaki c'yi göster
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    
    //const iterator
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		const_iterator cbegin() const{return this->c.cbegin();}
		const_iterator cend() const{return this->c.cend();}

    //reverse iterator		
    		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    		reverse_iterator rbegin(){return this->c.rbegin();}
    		reverse_iterator rend(){return this->c.rend();}
    
    //const reverse iterator			
    		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
    		const_reverse_iterator crbegin() const{return this->c.crbegin();}
    		const_reverse_iterator crend() const{return this->c.crend();}
};

#endif