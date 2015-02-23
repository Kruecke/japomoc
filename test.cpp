#include <GLFW/glfw3.h>

int main(int argc, char **argv) {
    // Initialize GLFW
    if (!glfwInit())
        return 1;
    struct eos_glfw { ~eos_glfw() {glfwTerminate();} } eos_terminate;

    // Create window with OpenCL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    if (!window)
        return 1;

    // !?
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // TODO: Render
        
        // Swap buffers
        glfwSwapBuffers(window);

        // Poll events
        glfwPollEvents();
    }

    return 0;
}
