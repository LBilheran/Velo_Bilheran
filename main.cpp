#include <iostream>
#include <random>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "spotlight.h"
#include "pointlight.h"


using namespace std;

int main()
{

/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);


/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }


/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;

/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string path = "/home/lbilheran/Documents/TSI/OpenGL/ProjetOGL/Velo_Bilheran/";

    Shader shader(path + "shaders/SimpleVertexShader.vertexshader", path + "shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée les vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    VertexArray vaVelo;
    vaVelo.Bind();
    VertexArray vaFloor;
    vaFloor.Bind();
    VertexArray vaLight;
    vaFloor.Bind();


/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    Camera cam(width, height);
    cam.position.x = 15.0f;
    cam.position.y = 30.0f;
    cam.position.z = 30.0f;
    cam.verticalAngle = -0.88f;

    NavigationControls controls(window, &cam);


/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Vélo
    std::string textVeloPath = path + "obj/bicycle/bicycle_texture.jpg";
    std::string veloPathString = path + "obj/bicycle/bicycle_triang.obj";
    const char *veloPath = veloPathString.c_str();
    Object velo(veloPath, textVeloPath);
    velo.rotationAngles.y = 1.57;

    // Sol
    std::string textFloorPath = path + "obj/ROAD/road.jpg";
    std::string floorPathString = path + "obj/ROAD/ROAD_triang.obj";
    const char *floorPath = floorPathString.c_str();
    Object floor(floorPath, textFloorPath);

    // Lampe torche
    SpotLight spotLight(
        glm::vec3(0.0f, 5.0f,-5.0f),   // Position (au-dessus du sol)
        glm::vec3(1.0f, -1.0f, 0.0f),  // Direction
        20.0f,                         // Puissance (intensité lumineuse)
        glm::vec3(0.0f, 1.0f, 0.0f),   // Couleur (vert)
        glm::cos(glm::radians(20.5f)),
        glm::cos(glm::radians(25.5f))
    );


    // Cube représentant la lumière
    vector<glm::vec3> light_vertex_buffer_data = {
        // Face avant
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),

        // Face arrière
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),

        // Face gauche
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),

        // Face droite
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),

        // Face supérieure
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3( 0.5f,  0.5f,  0.5f),
        glm::vec3( 0.5f,  0.5f, -0.5f),

        // Face inférieure
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
    };

    vector<glm::vec2> light_uv_buffer_data = {
        // Face avant
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        // Face arrière
        glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f),

        // Face gauche
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        // Face droite
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        // Face supérieure
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        // Face inférieure
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
    };

    std::vector<glm::vec3> light_normal_buffer_data = {
        // Face avant (normale = (0, 0, 1))
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        // Face arrière (normale = (0, 0, -1))
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),

        // Face gauche (normale = (-1, 0, 0))
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),

        // Face droite (normale = (1, 0, 0))
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        // Face supérieure (normale = (0, 1, 0))
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        // Face inférieure (normale = (0, -1, 0))
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
    };

    Object lightMarker(light_vertex_buffer_data, light_uv_buffer_data, light_normal_buffer_data, path + "textures/marbre.png");


