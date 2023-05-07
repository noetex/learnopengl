typedef struct
{
	vector3 Position;
	vector3 Right;
	vector3 Up;
	vector3 Front;
	float Yaw;
	float Pitch;
} camera;

#if 0
static matrix4
CameraView(camera Camera)
{
	matrix4 Translation = Matrix4_Translate(Vector3_Scale(Camera.Position, -1));
	matrix4 Transform;
	Transform.AxisX = (vector4){Camera.Right.X, Camera.Up.X, Camera.Front.X, 0};
	Transform.AxisY = (vector4){Camera.Right.Y, Camera.Up.Y, Camera.Front.Y, 0};
	Transform.AxisZ = (vector4){Camera.Right.Z, Camera.Up.Z, Camera.Front.Z, 0};
	Transform.AxisW = Vector4_UnitW();
	matrix4 Result = Matrix4_MultiplyMatrix4(Transform, Translation);
	return Result;
}
#endif

static matrix4
CameraView(camera Camera)
{
	float CY = cosf(Camera.Yaw);
	float SY = sinf(Camera.Yaw);
	float CP = cosf(Camera.Pitch);
	float SP = sinf(Camera.Pitch);
	float CYCP = CY * CP;
	float CYSP = CY * SP;
	float SYCP = SY * CP;
	float SYSP = SY * SP;
	vector3 Front = {SYCP, -SP, CYCP};
	vector3 Up = {SYSP, CP, CYSP};
	vector3 Right = {CY, 0, -SY};
	Assert(Camera.Pitch <= M_PI/2);
	matrix4 Result;
	Result.AxisX = (vector4){Right.X, Up.X, Front.X, 0};
	Result.AxisY = (vector4){Right.Y, Up.Y, Front.Y, 0};
	Result.AxisZ = (vector4){Right.Z, Up.Z, Front.Z, 0};
	Result.AxisW.X = -Vector3_Dot(Camera.Position, Right);
	Result.AxisW.Y = -Vector3_Dot(Camera.Position, Up);
	Result.AxisW.Z = -Vector3_Dot(Camera.Position, Front);
	Result.AxisW.W = 1;

	return Result;
}