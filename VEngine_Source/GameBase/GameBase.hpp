//
//  GameBase.hpp
//  VEngine_Source
//
//  Created by Srikanth_Siddhu on 09/10/21.
//

#ifndef GameBase_hpp
#define GameBase_hpp

#include <glad/glad.h>
#include <stdio.h>

class GameBase
{
public:
    void Init();
    //Get Inputs and do things
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    
};
#endif /* GameBase_hpp */
