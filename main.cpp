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

//ermm submitting this instead, I'm still optimizing the oop for the actual one im gonna use (it's based on the GRAP1 MP)

#include "Project/Vector3.hpp"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    float window_width = 500.f;
    float window_height = 500.f;

    window = glfwCreateWindow(window_width, window_height, "Nico Tolentino", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    #pragma region shader

        glViewport(0, 0, window_width, window_height);

        std::fstream vertSrc("Shaders/shaders.vert");

        std::stringstream vertBuff;
        vertBuff << vertSrc.rdbuf();

        std::string vertS = vertBuff.str();
        const char* v = vertS.c_str();

        std::fstream fragSrc("Shaders/shaders.frag");
        std::stringstream fragBuff;
        fragBuff << fragSrc.rdbuf();

        std::string fragS = fragBuff.str();
        const char* f = fragS.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &v, NULL);
        glCompileShader(vertexShader);

        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &f, NULL);
        glCompileShader(fragShader);

        GLuint shaderProg = glCreateProgram();
        glAttachShader(shaderProg, vertexShader);
        glAttachShader(shaderProg, fragShader);

        glLinkProgram(shaderProg);

    #pragma endregion

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


    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float size = 3.f;
    float znear = 1;
    float zfar = 10;

    Vector3 a = Vector3(3.f, 1.5f, 3.f);
    Vector3 b = Vector3(3.f, 2.5f, 1.f);

   

    a.Normalize();

    std::cout << "vec: " << a.Magnitude() << std::endl;


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


        glm::mat4 projectionMatrix = glm::ortho(-size, size, -size, size, znear, zfar);

        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));


        glm::mat4 transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        transformation_matrix = glm::scale(transformation_matrix, (glm::vec3)a);
        transformation_matrix = glm::rotate(transformation_matrix, glm::radians(0.f), glm::normalize(glm::vec3(0, 1, 0)));


        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));


        glUseProgram(shaderProg);
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
