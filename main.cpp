#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace glm;

struct Polygon {
    std::vector<vec2> points;
    float rotation = 0.0f;
    vec2 translation = vec2(0.0f);
    float scale = 1.0f;
    vec2 center = vec2(0.0f);
};

std::vector<Polygon> polygons;
std::vector<vec2> currentPolygon;
int selectedPolygon = -1;
bool isDrawing = false;
int windowWidth = 800, windowHeight = 600;

void renderPolygon(const Polygon& poly, bool selected) {
    if (poly.points.size() < 2) return;
    
    glPushMatrix();
    
    // Apply transformations
    glTranslatef(poly.translation.x, poly.translation.y, 0.0f);
    glTranslatef(poly.center.x, poly.center.y, 0.0f);
    glRotatef(poly.rotation, 0.0f, 0.0f, 1.0f);
    glScalef(poly.scale, poly.scale, 1.0f);
    glTranslatef(-poly.center.x, -poly.center.y, 0.0f);
    
    if (selected) {
        glColor3f(1.0f, 0.0f, 0.0f); // Red for selected
        glLineWidth(3.0f);
    } else {
        glColor3f(0.0f, 1.0f, 0.0f); // Green for others
        glLineWidth(1.0f);
    }
    
    glBegin(GL_LINE_LOOP);
    for (const auto& point : poly.points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw all polygons
    for (int i = 0; i < polygons.size(); i++) {
        renderPolygon(polygons[i], i == selectedPolygon);
    }
    
    // Draw current polygon being drawn
    if (isDrawing && currentPolygon.size() > 0) {
        glColor3f(0.0f, 0.0f, 1.0f); // Blue for drawing
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& point : currentPolygon) {
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }
    
    glFlush();
}

void reshape(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    vec2 mousePos = vec2(xpos, ypos);
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        currentPolygon.push_back(mousePos);
        isDrawing = true;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (isDrawing && currentPolygon.size() >= 3) {
            Polygon newPoly;
            newPoly.points = currentPolygon;
            
            // Calculate center
            vec2 center = vec2(0.0f);
            for (const auto& p : currentPolygon) {
                center += p;
            }
            center /= currentPolygon.size();
            newPoly.center = center;
            
            polygons.push_back(newPoly);
            selectedPolygon = polygons.size() - 1;
            currentPolygon.clear();
            isDrawing = false;
        }
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;
    if (selectedPolygon < 0 || selectedPolygon >= polygons.size()) return;
    
    Polygon& poly = polygons[selectedPolygon];
    
    switch (key) {
        case GLFW_KEY_L:
            poly.rotation += 1.0f; // Rotate counter-clockwise
            break;
        case GLFW_KEY_R:
            poly.rotation -= 1.0f; // Rotate clockwise
            break;
        case GLFW_KEY_UP:
            poly.translation.y -= 1.0f;
            break;
        case GLFW_KEY_DOWN:
            poly.translation.y += 1.0f;
            break;
        case GLFW_KEY_LEFT:
            poly.translation.x -= 1.0f;
            break;
        case GLFW_KEY_RIGHT:
            poly.translation.x += 1.0f;
            break;
        case GLFW_KEY_COMMA:
            poly.scale /= 1.1f; // Scale down 10%
            break;
        case GLFW_KEY_PERIOD:
            poly.scale *= 1.1f; // Scale up 10%
            break;
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, 
        "2D Polygon Drawing and Affine Transformation", nullptr, nullptr);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    glfwSetFramebufferSizeCallback(window, reshape);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    std::cout << "Controls:" << std::endl;
    std::cout << "  Left-click: Add polygon point" << std::endl;
    std::cout << "  Right-click: Finish polygon (min 3 points)" << std::endl;
    std::cout << "  L/R: Rotate counter-clockwise/clockwise" << std::endl;
    std::cout << "  Arrow Keys: Translate" << std::endl;
    std::cout << "  </> : Scale down/up" << std::endl;
    
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}