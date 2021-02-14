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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        world.OnKey(key, action, mods);
    }
}

static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(action == GLFW_RELEASE) {
        world.OnMouseReleased(button, mods);
    }
    if(action == GLFW_PRESS) {
        world.OnMousePressed(button, mods);
    }
}

static void glfwCursorPosCallback(GLFWwindow* window, const double x, const double y) {
    world.OnMouseMoved(static_cast<float>(x), static_cast<float>(y));
}

GLFWwindow* setupGL();

int main(int argc, char*argv[])
{
    // setup openGL context GLEW / GLFW calls, callbacks, etc....
    GLFWwindow *window = setupGL();
    if (window == nullptr) {
        return -1;
    }

    world.Startup();

    float deltaTime, lastFrameTime = 0;

    // Entering Main Loop
    while(!glfwWindowShouldClose(window)) {
        deltaTime = static_cast<float>(glfwGetTime()) - lastFrameTime; // In seconds
        lastFrameTime += deltaTime;

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

GLFWwindow* setupGL()  {
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
    GLFWwindow *window = glfwCreateWindow(world.windowWidth, world.windowHeight, world.windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(window, glfwCursorPosCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock cursor to window
    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    glfwMakeContextCurrent(window);

    // Enable vsync
    glfwSwapInterval(1);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}