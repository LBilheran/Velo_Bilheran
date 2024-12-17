#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include "shader.h" // Assurez-vous que Shader.h contient votre classe Shader

class PointLight {
private:
    glm::vec3 position;  // Position de la lumière
    glm::vec3 color;     // Couleur de la lumière
    float power;         // Intensité lumineuse

public:
    // Constructeur
    PointLight(glm::vec3 pos, glm::vec3 col, float intensity);

    // Méthodes
    void Bind(Shader& shader, const std::string& uniformName) const; // Lier la lumière au shader
    void Unbind(Shader& shader, const std::string& uniformName) const; // Enlever la lumière du shader

    // Accesseurs et mutateurs
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setColor(const glm::vec3& col);
    glm::vec3 getColor() const;

    void setPower(float intensity);
    float getPower() const;
};

#endif
