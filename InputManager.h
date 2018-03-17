#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init() {};
	void					update(DWORD milliseconds);
//checkout gameframework.cpp
	Coord2D*					getCurrentMousePosition(){};
	//keyboard interface?

private:
	InputManagerC(){};
	static InputManagerC *sInstance;
	
};
#endif