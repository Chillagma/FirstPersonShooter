#define TINYOBJLOADER_IMPLEMENTATION

#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>


#include <freeglut.h>
//#include<glad.h>
#include <glext.h>


#include "loadpng.h"
#include "process_image.h"
#include "gl_texture.h"
#include<iostream>
#include<tiny_obj_loader.h>

//#include<idea.glsl>
//test
//another test
//another test too



void timer(int);

//test
#define WIDTH 600
#define HEIGHT 600
#ifdef GL_ES
precision mediump float;
#endif
/*
const GLchar* vertex_shader =
"#version 150 core\n"
"in vec2 position;"
"void main()"
"{"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";
const GLchar* fragment_shader =
"#version 150 core\n"
"out vec4 outColor;"
"uniform vec3 triangleColor;"
"void main()"
"{"
"    outColor = vec4(triangleColor, 1.0);"
"}";*/
float i = 0.0;
float j = -200.0;
int iRandom = (rand() % 555) + 1;
class aclass {
    

    tinyobj::ObjReader reader;

public:
    const tinyobj::attrib_t attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t, std::allocator<tinyobj::shape_t>> shapes = reader.GetShapes();
    const std::vector<tinyobj::material_t, std::allocator<tinyobj::material_t> >
        materials = reader.GetMaterials();
    std::vector<GLdouble*> function() {
        std::string inputfile = "Part.obj";
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "./";  // Path to material files

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(inputfile, reader_config)) {
            if (!reader.Error().empty()) {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty()) {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();
        
        // Loop over shapes
        std::vector<GLdouble*> container, container2, container3;
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy =
                        //Random = (rand() % 10) + 1;
                        attrib.vertices[3 * size_t(idx.vertex_index)  + 1] *sin(s);
                    tinyobj::real_t vz =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                    ;
                    container.push_back(new GLdouble[3]{ vx, vy, vz });
                 //  container.push_back(new GLdouble[3]{ abs(sin(i)) + 5,vy , vz });
                   // container.push_back(new GLdouble[3]{vx ,vy , abs(sin(i)) + 5 });
                   // glColor4f(0, cos(i/2) * 255, sin(i/2)*255, 0.5);
                    
                    // container2.push_back(vy);
                     //container3.push_back(vz);


                     //  container.push_back(v);

                     // std::cout << val << std::endl;
                     // return val;

                     ///  std::cout << vx << std::endl;

                     //  std::cout << vx << std::endl;

                     // Check if `normal_index` is zero or positive. negative = no normal
                     // data
                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx =
                            attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny =
                            attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz =
                            attrib.normals[3 * size_t(idx.normal_index) + 2];
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no
                    // texcoord data
                    if (idx.texcoord_index >= 0) {
                        tinyobj::real_t tx =
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty =
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }

                    // Optional: vertex colors
                    // tinyobj::real_t red   =
                    // attrib.colors[3*size_t(idx.vertex_index)+0]; tinyobj::real_t
                    // green = attrib.colors[3*size_t(idx.vertex_index)+1];
                    // tinyobj::real_t blue =
                    // attrib.colors[3*size_t(idx.vertex_index)+2];
                }
                index_offset += fv;

                // per-face material
                shapes[s].mesh.material_ids[f];
            }
        }
        return (container);
    };
};

class bclass {


