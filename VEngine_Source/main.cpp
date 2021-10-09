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
#include <cmath>
#include "shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

GLfloat verticesQuadTex[]=
{
    
     0.5f , 0.5f ,0.0f,  1.0f,1.0f,
    0.5f , -0.5f ,0.0f,  1.0f ,0.0f,
    -0.5f , -0.5f ,0.0f,  0.0f,0.0f,
    -0.5f , 0.5f ,0.0f,  0.0f ,1.0f
};

GLfloat verticesCube[] =
{
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    
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

//Camera controls
float camMoveSpeed =1.0f;
glm::vec3 InpCamPos(0.0f ,0.0f ,3.0f);
glm::vec3 InpCamTargetDirection(0.0f ,0.0f ,-1.0f);
glm::vec3 InpCamUp(0.0f ,1.0f ,0.0f);

std::string GetLocationFullPath(const char* RootLocation , const char* FileName)
{
    std::string fileLocation = RootLocation ;
   
    fileLocation = fileLocation+ FileName;
    return  fileLocation;
}
float deltaTime = 0.0f;
float lastTime  = 0.0f;

int main(int argc, const char * argv[])
{

    
   // glfw: initialize and configure
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
    glBindVertexArray(0);
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
    
    shader uniformShader(GetLocationFullPath(ProjectLocation , "//Shaders//Simple.vert").c_str(),
                         GetLocationFullPath(ProjectLocation , "//Shaders//SimpleUniformCol.frag").c_str() );
    

    //---Loading TExtures
    //Creating a VBO stuff
    GLuint vaoTex , vboTex , eboTex;
    glGenVertexArrays(1, &vaoTex);
    glBindVertexArray(vaoTex);
    glGenBuffers(1, &vboTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(verticesQuadTex),verticesQuadTex,GL_STATIC_DRAW);
    
    glGenBuffers(1, &eboTex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboQuadTri);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesEBOQuad), indicesEBOQuad, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*5 , (void*) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,2,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*5 , (void*) (sizeof(float)*3));//NOTE: ONLY NUMBERS !

    glEnableVertexAttribArray(1);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(GetLocationFullPath(ProjectLocation , "//container.jpg").c_str(), &width, &height, &nrChannels, 0);
   
    GLuint texID;
    glGenTextures(1, &texID);
    
    glBindTexture(GL_TEXTURE_2D , texID);
  
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Texture not Loaded !"<<std::endl;
    }
    stbi_set_flip_vertically_on_load(true); 
    stbi_image_free(data);
    
    shader shaderTex(GetLocationFullPath(ProjectLocation ,"//Shaders//SimpleTex.vert").c_str(),
                     GetLocationFullPath(ProjectLocation ,"//Shaders//SimpleTex.frag").c_str()
                     );
    shaderTex.Use();
    shaderTex.setInt("ourTexture", 0);
    
    
    // Cube Creations...
    GLuint vaoCube, vboCube;
    
    glGenVertexArrays(1,&vaoCube);
    glBindVertexArray(vaoCube);
    
    glGenBuffers(1,&vboCube);
    glBindBuffer(GL_ARRAY_BUFFER , vboCube);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube),verticesCube,GL_STATIC_DRAW);
    //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*5 , (void*) 0);//NOTE: ONLY
    //UV
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT , GL_FALSE ,sizeof(GL_FLOAT)*5 , (void*) (sizeof(float)*3));//NOTE: ONLY
    
    shader shaderMVP(GetLocationFullPath(ProjectLocation ,"//Shaders//SimpleMVP.vert").c_str(),
                     GetLocationFullPath(ProjectLocation ,"//Shaders//SimpleMVP.frag").c_str()
                     );
    glm::mat4 model(1.0f) ;
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));//Right hand rule towards negative z axis  as you want camera be at orgin 0,0,0 
 
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    //Setup uniform
    shaderMVP.Use();
    shaderMVP.SetMat4("model", glm::value_ptr(model));
    
    //Position , lookpostion , up vector !
    //Moves in Postive Z axis
    view = glm::lookAt( glm::vec3(0.0f,0.0f,6.0f),
                        glm::vec3(0.0f),
                        glm::vec3(0.0f,1.0f,0.0f));
    shaderMVP.SetMat4("view", glm::value_ptr(view));
    
    shaderMVP.SetMat4("projection", glm::value_ptr(projection));
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glm::mat4 tempPos(1.0);
    
    glEnable(GL_DEPTH_TEST);
    float fCurrentTime = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // input
        // -----
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float TimeValue = glfwGetTime();
        fCurrentTime = glfwGetTime();
        deltaTime = fCurrentTime - lastTime;
        lastTime = fCurrentTime;
        //Simple VAO
        /*
        glBindVertexArray(vaoSingleTri);
        //glUseProgram(shaderProgram);
        simpleShader.Use();
        glDrawArrays(GL_TRIANGLES , 0 , 6);
        glBindVertexArray(0);
        
        */
        /*
        //Simple EBO
        glBindVertexArray(vaoQuadTri);
       // glUseProgram(shaderProgram);
        uniformShader.Use();
        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        uniformShader.setFloat4("colorToUse", 0.0f, 0,blueValue, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        */
        //Texture style
        /*
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glBindVertexArray(vaoTex);
        shaderTex.Use();
        glDrawElements(GL_TRIANGLES , 6, GL_UNSIGNED_INT , 0);
        glBindVertexArray(0);
        */
        //CUBE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glBindVertexArray(vaoCube);
        
        //Rotate View viewed from UP  vector
      /*
        float radius = 10.0f;
        float ZValue = sin(TimeValue) *radius;
        float XValue = cos(TimeValue) *radius;
        view = glm::lookAt( glm::vec3(XValue,0.0f,ZValue),
                            glm::vec3(0.0f),
                            glm::vec3(0.0f,1.0f,0.0f));
        
        */
        //Rotate with Controls
        view = glm::lookAt(InpCamPos,   InpCamPos+InpCamTargetDirection, InpCamUp);
        shaderMVP.SetMat4("view", glm::value_ptr(view));
        for(auto pos: cubePositions)
        {
            tempPos = model;
            tempPos =  glm::translate(tempPos, pos);
            //Rotate everybody !
            /*
            float timeValue = glfwGetTime();
            float blueValue = 360.0f*sin(timeValue) ;
            tempPos = glm::rotate(tempPos, glm::radians(blueValue), glm::vec3(0,1.0f,0));
            shaderMVP.Use();
          
            */
            shaderMVP.SetMat4("model", glm::value_ptr(tempPos));
             glDrawArrays(GL_TRIANGLES , 0 ,36);
        }
       // shaderMVP.Use();
       // glDrawArrays(GL_TRIANGLES , 0 ,36);
        
        
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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        InpCamPos +=InpCamTargetDirection*camMoveSpeed*deltaTime;
        std::cout<<InpCamPos.z<<","<<deltaTime<<"\n";
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        InpCamPos -=InpCamTargetDirection*camMoveSpeed*deltaTime;
        std::cout<<InpCamPos.z<<","<<deltaTime<<"\n";
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        auto crossVal = glm::normalize( glm::cross(InpCamTargetDirection,InpCamUp));
        InpCamPos +=crossVal*camMoveSpeed*deltaTime;
        std::cout<<InpCamPos.x<<","<<deltaTime<<"\n";
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        auto crossVal = glm::normalize( glm::cross(InpCamTargetDirection,InpCamUp));
        InpCamPos -=crossVal*camMoveSpeed*deltaTime;
        std::cout<<InpCamPos.x<<","<<deltaTime<<"\n";
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
