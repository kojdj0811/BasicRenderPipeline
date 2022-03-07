#include "engine.h"

int main()
{
    Engine engine(640, 480, "OpenGL Rendering Project");
    Utility* _utility = Utility::GetInstance();

    if(!engine.Initialize())
    {
        std::cout << std::endl << "Press any key to close program..." << std::endl;
        std::cin.get();
    }

    SAFE_DELETE(_utility);
}


// cf.
// http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-3-matrices/
// http://yoonbumtae.com/?p=982
