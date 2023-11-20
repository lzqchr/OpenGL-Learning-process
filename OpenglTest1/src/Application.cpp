#include <GL/glew.h>
#include <glfw3.h>

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
#include"mTexture.h"

#include"Camera.h"
#include"Model.h"

#include"tests/TestClearColor.h"
#include"tests/TestTexture2D.h"

#include"glm/glm.hpp"
#include"glm//gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

#include"GUI.h"
#include "vendor/imgui/imgui.h"
//#include"filesystem.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//void glfwSetMouseButtonCallback(GLFWwindow* window， mouse_button_callback);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
//Camera camera(glm::vec3(0.0f, 150.0f, 10.0f));
Camera camera(glm::vec3(500, 3500, 0),glm::vec3(0.0f, 1.0f, 0.0f),0, -90);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool  firstMouse = true;

//time
float deltaTime = 0.0f, 
      lastFrame = 0.0f;


static bool MouseClick = false ;

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "XD", NULL, NULL);
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
        return -1;
    }
    //别忘了反转纹理 不然就报错！！！！！！！！！
    stbi_set_flip_vertically_on_load(true);

    std::cout <<"实现厂商" << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
//    std::cout << glGetString(GLU_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout <<"----------------------------------------------------------" << std::endl;
    {
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        //深度检测
        glEnable(GL_DEPTH_TEST);

 

        // IMGUI 前置
        IMGUI_CHECKVERSION();
        ImGui::CreateContext(NULL);
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontFromFileTTF("D:\\imguilearn\\kaiu.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());//字体导入

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
        
        /*
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
        io.ConfigFlags |= ImGuiCol_DockingEmptyBg;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowRounding = 4;
        style.FrameRounding = 4;
        style.GrabRounding = 3;

        style.ScrollbarSize = 7;
        style.ScrollbarRounding = 0;
 
        */
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        test::Test* currentTest =nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color", camera);
        testMenu->RegisterTest<test::TestTexture2D>("Texture2D", camera);
        
        //test::TestClearColor XD( camera);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
           // GLCall(glClearColor(1,0,0,1))
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            //TIME
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //render
           // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//深度缓冲

            //-----UUUIIII
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
        //  ImGui::DockSpaceOverViewport();
        
             
        //    while (false)
            if (currentTest)
            {
                //INPUT
                processInput(window);
                //TIME
                float currentFrame = static_cast<float>(glfwGetTime());
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                
                currentTest->OnUpdate(currentFrame+30.0f);
                currentTest->OnRnder();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnimGuiRender();

            //    ImGui::ShowDemoWindow();

                ImGui::End();

           /*
                ImGui::Render();

                XD.OnRnder();
                XD.OnUpdate(0);
                XD.OnimGuiRender();
                */              
            } 

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
            
            glfwSwapBuffers(window);

            glfwPollEvents();
            
        }
        
        delete currentTest;
        if (currentTest != testMenu)
        {
            delete testMenu;
        }
        
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();//破坏上下文
    return 0;
}

void processInput(GLFWwindow* window)
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

    if (state1 == GLFW_PRESS)
        MouseClick = true;
    if (state1 == GLFW_RELEASE)
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