#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "E_scene.h"
#include "E_object.h"
#include "E_primitives.h"

#include "R_renderer.h"

#include <stdio.h>

static int   SCREEN_WIDTH  = 1200;
static int   SCREEN_HEIGHT = 800;
static char* WINDOW_NAME   = "CUBE";

static GLFWwindow* initialize_glfw(unsigned int width, unsigned int height, const char* title);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void process_input(GLFWwindow* window);

static GLFWwindow* initialize_glfw(unsigned int width, unsigned int height, const char* title)
{
  if (!glfwInit()) 
    return NULL;
   
  // Minimum required version of openGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  // Enable core profile of openGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
static int initialize_opengl(void)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    
    // Optional: Print OpenGL version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    
    return 0;
}

static void process_input(GLFWwindow* window)
{ 
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true); 
}

int main(int argc, char* argv[])
{
  // suppress warnings for now
  (void)argc;
  (void)argv;

  int something_failed = 0;

  GLFWwindow* window = initialize_glfw(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
  if (window == NULL)
    return 1;

  if (initialize_opengl() < 0) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  R_Renderer* renderer    = NULL;
  R_Camera*   camera      = NULL;
  E_Scene*    world_scene = NULL;


  renderer = r_renderer_create();
  if (renderer == NULL) {
    something_failed = 1;
    goto error_cleanup;
  }

  // camera = r_camera_create();
  // if (camera == NULL) {
  //   something_failed = 1;
  //   goto error_cleanup;
  // }

  world_scene = e_scene_create();
  if (world_scene == NULL) {
    something_failed = 1;
    goto error_cleanup;
  }

  while (!glfwWindowShouldClose(window))
  {
    process_input(window);

    //update_scene(&scene);
    //render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

error_cleanup:
  r_renderer_destroy(renderer);
  // r_camera_destroy(camera);
  e_scene_destroy(world_scene);

  glfwDestroyWindow(window);
  glfwTerminate();

  if (something_failed)
    return 1;

  return 0;
}

// THANKS CHAT!
// +-----------------------------------------------------+
// | Application / Game Logic                             |
// | - Game loop, input handling, AI, gameplay systems  |
// +-----------------------------------------------------+
// | Engine / Subsystems                                  |
// | - Scene management (entities, components)          |
// | - Physics, collision, animation                     |
// | - Audio, networking                                 |
// +-----------------------------------------------------+
// | Renderer / Graphics                                  |
// | - Meshes, shaders, textures, materials             |
// | - Cameras, lights, framebuffers                    |
// | - Low-level graphics API (OpenGL, Vulkan, DX)      |
// +-----------------------------------------------------+
// | Platform Abstraction / OS layer                     |
// | - Windowing, input devices, timers                 |
// | - File I/O                                         |
// +-----------------------------------------------------+

// int old_main(void)
// {
//   GLFWwindow* window = initialize_glfw(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
//   if (window == NULL)
//     return 1;




//   // openGL options
//   glEnable(GL_DEPTH_TEST);
//   glEnable(GL_CULL_FACE);
//   glCullFace(GL_BACK);  
//   glClearDepth(1.0f);
//   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//   while (!glfwWindowShouldClose(window))
//   {
//     process_input(window);

//     // clear screen
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     float ff = 20.0f * (float)sin(glfwGetTime());
//     printf("%f", ff);

//     glmc_mat4_identity(model_matrix);
//     update_cube(glfwGetTime());

//     glmc_mat4_identity(view_matrix);
//     glm_lookat((vec3){0.0f, 0.0f, 50.0f}, (vec3){-ff, ff, ff / 2}, (vec3){0.0f, 1.0f, 0.0f}, view_matrix);
//     glmc_perspective(glm_rad(60.0f), ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT), 0.1f, 100.0f, projection_matrix);

//     shader_bind(&shader);

//     // send uniform data
//     shader_send_uniform_int(&shader, debug_colors_draw ? 1 : 0, "debug_color_flag");
//     shader_send_uniform_vec3(&shader, 6, (float*)cube_alternative_color, "debug_color_array");
//     shader_send_uniform_mat4(&shader, model_matrix, "model");
//     shader_send_uniform_mat4(&shader, view_matrix, "view");
//     shader_send_uniform_mat4(&shader, projection_matrix, "projection");

//     // THIS IS LESS EFFICEINT OR SOMETHING // 
//     // glBindBuffer(GL_UNIFORM_BUFFER, grid->UBO);

//     // mat4* matrices = (mat4*)glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
//     // if (matrices) {
//     //   // change first matrix
//     //   for (int i = 0; i < grid->matrix_count; i++) {
//     //     glmc_mat4_copy(grid->model_matrices[i], matrices[i]);
//     //     glmc_translate(matrices[i], (vec3){0.0f, (float)sin(glfwGetTime()) * 5.0f, 0.0f});
//     //   }
      
//     //   // change more matrices as needed...
      
//     //   glUnmapBuffer(GL_UNIFORM_BUFFER);
//     // }

//     // glBindBuffer(GL_UNIFORM_BUFFER, 0);

//     glBindBuffer(GL_UNIFORM_BUFFER, grid->UBO);

//     mat4* matrices = (mat4*)glMapBufferRange(
//         GL_UNIFORM_BUFFER,
//         0,                       // offset
//         grid->matrix_bytes,      // size of the buffer
//         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
//     );

//     if (matrices) {
//         for (int i = 0; i < grid->matrix_count; i++) {
//             glmc_mat4_copy(grid->model_matrices[i], matrices[i]);
//             glmc_translate(matrices[i], (vec3){0.0f, (float)sin(glfwGetTime()), 0.0f});
//         }
//         glUnmapBuffer(GL_UNIFORM_BUFFER);
//     }

//     glBindBuffer(GL_UNIFORM_BUFFER, 0);

    
//     // render
//     mesh_bind(&cube);
//     switch (current_model)
//     {
//       case CUBE:
//         glDrawElements(GL_TRIANGLES,
//                        sizeof(cube_indices) / sizeof(GLuint),
//                        GL_UNSIGNED_SHORT,
//                        0);
//       break;
//       case RUBIX:
//         // Draw all instances in one drwa call
//         glPointSize(5.0f);
//         glDrawElementsInstanced(GL_TRIANGLES,
//                                 sizeof(cube_indices) / sizeof(GLuint),
//                                 GL_UNSIGNED_INT,
//                                 0,
//                                 grid->matrix_count);
//         // glDrawElements(GL_TRIANGLES,
//         //               sizeof(cube_indices) / sizeof(GLushort),
//         //               GL_UNSIGNED_SHORT,
//         //               0);

//         // glmc_translate(model_matrix, (vec3){2.0f, (float)sin(glfwGetTime()), -5.0f});
//         // shader_send_uniform_mat4(&shader, model_matrix, "model");
      
//         // glDrawElements(GL_TRIANGLES,
//         //               sizeof(cube_indices) / sizeof(GLushort),
//         //               GL_UNSIGNED_SHORT,
//         //               0);
//       break;
//     }

//     // swap and poll
//     glfwSwapBuffers(window);
//     glfwPollEvents();
//   }

//   grid_destroy(grid);

//   shader_destroy(&shader);
//   mesh_destroy(&cube);

//   return 0;
// }
