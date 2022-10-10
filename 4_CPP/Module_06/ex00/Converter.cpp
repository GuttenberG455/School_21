
#include "Converter.hpp"

Converter::Converter(char *argv) {
    this->_input = std::string(argv);
    this->_pseudo = NO_PSEUDO;
}

Converter::Converter(const Converter &old) : _input(old._input) {}

Converter::~Converter() {}

std::string Converter::getInput() {
    return (this->_input);
}

Converter &Converter::operator=(const Converter &old) {
    this->_input = old._input;
    return (*this);
}

int Converter::parseInput() {
    std::stringstream ss;
    int i = 0;

    if (this->_input.length() == 1 && !std::isdigit(this->_input[0])) {
        this->_type = CHAR_TYPE;
        ss << this->_input[i];
        ss >> this->_charConv;
        if (ss.fail())
            std::cerr << "Error stringstream!\n";
        return (1);
    }
    if (this->_input == "-inff" || this->_input == "-inf") {
        this->_pseudo = MINF_PSEUDO;
        return (2);
    } else if (this->_input == "+inff" || this->_input == "+inf" || this->_input == "inf") {
        this->_pseudo = INF_PSEUDO;
        return (2);
    } else if (this->_input == "nanf" || this->_input == "nan") {
        this->_pseudo = NAN_PSEUDO;
        return (2);
    }
    if (this->_input.length() > 1 && !std::isdigit(this->_input[0]) && !std::isdigit(this->_input[1]))
        return (0);
    while (this->_input[i] == '-' || this->_input[i] == '+') {
        if (this->_input[i] == '-') {
            ss << '-';
        }
        i++;
    }
    if (!this->_input[i]) {
        this->_type = INVALID_TYPE;
        return (0);
    }
    this->_type = INT_TYPE;
    while (this->_input[i] && isdigit(this->_input[i])) {
        ss << this->_input[i];
        i++;
    }
    if (this->_input[i] == '.') {
        this->_type = DOUBLE_TYPE;
        ss << '.';
        i++;
    } else {
        ss << ".0";
        ss >> this->_doubleConv;
        this->_type = DOUBLE_TYPE;
        if ((this->_doubleConv < INT_MAX) && (this->_doubleConv > INT_MIN)) {
            this->_type = INT_TYPE;
            this->_intConv = static_cast<int>(this->_doubleConv);
        }
        if (ss.fail())
            std::cerr << "Error stringstream!\n";
        return (1);
    }
    while (this->_input[i] && isdigit(this->_input[i])) {
        ss << this->_input[i];
        i++;
    }
    if (this->_input[i] == 'f') {
        this->_type = FLOAT_TYPE;
        i++;
    } else {
        ss >> this->_doubleConv;
        if (ss.fail())
            std::cerr << "Error stringstream!\n";
        return (1);
    }
    if (this->_input[i])
        return (0);
    ss >> this->_floatConv;
    if (ss.fail())
        std::cerr << "Error stringstream!\n";
    return (1);
}

void Converter::printPseudo() {
    switch (this->_pseudo) {
        case INF_PSEUDO:
            this->_charConv = static_cast<char>(INFINITY);
            this->_intConv = static_cast<int>(INFINITY);
            this->_floatConv = static_cast<float>(INFINITY);
            this->_doubleConv = static_cast<double>(INFINITY);
            break;
        case MINF_PSEUDO:
            this->_charConv = static_cast<char>(INFINITY * -1);
            this->_intConv = static_cast<int>(INFINITY * -1);
            this->_floatConv = static_cast<float>(INFINITY * -1);
            this->_doubleConv = static_cast<double>(INFINITY * -1);
            break;
        case NAN_PSEUDO:
            this->_charConv = static_cast<char>(NAN);
            this->_intConv = static_cast<int>(NAN);
            this->_floatConv = static_cast<float>(NAN);
            this->_doubleConv = static_cast<double>(NAN);
            break;
    }
}

void Converter::convertAll() {
    switch (this->_type) {
        case CHAR_TYPE:
            this->_intConv = static_cast<int>(this->_charConv);
            this->_floatConv = static_cast<float>(this->_charConv);
            this->_doubleConv = static_cast<double>(this->_charConv);
            break;
        case INT_TYPE:
            this->_charConv = static_cast<char>(this->_intConv);
            this->_floatConv = static_cast<float>(this->_intConv);
            this->_doubleConv = static_cast<double>(this->_intConv);
            break;
        case FLOAT_TYPE:
            this->_intConv = static_cast<int>(this->_floatConv);
            this->_doubleConv = static_cast<double>(this->_floatConv);
            this->_charConv = static_cast<char>(this->_intConv);
            break;
        case DOUBLE_TYPE:
            this->_intConv = static_cast<int>(this->_doubleConv);
            this->_floatConv = static_cast<float>(this->_doubleConv);
            this->_charConv = static_cast<char>(this->_intConv);
            break;
    }
}

int Converter::checkEnding() {
    int i = this->_input.find('.');
    if (i != -1) {
        i++;
        while (this->_input[i]) {
            if (this->_input[i] != '0' && this->_input[i] != 'f') {
                return true;
            }
            i++;
        }
        return false;
    }
    if (this->_input.length() >= 7)
        return true;
    else
        return false;
}

void Converter::printAll() {
    if (this->_charConv > 31 && this->_charConv < 127)
        std::cout << "char: '" << this->_charConv << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    if (this->_doubleConv > INT_MAX || this->_doubleConv < INT_MIN || this->_pseudo)
        std::cout << "int: Non displayable" << std::endl;
    else
        std::cout << "int: " << this->_intConv << std::endl;
    if (checkEnding() || this->_pseudo){
        std::cout << "float: " << this->_floatConv << 'f' << std::endl;
        std::cout << "double: " << this->_doubleConv << std::endl;
    } else {
        std::cout << "float: " << this->_floatConv << ".0f" << std::endl;
        std::cout << "double: " << this->_doubleConv << ".0" << std::endl;
    }
}

void Converter::print() {
    switch (parseInput()) {
        case 2:
            printPseudo();
            printAll();
            break;
        case 1:
            convertAll();
            printAll();
            break;
        default:
            std::cerr << "Error! Wrong Input" << std::endl;
            break;
    }
}