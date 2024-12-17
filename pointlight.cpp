#include "pointlight.h"

PointLight::PointLight(glm::vec3 pos, glm::vec3 col, float intensity)
    : position(pos), color(col), power(intensity) {}

void PointLight::Bind(Shader& shader, const std::string& uniformName) const {
    shader.setUniform3fv(uniformName+".position", glm::vec3(position.x, position.y, position.z));
    shader.setUniform3fv(uniformName+".color", glm::vec3(color.x, color.y, color.z));
    shader.setUniform1f(uniformName+".power", power);
}

void PointLight::Unbind(Shader& shader, const std::string& uniformName) const {
    shader.setUniform3fv(uniformName+".position", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniform3fv(uniformName+".color", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniform1f(uniformName+".power", 0.0f);
}

// Accesseurs et mutateurs
void PointLight::setPosition(const glm::vec3& pos) {
    position = pos;
}

glm::vec3 PointLight::getPosition() const {
    return position;
}

void PointLight::setColor(const glm::vec3& col) {
    color = col;
}

glm::vec3 PointLight::getColor() const {
    return color;
}

void PointLight::setPower(float intensity) {
    power = intensity;
}

float PointLight::getPower() const {
    return power;
}
