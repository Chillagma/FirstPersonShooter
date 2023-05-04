#define TINYOBJLOADER_IMPLEMENTATION
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>

#include <freeglut.h>
#include <glext.h>

#include "loadpng.h"
#include "process_image.h"
#include "gl_texture.h"
#include<iostream>
#include<tinyobjloader-2.0-rc1/tiny_obj_loader.h>
//#include<glfw3.h>

#define WIDTH 600
#define HEIGHT 600

class aclass {

    tinyobj::ObjReader reader;

public:
    const tinyobj::attrib_t attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t, std::allocator<tinyobj::shape_t>> shapes = reader.GetShapes();
    const std::vector<tinyobj::material_t, std::allocator<tinyobj::material_t> >
        materials = reader.GetMaterials();
    std::vector<GLdouble*> function() {
        std::string inputfile = "Lowpoly_tree.obj";
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
                        attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz =
                        attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    container.push_back(new GLdouble[3]{ vx, vy, vz });
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
    std::vector<GLdouble*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;
    GLuint list;
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
        std::vector<GLdouble*> Vcontainer;
        Vcontainer = e.function();
        for (GLdouble* val : Vcontainer)
        {

            vertices.push_back(val);
           

        }
        for (std::string& line : lines) {
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);

                    //vertices.push_back(new float[3]{ a, b, c});
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
       
        aclass e;
        e.function();
       
        std::vector<GLdouble*> container = e.function();
      
      
            //std::cout << val << std::endl;
        //std::cout << e.function() << std::endl;
        list = glGenLists(1);
        
        glNewList(list, GL_COMPILE);
     
     //   glBegin(GL_POLYGON);
        glBegin(GL_POLYGON);
       
        for (Face& face : faces) {
            
            for (int i = 0; i < face.edge; i++)
            {
              
               glVertex3dv(vertices[face.vertices[i]]);
            }
               
            for (GLdouble* val : container)
            {
               // glVertex3dv(val);
                glNormal3fv(normals[face.normal]);
              
            }
            
            if (face.normal >= 0){
               
               
            }

            else
            glEnable(GL_LIGHTING);
          
            
            for (int i = 0; i < face.edge; i++)
                if (face.vertices[i] > 0) {
                
                   // glVertex3fv(vertices[face.vertices[i]]);
                   // std::cout << vertices[face.vertices[i]] << std::endl;
                    }
                     
                   
            
         
          
        
            if (face.normal == -1)
                 glDisable(GL_LIGHTING);
        }
        glEnd();
        glEndList();
        printf("Model: %s\n", filename);
        printf("Vertices: %d\n", vertices.size());
        printf("Texcoords: %d\n", texcoords.size());
        printf("Normals: %d\n", normals.size());
        printf("Faces: %d\n", faces.size());


       


        for (GLdouble* f : vertices)
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
};

Model model;

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = { -1.0f, 10.0f, 100.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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

   model.load("Lowpoly_tree.obj");
}
float i = 0.0;
float j = -200.0;
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
    switch (key)
    {
    case GLUT_KEY_UP:
        //do something here
        j=j+5;
        break;
    case GLUT_KEY_DOWN:
        //do something here
        j=j-5;
        break;
    case GLUT_KEY_LEFT:
        //do something here
         i++;
        break;
    case GLUT_KEY_RIGHT:
        //do something here
        i--;
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


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
   //motion();
    //catchKey(0,0,0);
    /*if ((GLUT_KEY_UP)) {
       // x++;


        //glTranslatef(x, -30.0f, -200.0f);
    }*/
    glTranslatef(i, -10.0f, j);
    glRotatef(30.0f, 1.0f, -1.0f, 0.0f);
   
       // vCamera.y += 8.0f * fElapsedTime;
    model.draw();
    glutSwapBuffers();
}

/*void keyUp(unsigned char key, int x, int y)
{

    x--;
    key = x;


}*/

int main(int argc, char** argv) {
  glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Game");
    init();
    glutDisplayFunc(display);
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
  
  std::cin.get();
 
  return 0;
}


