#include "VD_Client.h"
unsigned int VBO, cubeVAO;
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* C_SimpleShader = "SimpleShader";
static VD_Client* instance = nullptr;
bool bFirst = false;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }
  //  return;
   if(instance != nullptr)
   {
      
       auto cam = &(instance->cam);
       if (!bFirst)
       {
           instance->xLast = xpos;
           instance->yLast = ypos;
           
       }
       float Xpos = xpos - instance->xLast;
       float Ypos =  instance->yLast - ypos;
       instance->xLast = xpos;
       instance->yLast = ypos;
       cam->pitch += ( Ypos *cam->mouseSentivity);
       cam->yaw += (Xpos * cam->mouseSentivity);
      // std::cout<< cam->yaw <<std::endl;
       if (cam->pitch <-89.0f)
       {
           cam->pitch = -89.0f;
       } 
       else if (cam->pitch > 89.0f)
       {
           cam->pitch = 89.0f;
       }
     
       cam->vFront.y = glm::sin(glm::radians(cam->pitch));

       cam->vFront.x = glm::cos(glm::radians(cam->yaw)) *
                      glm::cos(glm::radians(cam->pitch));

      cam->vFront.z = glm::sin(glm::radians( cam->yaw)) *
           glm::cos(glm::radians(cam->pitch));
      if (bFirst == false)
      {
          cam->vFront = glm::vec3(0, 0, 1);
          bFirst = true;
        
      }
      cam->vFront = glm::normalize(cam->vFront);

       
   }
}
//unsigned int textureID;
void VD_Client::Init(GLFWwindow* a_window)
{
    m_window = a_window;
    instance = this;
   

   square.vertices.push_back(Vertex{ 0,0,0 });
   square.UV.push_back(UV{ 0, 0 });
   square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });
   square.UV.push_back(UV{ 1, 1 });
   square.vertices.push_back(Vertex{ 0.0f,1.0f,0 });
   square.UV.push_back(UV{ 1, 0 });

	square.vertices.push_back(Vertex{ 0,0,0 });
    square.UV.push_back(UV{ 0, 0 });
	square.vertices.push_back(Vertex{1.0f,0.0f,0});
    square.UV.push_back(UV{ 0, 1 });
	square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });
    square.UV.push_back(UV{ 1, 1 });

	square.faces.push_back(Face{ 0,1,2 });
    //Cube declaration

    float Cubevertices[] = {
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

    float cubeWithNormal[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f ,0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f
    };

    float cubeWithSite[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    int temp_iAlignCounter = 0;
    for (int i=0;i<(180);i+=5)
    {
        temp_iAlignCounter++;
        Cube.vertices.push_back(Vertex{ Cubevertices[i],
                Cubevertices[i+1],
                 Cubevertices[i + 2] }
            );
        Cube.UV.push_back(UV{ Cubevertices[i + 3], Cubevertices[i + 4] });

        //
        LightCube.vertices.push_back(Vertex{ Cubevertices[i],
             Cubevertices[i + 1],
              Cubevertices[i + 2] }
        );
        LightCube.UV.push_back(UV{ Cubevertices[i + 3], Cubevertices[i + 4] });
        
    }
    temp_iAlignCounter = 0;
    for (int i=0;i<(6*6*8);i+=8)
    {
        temp_iAlignCounter++;
        CubeWithNormal.vertices.push_back(Vertex{ cubeWithSite[i],
                cubeWithSite[i + 1],
                 cubeWithSite[i + 2] });
        CubeWithNormal.normal.push_back(Vertex{ cubeWithSite[i + 3],
        cubeWithSite[i + 4],cubeWithSite[i + 5] });
        CubeWithNormal.UV.push_back(UV{ cubeWithSite[i + 6], cubeWithSite[i + 7] });
    
    }
    
	
    CreateBufferWithPositionAndUVOnly(square, triangleRenderer);
    CreateBufferWithPositionAndUVOnly(Cube, cubeRenderer);
    CreateBufferWithPositionAndUVOnly(LightCube, lightRenderer);
    CreateBufferWithPositionUVNormalOnly(CubeWithNormal,cubeWithNormalRenderer);
    //Testing from site
    //  // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // first, configure the cube's VAO (and VBO)
  
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //End here


    // ResourceManager::LoadShaderWithHardCoded(C_SimpleShader, vertexShaderSource, fragmentShaderSource);
    ResourceManager::LoadTexture(".//res//Textures//container2.png", true, "TestTexture");
    ResourceManager::LoadTexture(".//res//Textures//container2_specular.png", true, "TestTexture_Specular");
   
     ResourceManager::LoadShader("ShaderWithTexture",".//res//Shaders//Simple.vert",".//res//Shaders//Simple.frag");

     ResourceManager::LoadShader("ShaderWithTextureAndTransform", ".//res//Shaders//Simple_Transform.vert", ".//res//Shaders//Simple_Transform.frag");

   //  ResourceManager::LoadShader("ShaderMVP", ".//res//Shaders//Simple_MVP.vert", ".//res//Shaders//Simple_MVP.frag");

     //Light Shader
     ResourceManager::LoadShader("ShaderForLight", ".//res//Shaders//Simple_Color_MVP.vert", ".//res//Shaders//Simple_Color_MVP.frag");

     //Object Phong Lighting object
     ResourceManager::LoadShader("ShaderMVP", ".//res//Shaders//Simple_Phong_MVP.vert", ".//res//Shaders//Simple_Phong_Color_Text_Struct_MVP.frag");

     glfwSetCursorPosCallback(a_window, mouse_callback);
}

void VD_Client::Input(float dt)
{
    if (ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }
}

void VD_Client::Update(float dt)
{
    if (!ImGui::GetIO().WantCaptureMouse)
    {
        if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            cam.vPosition += cam.vFront * cam.KeyboardSentivity * dt;
        }
        else  if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            cam.vPosition -= cam.vFront * cam.KeyboardSentivity * dt;
        }
        if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            //TODO :Check why so
          //cam.vPosition += cam.vRight * cam.KeyboardSentivity * dt;
            cam.vPosition += glm::normalize(glm::cross(cam.vFront, cam.vUp)) * cam.KeyboardSentivity * dt;
        }
        else if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            cam.vPosition -= glm::normalize(glm::cross(cam.vFront, cam.vUp)) * cam.KeyboardSentivity * dt;
        }
        return;
    }
   


}

