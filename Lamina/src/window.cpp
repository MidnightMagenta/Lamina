#include "../Lamina/include/window.hpp"

bool lm::Window::CreateWindow(lm::vec2<int> windowSize, std::string windowName, int windowHints, int multisamplingLevel)
{
	bool fullScreen = false;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, multisamplingLevel);

	if (windowHints == NULL) glfwDefaultWindowHints();
	else
	{
		if (windowHints & LM_WINDOW_RESIZABLE)			glfwWindowHint(GLFW_RESIZABLE, true);
		else											glfwWindowHint(GLFW_RESIZABLE, false);
		if (windowHints & LM_WINDOW_VISIBLE)			glfwWindowHint(GLFW_VISIBLE, true);
		else											glfwWindowHint(GLFW_VISIBLE, false);
		if (windowHints & LM_WINDOW_DECORATED)			glfwWindowHint(GLFW_DECORATED, true);
		else											glfwWindowHint(GLFW_DECORATED, false);
		if (windowHints & LM_WINDOW_FOCUSED)			glfwWindowHint(GLFW_FOCUSED, true);
		else											glfwWindowHint(GLFW_FOCUSED, false);
		if (windowHints & LM_WINDOW_MAXIMIZED)			glfwWindowHint(GLFW_MAXIMIZED, true);
		else											glfwWindowHint(GLFW_MAXIMIZED, false);
		if (windowHints & LM_WINDOW_DOUBLE_BUFFER)		glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		else											glfwWindowHint(GLFW_DOUBLEBUFFER, false);
		if (windowHints & LM_WINDOW_FULLSCREEN)			fullScreen = true;
		else											fullScreen = false;
		if (windowHints & LM_WINDOW_SCALE_TO_MONITOR)	glfwWindowHint(GLFW_SCALE_TO_MONITOR, true);
		else											glfwWindowHint(GLFW_SCALE_TO_MONITOR, false);
	}


	if(fullScreen) window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), glfwGetPrimaryMonitor(), NULL);
	else window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window - window is NULL" << std::endl;
		return false;
	}
	else return true;
}

void lm::Window::Clear(lm::Color color)
{
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

	lm::ColorF floatColor = lm::GetFloatColor(color);
	glClearColor(floatColor.r, floatColor.g, floatColor.b, floatColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template<typename T>
void lm::Window::Draw(T target)
{
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

	// "Just delete it"
	/*if (std::is_same(T, lm::Rectangle))
	{

	}
	else if (std::is_same(T, lm::Triangle))
	{

	}
	else std::cout << "Undefined drawing type" << std::endl;*/
}