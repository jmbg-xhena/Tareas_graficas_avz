#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader/shader_s.h>
#include <camera/camera.h>
#include <iostream>
#include <vector>
#include<windows.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// generamos un vector de luz (punto de luz) en el espacio 
glm::vec3 lightPos(3.6f, 100.0f, 4.5f);

////////////////////
//////////////////// ///////////////////////// inicializaciones generales  /////////////////////////////////// inicializaciones generales  ///////////////////////////////////// inicializaciones generales  ////////////////////////////////////////////////////
//////////////////// ///////////////////////// inicializaciones generales  /////////////////////////////////// inicializaciones generales  ///////////////////////////////////// inicializaciones generales  ////////////////////////////////////////
//////////////////// ///////////////////////// inicializaciones generales  /////////////////////////////////// inicializaciones generales  ///////////////////////////////////// inicializaciones generales  ///////////////////////////////////////////////////
////////////////////


float roof[] = {
-0.5f, -0.75f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.75f, -0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, -0.5f,   0.5f, 0.5f,

-0.5f, -0.75f,  0.5f,  0.0f, 1.0f,
 0.5f, -0.75f,  0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, 0.5f,    0.5f, 0.5f,

 0.5f, -0.75f,  0.0f,  0.0f, 1.0f,
 0.5f, -0.75f,  -0.5f, 1.0f, 1.0f,
 0.0f,  0.0f, -0.5f,   0.5f, 0.5f,

 -0.5f, -0.75f,  -0.5f, 0.0f, 1.0f,
 -0.5f, -0.75f,  0.0f,  1.0f, 1.0f,
 0.0f,  0.0f, -0.5f,    0.5f, 0.5f,

  0.5f, -0.75f,  0.0f, 0.0f, 1.0f,
 0.5f, -0.75f,  0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, 0.5f,    0.5f, 0.5f,

 -0.5f, -0.75f,  0.5f, 0.0f, 1.0f,
 -0.5f, -0.75f,  0.0f, 1.0f, 1.0f,
 0.0f,  0.0f, 0.5f,    0.5f, 0.5f,

  0.0f, 0.0f,  0.5f,   0.0f, 1.0f,
 -0.5f, -0.75f,  0.0f, 1.0f, 1.0f,
  0.0f, 0.0f,  -0.5f,  0.5f, 0.5f,

  0.0f, 0.0f,  0.5f,   0.0f, 1.0f,
  0.5f, -0.75f,  0.0f, 1.0f, 1.0f,
  0.0f, 0.0f,  -0.5f,  0.5f, 0.5f,

-0.5f, -0.75f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.75f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.75f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.75f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.75f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.75f, -0.5f,  0.0f, 1.0f,
};

float techo[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, -0.3f,  0.5f, 0.5f,

-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, 0.3f,   0.5f, 0.5f,

 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
 0.5f, -0.5f,  -0.5f,  1.0f, 1.0f,
 0.0f,  0.0f, -0.3f,  0.0f, 0.0f,

 -0.5f, -0.5f,  -0.5f,  0.0f, 0.0f,
 -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
 0.0f,  0.0f, -0.3f,  1.0f, 1.0f,

  0.5f, -0.5f,  0.0f,  -1.0f, -1.0f,
 0.5f, -0.5f,  0.5f,  -1.0f, 0.0f,
 0.0f,  0.0f, 0.3f,  0.0f, 0.0f,

 -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f,
 -0.5f, -0.5f,  0.0f,  -1.0f, -1.0f,
 0.0f,  0.0f, 0.3f,    0.0f, 0.0f,

  0.0f, 0.0045f,  0.3f,  0.0f, 0.0f,
 -0.5f, -0.5055f,  0.0f,  -1.0f, -1.0f,
  0.0f, 0.0045f,  -0.3f,  0.0f, -1.0f,

  0.0f, 0.0045f,  0.3f,  0.0f, 0.0f,
  0.5f, -0.5055f,  0.0f,  -1.0f, -1.0f,
  0.0f, 0.0045f,  -0.3f,  0.0f, -1.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
};

