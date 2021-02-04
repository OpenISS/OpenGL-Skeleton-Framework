#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <iostream>
#include "world.h"

static World world = World();

static void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else
    {
        world.OnKey(key, action, mods);
    }
}

int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Prevent window resize
    glfwWindowHint(GLFW_SAMPLES, world.windowSamples); // MSAA
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Double buffering

    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(world.windowWidth, world.windowHeight, world.windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock cursor to window
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Enable vsync
    glfwSwapInterval(1);

    world.Startup();

    float currentFrameTime = static_cast<float>(glfwGetTime());
    float lastFrameTime = currentFrameTime;
    float deltaTime;
    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime; // In seconds
        lastFrameTime = currentFrameTime;

        world.Update(deltaTime);
        world.Render();

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    world.Shutdown();

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}
