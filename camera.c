#define CAMERA_PITCH_MAX ((float)M_PI/4.0f)

typedef struct
{
	vector3 Position;
	vector3 Right;
	vector3 Up;
	vector3 Front;
	float Yaw;
	float Pitch;
} camera;

static vector3
Camera_AxisX(camera Camera)
{
	vector3 Result;
	Result.X = cosf(Camera.Yaw);
	Result.Y = 0;
	Result.Z = -sinf(Camera.Yaw);
	return Result;
}

static vector3
Camera_AxisY(camera Camera)
{
	vector3 Result;
	Result.X = sinf(Camera.Yaw) * sinf(Camera.Pitch);
	Result.Y = cosf(Camera.Pitch);
	Result.Z = cosf(Camera.Yaw) * cosf(Camera.Pitch);
	return Result;
}

static vector3
Camera_AxisZ(camera Camera)
{
	vector3 Result;
	Result.X = sinf(Camera.Yaw) * cosf(Camera.Pitch);
	Result.Y = -sinf(Camera.Pitch);
	Result.Z = cosf(Camera.Yaw) * cosf(Camera.Pitch);
	return Result;
}

static matrix4
CameraView(camera* Camera)
{
	Camera->Pitch = Clamp(Camera->Pitch, -CAMERA_PITCH_MAX, CAMERA_PITCH_MAX);
	float CY = cosf(Camera->Yaw);
	float SY = sinf(Camera->Yaw);
	float CP = cosf(Camera->Pitch);
	float SP = sinf(Camera->Pitch);
	float CYCP = CY * CP;
	float CYSP = CY * SP;
	float SYCP = SY * CP;
	float SYSP = SY * SP;
	vector3 Front = {SYCP, -SP, CYCP};
	vector3 Up = {SYSP, CP, CYSP};
	vector3 Right = {CY, 0, -SY};
	matrix4 Result;
	Result.AxisX = (vector4){Right.X, Up.X, Front.X, 0};
	Result.AxisY = (vector4){Right.Y, Up.Y, Front.Y, 0};
	Result.AxisZ = (vector4){Right.Z, Up.Z, Front.Z, 0};
	Result.AxisW.X = -Vector3_Dot(Camera->Position, Right);
	Result.AxisW.Y = -Vector3_Dot(Camera->Position, Up);
	Result.AxisW.Z = -Vector3_Dot(Camera->Position, Front);
	Result.AxisW.W = 1;

	return Result;
}