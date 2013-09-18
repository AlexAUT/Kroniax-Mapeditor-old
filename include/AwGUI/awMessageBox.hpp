#ifndef AWMESSAGEBOX_HPP
#define AWMESSAGEBOX_HPP

#include <string>

namespace aw
{
    bool MessageBoxYesNo(std::string title, std::string text);
    void MessageBoxOK(std::string title, std::string text);
    std::string MessageBoxInput(std::string title, std::string text, std::string);
}

#endif
