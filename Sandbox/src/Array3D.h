#pragma once
class Array3D
{
public:
	Array3D();
	Array3D(int lengthX, int lengthY, int lengthZ);
	Array3D(int lengthX, int lengthY, int lengthZ, int* data);

	~Array3D();

	int GetDimX() { return m_X; }
	int GetDimY() { return m_Y; }
	int GetDimZ() { return m_Z; }

	unsigned char* GetData() { return m_Array; }
	int GetDataSize() { return m_X * m_Y * m_Z; }
	int GetIndex(int x, int y, int z, int zSize = 0);

	unsigned char GetIndexed(int x, int y, int z);

	void SetIndexed(int x, int y, int z, int value);
	void SetIndexed(int x, int y, int z[]);

	bool SetUniformArray(int value);
	bool SetUniformArray(int value[]);

	// Returns True if the arrays are dimensionally equivelent
	bool SetArrayCopy(int x, int y, int z, int* data);
	bool SetArrayCopy(int x, int y, int z, unsigned char* data);

	// Returns true if the dimensions are the same
	bool operator==(const Array3D& other) const;

protected:
	int m_X = 1;
	int m_Y = 1;
	int m_Z = 1;

	unsigned char* m_Array;
};

