//
//  main.cpp
//  VEngine_Source
// A Rework on Engine.
// Will be experiment ground to make 2D Games
//  Created by Srikanth_Siddhu on 04/10/21.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* ProjectLocation  = "//Users//Srikanth_Siddhu//VEngine_2.0//VEngineSource//VEngine_Source//VEngine_Source";

GLfloat verticesTriangleSimple[]=
{
     0.0f, 1.0f, 0.0f,
     -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
 
};
GLfloat verticesQuadSimple[]=
{
    // 0.0f, 1.0f, 0.0f,
    // -1.0f, -1.0f, 0.0f,
    // 1.0f, -1.0f, 0.0f,
    /*
    //MORE QUAD
        // first triangle
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left
        // second triangle
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    */
     0.5f , 0.5f ,0.0f,
    0.5f , -0.5f ,0.0f,
    -0.5f , -0.5f ,0.0f,
    -0.5f , 0.5f ,0.0f,
};
GLuint indicesEBOQuad[]=
{
  // 0 ,1 ,2,
  // 2 ,3 ,1
    0, 1, 3,   // first triangle
    1, 2, 3
};


unsigned int vertexShader;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(int argc, const char * argv[])
{  // glfw: initialize and configure
   // ------------------------------
  
   glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    
    
   // glfw window creation
   // --------------------
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "VEngine", NULL, NULL);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       return -1;
   }
     glfwMakeContextCurrent(window);
     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
        //Triangle Creations
    
        unsigned int vaoSingleTri , vboSingleTri;
   
        glGenVertexArrays(1, &vaoSingleTri);
        glBindVertexArray(vaoSingleTri);
        //Created Buffer
        glGenBuffers(1,&vboSingleTri);
        glBindBuffer(GL_ARRAY_BUFFER , vboSingleTri);
        //Loaded the Data into the buffer
        glBufferData(GL_ARRAY_BUFFER,sizeof(verticesTriangleSimple),verticesTriangleSimple,GL_STATIC_DRAW);
    
      
        
        //Setting up attrib pointer access and location for shaders !
        glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*3.0 , (void*) 0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    
   
    // EBO
    unsigned int vaoQuadTri , vboQuadTri,eboQuadTri;
    glGenVertexArrays(1, &vaoQuadTri);
    glBindVertexArray(vaoQuadTri);
    
    //Created Buffer
    glGenBuffers(1,&vboQuadTri);
    glBindBuffer(GL_ARRAY_BUFFER , vboQuadTri);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verticesQuadSimple),verticesQuadSimple,GL_STATIC_DRAW);
    
    glGenBuffers(1, &eboQuadTri);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboQuadTri);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesEBOQuad), indicesEBOQuad, GL_STATIC_DRAW);
    
    //Loaded the Data into the buffer

    
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*3.0 , (void*) 0);
    glEnableVertexAttribArray(0);
   // glBindVertexArray(0);
        //Shader Compile !
        int  success;
        char infoLog[512];
        GLuint  vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        GLuint fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        //TODO: reset infolog array !
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
           
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    
    //Shader object
    std::string vertLocation = ProjectLocation ;//+"//Shaders//Simple.vert";
    std::string FragLocation = ProjectLocation ;//+ "Shaders//Simple.frag";
    vertLocation = vertLocation+ "//Shaders//Simple.vert";
    FragLocation = FragLocation+ "//Shaders//Simple.frag";
    shader simpleShader(vertLocation.c_str(), FragLocation.c_str());
    
    /*shader a( "//Users//Srikanth_Siddhu//VEngine_2.0//VEngineSource//VEngine_Source//VEngine_Source//Shaders//Simple.vert" ,
           "//Users//Srikanth_Siddhu//VEngine_2.0//VEngineSource//VEngine_Source//VEngine_Source//Shaders//Simple.frag");*/
    
  

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

   
        //Simple VAO
        
        glBindVertexArray(vaoSingleTri);
        //glUseProgram(shaderProgram);
        simpleShader.Use();
        glDrawArrays(GL_TRIANGLES , 0 , 6);
        glBindVertexArray(0);
        //Simple EBO
        glBindVertexArray(vaoQuadTri);
       // glUseProgram(shaderProgram);
        simpleShader.Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
