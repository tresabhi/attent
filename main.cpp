#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

class Attent {
  public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

  private:
  GLFWwindow *window;

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  VkInstance instance;

  void createInstance() {
    // application info; not required but can help the gpu automatically
    // optimize thing or something. sType arbitrary discriminator
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Attent";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // this one the other hand is required and leverages the stuff from above
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // finding what extensions glfw needs within vulkan
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    // creating the instance for real now
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
      throw std::runtime_error("failed to create vulkan instance");
    }

    // getting the extensions is a pain in the butt as we have to first figure
    // out how many there are and then allocate an array to hold them
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // now we allocate and fill
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(
        nullptr, &extensionCount, extensions.data()
    );

    std::cout << "available extensions:\n";

    for (const auto &extension : extensions) {
      std::cout << '\t' << extension.extensionName << '\n';
    }
  }

  void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Attent", nullptr, nullptr);
  }

  void initVulkan() { createInstance(); }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
  }
};

int main() {
  Attent app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}