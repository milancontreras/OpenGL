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
int NumTri = 0;

float transparency = 0.5;
bool blDrawFuente = true;


//tamaño
float tamnC = 0.1;
float tamnI = 0.1;

//FUNCIONES
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void laodRoom();
void actializarVBOline(unsigned int& id, unsigned int offset, void* data, unsigned int size, unsigned int type);

// Configuraciones de pantalla
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camara
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//
glm::vec3 lightPos(1.3f, 1.0f, 1.0f);

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

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Shaders
    Shader IcosaedroShader("shader_lightcube.vs", "shader_lightcube.fs");
    Shader CuboShader("shader_1.vs", "shader_1.fs");
    Shader LineaShader("shader_linea.vs", "shader_linea.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------- GENERACION VERTICES DEL CUBO--------------------------------------------------------------
    //cargar el room (cubo)
    laodRoom();
    //int numeroTriangulos = NumTri;
    float verticesCubo[216];

    //Vertices del cubo
    int contradorVC = 0;
    float normal1[] = { 0.0,0.0,0.0 };
    for (int i = 0; i < r.NP; i++) {
        for (int j = 0; j < r.p[i].NT; j++) {

            if (i == 0) {
                normal1[0] = 0.0;
                normal1[1] = 0.0;
                normal1[2] = -1.0;
            }
            else if (i == 1) {
                normal1[0] = 0.0;
                normal1[1] = 0.0;
                normal1[2] = 1.0;
            }
            else if (i == 2) {
                normal1[0] = -1.0;
                normal1[1] = 0.0;
                normal1[2] = 0.0;
            }
            else if (i == 3) {
                normal1[0] = 1.0;
                normal1[1] = 0.0;
                normal1[2] = 0.0;
            }
            else if (i == 4) {
                normal1[0] = 0.0;
                normal1[1] = -1.0;
                normal1[2] = 0.0;
            }
            else if (i == 5) {
                normal1[0] = 0.0;
                normal1[1] = 1.0;
                normal1[2] = 0.0;
            }


            //tamC sirve para poner el valor de 0 - 1

                //Vertices
            verticesCubo[contradorVC] = r.p[i].t[j].p0.x * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p0.y * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p0.z * tamnC;
            contradorVC++;

            //Normal
            verticesCubo[contradorVC] = normal1[0];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[1];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[2];
            contradorVC++;

            //Vertices
            verticesCubo[contradorVC] = r.p[i].t[j].p1.x * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p1.y * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p1.z * tamnC;
            contradorVC++;

            //Normal
            verticesCubo[contradorVC] = normal1[0];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[1];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[2];
            contradorVC++;

            //Vertices
            verticesCubo[contradorVC] = r.p[i].t[j].p2.x * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p2.y * tamnC;
            contradorVC++;
            verticesCubo[contradorVC] = r.p[i].t[j].p2.z * tamnC;
            contradorVC++;

            //Normal
            verticesCubo[contradorVC] = normal1[0];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[1];
            contradorVC++;
            verticesCubo[contradorVC] = normal1[2];
            contradorVC++;

        }
    }
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------- GENERACION VERTICES DEL ICOSAEDRO---------------------------------------------------------
    //Vertices del icosaedro
    float verticesIcosaedro[180];
    int contradorIC = 0;
    for (int i = 0; i < 20; i++) {
        //tamI sirve para poner el valor de 0 - 1
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
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------- GENERACION DE RAYOS-----------------------------------------------------------------------
    //Creamos los rayos desde el icosaedro
    fuente.createRays(20);

    //Punto de origen del icosaedro
    point origen;
    origen.x = 0.0;
    origen.y = 0.0;
    origen.z = 0.0;


    //Creamos las reflexiones de los rayos
    reflection* arrayreflecciones;
    arrayreflecciones = r.RayTracing(origen, fuente.Rays, fuente.NRAYS);

    /*
    for (int i = 0; i < 300; i++) {
        printf("punto de golpe: indice: %d, x: %.2f, y: %.2f, z: %.2f\n",i, arrayreflecciones[1].r[i].x, arrayreflecciones[1].r[i].y, arrayreflecciones[1].r[i].z);
    }
    */



    //Nos quedamos copn las reflexiones de solo un rayo
    reflection arrayDePuntosDeChoque = arrayreflecciones[1];


    point puntoDeDestino;

    point puntoDeOrigen;

    puntoDeOrigen.x = arrayreflecciones[1].r[0].x * tamnC;
    puntoDeOrigen.y = arrayreflecciones[1].r[0].y * tamnC;
    puntoDeOrigen.z = arrayreflecciones[1].r[0].z * tamnC;

    puntoDeDestino.x = arrayreflecciones[1].r[1].x * tamnC;
    puntoDeDestino.y = arrayreflecciones[1].r[1].y * tamnC;
    puntoDeDestino.z = arrayreflecciones[1].r[1].z * tamnC;

    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    float puntosNuevos1[150];
    float puntosDinamicos[6];
    puntosNuevos1[0] = 0.0f;
    puntosNuevos1[1] = 0.0f;
    puntosNuevos1[2] = 0.0f;
    puntosDinamicos[0] = 0.0f;
    puntosDinamicos[1] = 0.0f;
    puntosDinamicos[2] = 0.0f;
    puntosDinamicos[3] = 1.2f;
    puntosDinamicos[4] = 1.2f;
    puntosDinamicos[5] = 0.0f;
    int au = 1,aux=0;
    for (int b = 3; b < 150; b++) {
        puntosNuevos1[b] = arrayreflecciones[1].r[au].x * tamnC;
        b++;
        puntosNuevos1[b] = arrayreflecciones[1].r[au].y * tamnC;
        b++;
        puntosNuevos1[b] = arrayreflecciones[1].r[au].z * tamnC;
        au++;
    }
   
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------- CONFIGURACION DEL VAO Y VBO---------------------------------------------------------------

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO[4], cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO, lineaVAO, lineaVAO1;

    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &VBO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesIcosaedro), verticesIcosaedro, GL_STATIC_DRAW);



    glBindVertexArray(lightCubeVAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ///////
    glGenVertexArrays(1, &lineaVAO);
    glGenBuffers(1, &VBO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(puntosNuevos1), puntosNuevos1, GL_STATIC_DRAW);

    glBindVertexArray(lineaVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    ///////
    glGenVertexArrays(1, &lineaVAO1);
    glGenBuffers(1, &VBO[3]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(puntosDinamicos), puntosDinamicos, GL_DYNAMIC_DRAW);

    glBindVertexArray(lineaVAO1);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------------------------


    double tiempoGuardado = 0; // Variable la cual permitira encerar el tiempo cada vez que el rayo tope con una pared
    int indiceReflexion = 0; // indiceDeReflexion
    int contadorGraficarVertice = 0;
    int contador = 3;
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
        glClearColor(0.14f, 0.25f, 0.48f, 1.0f); //COLOR DE LA SALA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //------------------------------------------------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------- DIBUJAR EL CUBO----------------------------------------------------------------------------
        CuboShader.use();

        CuboShader.setFloat("transparency", transparency);
        CuboShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        CuboShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        CuboShader.setVec3("lightPos", lightPos);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        CuboShader.setMat4("projection", projection);
        CuboShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        CuboShader.setMat4("model", model);

        // render the object

        glBindVertexArray(cubeVAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //------------------------------------------------------------------------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------------------------------------------------------------------------


        //------------------------------------------------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------- DIBUJAR EL ICOSAEDRO (FUENTE)-------------------------------------------------------------

            // Dibujar el icosaedro
        IcosaedroShader.use();
        IcosaedroShader.setMat4("projection", projection);
        IcosaedroShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        IcosaedroShader.setMat4("model", model);

        if (blDrawFuente) {
            glBindVertexArray(lightCubeVAO);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, 60);
        }

        //------------------------------------------------------------------------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------------------------------------------------------------------------



    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------- DIBUJAR EL ICOSAEDRO (RAYO)---------------------------------------------------------------
        
        float velocidadEnEje = (SPEED) / puntoDeOrigen.distancia(puntoDeDestino); // Velocidad la cual debera ser multiplicado cada eje
       
            
        

        if (((glfwGetTime() - tiempoGuardado) * (SPEED)) >= puntoDeOrigen.distancia(puntoDeDestino)) { //Entra en el if cada vez que el rayo topa con una pared

            tiempoGuardado = glfwGetTime();
            puntoDeOrigen = puntoDeDestino; //El punto de origen es el punto de destino anterior
            puntosDinamicos[0] = puntoDeOrigen.x;
            puntosDinamicos[1] = puntoDeOrigen.y;
            puntosDinamicos[2] = puntoDeOrigen.z;

            //printf("valores de  puntos nuevo %f %f %f el contador \n/////////////////////////////////////////////////////////\n/////////////////////////////////////////////////////////\n/////////////////////////////////////////////////////////\n", puntosDinamicos[0], puntosDinamicos[1], puntosDinamicos[2]);
            //printf("valores de  puntos nuevo %f %f %f el contador es %i\n/////////////////////////////////////////////////////////\n", puntoDeOrigen.x, puntoDeOrigen.y, puntoDeOrigen.z, contador);
            //printf("valores de  puntos nuevo %f %f %f el contador es %i\n/////////////////////////////////////////////////////////\n", puntosNuevos1[0+contador], puntosNuevos1[1 + contador], puntosNuevos1[2 + contador], contador);
            contador += 3;
            indiceReflexion++;
            contadorGraficarVertice++;
            //Nuevo punto de destino
            puntoDeDestino.x = arrayreflecciones[1].r[indiceReflexion].x * tamnC;
            puntoDeDestino.y = arrayreflecciones[1].r[indiceReflexion].y * tamnC;
            puntoDeDestino.z = arrayreflecciones[1].r[indiceReflexion].z * tamnC;

        };

        //Si llega a las 50 reflexiones deja de graficar el rayo
        if (indiceReflexion >= MAX_NUM_REFLECTIONS) {
            puntoDeDestino.Clear();
            puntoDeOrigen.Clear();
        };

        model = glm::mat4(1.0f);
        IcosaedroShader.setMat4("model", model);
        //Movimiento del rayo
        
        

        puntosDinamicos[3] = puntoDeOrigen.x + ((puntoDeDestino.x - puntoDeOrigen.x)) * (glfwGetTime() - tiempoGuardado) * velocidadEnEje;
        puntosDinamicos[4] = puntoDeOrigen.y + ((puntoDeDestino.y - puntoDeOrigen.y)) * (glfwGetTime() - tiempoGuardado) * velocidadEnEje;
        puntosDinamicos[5] = puntoDeOrigen.z + ((puntoDeDestino.z - puntoDeOrigen.z)) * (glfwGetTime() - tiempoGuardado) * velocidadEnEje;
        //printf("valores de  puntos nuevo %f %f %f el contador \n/////////////////////////////////////////////////////////\n", puntosDinamicos[3], puntosDinamicos[4], puntosDinamicos[5]);
        
        //actializarVBOline(VBO[3], 0, puntosDinamicos, sizeof(puntosDinamicos), GL_ARRAY_BUFFER);
        
       

        model = glm::translate(model,
            glm::vec3(puntosDinamicos[3], puntosDinamicos[4], puntosDinamicos[5]));


        model = glm::scale(model, glm::vec3(0.02f)); // Graficamos el rayo como un icosaedro
        IcosaedroShader.setMat4("model", model);
        
        //Renderizar el rayo
        glBindVertexArray(lightCubeVAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, 60);
        //printf("%f", puntosNuevos[1]);
        //------------------------------------------------------------------------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------------------------------------------------------------------------

                //intento linea

            // Dibujar linea
        LineaShader.use();
        LineaShader.setMat4("projection", projection);
        LineaShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        LineaShader.setMat4("model", model);

        glBindVertexArray(lineaVAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_LINE_STRIP, 0, contadorGraficarVertice);


        // Dibujar linea dinamica
        
        LineaShader.setMat4("projection", projection);
        LineaShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        LineaShader.setMat4("model", model);

        glBindVertexArray(lineaVAO1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_LINE_STRIP, 0, 2);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    //Limpieza de variables
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteVertexArrays(1, &lineaVAO);
    glDeleteVertexArrays(1, &lineaVAO1);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteBuffers(1, &VBO[2]);
    glDeleteBuffers(1, &VBO[3]);


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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (transparency <= 1.0) {
            transparency = transparency + 0.01;

        };

    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (transparency >= 0.0) {
            transparency = transparency - 0.01;

        };
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        blDrawFuente = false;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        blDrawFuente = true;
    }



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
        r.NewPlanes(6);// Geneara 6 planos
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
            for (int j = 0; j < r.p[i].NT; j++) {
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


void actializarVBOline(unsigned int & id, unsigned int offset,void* data, unsigned int size, unsigned int type) {

        glBindBuffer(type, id);
        glBufferSubData(type, offset, size, data);
}
