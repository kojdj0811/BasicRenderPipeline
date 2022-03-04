#include "engine.h"

int main()
{
    Engine engine(640, 480, "OpenGL Rendering Project");
    Utility::GetInstance();

    if(!engine.Initialize())
    {
        std::cout << std::endl << "Press any key to close program..." << std::endl;
        std::cin.get();
    }
}


//cf. http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-3-matrices/