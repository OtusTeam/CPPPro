
#include "glad.h"
#include <GLFW/glfw3.h> 

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
GLuint vbo_edges = 0;GLuint vao_edges = 0;


std::vector<float> points = {
             /*pos*/ -0.5f,0.0f,-0.5f,/*Color*/ 168.0f,57.0f,237.0f,
                     0.0f,0.5f,-0.5f, 168.0f,57.0f,237.0f,
                     0.5f,0.0f,-0.5f, 168.0f,57.0f,237.0f

                    



};





int main(void)
{
    
    
    GLFWwindow* window; 
    int err;
    
    if (!glfwInit()) 
        return -1; 

   
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); 
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
    
    glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_STATIC_DRAW);
    
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