/////////////////////////Initialisation de variables/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Initialisation des variables de temps
    float lastTime = glfwGetTime();
    float currentTime, deltaTime;
    int dayTime = 0;

    // Points du parcours
    std::vector<glm::vec3> points = {
        glm::vec3(0.5f, 0.3f, 18.0f),    // 0: Coin bas gauche
        glm::vec3(0.5f, 0.3f, -18.0f),   // 1: Coin haut gauche
        glm::vec3(28.5f, 0.3f, -18.0f),  // 2: Coin haut droit
        glm::vec3(28.5f, 0.3f, 18.0f),   // 3: Coin bas droit
        glm::vec3(18.5f, 0.3f, -18.0f),   // 4: Croisement haut
        glm::vec3(18.5f, 0.3f, 18.0f),  // 5: Croisement bas
        glm::vec3(18.5f, 0.3f, 0.0f),    // 6: Intersection centrale
        glm::vec3(0.5f, 0.3f, 0.0f),     // 7: Croisement gauche milieu
        glm::vec3(28.5f, 0.3f, 0.0f),     // 8: Croisement droit mileu
        glm::vec3(0.5f, 0.3f, 10.0f),    // 9: Croisement gauche bas
        glm::vec3(28.5f, 0.3f, 10.0f),    // 10: Croisement droit bas
        glm::vec3(18.5f, 0.3f, 10.0f)    // 11: Intersection bas
    };

    // Graphe de connexions entre les points
    std::map<int, std::vector<int>> connections = {
        {0, {9, 5}},            // Point 0 connecté à 9 et 5
        {1, {7, 4}},            // Point 1
        {2, {8, 4}},            // Point 2
        {3, {5, 10}},           // Point 3
        {4, {6, 1, 2}},         // Point 4
        {5, {3, 11, 0}},        // Point 5
        {6, {11, 4, 7, 8}},     // Point 6
        {7, {1, 9, 6}},         // Point 7
        {8, {2, 10, 6}},        // Point 8
        {9, {0, 11, 7}},        // Point 9
        {10, {3, 8, 11}},       // Point 10
        {11, {5, 9, 10, 6}},    // Point 11
    };

    // Variables nécessaires
    int current_point = 9; // Point qui va être visité
    int last_point = 0; // Dernier point visité (Point de départ ici)
    float speed = 10.0f; // Vitesse du vélo
    glm::vec3 current_direction = glm::normalize(points[(current_point) % points.size()] - points[last_point]);

    // Générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Dans la boucle de rendu :
    glm::vec3 bike_position = points[last_point];


