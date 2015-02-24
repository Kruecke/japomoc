#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

static void error_callback(int error, const char *description) {
    std::cerr << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char **argv) {
    // Initialize GLFW
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    struct eos_glfw { ~eos_glfw() {glfwTerminate();} } eos_terminate;

    // Create window with OpenCL context
    auto window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(800, 600, "Test", nullptr, nullptr), glfwDestroyWindow);
    if (window == nullptr)
        return 1;

    // Make the window context current
    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);

    // Set callback function for inputs
    glfwSetKeyCallback(window.get(), key_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window.get())) {
        // Get size of framebuffer
        int width, height;
        float ratio;
        glfwGetFramebufferSize(window.get(), &width, &height);
        ratio = width / (float) height;
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glRotatef((float) (glfwGetTime() * 50), 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.6f, -0.4f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.6f, -0.4f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.6f, 0.0f);
        glEnd();

        // Swap buffers and poll events
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }

    return 0;
}
