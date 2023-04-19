#include "Array3D.h"

Array3D::Array3D()
{
    m_Array = new unsigned char[GetDataSize()];
}

Array3D::Array3D(int lengthX, int lengthY, int lengthZ)
{
    m_X = lengthX;
    m_Y = lengthY;
    m_Z = lengthZ;

    m_Array = new unsigned char[GetDataSize()];
}

Array3D::Array3D(int lengthX, int lengthY, int lengthZ, int* data)
{
    m_X = lengthX;
    m_Y = lengthY;
    m_Z = lengthZ;

    m_Array = new unsigned char[GetDataSize()];
    SetArrayCopy(m_X, m_Y, m_Z, data);

}

Array3D::~Array3D()
{
    delete[] m_Array;
}

unsigned char Array3D::GetIndexed(int x, int y, int z)
{
    return m_Array[x * m_Y * m_Z + y * m_Z + z];
}

void Array3D::SetIndexed(int x, int y, int z, int value)
{
    m_Array[x * m_Y * m_Z + y * m_Z + z] = value;
}

void Array3D::SetIndexed(int x, int y, int z[])
{
    for (int i = 0; i < m_Z; i++)
    {
        m_Array[x * m_Y * m_Z + y * m_Z + i] = z[i];
    }
}

bool Array3D::SetUniformArray(int value)
{
    for (int x = 0; x < m_X; x++)
    {
        for (int y = 0; y < m_Y; y++)
        {
            for (int z = 0; z < m_Z; z++)
            {
                SetIndexed(x, y, z, value);
            }
        }
    }

    return true;
}

bool Array3D::SetUniformArray(int value[])
{
    for (int x = 0; x < m_X; x++)
    {
        for (int y = 0; y < m_Y; y++)
        {
            SetIndexed(x, y, value);
        }
    }
    return true;
}

bool Array3D::SetArrayCopy(int x, int y, int z, int* data)
{
    return SetArrayCopy(x, y, z, (unsigned char*)data);
}

bool Array3D::SetArrayCopy(int x, int y, int z, unsigned char* data)
{
    // Check Dimensionality
    if (x != m_X || y != m_Y || z != m_Z)
        return false;

    *m_Array = *data;
    return true;
}

bool Array3D::operator==(const Array3D& other) const
{
    return m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z;
}
