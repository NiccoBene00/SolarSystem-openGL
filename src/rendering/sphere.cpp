#include "sphere.h"

#include <vector>
#include <cmath>

Sphere::Sphere(unsigned int X_SEGMENTS, unsigned int Y_SEGMENTS)
{
    setupMesh(X_SEGMENTS, Y_SEGMENTS);
}

void Sphere::setupMesh(unsigned int X_SEGMENTS, unsigned int Y_SEGMENTS)
{
    std::vector<float> data; //total 8 float per vertex. position(3), normal(3), UV(2)
    std::vector<unsigned int> indices;

    const float PI = 3.14159265359f;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            //cartesian coordinates (normalized between 0 and 1)
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            
            //shpere formula
            //conversion : θ (theta) --> lungo l’equatore
            //             φ (phi) --> dall’alto al basso
            //mathematically: x = cos(θ) * sin(φ)
            //                y = cos(φ)
            //                z = sin(θ) * sin(φ)
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            // data storage order: position, normal, UV
            data.push_back(xPos);
            data.push_back(yPos);
            data.push_back(zPos);

            //normal = position since the sphere is centered at the origin
            data.push_back(xPos);
            data.push_back(yPos);
            data.push_back(zPos);

            // UV
            data.push_back(xSegment);
            data.push_back(ySegment);
        }
    }

    //TRIANGLE STRIP: a way to draw connected triangles efficiently (less memory, faster, better GPU cache)
    //by reusing vertices

    //Indeed the sphere is built as a grid of rows (latitude) and columns (longitudes)
    //Each row is connected to the next one by a strip of triangles

    bool oddRow = false; //this trick is used to create a zig-zag pattern of indices, otherwise we would have to duplicate
                        //vertices at the end of each row to connect them properly, which would increase memory usage and reduce performance
                        //In this way the strip doesn't need to restart at the end of each row but it can continue continuosly
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }

    indexCount = indices.size();

    //buffer generation
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //vertex data loading
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    //index data loading
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    unsigned int stride = (3 + 3 + 2) * sizeof(float);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

    // UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
}

void Sphere::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}