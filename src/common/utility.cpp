#include "utility.h"

Utility* Utility::m_instance;


Utility::Utility()
{

}

Utility::~Utility()
{
    if(m_instance != nullptr)
        delete m_instance;
}


Utility* Utility::GetInstance () {
    if(m_instance == nullptr) {
        m_instance = new Utility();
    }

    return m_instance;
}


std::string Utility::ReadStringFromFile (char* filePath) {
    std::ifstream ifs(filePath);
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();

    std::string buffer(size, ' ');
    ifs.seekg(0);
    ifs.read(&buffer[0], size);

    ifs.close();

    return buffer;
}
