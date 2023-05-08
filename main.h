#ifndef APIENTRY
	#define APIENTRY WINAPI
#endif
#define break_if(Condition) if(!(Condition)); else break
#define return_if(Condition) if(!(Condition)); else return
#define Assert(Condition) if(Condition); else __debugbreak()
#define Min(A, B) (((A) < (B)) ? (A) : (B))
#define Max(A, B) (((A) > (B)) ? (A) : (B))
#define Clamp(Value, Lo, Hi) (Min(Hi, Max(Lo, Value)))