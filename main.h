#ifndef APIENTRY
	#define APIENTRY WINAPI
#endif
#define break_if(Condition) if(!(Condition)); else break
#define return_if(Condition) if(!(Condition)); else return
#define Assert(Condition) if(Condition); else __debugbreak()