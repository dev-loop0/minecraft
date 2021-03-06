#include "player.hpp"

namespace minecraft {

Player::Player() : x(0), y(0), z(0), yaw(-90), pitch(0) {

}

void Player::set_x(float x) { this->x = x; }
void Player::set_y(float y) { this->y = y; }
void Player::set_z(float z) { this->z = z; }
void Player::set_yaw(float yaw) { this->yaw = yaw; }
void Player::set_pitch(float pitch) { this->pitch = pitch; }

float Player::get_x() { return this->x; }
float Player::get_y() { return this->y; }
float Player::get_z() { return this->z; }
float Player::get_yaw() { return this->yaw; }
float Player::get_pitch() { return this->pitch; }

void Player::handle_inputs(GLFWwindow* window) {
    float movement_x = 0.0f, movement_y = 0.0f, movement_z = 0.0f;
    float speed = 0.1f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement_z -= speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement_z += speed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement_x -= speed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement_x += speed;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        movement_y -= speed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        movement_y += speed;
    }
    
    this->x += movement_x;
    this->y += movement_y;
    this->z += movement_z;
}

void Player::handle_mouse(GLFWwindow* window, double x, double y) {
    float delta_x = (float) (x - (window_width / 2.0f)) / window_width;
    float delta_y = (float) (y - (window_height / 2.0f)) / window_height;

    this->yaw += delta_x * (float) M_PI / 180.0f * 1.0f;
    this->pitch += delta_y * (float) M_PI / 180.0f * 2.5f;

    this->pitch = std::min(this->pitch, 89.0f / 180 * (float) M_PI);
    this->pitch = std::max(this->pitch, -89.0f / 180 * (float) M_PI);

    std::cout << this->yaw << " " << this->pitch << std::endl;
}

Eigen::Matrix4f Player::generate_view_matrix() {
    float y = this->y + 1.62f; // eye height

    Eigen::Vector3f eye(this->x, y, this->z);
    Eigen::Vector3f direction(cos(this->yaw) * cos(this->pitch), sin(this->pitch), sin(this->yaw) * cos(this->pitch));

    Eigen::Vector3f camera_z = direction.normalized();
    Eigen::Vector3f camera_x = Eigen::Vector3f(0.0f, 1.0f, 0.0f).cross(camera_z).normalized();
    Eigen::Vector3f camera_y = camera_z.cross(camera_x);

    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    rotation.row(0).head(3) = camera_x;
    rotation.row(1).head(3) = camera_y;
    rotation.row(2).head(3) = camera_z;
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation.col(3).head(3) = -eye;
    return rotation * translation;
}

}