    tinyobj::ObjReader reader;

public:
    const tinyobj::attrib_t attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t, std::allocator<tinyobj::shape_t>> shapes = reader.GetShapes();
    const std::vector<tinyobj::material_t, std::allocator<tinyobj::material_t> >
        materials = reader.GetMaterials();
    std::vector<GLdouble*> function() {
       // i++;
        std::string inputfile = "wooden_sphere.obj";
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "./";  // Path to material files

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(inputfile, reader_config)) {
            if (!reader.Error().empty()) {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty()) {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        // Loop over shapes
        std::vector<GLdouble*> container, container2, container3;
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 0];//+25 * cos(s * ( 60.0f));
                    tinyobj::real_t vy =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 1];// * sin(s * ( 60.0f))*10;
                    tinyobj::real_t vz =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 2];// *cos(s * (60.0f));
                    ;
                    container.push_back(new GLdouble[3]{ vx, vy, vz });
                    //  container.push_back(new GLdouble[3]{ abs(sin(i)) + 5,vy , vz });
                      // container.push_back(new GLdouble[3]{vx ,vy , abs(sin(i)) + 5 });
                      // glColor4f(0, cos(i/2) * 255, sin(i/2)*255, 0.5);

                       // container2.push_back(vy);
                        //container3.push_back(vz);


                        //  container.push_back(v);

                        // std::cout << val << std::endl;
                        // return val;

                        ///  std::cout << vx << std::endl;

                        //  std::cout << vx << std::endl;

                        // Check if `normal_index` is zero or positive. negative = no normal
                        // data
                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx =
                            attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny =
                            attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz =
                            attrib.normals[3 * size_t(idx.normal_index) + 2];
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no
                    // texcoord data
                    if (idx.texcoord_index >= 0) {
                        tinyobj::real_t tx =
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty =
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }

                    // Optional: vertex colors
                    // tinyobj::real_t red   =
                    // attrib.colors[3*size_t(idx.vertex_index)+0]; tinyobj::real_t
                    // green = attrib.colors[3*size_t(idx.vertex_index)+1];
                    // tinyobj::real_t blue =
                    // attrib.colors[3*size_t(idx.vertex_index)+2];
                }
                index_offset += fv;

                // per-face material
                shapes[s].mesh.material_ids[f];
            }
        }
        return (container);
    };
};

class Model {
    aclass e;
   
private:
    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int edge, int* vertices, int* texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };
    std::vector<float*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;
    GLuint list;
    GLuint list2;
   
