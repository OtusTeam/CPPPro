
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
    "gl_Position = projection * vec4( vp, 1.0 );"
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





class BaseObject
{
    public:

    virtual void Update() = 0;
    virtual void Draw() = 0;
    std::vector<float>& GetPoints(){return points;}
    virtual ~BaseObject() = default;

    protected:
    GLuint vbo = 0;GLuint vao = 0;
    std::vector<float> points;
};


class Triangle : public BaseObject
{
    public:
    Triangle()
    {

        points = {
             /*pos*/ -0.5f,0.0f,-0.8f,/*Color*/ 168.0f,57.0f,237.0f,
                     0.0f,0.5f,-0.8f, 232.0f,235.0f,52.0f,
                     0.5f,0.0f,-0.8f, 52.0f,232.0f,235.0f
                   



            };
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
    
        glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_DYNAMIC_DRAW);
    
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_TRUE, 6* sizeof(float), (void*)0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
    
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );

    }
    void Update() override
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_DYNAMIC_DRAW);
    }

    void Draw() override 
    {
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,points.size());
    }



    
    

};


class Ground : public BaseObject
{
    public:
    Ground()
    {

        points = {
             /*pos*/ -1.0f,0.0f,1.0f,/*Color*/ 168.0f,57.0f,237.0f,
                     -1.0f,0.0f,-1.0f, 232.0f,235.0f,52.0f,

                     -1.0f,0.0f,-1.0f, 52.0f,232.0f,235.0f,
                      1.0f,0.0f,-1.0f, 52.0f,232.0f,235.0f,

                      1.0f,0.0f,-1.0f, 52.0f,232.0f,235.0f,
                      1.0f,0.0f, 1.0f, 232.0f,235.0f,52.0f,

                      1.0f,0.0f, 1.0f, 232.0f,235.0f,52.0f,
                     -1.0f,0.0f,1.0f,  168.0f,57.0f,237.0f
                      

                   



            };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
    
        glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_DYNAMIC_DRAW);
    
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_TRUE, 6* sizeof(float), (void*)0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
    
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );

    }
    void Update() override
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(float),points.data(),GL_DYNAMIC_DRAW);
    }

    void Draw() override 
    {
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES,0,points.size());
    }

    
    

};

std::vector<BaseObject*> objects;

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


    for(auto o : objects){
        std::vector<float>& points = o->GetPoints();

        for(int i = 0; i <= points.size() - 6;i += 6){
            tmp.x = points[i];
            std::cout << points[i] << std::endl;
            tmp.y = points[i+1];
            tmp.z = points[i+2];
            p_result = tmp * t;

            points[i] = p_result.x;
            points[i+1] = p_result.y;
            points[i+2] = p_result.z;
            std::cout << points[i] << std::endl;

        }
    }
        
    
   
}

void GLMScale(float ratio)
{
    glm::mat4 s = glm::mat4(1.0);
    s = glm::scale(s,{ratio,ratio,ratio});
    
    glm::vec4 tmp;
    glm::vec4 p;

    for(auto o : objects){

        std::vector<float>& points = o->GetPoints();  

        for(int i = 0; i <= points.size() - 6;i += 6){
            tmp.x = points[i];
            tmp.y = points[i+1];
            tmp.z = points[i+2];
            tmp.w = 1.0;

            p = tmp * s;

            points[i] = p.x;
            points[i+1] = p.y;
            points[i+2] = p.z;
          
        }
    }
        
    
   
}

void MoveY(float step)
{
    
    glm::vec4 tmp;
    
    for(auto o : objects){

        std::vector<float>& points = o->GetPoints();  

        for(int i = 0; i <= points.size() - 6;i += 6){
            
            tmp.y = points[i+1];
            tmp.y += step;
            points[i+1] = tmp.y;
         

          
        }
    }

   
}

void MoveX(float step)
{
    
    glm::vec4 tmp;
    
    for(auto o : objects){

        std::vector<float>& points = o->GetPoints();  

        for(int i = 0; i <= points.size() - 6;i += 6){
            
            tmp.x = points[i];
            tmp.x += step;
            points[i] = tmp.x;
         

          
        }
    }

   
}



void AppUpdateNDraw()
{
    for(int i = 0; i < objects.size();++i){
        objects[i]->Update();
        objects[i]->Draw();
    }
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
    

    Triangle* t = new Triangle();
    Ground* g = new Ground();

    objects.push_back(t);
    objects.push_back(g);


    while (!glfwWindowShouldClose(window)) 
    {

        
        glfwPollEvents();

        
        int win_h,win_w;
        glfwGetWindowSize(window,&win_h,&win_w);
        glViewport(0,0,win_h,win_w);
        
        
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        


        glUseProgram(shader_program);
        
        if(glfwGetKey(window,GLFW_KEY_A)){
            ApplyTransform(rotate_y_1deg_left);
        }

        if(glfwGetKey(window,GLFW_KEY_D)){
            ApplyTransform(rotate_y_1deg_right);
        }

        if(glfwGetKey(window,GLFW_KEY_W)){
            GLMScale(1.01);
        }

        if(glfwGetKey(window,GLFW_KEY_S)){
            GLMScale(0.9888);
        }

        if(glfwGetKey(window,GLFW_KEY_UP)){
            MoveY(-0.01f);
            
        }

        if(glfwGetKey(window,GLFW_KEY_DOWN)){
            MoveY(0.01f);
            
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT)){
            MoveX(0.01f);
            
        }

        if(glfwGetKey(window,GLFW_KEY_RIGHT)){
            MoveX(-0.01f);
        }

        if(glfwGetKey(window,GLFW_KEY_Q)){
            ApplyTransform(rotate_x_1deg);
        }

        if(glfwGetKey(window,GLFW_KEY_E)){
            ApplyTransform(rotate_x_minus1deg);
        }

        GLint uloc = glGetUniformLocation(shader_program,"projection");

        if(uloc == -1){
            std::cout << "UNABLE TO LOCATE PROJECTION!\n";
        }

        
        //glm::mat4 i = glm::mat4(1.0f);
        glm::mat4 i = glm::infinitePerspective(glm::degrees(45.0f),(float)win_w / (float)win_h,0.01f);
        glUniformMatrix4fv(uloc,1,GL_FALSE,glm::value_ptr(i));
        
        AppUpdateNDraw();

        
        
        glfwSwapBuffers(window);
        
        

        
       
        
    }

    glfwTerminate(); 
    return 0; 
}