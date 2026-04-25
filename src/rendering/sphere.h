#pragma once

#include <vector>
#include <glad/glad.h>

class Sphere {
public:
    Sphere(unsigned int X_SEGMENTS = 64, unsigned int Y_SEGMENTS = 64);
    void Draw();

private:
    unsigned int VAO, VBO, EBO;
    //VAO: keep vertex configuration
    //VBO: store vertex data
    //EBO: store indices (to avoid duplicates)
    unsigned int indexCount;//total number of indices to draw

    void setupMesh(unsigned int X_SEGMENTS, unsigned int Y_SEGMENTS); //generate shpere geometry
};