public:
    void load(const char* filename) {
        
        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);
        if (!in.is_open()) {
            printf("Cannot load model %s\n", filename);
            return;
        }
        while (!in.eof()) {
            std::getline(in, line);
            lines.push_back(line);
        }
        in.close();
        float a, b, c;
        for (std::string& line : lines) {
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);

                    vertices.push_back(new float[3]{ a, b, c});
                }
                else if (line[1] == 't') {
                    sscanf(line.c_str(), "vt %f %f", &a, &b);
                    texcoords.push_back(new float[2]{ a, b });
                    
                }
                else {
                    sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                    normals.push_back(new float[3]{ a, b, c });
                }
            }
            else if (line[0] == 'f') {
                int v0, v1, v2, t0, t1, t2, n;
                sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
                int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
                faces.push_back(Face(3, v, NULL, n - 1));
                glVertex3f(v0, v1, v2);
            }
        }

        bclass d;
        
        std::vector<GLdouble*> containerd = d.function();
        
        
        aclass e;
        e.function();
        std::vector<GLdouble*> container = e.function();
        
      
            //std::cout << val << std::endl;
        //std::cout << e.function() << std::endl;
        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        //glEnable(GL_NORMALIZE);
        glBegin(GL_POLYGON);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       
        glEnable(GL_BLEND);
        for (Face& face : faces) {
          //  glutSpecialFunc(SpecialInput);
           
            for (GLdouble* val : container)
            {
                //glMultMatrixd(val);
             //   glColorMask(true, GL_TRUE, GL_FALSE, GL_TRUE);
                /*if (j > 10) {
                    glColorMask(true, GL_FALSE, GL_FALSE, GL_TRUE);
                }
                if (j < 10) {
                    glColorMask(true, GL_TRUE, GL_FALSE, GL_TRUE);
                }*/
                //  glColor4f(255, 0, 0,0.5);
                //  std::cout << *val << std::endl;
                //  GLdouble* ref = val;
                 // GLdouble ref2 = *val;

             // glVertex3f(*val+20,*val,*val);
                glVertex3dv(val);
                
               // glTexCoord3f(2000, 2000, 2000);
                if ((int)*val >cos(*val)) {
                    glColor4f(0, 0, 0, 1);
                    //std::cout << *val << std::endl;
                    // glVertex3d(10,10,10);
                }
                if ((int)(val) % 3 == 0) {
                    glColor4f(0, 255, 255, 1);

                }
                if ((int)val % 7 == 0) {
                    glColor4f(255, 0, 255, 1);
                }

               
            }
            if (face.normal >= 0){
               
                glNormal3fv(normals[face.normal]);
            }

            else
            glEnable(GL_LIGHTING);
            
            for (int i = 0; i < face.edge; i++)
                if (face.vertices[i] > 0) {
                   
                
                   // glVertex3fv(vertices[face.vertices[i]]);
                   // std::cout << vertices[face.vertices[i]] << std::endl;
                    }
                     
                   
                   
         
          
            glEnd();
            if (face.normal == -1)
                 glDisable(GL_LIGHTING);
        }
        glEndList();
        list2 = glGenLists(1);
        glNewList(list2, GL_COMPILE);
        //glEnable(GL_NORMALIZE);
        glBegin(GL_POLYGON);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (Face& face : faces) {
            //  glutSpecialFunc(SpecialInput);
            glBegin(GL_QUADS);
            for (GLdouble* val : containerd)
            {
                //glMultMatrixd(val);
             //   glColorMask(true, GL_TRUE, GL_FALSE, GL_TRUE);
                /*if (j > 10) {
                    glColorMask(true, GL_FALSE, GL_FALSE, GL_TRUE);
                }
                if (j < 10) {
                    glColorMask(true, GL_TRUE, GL_FALSE, GL_TRUE);
                }*/
                //  glColor4f(255, 0, 0,0.5);
                //  std::cout << *val << std::endl;
                //  GLdouble* ref = val;
                 // GLdouble ref2 = *val;

             // glVertex3f(*val+20,*val,*val);

               
                
                glVertex3dv(val );
                
                
                //d.function();
               
               
                // glTexCoord3f(2000, 2000, 2000);
                if ((int)*val >  cos(*val)) {
                    glColor4f(0, 0, 0, 1);
                    // glVertex3d(10,10,10);
                }
                if ((int)(val) % 3 == 0) {
                    glColor4f(0, 255, 255, 1);

                }
                if ((int)val % 7 == 0) {
                    glColor4f(255, 0, 255, 1);
                }


            }
            if (face.normal >= 0) {

                glNormal3fv(normals[face.normal]);
            }

            else
                glEnable(GL_LIGHTING);

            for (int i = 0; i < face.edge; i++)
                if (face.vertices[i] > 0) {


                    // glVertex3fv(vertices[face.vertices[i]]);
                    // std::cout << vertices[face.vertices[i]] << std::endl;
                }





            glEnd();
            if (face.normal == -1)
                glDisable(GL_LIGHTING);
        }
        glEndList();
        printf("Model: %s\n", filename);
        printf("Vertices: %d\n", vertices.size());
        printf("Texcoords: %d\n", texcoords.size());
        printf("Normals: %d\n", normals.size());
        printf("Faces: %d\n", faces.size());


     


        for (float* f : vertices)
            delete f;
        vertices.clear();
        for (float* f : texcoords)
            delete f;
        texcoords.clear();
        for (float* f : normals)
            delete f;
        normals.clear();
        faces.clear();
    }
    void draw() { glCallList(list); }
    void draw2() { glCallList(list2); }
};

Model model;
GLuint texture[6];
GLuint LoadTexture(const char* filename, int width, int height) {
    GLuint texture;
    unsigned char* data;
    FILE* file;

    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    return texture;
}
void FreeTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}


void skybox(void) {
    float x = 0;
    float y = 0;
    float z = 0;
    float width = 100;
    float height = 100;
    float length = 100;
    // Bind the BACK texture of the sky map to the BACK side of the cube
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // Center the skybox
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;
    glBegin(GL_QUADS);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();
    //glBindTexture( GL_TEXTURE_CUBE_MAP, texture[0] ); //bind the texture
    //glRotatef( angle, 1.0f, 1.0f, 1.0f );
    //glutSolidSphere(2, 40, 40);
}
void disply(void) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
   // cam.camera();
    gluLookAt (20.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    texture[0] = LoadTexture("back.jpg", 256, 256); //load the texture
    texture[1] = LoadTexture("front.jpg", 256, 256); //load the texture
    texture[2] = LoadTexture("left.jpg", 256, 256); //load the texture
    texture[3] = LoadTexture("right.jpg", 256, 256); //load the texture
    texture[4] = LoadTexture("bottom.jpg", 256, 256); //load the texture
    texture[5] = LoadTexture("top.jpg", 256, 256); //load the texture
    glEnable(GL_TEXTURE_2D); //enable 2D texturing
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
   glEnable(GL_TEXTURE_GEN_T);
    skybox();
    for (int i = 0; i < 6; i++) {
        FreeTexture(texture[i]);
    }
    glutSwapBuffers();
    //angle = angle + 0.5;
   // cam.incAngle();
}
void init() {
   
   //_skybox[0] = Load_Texture(0, 0);
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
  //  glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = { -1.0f,j, 100.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glutTimerFunc(1000, timer, 0);
    model.load("Lowpoly_tree.obj");
    //d.function();
 
  
  
}