float cuadro_base[] = {
    -0.5f, -0.45f, -0.5f,    0.0f, 0.0f,
     0.5f, -0.45f, -0.5f,    1.0f, 0.0f,
     0.5f, 0.45f, -0.5f,  1.0f, 1.0f,
     0.5f, 0.45f, -0.5f,  1.0f, 1.0f,
    -0.5f, 0.45f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.45f, -0.5f,    0.0f, 0.0f,
            
    -0.5f, -0.45f,  0.5f,    0.0f, 0.0f,
     0.5f, -0.45f,  0.5f,    1.0f, 0.0f,
     0.5f, 0.45f,  0.5f,  1.0f, 1.0f,
     0.5f, 0.45f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.45f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.45f,  0.5f,    0.0f, 0.0f,

    -0.5,  0.45f,  0.5,  1.0f, 1.0f,
    -0.5,  0.45f, -0.5,  0.0f, 1.0f,
    -0.5f, -0.45f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.45f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.45f,  0.5f,  1.0f, 0.0f,
    -0.5,  0.45f,  0.5,  1.0f, 1.0f,

     0.5,  0.45f,  0.5,  1.0f, 1.0f,
     0.5,  0.45f, -0.5,  0.0f, 1.0f,
     0.5f, -0.45f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.45f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.45f,  0.5f,  1.0f, 0.0f,
     0.5,  0.45f,  0.5,  1.0f, 1.0f,
            
    -0.5, -0.45f, -0.5f,  0.0f, 0.0f,
     0.5, -0.45f, -0.5f,  1.0f, 0.0f,
     0.5, -0.45f,  0.5f,  1.0f, 1.0f,
     0.5, -0.45f, 0.5f,   1.0f, 1.0f,
    -0.5, -0.45f,  0.5f,  0.0f, 1.0f,
    -0.5, -0.45f, -0.5f,  0.0f, 0.0f,
            
    -0.5,  0.45f, -0.5,  0.0f, 0.0f,
     0.5,  0.45f, -0.5,  1.0f, 0.0f,
     0.5,  0.45f,  0.5,  1.0f, 1.0f,
     0.5,  0.45f, 0.5,    1.0f, 1.0f,
    -0.5,  0.45f,  0.5,  0.0f, 1.0f,
    -0.5,  0.45f, -0.5,  0.0f, 0.0f
};

// world space positions
glm::vec3 cubePosition;
glm::vec3 techoPositionf;
glm::vec3 puerta_pos;
glm::vec3 ventana1_pos;
glm::vec3 ventana2_pos;

glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);
unsigned int VBO, VAO, lightCubeVAO;

////////////////////
////////////////////   funciones de creación de bloques de estructura del castillo  ////////////////////  funciones de creación de bloques de estructura del castillo  ///////////////////////////////////////////////////////
////////////////////   funciones de creación de bloques de estructura del castillo  ////////////////////  funciones de creación de bloques de estructura del castillo  ///////////////////////////////////////////////////////
////////////////////   funciones de creación de bloques de estructura del castillo  ////////////////////  funciones de creación de bloques de estructura del castillo  ///////////////////////////////////////////////////////
////////////////////

void crear_cubo_castillo(Shader ourShader, Shader techoShader,glm::vec3 transform_cubo, glm::vec3 transform_techo,glm::vec3 scale_cubo, glm::vec3 scale_techo) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadro_base), cuadro_base, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    ourShader.use();
    ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader.setMat4("view", view);
    cubePosition = glm::vec3(0.0f, -2.0f + 0.4, -10.0f);
    model = glm::translate(model, cubePosition + transform_cubo);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.3f, 0.0f));
    model = glm::scale(model, glm::vec3(2, 10, 2)+scale_cubo);
    ourShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(techo), techo, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    techoShader.use();
    techoShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    techoShader.setMat4("view", view);
    cubePosition = glm::vec3(0.0f, -2.0f + 3, -10.0f);
    model = glm::translate(model, cubePosition + transform_techo);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.3f, 0.0f));
    model = glm::scale(model, glm::vec3(2.1f, 15, 2.1f) + scale_techo);
    techoShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////
}


void crear_cubo_castillo_parent(Shader ourShader, Shader techoShader, glm::vec3 transform_cubo, glm::vec3 transform_techo, glm::vec3 scale_cubo, glm::vec3 scale_techo) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadro_base), cuadro_base, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    ourShader.use();
    ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader.setMat4("view", view);
    model = glm::translate(model, cubePosition);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.3f, 0.0f));
    model = glm::scale(model, glm::vec3(2, 10, 2) + scale_cubo);
    model = glm::translate(model, transform_cubo);
    ourShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(techo), techo, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    techoShader.use();
    techoShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    techoShader.setMat4("view", view);
    model = glm::translate(model, cubePosition);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.3f, 0.0f));
    model = glm::scale(model, glm::vec3(2.1f, 15, 2.1f) + scale_techo);
    model = glm::translate(model, transform_techo);
    techoShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////
}

