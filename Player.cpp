#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"


#include "collInfo.h"

#include "Object.h"
#include "Utils.h"
#include "game.h"
#include "RenderSprites.h"
#include "UI.h"
#include "Player.h"
#include "Background.h"
#include "SOIL.h"
#include "AudioManager.h"

#define MAX_HEALTH 100
#define DAMAGE_PER_SHOT 500

#define M_PI (3.14159265358979323846)

#define COLLISION_PUSH 0.05f

#define SPAWN_OFFSET_VALUE 100

int XOffsets[MAX_PLAYER_COUNT] = { SPAWN_OFFSET_VALUE, SPAWN_OFFSET_VALUE, -SPAWN_OFFSET_VALUE, -SPAWN_OFFSET_VALUE };
int YOffsets[MAX_PLAYER_COUNT] = { SPAWN_OFFSET_VALUE, -SPAWN_OFFSET_VALUE, SPAWN_OFFSET_VALUE, -SPAWN_OFFSET_VALUE };

PlayerC* PlayerC::sInstance[MAX_PLAYER_COUNT] = { NULL };
Coord2D PlayerC::offsetFromCenter = { (float)SPRITE_SECTION_WIDTH / 2, (float)SPRITE_SECTION_HEIGHT / 2 };
PlayerC* PlayerC::CreateInstanceByID(int id)
{
	if (sInstance[id] != NULL)
	{
		return sInstance[id];
	}
	else
	{
		sInstance[id] = new PlayerC();
	}
	return sInstance[id];
}
PlayerC::PlayerC()
{
}

PlayerC::PlayerC(float_t initPosX, float_t initPosY, float_t velX, float_t velY, int id)
{
	mPosition.x = initPosX;
	mPosition.y = initPosY;
}

void PlayerC::init(int id, GLuint texID, GLuint reticleTexID, GLuint reticleBGTexID, GLuint UIBGID, GLuint UIFillID, GLuint *numTexes)
{
	mPlayerID = id;
	mNumTexes = numTexes;
	mScoreUI.init(mNumTexes);
	mRespawnUI.init(mNumTexes, true);
	int xOffset = XOffsets[id];
	int yOffset = YOffsets[id];

	if (xOffset > 0)
	{
		mPosition.x = CGame::mViewingVolumeXMax - xOffset;
	}
	else if (xOffset < 0)
	{
		mPosition.x = CGame::mViewingVolumeXMin - xOffset;
	}

	if (yOffset > 0)
	{
		mPosition.y = CGame::mViewingVolumeYMax - yOffset;
	}
	else if (yOffset < 0)
	{
		mPosition.y = CGame::mViewingVolumeYMin - yOffset;
	}
	mPaintedLastFrame = false;
	mVelocity.x = NORMAL_SPEED;
	mVelocity.y = NORMAL_SPEED;
	mSize.x = SPRITE_SECTION_WIDTH;
	mSize.y = SPRITE_SECTION_HEIGHT;
	recomputeUV();
	mLerpingUp = true;
	mReticleTexID = reticleTexID;
	mReticleBGTexID = reticleBGTexID;
	mReticle.init(id, mPosition.x, mPosition.y, mReticleTexID, mReticleBGTexID);
	mTexID = texID;
	switch (id)
	{
	case 0:
		mPlayerColor = BLUE;
		break;
	case 1:
		mPlayerColor = ORANGE;
		break;
	case 2:
		mPlayerColor = GREEN;
		break;
	case 3:
		mPlayerColor = PINK;
		break;
	default:
		break;
	}

	mIsDead = false;
	mHealth = MAX_HEALTH;
	mDamage = DAMAGE_PER_SHOT;
	mIsInvulnerable = true;
	mInvulnerabilityDuration = INVULNERABILITY_TIME;
	mRespawnLerpTime = 0;
	mAmmoLeft = MAX_PAINT_AMMO;
	
	mBGTexture = UIBGID;
	mFillTexture = UIFillID;
	HP_UI.init(UIBGID, UIFillID, { 0, 0 }, HP, ReturnColorFromEnum(mPlayerColor));
	PaintUI.init(UIBGID, UIFillID, { 0, 0 }, PAINT, ReturnColorFromEnum(mPlayerColor));
	mPlayerCollider.init(mPosition.x , mPosition.y, ((mSize.x/2)), ((mSize.y/2)));

	mHasTakenDamage = false;
	mSquidModeSoundPlayed = false;
	UIUpdate();
	mTimeElapsedSinceSoundPlayStart = NO_AMMO_SOUND_TIME_ELAPSED;

}

