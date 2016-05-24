#include <ijengine/exception.h>
#include <iostream>

#include "test_game.h"

using namespace ijengine;
using namespace std;

void initializeEngine(){
    /* Code here */
}

void readAssets(){
    /* 
    Code here 
    Compila cada Shader.
    */  
}

void positionAssets(){
    /* Code here */
}

void initalizeLights(){
    /* Code here */
}

void initalizeSounds(){
    /* Code here */
}

void initalizeCamera(){
    /* Code here */
}

void principalGameLoop(int flag){
    /*
    Code here 
    Com uma entrada para gerar uma lógica de saída.
    */
}

int main()
{
    int rc;

    try
    {
        TestGame game("Teste", 640, 480);
        rc = game.run("red");
    } catch (Exception& ex)
    {
        cout << ex.what() << endl;
    } 
    
    return rc; 
}