void crear_pared(Shader ourShader, glm::vec3 transform_cubo, glm::vec3 scale_cubo) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadro_base), cuadro_base, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    ourShader.use();
    ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader.setMat4("view", view);
    model = glm::translate(model, cubePosition);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.3f, 0.0f));
    model = glm::scale(model, glm::vec3(2, 10, 2) + scale_cubo);
    model = glm::translate(model, transform_cubo);
    ourShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void crear_piramide_castillo_parent(Shader ourShader, Shader techoShader, glm::vec3 transform_cubo, glm::vec3 transform_techo, glm::vec3 scale_cubo, glm::vec3 scale_techo, float roty_cubo, float roty_techo) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadro_base), cuadro_base, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    ourShader.use();
    ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader.setMat4("view", view);
    model = glm::translate(model, cubePosition);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, roty_cubo, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2, 10, 2) + scale_cubo);
    model = glm::translate(model, transform_cubo);
    ourShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roof), roof, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // render boxes
    glBindVertexArray(VAO);
    model = glm::mat4(1.0f);
    techoShader.use();
    techoShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    techoShader.setMat4("view", view);
    model = glm::translate(model, cubePosition);
    model = glm::scale(model, glm::vec3(4.0f, 0.2f, 4.0f));
    model = glm::rotate(model, roty_techo, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.1f, 15, 2.1f) + scale_techo);
    model = glm::translate(model, transform_techo);
    techoShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ////////////////////////////////////////
}

