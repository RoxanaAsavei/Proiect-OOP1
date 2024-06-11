
#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <stdexcept>
#include <string>


class gameExceptions : public std::runtime_error {
    using std::runtime_error::runtime_error;
};


class fileError : public gameExceptions {
public:
    explicit fileError(const std::string& fileName);
};


class fontError : public gameExceptions {
public:
    explicit fontError(const std::string& fileName);
};


class textureError : public gameExceptions {
public:
    explicit textureError(const std::string& path);
};


#endif //OOP_EXCEPTIONS_H