void motion() {
    if ((GLUT_KEY_DOWN)) {
        i--;
       
        //glTranslatef(x, -30.0f, -200.0f);
    }
    else if((GLUT_KEY_DOWN)) {
        i++;

        //glTranslatef(x, -30.0f, -200.0f);
    }
   // glutPostRedisplay();
}
void SpecialInput(int key, int x, int y)
{
    aclass e;
    e.function();
    std::vector<GLdouble*> container = e.function();
    /*if (true) {
        j = j + 5;
    }*/
    switch (key)
    {
    case GLUT_KEY_UP:
        //do something here
        model.load("Lowpoly_tree.obj");
        j=j+5;
        break;
    case GLUT_KEY_DOWN:
        //do something here
        model.load("Lowpoly_tree.obj");
        j=j-5;
        break;
    case GLUT_KEY_LEFT:
        //do something here
       
        
       


        //std::cout << val << std::endl;
    //std::cout << e.function() << std::endl;
     /*  GLuint list;
       list = glGenLists(1);
       glNewList(list, GL_COMPILE);
        glEnable(GL_NORMALIZE);
        glBegin(GL_POLYGON);


        glEnable(GL_BLEND);*/ 
         i++;
         model.load("Lowpoly_tree.obj");
        // glColorMask(true, GL_FALSE, GL_FALSE, GL_FALSE);
       /*  for (GLdouble* val : container)
         {
             // glMultMatrixd(val);


               glColorMask(true,GL_FALSE, GL_FALSE, GL_FALSE);
           
             //  std::cout << *val << std::endl;
             //  GLdouble* ref = val;
              // GLdouble ref2 = *val;
             glVertex3dv(val);


         }*/
        break;
    case GLUT_KEY_RIGHT:
        //do something here
        i--;
        model.load("Lowpoly_tree.obj");
        break;
    }
    glutPostRedisplay();
}
/*void catchKey(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) {
        x--;
        //key = x;
    }



}*/


