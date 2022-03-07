#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"


#define SAFE_DELETE(var)    { delete var; var = NULL; }


class Utility
{
private:
    static Utility* m_instance;

public:


private:
    Utility();

public:
    ~Utility();

    static Utility* GetInstance ();
    static std::string ReadStringFromFile (char* filePath);
};