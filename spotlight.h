#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include "shader.h" // Assurez-vous que Shader.h contient votre classe Shader

class SpotLight {
private:
    glm::vec3 position;  // Position de la lumière
    glm::vec3 direction;
    float power;         // Intensité lumineuse
    glm::vec3 color;
    float cutoff;       // Cosinus de l'angle d'ouverture
    float outerCutoff;  // Cosinus de l'angle externe pour un adoucissement


public:
    // Constructeur
    SpotLight(glm::vec3 pos, glm::vec3 dir, float intensity, glm::vec3 col, float cut, float outer);

    // Méthodes
    void Bind(Shader& shader, const std::string& uniformName) const; // Lier la lumière au shader
    void Unbind(Shader& shader, const std::string& uniformName) const; // Enlever la lumière du shader

    // Accesseurs et mutateurs
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setDirection(const glm::vec3& dir);

    void setColor(const glm::vec3& col);
    glm::vec3 getColor() const;

    void setPower(float intensity);
    float getPower() const;
};

#endif