void VD_Client::Render()
{
    unsigned int modelLoc, viewLoc, projLoc , objectColorLoc,lightPosLoc , lightColorLoc;
    glm::vec4 lightColor = glm::vec4(1.0f, 1, 1, 1.0f);
    glm::vec4 objectColor = glm::vec4(1.0f,0,0,1.0f);

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    //Scene Setup
    view = cam.GetViewMat();
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), ((float)800 / (float)600), 0.1f, 100.0f);

    glm::vec3 ambientForObject = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 diffuseForObject = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 specularForObject = glm::vec3(0.5f, 0.5f, 0.5f);
    float shininessForObject = 64.0f;

    glm::vec3 ambientForLight = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuseForLight = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 specularForLight = glm::vec3(1.0f, 1.0f, 1.0f);
    unsigned int camLoc = 0;
    lightPosition = glm::vec3(0, 0, 1.0f);
    ImGui::Begin("VD Engine ToolBox");
    ImGui::Text("This works perfectly ! ");
    ImGui::InputFloat("Specular Shiness", &shininessForObject);
    ImGui::End();
    //-----------Light Position---------------------
    glBindVertexArray(lightRenderer.VAO);
  
  
    ResourceManager::GetShader("ShaderForLight").Use();
    glm::mat4 modelLightPos = glm::mat4(1.0f);
    modelLightPos = glm::translate(modelLightPos, lightPosition);
    modelLightPos = glm::scale(modelLightPos, glm::vec3(0.1f));
    
    //Get Uniform
    modelLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderForLight").GetID(), "model");
    viewLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderForLight").GetID(), "view");
    projLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderForLight").GetID(), "projection");
    unsigned int baseColorLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderForLight").GetID(), "objectColor");


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLightPos));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform4f(baseColorLoc, lightColor.x, lightColor.y, lightColor.z, lightColor.w);

  
    glDrawArrays(GL_TRIANGLES, 0, LightCube.vertices.size());
    //--------------Light Ends Here


    //-----------object 

    ResourceManager::GetShader("ShaderMVP").Use();
  
   // glBindVertexArray(cubeRenderer.VAO);//---REusing //TODO: We used same set of calls to create this cube
    //glBindVertexArray(cubeVAO);
   glBindVertexArray(cubeWithNormalRenderer.VAO);//TODO add this later
    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
   // model = glm::rotate(model, -45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

     modelLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderMVP").GetID(), "model");
   viewLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderMVP").GetID(), "view");
    projLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderMVP").GetID(), "projection");
    //Lighting the Object
    objectColorLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderMVP").GetID(), "objectColor");
     camLoc  = glGetUniformLocation(ResourceManager::GetShader("ShaderMVP").GetID(),"viewPos");

    //TODO: ALWays object color is 3
    glUniform3f(objectColorLoc, objectColor.x, objectColor.y, objectColor.z);
    glUniform3f(camLoc, cam.vPosition.x, cam.vPosition.y, cam.vPosition.z);
   
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
  

    //Try to reroute all the changeable values here
 

   // ResourceManager::GetShader("ShaderMVP").SetVec3("material.ambient", ambientForObject);
  //  ResourceManager::GetShader("ShaderMVP").SetVec3("material.diffuse", diffuseForObject);
  //  ResourceManager::GetShader("ShaderMVP").SetVec3("material.specular", specularForObject);
    ResourceManager::GetShader("ShaderMVP").SetFloat("material.shininess", shininessForObject);

  
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture("TestTexture").Bind();
    glActiveTexture(GL_TEXTURE1);
    ResourceManager::GetTexture("TestTexture_Specular").Bind();

  


    ResourceManager::GetShader("ShaderMVP").SetVec3("light.position", lightPosition);
    ResourceManager::GetShader("ShaderMVP").SetVec3("light.ambient", ambientForLight);
    ResourceManager::GetShader("ShaderMVP").SetVec3("light.diffuse", diffuseForLight);
    ResourceManager::GetShader("ShaderMVP").SetVec3("light.specular", specularForLight);

  


    glDrawArrays(GL_TRIANGLES, 0, CubeWithNormal.vertices.size());
    
    glm::vec3 startPos = glm::vec3(1.0f,0,0);
    glm::mat4 tempMat = glm::mat4(1.0f);
    for (unsigned int i = 0; i < 5; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(tempMat, startPos);
        
       // float angle = 20.0f * i;
       // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.5f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, CubeWithNormal.vertices.size());
        startPos.x += 2;
    
    }
    
    
    
  

   
}
