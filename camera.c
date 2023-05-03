typedef struct
{
	vector3 Position;
	vector3 Right;
	vector3 Up;
	vector3 Front;
} camera;

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