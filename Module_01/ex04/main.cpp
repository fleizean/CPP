/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:21:31 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/19 12:21:31 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

void transform(std::string& line, std::string const& s_find, std::string const& s_replace)
{
	std::string::size_type pos; // string'in size_t'si diyebiliriz

	pos = line.find(s_find); // bir dizenin belirli konumunu arar ve index döndürür
	while (pos != std::string::npos) // npos burada bizim oluşturduğumuz bir işlev değil parametre olarak kullanabileceğimiz dizinin sonuna kadar ifadesini sağlar
	{
		line.erase(pos, s_find.length()); // dize içerisinden belirtilen karakter aralığı kadarını silin
		line.insert(pos, s_replace); // bir dizenin ortasına ekleme yapma
		pos = line.find(s_find, pos + s_replace.length()); // başka bir yerde aynı karakter olabilme durumu için pos değerime değiştirdiğim değerin en son index değerini atıp devam ediyorum.
	}
}

void replace(std::string const& filename, std::string const& s_find, std::string const& s_replace)
{
	std::ifstream in(filename); // dosyadan okuma işlemi için in ile çağırabileceğimiz obje oluşturduk.
	std::ofstream out(filename + ".replace", std::ofstream::out | std::ofstream::trunc); // ofstreami tanımladık artık out ile çağırabiliriz. out yazmak için aç demek, trunc dosya zaten varsa içine ekler - dosyaya yazma işlevi
	std::string line;

	if (!in || !out) // hata check
	{
		if (in)
			in.close();
		else if (out)
			out.close();
		std::cerr << "Error : open fail" << std::endl;
		return ;
	}
	while (std::getline(in, line)) // getline ile in'in içerisini alıp line'a atıyoruz
	{
		transform(line, s_find, s_replace); // transform fonksiyonuna aranacak kelimeyi ve replace edilecek kelimeyi yolluyorum
		out << line << std::endl; // line'ı out'un içerisine atar
	}
	in.close();
	out.close();
}

int main(int argc, char **argv)
{
	if (argc != 4)
		std::cout << "Usage : ./replace [File name] [Str1] [Str2]" << std::endl;
	else
		replace(argv[1], argv[2], argv[3]);
}
