#pragma once
class PVector {
private:
	float x, y, z, r, g, b;
public:
	PVector(float x, float y, float z, float r = 1.0, float g = 1.0, float b = 1.0) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	virtual void drawGlPVector();
	virtual PVector getProjectedPVector();
	virtual PVector rotate(float ax, float ay);
    virtual PVector crossProd(PVector v);
    virtual double dotProd(PVector v);
    virtual PVector transform(PVector v);
    virtual void scale(float m);
    virtual double getMagnitude();
	virtual void setRGB(float r, float g, float b);
    virtual float getX();
    virtual float getY();
    virtual float getZ();
    virtual void setX(float newX);
    virtual void setY(float newY);
    virtual void setZ(float newZ);
};
