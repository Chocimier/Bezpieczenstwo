#ifndef BSERVER_H
#define BSERVER_H

#include <utility>
#include <string>

#include <libblind.h>

void main_setup();
void main_sign_service();
bool password_matches(const std::string &password);
std::pair<bool, Bigint> sign(const Bigint &number);

#endif
