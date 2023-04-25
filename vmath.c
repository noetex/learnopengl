typedef struct
{
	float Elements[16];
} matrix4;

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