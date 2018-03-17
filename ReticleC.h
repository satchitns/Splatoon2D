#include "Utils.h"

#include <Xinput.h>

#define SIZE_X 32
#define SIZE_Y 32
#define BG_SIZE_X 48
#define BG_SIZE_Y 48
#define RETICLE_SPEED 0.4f
#define MAX_RETICLE_OFFSET 300
#define VIBRATE_TIME 0.5f
#define RETICLE_VIBRATION_VALUE 15000

class ReticleC
{
public:
	ReticleC();
	~ReticleC();
	void SetPosition(DWORD milliseconds, float x, float y);
	void UpdateReticleOffset(Coord2D* playerPosition);
	void render();
	void init(int id, int playerPositionX, int playerPositionY, GLuint reticleTexID, GLuint reticleBGID);
	Coord2D ReturnPosition();
	Coord2D GetOffsetFromPlayer() { return mOffsetFromPlayer; }
	void SetOffsetFromPlayer(float x, float y) { mOffsetFromPlayer = { x, y }; }
	void SetReticleVibration(WORD leftMotor, WORD rightMotor);

private:
	float mTimeVibrated;
	static Coord2D offsetFromCenter, offsetBGFromCenter;
	int mID;
	bool mVibrated;
	Coord2D mSize;
	GLuint mTexID, mBGTexID;
	Coord2D mPosition;
	Coord2D mOffsetFromPlayer;
	Color mRenderColor;
	XINPUT_VIBRATION* vibration;

};

