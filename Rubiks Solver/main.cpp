#include <Windows.h>
#include <iostream>
#include "rubiks_cube.hpp"

int main()
{
    RubiksCube* cube = new RubiksCube();

    cube->SetupCube();

    if (!cube->ValidCube())
    {
        MessageBoxA(nullptr, "Invalid cube colors!", "ERROR", MB_OK);
        std::quick_exit(-1);
    }

    cube->Solve();

    system("pause");

    return 0;
}