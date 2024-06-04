#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string>

//ermm ill work on the model class another day

#include "Project/Vector3.hpp"
#include "Project/Managers/ShaderManager.hpp"
#include "Project/Components/ShaderNames.hpp"
#include "Project/Managers/CameraManager.hpp"

#include "config.hpp"
using namespace managers;


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    float window_width = 500.f;
    float window_height = 500.f;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Nico Tolentino", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    ShaderManager::getInstance()->buildShaders();

    //glViewport(0, 0, window_width, window_height);

    #pragma region model
        std::string path = "3D/sphere.obj";
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> material;
        std::string warning, error;

        tinyobj::attrib_t attributes;

        bool success = tinyobj::LoadObj(
            &attributes,
            &shapes,
            &material,
            &warning,
            &error,
            path.c_str()
        );

        if (!success) {
            std::cout << "Failed to Load Model" << std::endl;
            return -3;
        }

        std::vector<GLuint> mesh_indices;
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }

        GLuint VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);


        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(), attributes.vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(), mesh_indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    #pragma endregion

    Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
    CameraManager::getCamera()->assignShader(shader);
    OrthographicCamera* ortho = (OrthographicCamera*) CameraManager::getCamera();
    ortho->setOrthoData(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        CameraManager::getCamera()->Draw();

        glm::mat4 transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        
        transformation_matrix = glm::scale(transformation_matrix, glm::vec3(50, 50, 50));
       


        unsigned int transformLoc = glGetUniformLocation(shader->getShaderProg(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));


        glUseProgram(shader->getShaderProg());
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
