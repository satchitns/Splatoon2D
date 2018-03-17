#pragma once

#define UI_WIDTH 40
#define UI_HEIGHT 8
#define PAINT_OFFSET UI_HEIGHT
#define HP_OFFSET PAINT_OFFSET + UI_HEIGHT + 1

enum UIType
{
	INVALID,
	HP,
	PAINT,
	MAX
};

class UI
{
public:
	UI();
	~UI();
	void init(GLuint BGTexID, GLuint FillTexID, Coord2D offset, UIType type, Color color = { 0,0,0,255 });
	void render();
	void update(Coord2D position, float amount);
private:
	UIType mUIType;
	float mAmount;
	Coord2D mOffset;
	Coord2D mPosition, mSize;
	GLuint mBGTexID, mFillTexID;
	Color mColor;
};

