typedef struct
{
	float X;
	float Y;
	float Z;
} vector3;

typedef struct
{
	float X;
	float Y;
	float Z;
	float W;
} vector4;

typedef union
{
	float Elements[16];
	struct
	{
		vector4 AxisX;
		vector4 AxisY;
		vector4 AxisZ;
		vector4 AxisW;
	};
} matrix4;

static vector4
Vector4_Add(vector4 A, vector4 B)
{
	vector4 Result;
	Result.X = A.X + B.X;
	Result.Y = A.Y + B.Y;
	Result.Z = A.Z + B.Z;
	Result.W = A.W + B.W;
	return Result;
}

static vector4
Vector4_Scale(vector4 Vector, float Scale)
{
	vector4 Result;
	Result.X = Vector.X * Scale;
	Result.Y = Vector.Y * Scale;
	Result.Z = Vector.Z * Scale;
	Result.W = Vector.W * Scale;
	return Result;
}

static vector4
Matrix4_MultiplyVector4(matrix4 Matrix, vector4 Vector)
{
	vector4 Result = Vector4_Scale(Matrix.AxisX, Vector.X);
	Result = Vector4_Add(Result, Vector4_Scale(Matrix.AxisY, Vector.Y));
	Result = Vector4_Add(Result, Vector4_Scale(Matrix.AxisZ, Vector.Z));
	Result = Vector4_Add(Result, Vector4_Scale(Matrix.AxisW, Vector.W));
	return Result;
}

static matrix4
Matrix4_MultiplyMatrix4(matrix4 M2, matrix4 M1)
{
	matrix4 Result;
	Result.AxisX = Matrix4_MultiplyVector4(M1, M2.AxisX);
	Result.AxisY = Matrix4_MultiplyVector4(M1, M2.AxisY);
	Result.AxisZ = Matrix4_MultiplyVector4(M1, M2.AxisZ);
	Result.AxisW = Matrix4_MultiplyVector4(M1, M2.AxisW);
	return Result;
}

static matrix4
Matrix4_Scale(vector3 Factor)
{
	matrix4 Result =
	{
		Factor.X, 0, 0, 0,
		0, Factor.Y, 0, 0,
		0, 0, Factor.Z, 0,
		0, 0, 0, 1,
	};
	return Result;
}

static matrix4
Matrix4_RotateZ(float Angle)
{
	float C = cosf(Angle);
	float S = sinf(Angle);
	matrix4 Result =
	{
		C, -S, 0, 0,
		S, C, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	return Result;
}

static matrix4
Matrix4_Translate(vector3 Translation)
{
	matrix4 Result =
	{
		1, 0, 0, Translation.X,
		0, 1, 0, Translation.Y,
		0, 0, 1, Translation.Z,
		0, 0, 0, 1, 
	};
	return Result;
}