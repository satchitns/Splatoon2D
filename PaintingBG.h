#pragma once
#define DECAL_WIDTH 32
#define DECAL_HEIGHT 32
#define COL_1 5
#define COL_2 3
#define COL_3 1

class BackgroundC
{
public:
	BackgroundC();
	~BackgroundC();
	static BackgroundC* CreateInstance();
	static BackgroundC*	GetInstance() { return sInstance; };
	void render();
	void init();
	void BackgroundC::sprayPaint(Coord2D position);
	GLuint mTexID;
private:
	GLuint mMapID;
	Coord2D decalPosition;
	bool decalPaintedInFrame = false;
	static BackgroundC* sInstance;
};

