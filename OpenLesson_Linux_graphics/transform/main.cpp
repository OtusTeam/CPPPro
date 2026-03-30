
#include "glad.h"
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <thread>

using namespace std::chrono_literals;
//  g++ *.cpp *.c -lglfw -lGL -o gl.exe
const char* vertex_shader =
"#version 410 core\n"
"layout (location = 0) in vec3 vp;"
"layout (location = 1) in vec3 v_color;"
"uniform mat4 projection;"
"out vec4 vertex_out_color;"
"void main() {"
    "vec4 vp_ext = vec4(vp,1.0);"
    "gl_Position = vec4( vp, 1.0 );"
    "vec3 v_color_normalized = normalize(v_color);"
    "vertex_out_color = vec4(v_color_normalized,1.0);"
"}";

const char* fragment_shader =
"#version 410 core\n"
"in vec4  vertex_out_color;"
"out vec4 FragColor;"
"void main() {"
    "FragColor = vertex_out_color;"
    
"}";


GLuint vbo = 0;GLuint vao = 0;



std::vector<float> points = {
             /*pos*/ -0.5f,0.0f,0.0f,/*Color*/ 168.0f,57.0f,237.0f,
                     0.0f,0.5f,0.0f, 232.0f,235.0f,52.0f,
                     0.5f,0.0f,0.0f, 52.0f,232.0f,235.0f

                    



};

std::vector<GLfloat> rotate_x_1deg = { 1.0f,0.0f,0.0f,
                                              0.0f,0.99985f,-0.01745f,
                                              0.0f,0.01745f,0.99985f};
                                              
std::vector<GLfloat> rotate_x_minus1deg = { 1.0f,0.0f,0.0f,
                                              0.0f,0.99985f, 0.01745f,
                                              0.0f,-0.01745f,0.99985f};

std::vector<GLfloat> rotate_z_minus1deg = { 0.99985f,-0.01745f,0.0f,
                                              0.01745f,0.99985f, 0.0f,
                                              0.0f, 0.0f,1.0f}; 
                                              
std::vector<GLfloat> rotate_z_1deg = { 0.99985f,0.01745f,0.0f,
                                      -0.01745f,0.99985f, 0.0f,
                                              0.0f, 0.0f,1.0f};


std::vector<GLfloat> rotate_y_1deg_left = { 0.9998f,0.0f,0.0175,
                                      0.0f,1.0f,0.0f,
                                      -0.0175f,0.0f,0.9998f};


std::vector<GLfloat> rotate_y_1deg_right = { 0.9998f,0.0f,-0.0175,
                                      0.0f,1.0f,0.0f,
                                      0.0175f,0.0f,0.9998f};                                      


void ApplyTransform(std::vector<GLfloat>& transform)
{
    glm::vec3 tmp;
    glm::vec3 p_result;
    glm::mat3x3 t = glm::make_mat3x3(transform.data());

    

    for(int i = 0; i <= points.size() - 6;i += 6){
        tmp.x = points[i];
        tmp.y = points[i+1];
        tmp.z = points[i+2];
        p_result = tmp * t;

        points[i] = p_result.x;
        points[i+1] = p_result.y;
        points[i+2] = p_result.z;

    }

    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindVertexArray(vao);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float) * points.size(),points.data());
   
}


void ApplyTransformGLMYLeft()
{
    glm::vec3 tmp;
    glm::vec3 p_result;
    

    glm::mat4 ry = glm::mat4(1.0f);
    ry = glm::rotate(ry,glm::radians(0.1f),glm::vec3(0.0f,1.0f,0.0f));

    glm::mat3x3 t = glm::mat3(ry);

    for(int i = 0; i <= points.size() - 6;i += 6){
        tmp.x = points[i];
        tmp.y = points[i+1];
        tmp.z = points[i+2];
        p_result = tmp * t;

        points[i] = p_result.x;
        points[i+1] = p_result.y;
        points[i+2] = p_result.z;

    }

    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindVertexArray(vao);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float) * points.size(),points.data());
   
}

void ApplyTransformGLMYRight()
{
    glm::vec3 tmp;
    glm::vec3 p_result;
    

    glm::mat4 ry = glm::mat4(1.0f);
    ry = glm::rotate(ry,glm::radians(-0.1f),glm::vec3(0.0f,1.0f,0.0f));

    glm::mat3x3 t = glm::mat3(ry);

    for(int i = 0; i <= points.size() - 6;i += 6){
        tmp.x = points[i];
        tmp.y = points[i+1];
        tmp.z = points[i+2];
        p_result = tmp * t;

        points[i] = p_result.x;
        points[i+1] = p_result.y;
        points[i+2] = p_result.z;

    }

    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindVertexArray(vao);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float) * points.size(),points.data());
   
}
                                              
int main(void)
{
    
    
    GLFWwindow* window; 
    int err;
    
    if (!glfwInit()) 
        return -1; 

   
    window = glfwCreateWindow(640, 480, "Transforms", NULL, NULL); 
    if (!window) 
    {
        glfwTerminate(); 
        return -1; 
    }

    
    
   
    glfwMakeContextCurrent(window);

    int glad_v = gladLoadGL();
    
    if(glad_v){
        std::cout << "Loaded OpenGL!" << std::endl;
    }
    
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    
    glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_TRUE, 6* sizeof(float), (void*)0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
    
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    
    
    
    

    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vs, 1, &vertex_shader, NULL );
    glCompileShader( vs );
    GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fs, 1, &fragment_shader, NULL );
    glCompileShader( fs );

    GLuint shader_program = glCreateProgram();
    glAttachShader( shader_program, vs );
    glAttachShader( shader_program, fs );
    
    glLinkProgram( shader_program );
    
    
    
    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) 
    {

        
        glfwPollEvents();

        
        int win_h,win_w;
        glfwGetWindowSize(window,&win_h,&win_w);
        glViewport(0,0,win_h,win_w);
        
        
        if(glfwGetKey(window,GLFW_KEY_A)){
            ApplyTransform(rotate_z_minus1deg);
        }

        if(glfwGetKey(window,GLFW_KEY_D)){
            ApplyTransform(rotate_z_1deg);
        }

        if(glfwGetKey(window,GLFW_KEY_Q)){
            ApplyTransform(rotate_y_1deg_left);
        }
        
        if(glfwGetKey(window,GLFW_KEY_E)){
            ApplyTransform(rotate_y_1deg_right);
        }

        if(glfwGetKey(window,GLFW_KEY_W)){
            ApplyTransform(rotate_x_1deg);
        }
        
        if(glfwGetKey(window,GLFW_KEY_S)){
            ApplyTransform(rotate_x_minus1deg);
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT)){
            ApplyTransformGLMYLeft();
        }

        if(glfwGetKey(window,GLFW_KEY_RIGHT)){
            ApplyTransformGLMYRight();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        


        glUseProgram(shader_program);
        
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,points.size());
              

        
        
        glfwSwapBuffers(window);
        
        

        
       
        
    }

    glfwTerminate(); 
    return 0; 
}