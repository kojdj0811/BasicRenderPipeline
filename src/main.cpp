#include "engine.h"

int main()
{
    Engine engine(640, 480, "OpenGL Rendering Project");

    if(!engine.Initialize())
    {
        std::cout << std::endl << "Press any key to close program..." << std::endl;
        std::cin.get();
    }
}