PlayerC::~PlayerC()
{

}

void PlayerC::recomputeUV()
{
	minUV.x = (float)(((mPlayerID) * NUM_ANIM_SPRITES + 1.0f/(SPRITE_SECTION_WIDTH)) +  mCurrentAnimFrame); //1 value chosen by trial-and-error
	minUV.y = (float)(mCurrentAnimState);
	if (squidState)
	{
		minUV.y -= NUM_ANIM_STATES;
	}
	maxUV.x = minUV.x + (((float)SPRITE_SECTION_WIDTH - 2)/ SPRITE_SECTION_WIDTH); //2 value chosen by trial-and-error
	maxUV.y = minUV.y + (((float)SPRITE_SECTION_HEIGHT) / SPRITE_SECTION_HEIGHT); 
	minUV.x /= SPRITE_HORIZONTAL_SECTIONS;
	maxUV.x /= SPRITE_HORIZONTAL_SECTIONS;
	minUV.y /= SPRITE_VERTICAL_SECTIONS;
	maxUV.y /= SPRITE_VERTICAL_SECTIONS;
	
}

void PlayerC::SetSquidState()
{
	if (BackgroundC::getInstance()->returnColorAtPoint(mPosition) == mPlayerColor)
	{
		squidState = true;
		squidStateCooldownTimer = SQUID_STATE_COOLDOWN_TIME;
		recomputeUV();
	}
}

void PlayerC::ClearSquidState()
{
	if (squidState)
	{
		squidState = false;
		recomputeUV();
	}
}

void PlayerC::render()
{
	if (!mIsDead)
	{
		RenderSprites({ mPosition.x - offsetFromCenter.x , mPosition.y - offsetFromCenter.y }, mSize, mTexID, minUV, maxUV, false, mPlayerSpriteColor);
	}
}

void PlayerC::reticleRender()
{
	if (!mIsDead)
	{
		if (squidStateCooldownTimer <= 0)
		{
			mReticle.render();
		}
		HP_UI.render();
		PaintUI.render();
		mScoreUI.render();
	}
	else
	{
		mRespawnUI.render();
	}
}

void PlayerC::move(DWORD milliseconds, float axisValueX, float axisValueY)
{
	if (!mIsDead)
	{
		mPosition.x += mVelocity.x * milliseconds * axisValueX;
		mPosition.y += mVelocity.y * milliseconds * axisValueY;
		mMovedThisFrame = true;

		updateSpriteAnimStateAndReticleOffset(milliseconds, 0.0f, 0.0f);

		if (squidState)
		{
			if (abs((int)(axisValueX * 1000)) > abs((int)(axisValueY * 1000)))
			{
				if (axisValueX >= 0)
				{
					mCurrentAnimState = RIGHT_ANIM_OFFSET;
				}
				else if (axisValueX < 0)
				{
					mCurrentAnimState = LEFT_ANIM_OFFSET;
				}
			}
			else {
				if (axisValueY >= 0)
				{
					mCurrentAnimState = UP_ANIM_OFFSET;
				}
				else if (axisValueY < 0)
				{
					mCurrentAnimState = DOWN_ANIM_OFFSET;
				}
			}
			recomputeUV();
		}
		if (mPosition.x > (float)CGame::mViewingVolumeXMax)
		{
			mPosition.x = CGame::mViewingVolumeXMax;
		}
		else if (mPosition.x < (float)CGame::mViewingVolumeXMin)
		{
			mPosition.x = CGame::mViewingVolumeXMin;
		}

		if (mPosition.y > (float)CGame::mViewingVolumeYMax)
		{
			mPosition.y = CGame::mViewingVolumeYMax;
		}
		else if (mPosition.y < (float)CGame::mViewingVolumeYMin)
		{
			mPosition.y = CGame::mViewingVolumeYMin;
		}

		mIsMoving = true;
	}
}

