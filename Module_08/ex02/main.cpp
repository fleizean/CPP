/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleizean <fleizean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:37:16 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/09 19:07:45 by fleizean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "******* TOP *******" << std::endl;
    std::cout << mstack.top() << std::endl; // ne geldiğini göster ve LIFO yapısını göster notion
    std::cout << "\n\n******* POP & SIZE *******" << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    // std::cout << "\n" << mstack.top() << std::endl;  // kimin çıktığını görmek için aç
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0); // sırasıyla girenler; 0, 737, 5, 3, 5,
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    std::cout << "\n\n******* WHILE LOOP *******" << std::endl; 
    while (it != ite)
    {
    std::cout << *it << std::endl;
    ++it;
    }
    std::stack<int> s(mstack);
    return 0;
}