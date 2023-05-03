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

typedef struct
{
	vector4 AxisX;
	vector4 AxisY;
	vector4 AxisZ;
	vector4 AxisW;
} matrix4;

static vector3
Vector3_UnitY(void)
{
	vector3 Result = {0, 1, 0};
	return Result;
}

static vector3
Vector3_Sub(vector3 V1, vector3 V2)
{
	vector3 Result;
	Result.X = V1.X - V2.X;
	Result.Y = V1.Y - V2.Y;
	Result.Z = V1.Z - V2.Z;
	return Result;
}

static vector3
Vector3_Scale(vector3 V, float Scale)
{
	vector3 Result;
	Result.X = V.X * Scale;
	Result.Y = V.Y * Scale;
	Result.Z = V.Z * Scale;
	return Result;
}

static float
Vector3_Dot(vector3 V1, vector3 V2)
{
	float Result = (V1.X * V2.X) + (V1.Y * V2.Y) + (V1.Z * V2.Z);
	return Result;
}

static vector3
Vector3_Cross(vector3 V1, vector3 V2)
{
	vector3 Result;
	Result.X = (V1.Y * V2.Z) - (V1.Z * V2.Y);
	Result.Y = (V1.Z * V2.X) - (V1.X * V2.Z);
	Result.Z = (V1.X * V2.Y) - (V1.Y * V2.X);
	return Result;
}

static float
Vector3_Length2(vector3 V)
{
	float Result = Vector3_Dot(V, V);
	return Result;
}

static float
Vector3_Length(vector3 V)
{
	float Length2 = Vector3_Length2(V);
	float Result = sqrtf(Length2);
	return Result;
}

static vector3
Vector3_Unit(vector3 V)
{
	float Length2 = Vector3_Length2(V);
	if((Length2 == 0) || (Length2 == 1))
	{
		return V;
	}
	float Length = sqrtf(Length2);
	vector3 Result = Vector3_Scale(V, 1/Length);
	return Result;
}

static vector4
Vector4_UnitX(void)
{
	vector4 Result = {1, 0, 0, 0};
	return Result;
}

static vector4
Vector4_UnitY(void)
{
	vector4 Result = {0, 1, 0, 0};
	return Result;
}

static vector4
Vector4_UnitZ(void)
{
	vector4 Result = {0, 0, 1, 0};
	return Result;
}

static vector4
Vector4_UnitW(void)
{
	vector4 Result = {0, 0, 0, 1};
	return Result;
}

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
	Result.AxisX = Matrix4_MultiplyVector4(M2, M1.AxisX);
	Result.AxisY = Matrix4_MultiplyVector4(M2, M1.AxisY);
	Result.AxisZ = Matrix4_MultiplyVector4(M2, M1.AxisZ);
	Result.AxisW = Matrix4_MultiplyVector4(M2, M1.AxisW);
	return Result;
}

static matrix4
Matrix4_Scale(vector3 Factor)
{
	matrix4 Result;
	Result.AxisX = (vector4){Factor.X, 0, 0, 0};
	Result.AxisY = (vector4){0, Factor.Y, 0, 0};
	Result.AxisZ = (vector4){0, 0, Factor.Z, 0};
	Result.AxisW = Vector4_UnitW();
	return Result;
}

static matrix4
Matrix4_RotateX(float Angle)
{
	float C = cosf(Angle);
	float S = sinf(Angle);
	matrix4 Result;
	Result.AxisX = Vector4_UnitX();
	Result.AxisY = (vector4){0, C, S, 0};
	Result.AxisZ = (vector4){0, -S, C, 0};
	Result.AxisW = Vector4_UnitW();
	return Result;
}

static matrix4
Matrix4_RotateY(float Angle)
{
	float C = cosf(Angle);
	float S = sinf(Angle);
	matrix4 Result;
	Result.AxisX = (vector4){C, 0, -S, 0};
	Result.AxisY = Vector4_UnitY();
	Result.AxisZ = (vector4){S, 0, C, 0};
	Result.AxisW = Vector4_UnitW();
	return Result;
}

