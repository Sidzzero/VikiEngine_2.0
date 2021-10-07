//
//  shader.hpp
//  VEngine_Source
//
//  Created by Srikanth_Siddhu on 05/10/21.
//

#ifndef shader_hpp
#define shader_hpp


#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class shader
{
    public:
    shader(const char *vertSource , const char *fragSource);
    
    GLuint ID;
    
    void Use();
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setFloat4(const std::string &name , float x ,float y, float z, float w) const;
    
    void SetMat4(const std::string &name,
                 const GLfloat *value) const;
    
};

#endif /* shader_hpp */
