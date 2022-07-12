#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>
//==================================
#include "Header.h"

//VariablesGlobales
source fuente;
bool loadedRoom;
room r;
int NumTri=0;

//tama�o
float tamnC = 0.1;
float tamnI = 0.1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void laodRoom();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Exercise 13
//lighting
glm::vec3 lightPos(1.2f, 0.0f, 0.0f);

int main()
{
    

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    //Version de Open gl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Modelos y Simulacion", NULL, NULL);
    // Check si falla al crear
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Introduce th wwindow into the current context
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);



    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Exercise 13 Task 1
    // build and compile our shader zprogram
    // ------------------------------------
    //Shader lightingShader("D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13t3_colors.vs", "D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13t3_colors.fs");
    //Shader lightCubeShader("D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13_lightcube.vs", "D:/Users/mlcon/2022-A/Modelos y Simulacion/proyectos/shaders/shader_exercise13_lightcube.fs");
    
    Shader lightCubeShader("shader_lightcube.vs","shader_lightcube.fs");
    Shader lightingShader("shader_1.vs", "shader_1.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    laodRoom();
    int numeroTriangulos = NumTri;
    float verticesCubo [108];
    int contradorVC = 0;
    /*printf("planos %d \n", r.NP);

    printf("triangulos %d \n", r.p[0].NT);
    printf("triangulos %d \n", r.p[1].NT);
    printf("triangulos %d \n", r.p[2].NT);
    printf("triangulos %d \n", r.p[3].NT);
    printf("triangulos %d \n", r.p[4].NT);
    printf("triangulos %d \n", r.p[5].NT);*/
    


    for (int i = 0; i < r.NP;i++) {
        for (int j = 0; j < r.p[i].NT;j++) {
                verticesCubo[contradorVC] = r.p[i].t[j].p0.x * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p0.y * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p0.z * tamnC;
                contradorVC++;


                verticesCubo[contradorVC] = r.p[i].t[j].p1.x * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p1.y * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p1.z * tamnC;
                contradorVC++;


                verticesCubo[contradorVC] = r.p[i].t[j].p2.x * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p2.y * tamnC;
                contradorVC++;
                verticesCubo[contradorVC] = r.p[i].t[j].p2.z * tamnC;
                contradorVC++;

        }
    }

    float verticesIcosaedro[180];
    int contradorIC = 0;
    for (int i = 0;i < 20; i++) {
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p0.x * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p0.y * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p0.z * tamnI;
        contradorIC++;

        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p1.x * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p1.y * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p1.z * tamnI;
        contradorIC++;

        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p2.x * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p2.y * tamnI;
        contradorIC++;
        verticesIcosaedro[contradorIC] = fuente.IcoFace[i].p2.z * tamnI;
        contradorIC++;
    }


    fuente.createRays(20);
    
    printf("Rayos\n");


    for (int i = 0; i < 20; i++) {
        printf("Rayos: x: %f, y: %f, z: %f\n", fuente.Rays[i].x, fuente.Rays[i].y, fuente.Rays[i].z);
    }


    point origen;
    origen.x = 0.0;
    origen.y = 0.0;
    origen.z = 0.0;

    reflection *arrayreflecciones;

    arrayreflecciones = r.RayTracing(origen, fuente.Rays, fuente.NRAYS);

    
    for (int i = 0; i < MaxNPoints; i++) {
        printf("punto de golpe: x: %f, y: %f, z: %f\n", arrayreflecciones[1].r[i].x, arrayreflecciones[1].r[i].y, arrayreflecciones[1].r[i].z);
    }
    
    

    reflection arrayDePuntosDeChoque = arrayreflecciones[1];


    point puntoDePrueba;
    
    point puntoDeOrigen;

    puntoDeOrigen.x = arrayreflecciones[1].r[0].x * tamnC;
    puntoDeOrigen.y = arrayreflecciones[1].r[0].y * tamnC;
    puntoDeOrigen.z = arrayreflecciones[1].r[0].z * tamnC;

    puntoDePrueba.x = arrayreflecciones[1].r[1].x * tamnC;
    puntoDePrueba.y = arrayreflecciones[1].r[1].y * tamnC;
    puntoDePrueba.z = arrayreflecciones[1].r[1].z * tamnC;


    
    
    






    // first, configure the cube's VAO (and VBO)
    unsigned int VBO[2], cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenBuffers(1, &VBO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesIcosaedro), verticesIcosaedro, GL_STATIC_DRAW);


    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    double tiempo1=0;
    int contadorTemporal=0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