/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

        // Set Time
        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;


        /////////////////////////Lumière//////////////////////////////////////////////////////////////


        // Application de la lumière ponctuelle
        shader.setUniform3fv("lightPosition",spotLight.getPosition());
        shader.setUniform3fv("cameraPosition",cam.position);
        spotLight.Bind(shader, "u_SpotLight");


        dayTime += 1;
        if (dayTime > 600) {
            dayTime = 0; // Réinitialise le cycle après 600 "unités de temps"
        }

        // Définir les couleurs pour le jour et la nuit
        glm::vec3 dayColor = glm::vec3(0.5f, 0.7f, 1.0f);  // Bleu clair pour le jour
        glm::vec3 nightColor = glm::vec3(0.02f, 0.02f, 0.1f); // Bleu très sombre pour la nuit

        // Calculer un facteur d'interpolation
        float t = 0.0f;
        if (dayTime <= 200) {
            // Transition nuit → jour maximal (lever du soleil)
            t = static_cast<float>(dayTime) / 200.0f;
        } else if (dayTime <= 400) {
            // Jour maximal → nuit (coucher du soleil)
            t = 1.0f - static_cast<float>(dayTime - 200) / 200.0f;
        } else {
            // Nuit totale (de 400 à 600)
            t = 0.0f;
        }

        // Interpoler entre la couleur du jour et celle de la nuit
        glm::vec3 backgroundColor = glm::mix(nightColor, dayColor, t);

        // Appliquer la couleur de fond
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);

        // Continuer avec le reste du cycle de la lumière
        glm::vec3 ambientLightColor = glm::mix(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), t);
        shader.setUniform3fv("ambientLightColor", ambientLightColor);


        /////////////////////////Déplacement/////////////////////////////////////////////////////////////


        // Calculer la direction du vélo vers le point suivant
        glm::vec3 target = points[current_point];
        glm::vec3 direction = glm::normalize(target - bike_position);

        // Avancer vers le point
        bike_position += direction * speed * deltaTime;

        // Vérifier si le vélo a atteint le point cible
        if (glm::distance(bike_position, target) < 0.1f) {
            // Choisir un prochain point aléatoire
            std::vector<int> possible_points = connections[current_point];
            if (!possible_points.empty()) {
                // Filtrer pour éviter le demi-tour
                std::vector<int> valid_points;
                for (int point : possible_points) {
                    if (point != last_point) {
                        valid_points.push_back(point);
                    }
                }

                // Choisir aléatoirement parmi les points valides
                std::uniform_int_distribution<> dis(0, valid_points.size() - 1);
                int next_point = valid_points[dis(gen)];

                // Mettre à jour les points
                last_point = current_point;
                current_point = next_point;

                // Calculer la nouvelle direction cible
                glm::vec3 new_direction = glm::normalize(points[current_point] - bike_position);

                // Calculer l'angle de rotation
                float angle = atan2(new_direction.z, new_direction.x) - atan2(current_direction.z, current_direction.x);

                // Normaliser l'angle entre -PI et PI
                if (angle > glm::pi<float>()) angle -= 2.0f * glm::pi<float>();
                if (angle < -glm::pi<float>()) angle += 2.0f * glm::pi<float>();

                // Appliquer des sauts de ±1.57 radians (90°) ou aucun saut si tout droit
                if (angle > 0.78f && angle < 2.36f) { // Rotation à gauche
                    velo.rotationAngles.y -= 1.57f;
                } else if (angle < -0.78f && angle > -2.36f) { // Rotation à droite
                    velo.rotationAngles.y += 1.57f;
                }

                // Mettre à jour la direction actuelle
                current_direction = new_direction;

                // Maintenir la position verticale constante
                velo.position.y = bike_position.y;
            }
        }
        // Mettre à jour la position du vélo dans la scène
        velo.position = bike_position;


        // Calcul de la direction "avant" du vélo
        glm::vec3 forward = glm::vec3(
            cos(velo.rotationAngles.y),  // Composante X
            0.0f,                        // Composante Y
            -sin(velo.rotationAngles.y)  // Composante Z
        );

        // Calcul de la direction de la lumière
        float verticalInclination = -1.0f; // Inclinaison de la lumière vers le bas
        glm::vec3 lightDirection = glm::normalize(glm::vec3(
            forward.x,              // Direction avant (X)
            verticalInclination,    // Inclinaison (Y)
            forward.z               // Direction avant (Z)
        ));

        // Mise à jour de la position et de la direction de la lumière
        spotLight.setPosition(velo.position + glm::vec3(0, 3, 0) + forward * 2.5f);
        spotLight.setDirection(lightDirection);

        // Mise à jour du marqueur de lumière
        lightMarker.position = spotLight.getPosition();


        // Mise à jour des contrôles et de la caméra
        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);


        /////////////////////////Renderer//////////////////////////////////////////////////////////////


        renderer.Clear(); // Vider les buffers

        glm::mat4 viewMatrix = cam.getViewMatrix();
        glm::mat4 projectionMatrix = cam.getProjectionMatrix();


        // Rendu du vélo
        glm::mat4 modelMatrixVelo = velo.getModelMatrix(); // Matrice propre au vélo
        glm::mat4 mvpVelo= projectionMatrix * viewMatrix * modelMatrixVelo;

        shader.setUniformMat4f("modelMatrix", modelMatrixVelo);
        shader.setUniformMat4f("MVP", mvpVelo); // Envoyer la MVP du vélo

        renderer.Draw(vaVelo, velo, shader); // Rendre le cube


        // Rendu du sol
        glm::mat4 modelMatrixFloor = glm::translate(glm::mat4(1.0f), floor.position); // Matrice propre au sol
        glm::mat4 mvpFloor = projectionMatrix * viewMatrix * modelMatrixFloor;

        shader.setUniformMat4f("modelMatrix", modelMatrixFloor);
        shader.setUniformMat4f("MVP", mvpFloor); // Envoyer la MVP du sol
        renderer.Draw(vaFloor, floor, shader); // Rendre le sol


        // Rendu du cube de lumière
        glm::mat4 modelMatrixLight = glm::translate(glm::mat4(1.0f), lightMarker.position); // Matrice propre à la lumière
        glm::mat4 mvpLight = projectionMatrix * viewMatrix * modelMatrixLight;

        shader.setUniformMat4f("modelMatrix", modelMatrixLight);
        shader.setUniformMat4f("MVP", mvpLight);

        renderer.Draw(vaLight, lightMarker, shader);


        ////////////////Partie rafraichissement de l'image et des évènements///////////////

        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();


    return 0;
}
