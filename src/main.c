#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/call.h>
#include <cglm/quat.h>

#include "object.h"
#include "shader.h"
#include "cube.h"

  // MATRIX CHEAT SHEET
  // [00 10 20 30]
  // [01 11 21 31]
  // [02 12 22 32]
  // [03 13 23 33]

  // CPU Frame
  // update_game_logic();           // Positions, rotations
  // dispatch_compute_culling();    // GPU does frustum culling
  // dispatch_compute_animation();  // GPU builds final matrices
  // draw_indirect();              // GPU draws visible objects


typedef enum { IDLE = 0, FORWARD, BACKWARD, TO_LEFT, TO_RIGHT } cube_state;
typedef enum { CUBE = 0, RUBIX } model;

static int  SCREEN_WIDTH  = 800;
static int SCREEN_HEIGHT  = 600;
static char* WINDOW_NAME  = "CUBE";

mat4 model_matrix         = GLM_MAT4_IDENTITY_INIT;
mat4 view_matrix          = GLM_MAT4_IDENTITY_INIT;
mat4 projection_matrix    = GLM_MAT4_IDENTITY_INIT;
versor orientation        = GLM_QUAT_IDENTITY_INIT; // unused for now!

cube_state current_cube_state = IDLE;
model current_model           = CUBE;
float rotation_speed          = 2.0f;
bool debug_colors_draw        = false;

static GLFWwindow* initialize_glfw(unsigned int width, unsigned int height, const char* title);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void process_input(GLFWwindow* window);
static void rotate_cube(cube_state direction);
static void update_cube(double time);

static GLFWwindow* initialize_glfw(unsigned int width, unsigned int height, const char* title)
{
  if (!glfwInit()) 
    return NULL;
   
  // Minimum required version of openGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  // Enable core profile of openGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window;
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  return window;
}
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
  glViewport(0, 0, width, height);
}

static void update_cube(double time)
{
  static float rot_degrees = 0.0f;

  // move the cube right spot
  glmc_translate(model_matrix, (vec3){0.0f, (float)sin(glfwGetTime()), -5.0f});

  if (current_cube_state != IDLE) 
    rot_degrees += rotation_speed;

  switch (current_cube_state)
  {
    case FORWARD:
      glmc_rotate(model_matrix, glm_rad(-rot_degrees), (vec3){1.0f, 0.0f, 0.0f});
    break;
    case BACKWARD:
      glmc_rotate(model_matrix, glm_rad(rot_degrees), (vec3){1.0f, 0.0f, 0.0f});
    break;
    case TO_RIGHT:
      glmc_rotate(model_matrix, glm_rad(rot_degrees), (vec3){0.0f, 1.0f, 0.0f});
    break;
    case TO_LEFT:
      glmc_rotate(model_matrix, glm_rad(-rot_degrees), (vec3){0.0f, 1.0f, 0.0f});
    break;
    case IDLE:
    default:
    break;
  }

#ifdef DEBUGprintf
  glmc_mat4_print(model_matrix, stdout);
  printf("%f", rot_degrees);
  fflush(stdout);
#endif

  if (rot_degrees >= 90.0f) {
    current_cube_state = IDLE;
    rot_degrees = 0.0f;
  }

}

static void rotate_cube(cube_state direction)
{
  if (current_cube_state != IDLE)
    return;
  
  switch (direction)
  {
    case FORWARD:  current_cube_state = FORWARD; break;
    case BACKWARD: current_cube_state = BACKWARD; break;
    case TO_RIGHT: current_cube_state = TO_RIGHT; break;
    case TO_LEFT:  current_cube_state = TO_LEFT; break;
    default: return;
  }
  
}

static void process_input(GLFWwindow* window)
{
  static bool space_held_down = false;
  
  // flag reset block //
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    space_held_down = false;

  // input block // 
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true); 
  
  // change model
  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    current_model = CUBE;
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    current_model = RUBIX;

  // rotate model
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    rotate_cube(FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    rotate_cube(BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    rotate_cube(TO_LEFT);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    rotate_cube(TO_RIGHT);

  // debug part
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !space_held_down) {
    debug_colors_draw ^= 1;
    space_held_down = true;
  }
}


int main(void)
{
  GLFWwindow* window = initialize_glfw(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
  if (window == NULL)
    return 1;

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		fprintf(stderr, "Failed to initialize GLAD!\n");

		glfwTerminate();

		return 1;
	} 

  Shader_program shader;
  if (shader_create(&shader, "res/cube.vert", "res/cube.frag") != 0) {

    fprintf(stderr, "Failed shader creation!\n");

    glfwTerminate();

    return 1;
  }

  // load primitive shapes
  Object cube;
  int result = -1;
  result = object_create(&cube, &shader, cube_attribs, (float*)cube_vertices, cube_indices, 2, 6, 24, 36);
  if (result < 0)
    return 1;

  
#if 0
  float spacing = 1.0f;
  float gap     = 0.0f;

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      for (int k = 0; k < 10; k++) {

        mat4 destination_mat;

        glmc_mat4_identity(destination_mat);
        glmc_translate(destination_mat, (vec3){i*(spacing+gap), j*(spacing+gap), k*(spacing+gap)});

        glmc_mat4_print(destination_mat, stdout);
        
      }
#endif



  // openGL options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);  
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


  while (!glfwWindowShouldClose(window))
  {
    process_input(window);

    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glmc_mat4_identity(model_matrix);
    update_cube(glfwGetTime());

    // camera did not move, so it's (0,0,0) looking at -Z.
    glmc_perspective(glm_rad(60.0f), ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT), 0.1f, 10.0f, projection_matrix);

    shader_bind(&shader);

    // send uniform data
    shader_send_uniform_int(&shader, debug_colors_draw ? 1 : 0, "debug_color_flag");
    shader_send_uniform_vec3(&shader, 6, (float*)cube_alternative_color, "debug_color_array");
    shader_send_uniform_mat4(&shader, model_matrix, "model");
    shader_send_uniform_mat4(&shader, view_matrix, "view");
    shader_send_uniform_mat4(&shader, projection_matrix, "projection");
    
    // render
    switch (current_model)
    {
      case CUBE:
        object_bind(&cube);
        glDrawElements(GL_TRIANGLES,
                      sizeof(cube_indices) / sizeof(GLushort),
                      GL_UNSIGNED_SHORT,
                      0);
      break;
      case RUBIX:
        object_bind(&cube);
        glDrawElements(GL_TRIANGLES,
                      sizeof(cube_indices) / sizeof(GLushort),
                      GL_UNSIGNED_SHORT,
                      0);

        glmc_translate(model_matrix, (vec3){2.0f, (float)sin(glfwGetTime()), -5.0f});
        shader_send_uniform_mat4(&shader, model_matrix, "model");
      
        glDrawElements(GL_TRIANGLES,
                      sizeof(cube_indices) / sizeof(GLushort),
                      GL_UNSIGNED_SHORT,
                      0);
      break;
    }

#ifdef DEBUG
    if (debug_colors_draw)
      printf("DEBUG!\n");
    else
      printf("NDEBUG!\n");
    fflush(stdout);
#endif

    // swap and poll
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  shader_destroy(&shader);
  object_destroy(&cube);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
