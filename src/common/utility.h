#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"


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