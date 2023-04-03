#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "draw.h"

void clog(const char* msg);
void cerror(const char* msg);

void glfw_error_callback(int error, const char* description);
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int main() {
    clog("Hello, world!\n");

    // Before you can use most GLFW functions, the library must be initialized
    if (!glfwInit())
    {
        cerror("GLFW init failed");
        return 1;
    }
    glfwSetErrorCallback(glfw_error_callback);


    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        cerror("GLFW init failed");
        glfwTerminate();
        return 1;
    }

    // Before you can use the OpenGL API, you must have a current OpenGL context.
    glfwMakeContextCurrent(window);
    // The swap interval indicates how many frames to wait until swapping the buffers, commonly known as vsync. 
    // By default, the swap interval is zero
    glfwSwapInterval(1);
    // Example setup of keyboard events to close window with Escape key - must be called after gflwMakeContextCurrent
    glfwSetKeyCallback(window, glfw_key_callback);

    // load OpenGL functions - must be done after glfwMakeContextCurrent
    GLenum glewErr = glewInit();
    if(glewErr != GLEW_OK) {
        // OpenGL function loading failed
        cerror("GLEW init failed");
        cerror((const char *)glewGetErrorString(glewErr));
        glfwTerminate();
        return 1;
    }

    DrawConfig drawConfig = setup();

    // Each window has a flag indicating whether the window should be closed.
    while (!glfwWindowShouldClose(window))
    {
        // The framebuffer size needs to be retrieved for glViewport
        // You can also set a framebuffer size callback using glfwSetFramebufferSizeCallback and be notified when the size changes.
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        draw(drawConfig);

        // When the entire frame has been rendered, the buffers need to be swapped with one another, 
        // so the back buffer becomes the front buffer and vice versa.
        glfwSwapBuffers(window);
        // Keep running
        glfwPollEvents();
    }

    // When a window and context is no longer needed, destroy it.
    glfwDestroyWindow(window);
    // When you are done using GLFW, typically just before the application exits, you need to terminate GLFW.
    glfwTerminate();
    return 0;
}

void clog(const char* msg) {
    std::cout << msg << std::endl;
}
void cerror(const char* msg) {
    std::cerr << msg << std::endl;
}

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        clog("Key pressed: ");
        clog(std::to_string(key).c_str());

        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}