void PlayerC::lerpColor(float time)
{
	Color playerColor = ReturnColorFromEnum(mPlayerColor);
	mPlayerSpriteColor.R = (1 - time) * MAX_COLOR + time * playerColor.R;
	mPlayerSpriteColor.G = (1 - time) * MAX_COLOR + time * playerColor.G;
	mPlayerSpriteColor.B = (1 - time) * MAX_COLOR + time * playerColor.B;
	mPlayerSpriteColor.A = (1 - time) * MAX_COLOR;
}

void PlayerC::paint()
{
	if (!mIsDead)
	{
		mPaintedLastFrame = true;
		if ((!mRanOutOfAmmo) && (squidStateCooldownTimer <= 0))
		{
			mAmmoLeft--;
			BackgroundC::getInstance()->sprayPaint(mReticle.ReturnPosition(), mPlayerColor, mPlayerID, mPaintRadiusModifier);
			if (mTimeElapsedSinceSoundPlayStart >= SHOOT_SOUND_TIME_ELAPSED)
			{
				AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetShootSound2(), false);
				mTimeElapsedSinceSoundPlayStart = 0.0f;
			}
			Coord2D reticlePosition = this->mReticle.ReturnPosition();

			for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			{
				if (sInstance[i] != this)
				{
					if ((mReticle.ReturnPosition().x >= (sInstance[i]->getPosition()->x - (sInstance[i]->mSize.x / 2))) &&
						(mReticle.ReturnPosition().x <= (sInstance[i]->getPosition()->x + (sInstance[i]->mSize.x / 2))) &&
						(mReticle.ReturnPosition().y >= (sInstance[i]->getPosition()->y - (sInstance[i]->mSize.y / 2))) &&
						(mReticle.ReturnPosition().y <= (sInstance[i]->getPosition()->y + (sInstance[i]->mSize.y / 2))))
					{
						if (!mHasTakenDamage)
						{
							if (mTimeElapsedSinceSoundPlayStart >= NO_AMMO_SOUND_TIME_ELAPSED)
							{
								AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetHitPlayerSound(), false);
							}
							if(!GetInstanceByID(i)->mIsInvulnerable)
								GetInstanceByID(i)->ApplyDamage(mPlayerID, mPlayerColor);
						}
					}
				}
			}

		}
		else if (mRanOutOfAmmo)
		{
			if (mTimeElapsedSinceSoundPlayStart >= NO_AMMO_SOUND_TIME_ELAPSED)
			{
				AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetNoDamageSound(), false);
				mTimeElapsedSinceSoundPlayStart = 0.0f;
			}
		}
	}
}

void PlayerC::ApplyDamage(int playerID, ColorT playerColor)
{
	if (!squidState)
	{
		mLastEnemyID = playerID;
		mLastEnemyColor = playerColor;
		mHasTakenDamage = true;
	}
}

void PlayerC::updateSpriteAnimStateAndReticleOffset(DWORD milliseconds, float axisValueX, float axisValueY)
{
	mReticle.SetPosition(milliseconds, axisValueX, axisValueY);

	
		float angle;


		if (!squidState)
		{

			mReticle.UpdateReticleOffset(PlayerC::getPosition());
			if (mReticle.GetOffsetFromPlayer().x == 0.0f && mReticle.GetOffsetFromPlayer().y < 0.0f)
			{
				angle = 90;
			}
			else if (mReticle.GetOffsetFromPlayer().x == 0 && mReticle.GetOffsetFromPlayer().y > 0.0f)
			{
				angle = 270;
			}
			else
			{
				float gradient = (float)mReticle.GetOffsetFromPlayer().y / mReticle.GetOffsetFromPlayer().x;
				angle = -atan(gradient) * 180 / M_PI;
				if (mReticle.GetOffsetFromPlayer().x < 0)
				{
					angle += 180;
				}
				else if (mReticle.GetOffsetFromPlayer().y > 0)
				{
					angle += 360;
				}
			}

			if (angle <= 45 || angle > 315)
			{
				mCurrentAnimState = RIGHT_ANIM_OFFSET;

			}
			else if (angle > 45 && angle <= 135)
			{
				mCurrentAnimState = DOWN_ANIM_OFFSET;
			}
			else if (angle > 135 && angle <= 225)
			{
				mCurrentAnimState = LEFT_ANIM_OFFSET;
			}
			else if (angle > 225 && angle <= 315)
			{
				mCurrentAnimState = UP_ANIM_OFFSET;
			}
			recomputeUV();
		}
		
}

