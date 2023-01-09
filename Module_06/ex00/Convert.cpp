/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:01 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 17:25:01 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

// Control Area
bool isPseudo(std::string s)
{
    return (s == "nan" || s == "nanf" || s == "-inf" || s == "inf" || s == "+inf" || s == "-inff" || s == "inff" || s == "+inff");
}

bool isOk(std::string &str)
{
    size_t i;
    std::ostringstream outs;
    char tmp;

    if(isPseudo(str))
        return (true);
    if(str.length() == 1 && isalpha(str[0]))
    {
        outs << static_cast<int>(str[0]);
        str = outs.str();
        return(true);
    }
    for(i = 0; i < str.size(); i++)
    {
        tmp = str[i];
        if (!isdigit(tmp) && tmp != '-' && tmp != '+' && tmp != 'f' && tmp != '.') // dönüştüremeyeği şeyleri örn: %
            return (false);
    }
    return(true);
}
// convert methods
static void toChar(std::string &str)
{
    char tmp;
    if(isPseudo(str)){
        std::cerr << "Impossible conversion" << std::endl;
        return;
    }
    tmp = static_cast<char>(std::atoi(str.c_str())); // atoi char* tipinde aldığı için c_str ile str'nin sonuna '\0' atarak char * çevirdik
    if (!std::isprint(tmp)){
        std::cerr << "Non Displayable" << std::endl;
        return;
    }
    std::cout << tmp << std::endl;
}

static void toInt(std::string &str)
{
    if(isPseudo(str)){
        std::cerr << "Impossible conversion" << std::endl;
        return;
    }
    if (atol(str.c_str()) > INT_MAX || atol(str.c_str()) < INT_MIN){
        std::cerr << "Impossible Max-Min conversion" << std::endl;
        return;
    }
    std::cout << std::atoi(str.c_str()) << std::endl;
}

static void toFloat(std::string &str)
{
    float num = std::strtof(str.c_str(), 0); // eğer sonunda string olan bir değer verirsen örn: (2343abc) abc'yi vermesi için
    if (num == static_cast<int>(num))
        std::cout << num << ".0f" << std::endl;
    else // 123.456 noktalı durumda girer
        std::cout << num << "f" << std::endl;
}

static void toDouble(std::string &str)
{
    double num = std::strtod(str.c_str(), 0);
    if(num - static_cast<int>(num) == 0){ // 0 ile bitiyorsa örn 12 girdik 12-12=12.0 olacaği için
        std::cout << num << ".0" << std::endl;
        return ;
    }
    std::cout << num << std::endl;
}

// conversion panel
void conversionall(std::string str)
{
    std::cout << "------ All Conversion ------" << std::endl;
    std::cout << "Char : ", toChar(str);
    std::cout << "Int : ", toInt(str);
    std::cout << "Float : ", toFloat(str);
    std::cout << "Double : ", toDouble(str);
    std::cout << "----------------------------" << std::endl;
}
