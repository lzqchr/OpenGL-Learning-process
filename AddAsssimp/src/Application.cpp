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
Camera camera(glm::vec3(0.0f, 5.0f, 15.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool  firstMouse = true;

//time
float deltaTime = 0.0f, 
      lastFrame = 0.0f;


static bool MouseClick = false ;
glm::vec3 lightPos (0.0f, 0.0f, 0.0f);

float cubeVertices[] = {
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
float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
     5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

    std::cout << glGetString(GL_VERSION) << std::endl;
    
   //     GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
     //   GLCall(glEnable(GL_BLEND));
        //深度检测
        glEnable(GL_DEPTH_TEST);

        VertexBuffer cubeVb(cubeVertices,8*6*6*sizeof(float));
        VertexBuffer planeVb(planeVertices, 5*3*2* sizeof(float));

        VertexArray cubeVa;
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        cubeVa.AddBuffer(cubeVb, layout);

        VertexArray planeVa;
        VertexBufferLayout planeLayout;
        planeLayout.Push<float>(3);
        planeLayout.Push<float>(2);
        planeVa.AddBuffer(planeVb, planeLayout);


        Shader modelShader("res/shaders/model.shader");
        Shader cubeShader("res/shaders/cube.shader");
        Shader groundShader("res/shaders/ground.shader");
        //  Texture diffuseMap("res/texture/1.png");
        mTexture diffuseMap("res/textures/box.png");
        mTexture specularMap("res/textures/specular.png");
        mTexture groundTex("res/textures/ground.png");

        

        Model ourModel(("res/model/objects/backpack/backpack.obj"));



        ImVec4 clear_color = ImVec4(1.0f, 0.1f, 0.1f, 1.00f);

        // IMGUI 前置
        IMGUI_CHECKVERSION();
        ImGui::CreateContext(NULL);
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontFromFileTTF("D:\\imguilearn\\kaiu.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());//字体导入

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

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //render
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//深度缓冲

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            //TIME
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //INPUT
            processInput(window);

            

            //
            modelShader.Bind();

            //-----UUUIIII
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport();

            //具体组件
            DrawGUI();



            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
            //--------------------------------------------------------------------




            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMat();
            modelShader.SetUniformMat4f("projection", projection);
            modelShader.SetUniformMat4f("view", view);


            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
            modelShader.SetUniformMat4f("model", model);
            ourModel.Draw(modelShader);

            //----------------------------
            groundShader.Bind();
            groundShader.SetUniformMat4f("model", glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)));
            groundShader.SetUniformMat4f("projection", projection);
            groundShader.SetUniformMat4f("view", view);  

            groundTex.Bind(0);
            planeVa.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //------------------------------------
            cubeVa.Bind();
            cubeShader.Bind();
            diffuseMap.Bind(0);
            specularMap.Bind(1);
            
          
            cubeShader.SetUniformMat4f("model", glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f)));
            cubeShader.SetUniformMat4f("projection", projection);
            cubeShader.SetUniformMat4f("view", view);

            cubeShader.SetUniform3f("light.position", lightPos);
           
            cubeShader.SetUniform1i("material.diffuse", 0);
            cubeShader.SetUniform1i("material.specular", 1);

            // light properties
            cubeShader.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
            cubeShader.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
            cubeShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

            // material properties
            cubeShader.SetUniform1f("material.shininess", 64.0f);
           
            lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
            lightPos.y = 1.0f+sin(glfwGetTime() / 2.0f) * 1.0f;

            

            glDrawArrays(GL_TRIANGLES, 0, 36);
            //----------------------------

            


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }
    
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