void PlayerC::UIUpdate()
{
	HP_UI.update({ mPosition.x - (float)UI_WIDTH / 2 , mPosition.y + offsetFromCenter.y + HP_OFFSET }, (float)mHealth / MAX_HEALTH);
	PaintUI.update({ mPosition.x - (float)UI_WIDTH / 2 , mPosition.y + offsetFromCenter.y + PAINT_OFFSET }, (float)mAmmoLeft / MAX_PAINT_AMMO);
	mScoreUI.update(BackgroundC::getInstance()->getPlayerScore(mPlayerID), { mPosition.x - (float)SCORE_UI_WIDTH * 1.5f, mPosition.y + offsetFromCenter.y + PAINT_OFFSET + HP_OFFSET + SCORE_PADDING });
}
void PlayerC::update(DWORD milliseconds)
{

	if (!mIsDead)
	{

		//invulnerability stuff
		if (mIsInvulnerable)
		{
			mInvulnerabilityDuration -= (float)milliseconds / 1000;
			if (mInvulnerabilityDuration <= 0.0f)
			{
				mIsInvulnerable = false;
			}
			if (mLerpingUp)
			{
				if (mRespawnLerpTime < LERP_SECONDS)
				{
					mRespawnLerpTime += (float)milliseconds / 1000;
				}
				else 
				{
					mLerpingUp = false;
				}
			}
			else
			{
				if (mRespawnLerpTime > 0)
				{
					mRespawnLerpTime -= (float)milliseconds / 1000;
				}
				else
				{
					mLerpingUp = true;
				}
			}
			lerpColor(mRespawnLerpTime);
		}
		else {
			mPlayerSpriteColor = { MAX_COLOR, MAX_COLOR, MAX_COLOR, MAX_COLOR };
		}
		
		UIUpdate();
		mTimeElapsedSinceSoundPlayStart += (float)milliseconds / 1000;
		if (mHasTakenDamage)
		{
			mHealth -= DAMAGE_PER_SHOT * (float)milliseconds / 1000;
			mHasTakenDamage = false;
		}
		if (!mPaintedLastFrame)
		{
			mPaintRadiusModifier = DEFAULT_PAINT_RADIUS_MODIFIER;
		}
		else
		{
			mPaintRadiusModifier += (float)milliseconds/1000 * PAINT_RADIUS_INCREASE_PER_SECOND;
			if (mPaintRadiusModifier > MAX_PAINT_RADIUS_MODIFIER)
			{
				mPaintRadiusModifier = MAX_PAINT_RADIUS_MODIFIER;
			}
		}
		mTimeSinceLastFrame += milliseconds;
		if (squidStateCooldownTimer > 0)
		{
			squidStateCooldownTimer -= (float)milliseconds / 1000;
		}
		if (squidState)
		{
			float ammoBoost = ((float)milliseconds * AMMO_MULTIPLIER_SQUID) / 1000;
			if (mAmmoLeft + ammoBoost <= MAX_PAINT_AMMO)
			{
				mAmmoLeft += ammoBoost;
			}
		}
		ColorT playerTileColor = BackgroundC::getInstance()->returnColorAtPoint(mPosition);

		if (mHealth <= MAX_HEALTH && playerTileColor == NONE)
		{
			mHealth += HEALTH_MULTIPLIER_DEFAULT;
		}

		if (mHealth <= MAX_HEALTH && playerTileColor == mPlayerColor)
		{
			mHealth += HEALTH_MULTIPLIER_BOOST;
		}

		if (playerTileColor == mPlayerColor)
		{
			if (squidState)
			{
				if (!mSquidModeSoundPlayed)
				{
					AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetEnterSquidModeSound(), false);
					mSquidModeSoundPlayed = true;
				}
				mVelocity = { SQUID_SPEED, SQUID_SPEED };
			}
			else
			{
				if (mSquidModeSoundPlayed)
				{
					AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetExitSquidModeSound(), false);
					mSquidModeSoundPlayed = false;
				}
				mVelocity = { NORMAL_SPEED, NORMAL_SPEED };
				if (!mPaintedLastFrame && mAmmoLeft < MAX_PAINT_AMMO)
				{
					mAmmoLeft += AMMO_MULTIPLIER_DEFAULT;
				}
			}
		}
		else
		{
			if (mSquidModeSoundPlayed)
			{
				AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetExitSquidModeSound(), false);
				mSquidModeSoundPlayed = false;
			}

			ClearSquidState();
			if (playerTileColor == NONE)
			{
				mVelocity = { NORMAL_SPEED, NORMAL_SPEED };
				if (!mPaintedLastFrame && mAmmoLeft < MAX_PAINT_AMMO)
				{
					mAmmoLeft += AMMO_MULTIPLIER_DEFAULT;
				}
			}
			else {
				mVelocity = { ENEMY_SPEED, ENEMY_SPEED };
				if(!mIsInvulnerable)
					mHealth -= DAMAGE_PER_SECOND * (float)milliseconds / 1000;
			}
		}
		if (mMovedThisFrame)
		{
			if (mTimeSinceLastFrame > MILLISECONDS_PER_FRAME)
			{
				mTimeSinceLastFrame = 0;
				mCurrentAnimFrame++;
				mCurrentAnimFrame %= NUM_ANIM_SPRITES;
				recomputeUV();
			}
			mMovedThisFrame = false;
		}

		GetPlayerCollider()->updateCollider(mPosition.x, mPosition.y, ((mSize.x / 2)), ((mSize.y / 2)));

		for (int i = 0; i < MAX_PLAYER_COUNT; i++)
		{
			if (PlayerC::sInstance[i] != this && !mIsDead)
			{
				if (!PlayerC::sInstance[i]->mIsDead)
				{
					Coord2D positionOffset = mPlayerCollider.detectCollision(*GetPlayerCollider(), *(sInstance[i]->GetPlayerCollider()));
					if ((positionOffset.x != 0.0f || positionOffset.y != 0.0f))
					{
						move(milliseconds, -positionOffset.x, -positionOffset.y);
						sInstance[i]->move(milliseconds, positionOffset.x, positionOffset.y);
					}
				}
			}
		}

		mIsMoving = false;

		if (mAmmoLeft <= 0.0f)
		{
			mRanOutOfAmmo = true;
		}

		if (mAmmoLeft >= MIN_AMMO_REQUIRED)
		{
			mRanOutOfAmmo = false;
		}

		if (mHealth <= 0.0f)
		{
			AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetPlayerDeathSound(), false);
			mIsDead = true;
			BackgroundC::getInstance()->sprayPaint(mPosition, mLastEnemyColor, mLastEnemyID, mPaintRadiusModifier, true);
			mPaintRadiusModifier = START_DEATH_RADIUS_MODIFIER;
			mRespawnTimeRemaining = RESPAWN_TIME;
		}
		mPaintedLastFrame = false;
	}
	else
	{
		if (mPaintRadiusModifier <= MAX_DEATH_RADIUS_MODIFIER)
		{
			mPaintRadiusModifier += DEATH_PAINT_RADIUS_INCREASE_PER_SECOND * (float)milliseconds / 1000;
			BackgroundC::getInstance()->sprayPaint(mPosition, mLastEnemyColor, mLastEnemyID, mPaintRadiusModifier, true);
		}
		mRespawnTimeRemaining -= (float)milliseconds/1000;
		if (mRespawnTimeRemaining < 0.0f)
		{
			init(mPlayerID, mTexID, mReticleTexID, mReticleBGTexID, mBGTexture, mFillTexture, mNumTexes);
		}
		DeathUIUpdate();
	}
}

void PlayerC::DeathUIUpdate()
{
	mRespawnUI.update(mRespawnTimeRemaining + 1, { mPosition.x - offsetFromCenter.x, mPosition.y - offsetFromCenter.y/2 });
}