// ------
        //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.2f, 1.0f, 1.0f);

        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        //Exercise 13 Task 2
        lightingShader.setVec3("lightPos", lightPos);

        //Exercise 13 Task 3
        lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();


        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // render the cube
        glBindVertexArray(cubeVAO);      
        glDrawArrays(GL_TRIANGLES, 0, 36);




        


        
        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 60);


        //
        // 
        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        
        /* 
        if ((puntoDeOrigen + ((puntoDePrueba) * (glfwGetTime() - tiempo1) * 0.05) == puntoDePrueba)) {

            tiempo1 = glfwGetTime();
            puntoDeOrigen = puntoDePrueba;
            puntoDePrueba.x;

            contadorTemporal++;
            puntoDePrueba.x = arrayreflecciones[1].r[contadorTemporal].x * tamnC;
            puntoDePrueba.y = arrayreflecciones[1].r[contadorTemporal].y * tamnC;
            puntoDePrueba.z = arrayreflecciones[1].r[contadorTemporal].z * tamnC;
        }

        printf("Tiempo: %f", glfwGetTime() *0.05);

        //model = glm::translate(model, glm::vec3((puntoDePrueba.x - puntoDeOrigen.x) * (glfwGetTime()- tiempo1) * 0.05, (puntoDePrueba.y - puntoDeOrigen.y) * (glfwGetTime() - tiempo1) * 0.05, (puntoDePrueba.z - puntoDeOrigen.z) * (glfwGetTime() - tiempo1) * 0.05));
        model = glm::translate(model, glm::vec3(puntoDeOrigen.x + ((puntoDePrueba.x) * (glfwGetTime() - tiempo1) * 0.05), puntoDeOrigen.y + ((puntoDePrueba.y) * (glfwGetTime() - tiempo1) * 0.05), puntoDeOrigen.z + ((puntoDePrueba.z ) * (glfwGetTime() - tiempo1) * 0.05)));

        */


        
        //model = glm::translate(model, glm::vec3(puntoDePrueba.x * glfwGetTime() * 0.05, puntoDePrueba.y * glfwGetTime() * 0.05, puntoDePrueba.z * glfwGetTime() * 0.05));
        
        if ( (puntoDeOrigen.distancia(puntoDePrueba) * (glfwGetTime() - tiempo1) * SPEED) >= puntoDeOrigen.distancia(puntoDePrueba)) {

            tiempo1 = glfwGetTime();
            puntoDeOrigen = puntoDePrueba;

            contadorTemporal++;
            puntoDePrueba.x = arrayreflecciones[1].r[contadorTemporal].x * tamnC;
            puntoDePrueba.y = arrayreflecciones[1].r[contadorTemporal].y * tamnC;
            puntoDePrueba.z = arrayreflecciones[1].r[contadorTemporal].z * tamnC;
        };




        //model = glm::translate(model, glm::vec3((puntoDePrueba.x - puntoDeOrigen.x) * (glfwGetTime()- tiempo1) * 0.05, (puntoDePrueba.y - puntoDeOrigen.y) * (glfwGetTime() - tiempo1) * 0.05, (puntoDePrueba.z - puntoDeOrigen.z) * (glfwGetTime() - tiempo1) * 0.05));
        model = glm::translate(model, glm::vec3(puntoDeOrigen.x + ((puntoDePrueba.x- puntoDeOrigen.x) * (glfwGetTime() - tiempo1) * SPEED), puntoDeOrigen.y + ((puntoDePrueba.y- puntoDeOrigen.y) * (glfwGetTime() - tiempo1) * SPEED), puntoDeOrigen.z + ((puntoDePrueba.z- puntoDeOrigen.z) * (glfwGetTime() - tiempo1) * SPEED)));








        model = glm::scale(model, glm::vec3(0.01f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 60);

        //glEnableClientState(GL_VERTEX_ARRAY);
        //glBindVertexArray(*pointVertex);
        //glVertexPointer(3, GLfloat, 0, pointVertex);
        //glDrawArrays(GL_POINT, 0, 1);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteBuffers(1, &VBO[1]);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 0.5);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 0.5);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * 0.5);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * 0.5);

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
//================================================================================================================================================

void laodRoom() {
    if (!loadedRoom) {
        int nDivTri;
        nDivTri = 2;
        r.NewPlanes(6);// Genearra 6 planos
        //square back
        r.p[0].NewPoints(4);// Gnererar los 4 puntos

        r.p[0].p[0].x = -2.0f;
        r.p[0].p[0].y = 2.0f;
        r.p[0].p[0].z = 2.0f;

        r.p[0].p[1].x = -2.0f;
        r.p[0].p[1].y = -2.0f;
        r.p[0].p[1].z = 2.0f;

        r.p[0].p[2].x = -2.0f;
        r.p[0].p[2].y = -2.0f;
        r.p[0].p[2].z = -2.0f;

        r.p[0].p[3].x = -2.0f;
        r.p[0].p[3].y = 2.0f;
        r.p[0].p[3].z = -2.0f;

        r.p[0].PointGenTriangle();

       

        //square front
        r.p[1].NewPoints(4);// Gnererar los 4 puntos

        r.p[1].p[0].x = 2.0f;
        r.p[1].p[0].y = 2.0f;
        r.p[1].p[0].z = 2.0f;

        r.p[1].p[1].x = 2.0f;
        r.p[1].p[1].y = 2.0f;
        r.p[1].p[1].z = -2.0f;

        r.p[1].p[2].x = 2.0f;
        r.p[1].p[2].y = -2.0f;
        r.p[1].p[2].z = -2.0f;

        r.p[1].p[3].x = 2.0f;
        r.p[1].p[3].y = -2.0f;
        r.p[1].p[3].z = 2.0f;

        r.p[1].PointGenTriangle();

        //square left
        r.p[2].NewPoints(4);

        r.p[2].p[0].x = -2.0f;
        r.p[2].p[0].y = -2.0f;
        r.p[2].p[0].z = 2.0f;

        r.p[2].p[1].x = 2.0f;
        r.p[2].p[1].y = -2.0f;
        r.p[2].p[1].z = 2.0f;

        r.p[2].p[2].x = 2.0f;
        r.p[2].p[2].y = -2.0f;
        r.p[2].p[2].z = -2.0f;

        r.p[2].p[3].x = -2.0f;
        r.p[2].p[3].y = -2.0f;
        r.p[2].p[3].z = -2.0f;
        r.p[2].PointGenTriangle();

        //square right
        r.p[3].NewPoints(4);// Gnererar los 4 puntos

        r.p[3].p[0].x = 2.0f;
        r.p[3].p[0].y = 2.0f;
        r.p[3].p[0].z = 2.0f;

        r.p[3].p[1].x = -2.0f;
        r.p[3].p[1].y = 2.0f;
        r.p[3].p[1].z = 2.0f;

        r.p[3].p[2].x = -2.0f;
        r.p[3].p[2].y = 2.0f;
        r.p[3].p[2].z = -2.0f;

        r.p[3].p[3].x = 2.0f;
        r.p[3].p[3].y = 2.0f;
        r.p[3].p[3].z = -2.0f;
        r.p[3].PointGenTriangle();

   
        //square top
        r.p[4].NewPoints(4);

        r.p[4].p[0].x = -2.0f;
        r.p[4].p[0].y = -2.0f;
        r.p[4].p[0].z = 2.0f;

        r.p[4].p[1].x = -2.0f;
        r.p[4].p[1].y = 2.0f;
        r.p[4].p[1].z = 2.0f;

        r.p[4].p[2].x = 2.0f;
        r.p[4].p[2].y = 2.0f;
        r.p[4].p[2].z = 2.0f;

        r.p[4].p[3].x = 2.0f;
        r.p[4].p[3].y = -2.0f;
        r.p[4].p[3].z = 2.0f;
        r.p[4].PointGenTriangle();

        //square bottom
        r.p[5].NewPoints(4);

        r.p[5].p[0].x = -2.0f;
        r.p[5].p[0].y = 2.0f;
        r.p[5].p[0].z = -2.0f;

        r.p[5].p[1].x = -2.0f;
        r.p[5].p[1].y = -2.0f;
        r.p[5].p[1].z = -2.0f;

        r.p[5].p[2].x = 2.0f;
        r.p[5].p[2].y = -2.0f;
        r.p[5].p[2].z = -2.0f;

        r.p[5].p[3].x = 2.0f;
        r.p[5].p[3].y = 2.0f;
        r.p[5].p[3].z = -2.0f;
        r.p[5].PointGenTriangle();

        /*
        for (int i = 0; i < 6;i++) {
            printf("+++++++++++++++++++++++++++++\n");
            printf("Plano%d\n", i + 1);
            for (int j = 0; j < 2;j++) {
                printf("Punto 1\n");
                printf("x: %f, y: %f, z: %f \n", r.p[i].t[j].p0.x, r.p[i].t[j].p0.y, r.p[i].t[j].p0.z);
                printf("Punto 2\n");
                printf("x: %f, y: %f, z: %f \n", r.p[i].t[j].p1.x, r.p[i].t[j].p1.y, r.p[i].t[j].p1.z);
                printf("Punto 3\n");
                printf("x: %f, y: %f, z: %f \n", r.p[i].t[j].p2.x, r.p[i].t[j].p2.y, r.p[i].t[j].p2.z);
            }
            printf("+++++++++++++++++++++++++++++\n");
        }
        */

        //Calcular los normales del plano
        int cont_t = 0;
        for (int i = 0; i < r.NP; i++) {
            r.p[i].n = NormalPlano(r.p[i]);
            for (int j = 0;j < r.p[i].NT;j++) {
                r.p[i].t[j].CalculateProjection();
                r.p[i].t[j].Centroid();
                r.p[i].t[j].ID = cont_t;
                cont_t++;
            }

        }

        NumTri = cont_t;
        //numRec = 27;




    }
}