static matrix4
Matrix4_RotateZ(float Angle)
{
	float C = cosf(Angle);
	float S = sinf(Angle);
	matrix4 Result;
	Result.AxisX = (vector4){C, S, 0, 0};
	Result.AxisY = (vector4){-S, C, 0, 0};
	Result.AxisZ = Vector4_UnitZ();
	Result.AxisW = Vector4_UnitW();
	return Result;
}

static matrix4
Matrix4_RotateAround(vector3 Axis, float Angle)
{
	Axis = Vector3_Unit(Axis);
	float C = cosf(Angle);
	float S = sinf(Angle);
	float OMC = 1 - C;
	float X2 = Axis.X * Axis.X;
	float Y2 = Axis.Y * Axis.Y;
	float Z2 = Axis.Z * Axis.Z;
	float XY = Axis.X * Axis.Y;
	float XZ = Axis.X * Axis.Z;
	float YZ = Axis.Y * Axis.Z;
	matrix4 Result;
	Result.AxisX.X = X2*OMC + C;
	Result.AxisX.Y = XY*OMC + Axis.Z*S;
	Result.AxisX.Z = XZ*OMC - Axis.Y*S;
	Result.AxisX.W = 0;
	Result.AxisY.X = XY*OMC - Axis.Z*S;
	Result.AxisY.Y = Y2*OMC + C;
	Result.AxisY.Z = YZ*OMC + Axis.X*S;
	Result.AxisY.W = 0;
	Result.AxisZ.X = XZ*OMC + Axis.Y*S;
	Result.AxisZ.Y = YZ*OMC - Axis.X*S;
	Result.AxisZ.Z = Z2*OMC + C;
	Result.AxisZ.W = 0;
	Result.AxisW = Vector4_UnitW();
	return Result;
}

static matrix4
Matrix4_Translate(vector3 Translation)
{
	matrix4 Result;
	Result.AxisX = Vector4_UnitX();
	Result.AxisY = Vector4_UnitY();
	Result.AxisZ = Vector4_UnitZ();
	Result.AxisW = (vector4){Translation.X, Translation.Y, Translation.Z, 1};
	return Result;
}

static matrix4
Matrix4_Perspective(float FieldOfView, float AspectRatio, float Near, float Far)
{
	float F = 1/tanf(FieldOfView/2);
	float Q = 1/(Near - Far);
	matrix4 Result;
	Result.AxisX = (vector4){AspectRatio*F, 0, 0, 0};
	Result.AxisY = (vector4){0, F, 0, 0};
	Result.AxisZ = (vector4){0, 0, Q*(Far+Near), -1};
	Result.AxisW = (vector4){0, 0, Q*(2*Far*Near), 0};
	return Result;
}

static matrix4
Matrix4_LookAt(vector3 From, vector3 To, vector3 UpDirection)
{
	vector3 LookDirection = Vector3_Sub(To, From);
	vector3 RightDirection = Vector3_Cross(UpDirection, LookDirection);
	vector3 Front = Vector3_Unit(LookDirection);
	vector3 Right = Vector3_Unit(RightDirection);
	vector3 Up = Vector3_Unit(UpDirection);
	matrix4 Transform;
	Transform.AxisX = (vector4){Right.X, Up.X, Front.X, 0};
	Transform.AxisY = (vector4){Right.Y, Up.Y, Front.Y, 0};
	Transform.AxisZ = (vector4){Right.Z, Up.Z, Front.Z, 0};
	Transform.AxisW = Vector4_UnitW();
	matrix4 Translation = Matrix4_Translate(Vector3_Scale(From, 1));
	matrix4 Result = Matrix4_MultiplyMatrix4(Transform, Translation);
	return Result;
}