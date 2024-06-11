#include "Exceptions.h"


fileError::fileError(const std::string& fileName) :
        gameExceptions("Nu se poate deschide fisierul: " + fileName) {}

fontError::fontError(const std::string& fileName) :
        gameExceptions("Nu se poate incarca fontul: " + fileName) {}

textureError::textureError(const std::string& path) :
        gameExceptions("Nu se poate incarca textura: " + path) {}


