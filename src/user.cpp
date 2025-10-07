#include "../include/User.h"

bool User::checkLogin(string uname, string pwd) {
    return (uname == username && pwd == password);
}