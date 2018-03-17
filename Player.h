#include "ReticleC.h"
#include "Utils.h"
#include "Collider.h"
#include "UI.h"
#include "ScoreUI.h"

#define NORMAL_SPEED 0.2f
#define SQUID_SPEED 0.3f
#define ENEMY_SPEED 0.1f

#define ANIMATION_FPS 30
#define MILLISECONDS_PER_FRAME (1000.0f/ANIMATION_FPS)

#define NUM_ANIM_SPRITES 3
#define NUM_ANIM_STATES 4

#define SPRITE_VERTICAL_SECTIONS 8
#define SPRITE_HORIZONTAL_SECTIONS 12

#define SPRITE_SECTION_HEIGHT 32
#define SPRITE_SECTION_WIDTH 32

#define SPRITE_PATH "Sprites/splatoon2D.png"

#define UP_ANIM_OFFSET 4
#define DOWN_ANIM_OFFSET 7
#define LEFT_ANIM_OFFSET 6
#define RIGHT_ANIM_OFFSET 5

#define DAMAGE_PER_SECOND 2.0f

#define SQUID_STATE_COOLDOWN_TIME 0.35f

#define MAX_PAINT_AMMO 500
#define AMMO_MULTIPLIER_SQUID 150
#define AMMO_MULTIPLIER_DEFAULT 0.1f
#define HEALTH_MULTIPLIER_DEFAULT 0.05f
#define HEALTH_MULTIPLIER_BOOST 0.1f

#define MAX_PLAYER_COUNT 4

#define MIN_AMMO_REQUIRED 20.0f

#define RESPAWN_TIME 5.0f
#define INVULNERABILITY_TIME 2.0f

#define NO_AMMO_SOUND_TIME_ELAPSED 0.6f
#define SHOOT_SOUND_TIME_ELAPSED 0.25f

#define DEFAULT_PAINT_RADIUS_MODIFIER 0.2f
#define MAX_PAINT_RADIUS_MODIFIER 1.0f
#define PAINT_RADIUS_INCREASE_PER_SECOND 1.75f
#define START_DEATH_RADIUS_MODIFIER 1.0f
#define MAX_DEATH_RADIUS_MODIFIER 2.0f
#define DEATH_PAINT_RADIUS_INCREASE_PER_SECOND 7.0f

#define MAX_COLOR 255

#define LERP_SECONDS 0.25f
enum moveDirection
{
	MOVE_INVALID,
	LEFT, 
	RIGHT,
	UP,
	DOWN,
	MOVE_MAX
};

class PlayerC: public ObjectC
{
public:
	static PlayerC	*CreateInstanceByID(int id);
	static PlayerC	*GetInstanceByID(int id) { return sInstance[id]; };
	PlayerC();
	PlayerC(float_t initPosX, float_t initPosY, float_t velX, float_t velY, int id);
	~PlayerC();
	void move(DWORD milliseconds, float axisValueX, float axisValueY);

	void paint();
	void updateSpriteAnimStateAndReticleOffset(DWORD milliseconds, float axisValueX, float axisValueY);
	void update(DWORD milliseconds);
	bool GetSquidState() { return squidState; };
	void SetSquidState();
	void ClearSquidState();
	void render();
	ColorT getColor(){ return mPlayerColor; };
	int	getID() { return mPlayerID; };
	void init(int id, GLuint texID, GLuint reticleTexID, GLuint reticleBGTexID, GLuint UI_BG_ID, GLuint UIFillID, GLuint *numTexes);
	void reticleRender();
	void ApplyDamage(int playerID, ColorT playerColor);
	void UIUpdate();
	bool GetIsDead() { return mIsDead; }
	void DeathUIUpdate();
	Collider* GetPlayerCollider() { return &mPlayerCollider; }

	ReticleC mReticle;
	void lerpColor(float time);
private:
	UI HP_UI, PaintUI;
	int mLastEnemyID;
	ScoreUI mScoreUI, mRespawnUI;
	GLuint mReticleTexID, mBGTexture, mFillTexture, mReticleBGTexID;
	GLuint *mNumTexes;
	float squidStateCooldownTimer = 0;
	float mAmmoLeft = MAX_PAINT_AMMO;
	bool squidState = false;
	float mPaintRadiusModifier = DEFAULT_PAINT_RADIUS_MODIFIER;
	void recomputeUV();
	ColorT mPlayerColor;
	Color mPlayerSpriteColor;
	static Coord2D offsetFromCenter;
	bool mMovedThisFrame = false;
	int mPlayerID = 1;
	int mCurrentAnimFrame = 0;
	int mCurrentAnimState = LEFT_ANIM_OFFSET;
	DWORD mTimeSinceLastFrame = 0;
	Coord2D mSize;
	Coord2D minUV, maxUV;
	GLuint mTexID;
	bool mIsGrounded = true;
	bool mHasJumped = false;
	static PlayerC *sInstance[MAX_PLAYER_COUNT];

	bool mIsMoving;
	bool mPaintedLastFrame = false;
	Collider mPlayerCollider;
	ColorT mLastEnemyColor;
	float mHealth;
	float mDamage;
	bool mHasTakenDamage;
	bool mIsDead;
	float mRespawnTimeRemaining;
	bool mRanOutOfAmmo;
	float mRespawnLerpTime;
	bool mLerpingUp;
	bool mIsInvulnerable;
	float mInvulnerabilityDuration;

	bool mSquidModeSoundPlayed;

	float mTimeElapsedSinceSoundPlayStart;

};

