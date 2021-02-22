#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Projections
static glm::mat4 model = glm::mat4( 1.0f ); // Create a matrix for all of the local transformations of the objects (Used to translate local coords to world coords)
static glm::mat4 view;						// Create the view matrix to move from world coords to cameraspace/view coords
static glm::mat4 projection;				// Create the projection matrix to project objects onto a perspective view