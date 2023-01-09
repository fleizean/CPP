/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:14:12 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:23:52 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Info.hpp"

void Info::setFirstName(const std::string str) { firstName_ = str; }
void Info::setLastName(const std::string str) { lastName_ = str; }
void Info::setNickname(const std::string str) { nickname_ = str; }
void Info::setLogin(const std::string str) { login_ = str; }
void Info::setEmailAddress(const std::string str) { emailAddress_ = str; }
void Info::setPhoneNumber(const std::string str) { phoneNumber_ = str; }

std::string Info::getFirstName(void) const { return (firstName_); }
std::string Info::getLastName(void) const { return (lastName_); }
std::string Info::getNickname(void) const { return (nickname_); }
std::string Info::getLogin(void) const { return (login_); }
std::string Info::getEmailAddress(void) const { return (emailAddress_); }
std::string Info::getPhoneNumber(void) const { return (phoneNumber_); }