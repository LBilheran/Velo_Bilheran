#include "spotlight.h"

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir, float intensity, glm::vec3 col, float cut, float outer)
    : position(pos), direction(dir), power(intensity), color(col), cutoff(cut), outerCutoff(outer) {}

void SpotLight::Bind(Shader& shader, const std::string& uniformName) const {
    shader.setUniform3fv(uniformName+".position", glm::vec3(position.x, position.y, position.z));
    shader.setUniform3fv(uniformName+".direction", glm::vec3(direction.x, direction.y, direction.z));
    shader.setUniform1f(uniformName+".power", power);
    shader.setUniform3fv(uniformName+".color", glm::vec3(color.x, color.y, color.z));
    shader.setUniform1f(uniformName+".cutoff", cutoff);
    shader.setUniform1f(uniformName+".outerCutoff", outerCutoff);
}

void SpotLight::Unbind(Shader& shader, const std::string& uniformName) const {
    shader.setUniform3fv(uniformName+".position", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniform3fv(uniformName+".direction", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniform1f(uniformName+".power", 0.0f);
    shader.setUniform3fv(uniformName+".color", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setUniform1f(uniformName+".cutoff", 0.0f);
    shader.setUniform1f(uniformName+".outerCutoff", 0.0f);
}

// Accesseurs et mutateurs
void SpotLight::setPosition(const glm::vec3& pos) {
    position = pos;
}

glm::vec3 SpotLight::getPosition() const {
    return position;
}

void SpotLight::setDirection(const glm::vec3& dir) {
    direction = dir;
}

void SpotLight::setColor(const glm::vec3& col) {
    color = col;
}

glm::vec3 SpotLight::getColor() const {
    return color;
}

void SpotLight::setPower(float intensity) {
    power = intensity;
}

float SpotLight::getPower() const {
    return power;
}
