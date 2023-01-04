#ifndef PRIMITIVEDATA_H
#define PRIMITIVEDATA_H



class PrimitiveData
{
public:
	PrimitiveData(double x, double y, double z,
		double width, double length, double height) : 
		m_X(x), m_Y(y), m_Z(z), m_Width(width), m_Length(length), m_Height(height)
	{
	}
	double getX() const {return m_X;}
	double getY() const {return m_Y;}
	double getZ() const {return m_Z;}
	double getWidth() const {return m_Width;}
	double getLength() const {return m_Length;}
	double getHeight() const {return m_Height;}


private:
	double m_X;
	double m_Y;
	double m_Z;
	double m_Width;
	double m_Length;
	double m_Height;
};

#endif //PRIMITIVEDATA_H