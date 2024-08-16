/*****************************************************************//**
 * \file   object.hpp
 * \brief  ObjectData structure and Object class and subclasses
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <vector>

/**
 * \param int type
 * \param int material
 * \param float x
 * \param float y
 * \param float z
 * \param float l1
 * \param float dx
 * \param float dy
 * \param float dz
 * \param bool down
 * \param bool moving
 */
struct ObjectData {
    int type, material;
    float x, y, z, l1, dx, dy, dz;
    bool down = true, moving = false;
};

class Object {
protected:
    ObjectData data;
    float lastT;

    /**
     * Returns the evaluated SDF
     * 
     * \return float
     */
    float SDF() {}
public:
    /**
     * Initialises the object class
     * 
     * \param ObjectData data
     */
    Object(ObjectData data);

    /**
     * Updates object data variables
     * 
     * \param float f
     */
    void update(float f);

    /**
     * Applies gravity to an object
     * 
     * \param float g
     * \param float r
     */
    void applyGravity(float g, float r);

    /**
     * Stops an object from moving
     * 
     */
    void stopMoving();

    /**
     * Determines if an object has been clicked
     * 
     * \param float xpos
     * \param float ypos
     * \param float zpos
     * \param float finalT
     * \return bool
     */
    bool isClicked(float xpos, float ypos, float zpos, float finalT) { return false; }

    /**
     * Gets the last SDF t value
     * 
     * \return float
     */
    float getLastT();

    /**
     * Returns all data relating to the object
     * 
     * \return ObjectData*
     */
    ObjectData *getData();
};

class Sphere : public Object {
protected:
    /**
     * Sphere SDF
     * 
     * \param float px
     * \param float py
     * \param float pz
     * \param float cx
     * \param float cy
     * \param float cz
     * \param float r
     * \return float
     */
    float SDF(float px, float py, float pz, float cx, float cy, float cz, float r);
public:
    /**
     * Initialises the sphere object class
     *
     * \param ObjectData data
     */
    Sphere(ObjectData data) : Object(data) {}

    bool isClicked(float xpos, float ypos, float zpos, float finalT);
};