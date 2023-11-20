#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Render.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"
#include"Camera.h"

#include"glm/glm.hpp"
#include"glm//gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window,float& mixValue);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//void glfwSetMouseButtonCallback(GLFWwindow* window， mouse_button_callback);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f, lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

static bool MouseClick = false ;

int main(void)
{
  

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "XD", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
   

    glfwSwapInterval(1);//fps限制

    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {  
        //位置+法线+纹理
        float vertices2[] = {
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

        glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        //深度检测
        glEnable(GL_DEPTH_TEST);
    
     VertexBuffer vb(vertices2, 8*6 * 6 * sizeof(float));

     VertexArray va; 
     VertexBufferLayout layout;
     layout.Push<float>(3);
     layout.Push<float>(3);
     layout.Push<float>(2);
     va.AddBuffer(vb, layout);

     VertexArray lightVa;
     VertexBufferLayout lightLayout;
     lightLayout.Push<float>(3);
     lightLayout.Push<float>(3);
     lightLayout.Push<float>(2);
     lightVa.AddBuffer(vb , lightLayout);
    

     Shader objShader("res/shaders/Color.shader");
     Shader lightShader("res/shaders/Light.shader");

     Texture diffuseMap("res/textures/box.png");
     Texture specularMap("res/textures/specular.png");
   
     objShader.Bind();
     objShader.SetUniform1i("material.diffuse", 1);
     objShader.SetUniform1i("material.specular", 1);
     Render renderer;

     ImGui::CreateContext();
     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init("#version 330 core");
     ImGui::StyleColorsDark();


        float r = 0.0f;
        float increment = 0.05f;
        float mixValue = 0.5;

        //imagui 参数
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.1f, 0.5f, 0.3f, 1.00f);
 
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //输入检测
            processInput(window, mixValue);

            renderer.Clear();
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//深度缓冲


            glm::vec3 lightColor;

            lightColor.x = 1.0f;
            lightColor.y = 1.0f;
            lightColor.z = 1.0f;
            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence


            objShader.Bind();
    
            objShader.SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
            objShader.SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            objShader.SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            objShader.SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
            // point light 1
            objShader.SetUniform3f("pointLights[0].position", pointLightPositions[0]);
            objShader.SetUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            objShader.SetUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            objShader.SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform1f("pointLights[0].constant", 1.0f);
            objShader.SetUniform1f("pointLights[0].linear", 0.09f);
            objShader.SetUniform1f("pointLights[0].quadratic", 0.032f);
            // point light 2
            objShader.SetUniform3f("pointLights[1].position", pointLightPositions[1]);
            objShader.SetUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            objShader.SetUniform3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            objShader.SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform1f("pointLights[1].constant", 1.0f);
            objShader.SetUniform1f("pointLights[1].linear", 0.09f);
            objShader.SetUniform1f("pointLights[1].quadratic", 0.032f);
            // point light 3
            objShader.SetUniform3f("pointLights[2].position", pointLightPositions[2]);
            objShader.SetUniform3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            objShader.SetUniform3f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            objShader.SetUniform3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform1f("pointLights[2].constant", 1.0f);
            objShader.SetUniform1f("pointLights[2].linear", 0.09f);
            objShader.SetUniform1f("pointLights[2].quadratic", 0.032f);
            // point light 4
            objShader.SetUniform3f("pointLights[3].position", pointLightPositions[3]);
            objShader.SetUniform3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            objShader.SetUniform3f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            objShader.SetUniform3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform1f("pointLights[3].constant", 1.0f);
            objShader.SetUniform1f("pointLights[3].linear", 0.09f);
            objShader.SetUniform1f("pointLights[3].quadratic", 0.032f);
            // spotLight
            objShader.SetUniform3f("spotLight.position", camera.cameraPos);
            objShader.SetUniform3f("spotLight.direction", camera.cameraFront);
            objShader.SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            objShader.SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
            objShader.SetUniform1f("spotLight.constant", 1.0f);
            objShader.SetUniform1f("spotLight.linear", 0.09f);
            objShader.SetUniform1f("spotLight.quadratic", 0.032f);
            objShader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            objShader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMat();
            objShader.SetUniformMat4f("u_Pro", projection);
            objShader.SetUniformMat4f("u_View", view);

            // world transformation
            glm::mat4 model = glm::mat4(1.0f);
            objShader.SetUniformMat4f("u_Model", model);

            diffuseMap.Bind(0);
            specularMap.Bind(1);

            objShader.Bind();
            objShader.SetUniform3f("viewPos", camera.cameraPos);
            objShader.SetUniform1f("material.shininess", 32.0f);
            va.Bind();
           

            for (unsigned int i = 0; i <10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                objShader.SetUniformMat4f("u_Model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            lightShader.Bind();
            lightShader.SetUniformMat4f("u_Pro", projection);
            lightShader.SetUniformMat4f("u_View", view);
            lightVa.Bind();
            for (unsigned int i = 0; i < 4; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                lightShader.SetUniformMat4f("u_Model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            } 
         
            //imgui 相关
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);
            
                ImGui::SliderFloat3("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }


            //imgui渲染
            ImGui::Render();
            
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            
           /* glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            */
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }
    }
    glfwTerminate();//破坏上下文

    // 清除imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void processInput(GLFWwindow* window,float& mixValue)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.CameraMove(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.CameraMove(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.CameraMove(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.CameraMove(RIGHT, deltaTime);
    
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        if (MouseClick)
        {
            camera.CameraMouseView(xoffset, yoffset);
        }
  
        
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int state1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    if (state == GLFW_PRESS)
        MouseClick = true;
    if (state == GLFW_RELEASE)
        MouseClick = false;

}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.CameraScroll(static_cast<float>(yoffset));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}