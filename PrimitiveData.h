#ifndef PRIMITIVEDATA_H
#define PRIMITIVEDATA_H

#include <string>

enum PrimitiveType
{
	None = 0,
	Cuboid,
	Pyramid,
	Cylinder,
	Cone,
	Sphere,
	Torus
};

class PrimitiveData
{
public:

	PrimitiveData(const PrimitiveType primitiveTypeIn, double x, double y, double z,
				  double width, double length, double height) : m_PrimitiveType(primitiveTypeIn), m_X(x), m_Y(y), m_Z(z), m_Width(width), m_Length(length), m_Height(height)
	{
	}
	double getX() const { return m_X; }
	double getY() const { return m_Y; }
	double getZ() const { return m_Z; }
	double getWidth() const { return m_Width; }
	double getLength() const { return m_Length; }
	double getHeight() const { return m_Height; }
	PrimitiveType getPrimitiveType() const { return m_PrimitiveType; }

private:
	PrimitiveType m_PrimitiveType;
	double m_X;
	double m_Y;
	double m_Z;
	double m_Width;
	double m_Length;
	double m_Height;
};

#endif // PRIMITIVEDATA_H