int x = 0;
bool toggle = true;
void display() {
   
    //i++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // Store the current matrix
    glPushMatrix();

    // Reset and transform the matrix.
    glLoadIdentity();
    
    /*gluLookAt(
        0, 0, 0,
        camera->x(), camera->y(), camera->z(),
        0, 1, 0);*/

        // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    ///comment for github
    // Just in case we set all vertices to white.
    glColor4f(1, 1, 1, 1);

    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    //cam.camera();
    gluLookAt(20.0+i, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    texture[0] = LoadTexture("back.jpg", 16, 16); //load the texture
    texture[1] = LoadTexture("front.jpg", 16, 16); //load the texture
    texture[2] = LoadTexture("left.jpg", 16, 16); //load the texture
    texture[3] = LoadTexture("right.jpg", 16, 16); //load the texture
    texture[4] = LoadTexture("bottom.jpg", 16, 16); //load the texture
    texture[5] = LoadTexture("top.jpg", 16, 16); //load the texture
    glEnable(GL_TEXTURE_2D); //enable 2D texturing
  // glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
   // glEnable(GL_TEXTURE_GEN_T);
    skybox();
    for (int i = 0; i < 6; i++) {
        FreeTexture(texture[i]);
    }
    
    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
   //motion();
    //catchKey(0,0,0);
    /*if ((GLUT_KEY_UP)) {
       // x++;


        //glTranslatef(x, -30.0f, -200.0f);
    }*/
    //i++;
    //glPushMatrix();

  
    
    glTranslatef( x, -10.0f, j);
    
 glPushMatrix();
    iRandom = (rand()%5)+1;
      if (x > 20) {
        toggle = false;
    }
    if (x <- 20) {
        toggle = true;
    }
    if (toggle == true) {
        x++;
    }
    if (toggle == false) {
        x--;
    }
    glPopMatrix();
  glEnable(GL_COLOR_MATERIAL);
  
   // glPopAttrib();*/
  //  glColor4f(0, 0, 255, 0.1);
    glRotatef(30.0f, 1.0f, -1.0f, 0.0f);
  //  glRotatef(30.0f + x * 20, 1.0f, -1.0f, 0.0f);

    //use this for collision
  //  
       // vCamera.y += 8.0f * fElapsedTime;
  
    model.draw();
  //  glutTimerFunc(1000, timer, 0);
    glPushMatrix();
   
        glTranslatef(-20, -10.0f + i *5, j+225);
   
    
    //d.function();
  
  
    model.draw2();
   
    glPopMatrix();
    glutSwapBuffers();
}

/*void keyUp(unsigned char key, int x, int y)
{

    x--;
    key = x;


}*/
/*attribute vec4 a_position;
uniform mat4 u_mvp;
uniform float u_timer;*/


float skyboxVertices[] =
{
    //   Coordinates
    -1.0f, -1.0f,  1.0f,//        7--------6
     1.0f, -1.0f,  1.0f,//       /|       /|
     1.0f, -1.0f, -1.0f,//      4--------5 |
    -1.0f, -1.0f, -1.0f,//      | |      | |
    -1.0f,  1.0f,  1.0f,//      | 3------|-2
     1.0f,  1.0f,  1.0f,//      |/       |/
     1.0f,  1.0f, -1.0f,//      0--------1
    -1.0f,  1.0f, -1.0f
};


unsigned int skyboxIndices[] =
{
    // Right
    1, 2, 6,
    6, 5, 1,
    // Left
    0, 4, 7,
    7, 3, 0,
    // Top
    4, 5, 6,
    6, 7, 4,
    // Bottom
    0, 3, 2,
    2, 1, 0,
    // Back
    0, 1, 5,
    5, 4, 0,
    // Front
    3, 7, 6,
    6, 2, 3
};
using namespace std;

int main(int argc, char** argv) {
   /* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // Store the current matrix
    glPushMatrix();

    // Reset and transform the matrix.
    glLoadIdentity();
    /*gluLookAt(
        0, 0, 0,
        camera->x(), camera->y(), camera->z(),
        0, 1, 0);*/

    // Enable/Disable features
    /*glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    // Just in case we set all vertices to white.
    glColor4f(1, 1, 1, 1);

    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    //cam.camera();
    gluLookAt (20.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    texture[0] = LoadTexture("back.jpg", 256, 256); //load the texture
    texture[1] = LoadTexture("front.jpg", 256, 256); //load the texture
    texture[2] = LoadTexture("left.jpg", 256, 256); //load the texture
    texture[3] = LoadTexture("right.jpg", 256, 256); //load the texture
    texture[4] = LoadTexture("bottom.jpg", 256, 256); //load the texture
    texture[5] = LoadTexture("top.jpg", 256, 256); //load the texture
    glEnable(GL_TEXTURE_2D); //enable 2D texturing
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    skybox();
    for (int i = 0; i < 6; i++) {
        FreeTexture(texture[i]);
    }
    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
    */
  glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_POLYGON);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH)  >> 1;
    int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Game");
    glutTimerFunc(1000, timer,0);
    init();
    glutDisplayFunc(display);
   // glutDisplayFunc(disply);
   // glutIdleFunc(disply);
    //if (GLUT_KEY_UP)
        //  glutKeyboardFunc(keyDown);
   // else
        //glutKeyboardFunc(keyUp);
   glutSpecialFunc(SpecialInput);
    glutMainLoop();
  ; glEnd();
  //glutKeyboardFunc(keyboard);
  glFlush();
  glutPostRedisplay();
  //gl_FragColor()
 // std::cin.get();
 
  return 0;
}


void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}