////////////////////
////////////////////  main  /////////////////  main  ///////////  main  ///////////  main  /////////////////  main  ///////////  main  //////////////  main  /////////////  main  //////////////////////////////////////////////////////////
////////////////////  main  /////////////////  main  ///////////  main  ///////////  main  /////////////////  main  ///////////  main  //////////////  main  /////////////  main  //////////////////////////////////////////////////////////
////////////////////  main  /////////////////  main  ///////////  main  ///////////  main  /////////////////  main  ///////////  main  //////////////  main  /////////////  main  //////////////////////////////////////////////////////////
////////////////////

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Granja perrona", NULL, NULL);
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

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    Shader ourShader("cubos.vs", "cubos.fs");
    Shader techoShader("cubos.vs", "techo.fs");
    Shader puertaShader("cubos.vs", "puerta.fs");
    Shader ventanaShader("cubos.vs", "ventana.fs");
    Shader rockShader("cubos.vs", "rock.fs");
    Shader pastoShader("cubos.vs", "pasto.fs");
    Shader lightingShader("luzbasica.vs", "luzbasica.fs");
    Shader lightCubeShader("luzcubo.vs", "luzcubo.fs");
    Shader skyboxShader("skybox.vs", "skybox.fs");
    Shader outShader("cubos.vs", "puerta_casa.fs");
    // ------------------------------------
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6, texture7;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("piedra.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("teja.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 3
// ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("piramid.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 4
// ---------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("ventana.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 5
// ---------
    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("escaleras.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 6
// ---------
    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("pasto.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture7);
    glBindTexture(GL_TEXTURE_2D, texture7);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("puerta_casa.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    techoShader.use();
    techoShader.setInt("texture1", 1);
    puertaShader.use();
    puertaShader.setInt("texture1", 2);
    ventanaShader.use();
    ventanaShader.setInt("texture1", 3);//hacer textura
    rockShader.use();
    rockShader.setInt("texture1", 4);//hacer textura
    pastoShader.use();
    pastoShader.setInt("texture1", 5);//hacer textura
    outShader.use();
    outShader.setInt("texture1", 6);

    // render loop
    // -----------
    glm::vec3 parentTrans;
    short key=0;
    float x_move = 0;
    float z_move = 0;
    float y_move = 0;
    float initial_x_move = 0;
    float initial_y_move = -5.0f;
    float initial_z_move = -50.0f;
    float x_rotate = 0;
    float y_rotate = 0;

    //configuracion del skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    vector<std::string> faces
    {
        ("resources/textures/skybox/skybox/right.jpg"),
        ("resources/textures/skybox/skybox/left.jpg"),
        ("resources/textures/skybox/skybox/bottom.jpg"),
        ("resources/textures/skybox/skybox/top.jpg"),
        ("resources/textures/skybox/skybox/front.jpg"),
        ("resources/textures/skybox/skybox/back.jpg")
    };

    unsigned int cubemapTexture = loadCubemap(faces);

    //configuracion del shader
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    //confguracion del VAO y VBO de cubo sencillo
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // configuracion de los atributos de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // configuramos un segundo VAO en este caso para el cubo de luz
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ten en cuenta que actualizamos la zancada del atributo de posición de la luz para reflejar los datos de búfer actualizados
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        // input
// -----

        key = GetKeyState(0x41);
        if (key < 0) {
            x_move += 0.02;
        }

        key = GetKeyState(0x44);
        if (key < 0) {
            x_move -= 0.02;
        }

        key = GetKeyState(0x57);
        if (key < 0) {
            z_move += 0.02;
        }

        key = GetKeyState(0x53);
        if (key < 0) {
            z_move -= 0.02;
        }

        key = GetKeyState(0x45);
        if (key < 0) {
            y_move -= 0.02;
        }

        key = GetKeyState(0x51);
        if (key < 0) {
            y_move += 0.02;
        }

        key = GetKeyState(0x25);
        if (key < 0) {
            y_rotate += 0.001;
        }

        key = GetKeyState(0x27);
        if (key < 0) {
            y_rotate -= 0.001;
        }


        key = GetKeyState(0x28);
        if (key < 0) {
            x_rotate -= 0.001;
        }

        key = GetKeyState(0x26);
        if (key < 0) {
            x_rotate += 0.001;
        }

        processInput(window);


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // se tiene que asegurar el activado de los shaders cuando configuramos o dibujamos los objetos
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", glm::vec3(initial_x_move + x_move, initial_y_move + y_move, initial_z_move + z_move));

         // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, texture5);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, texture6);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, texture7);

        // create transformations
        view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 150.0f);
        view = glm::translate(view, glm::vec3(initial_x_move+x_move, initial_y_move+y_move, initial_z_move+z_move));
        view = glm::rotate(view,x_rotate, glm::vec3(1, 0, 0.0f));
        view = glm::rotate(view, y_rotate, glm::vec3(0, 1, 0.0f));

        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // transformaciones globales
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // renderizamos el cubo
        //glBindVertexArray(cubeVAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);


        ///crear los bloques de castillo
        
        crear_cubo_castillo_parent(ourShader, techoShader, glm::vec3(0, -4.9, 0), glm::vec3(-0, -2.93, 0), glm::vec3(0.5, 3.5, 1), glm::vec3(0.5, 2.5, 1));
        crear_cubo_castillo_parent(outShader, techoShader, glm::vec3(6, -4.9, -15), glm::vec3(6, -11.5, -15), glm::vec3(-1.7, 3.5, -1.7), glm::vec3(-1.8, -10, -1.8));
        
        ////murallas
        crear_pared(rockShader, glm::vec3(-0.06 ,-13.9, 50), glm::vec3(9.4, -5, -1.9));
        crear_pared(rockShader, glm::vec3(-0.06,-13.9, -50), glm::vec3(9.4, -5, -1.9));
        crear_pared(rockShader, glm::vec3(50.35, -13.9, 0), glm::vec3(-1.9,-5, 8.05));
        crear_pared(rockShader, glm::vec3(-63.7, -13.9, 0), glm::vec3(-1.9,-5, 8.05));
        crear_pared(rockShader, glm::vec3(-2, -13.9, 9.5), glm::vec3(0, -5, -1.9));
        crear_pared(rockShader, glm::vec3(-2, -13.9, -9.5),glm::vec3(0, -5, -1.9));
        crear_pared(rockShader, glm::vec3(-30, -13.9, 0), glm::vec3(-1.9, -5, 0));
        crear_pared(rockShader, glm::vec3(-50, -13.9, 0), glm::vec3(-1.9, -5, 0));

        crear_pared(pastoShader, glm::vec3(-0.06, -72, 0), glm::vec3(9.35, -9, 8));


        // dibujamos el cubo de luz
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(2.0f)); // un cubiiiiiitoooo masssssss
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        //view = glm::mat4(1.0f);// remove translation from the view matrix
        view = glm::scale(view, glm::vec3(1000, 1000, 1000));
        view = glm::rotate(view, 40.85f, glm::vec3(1, 0, 0));
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default


// -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &skyboxVAO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}