#pragma once

#define SCORE_UI_WIDTH 24
#define SCORE_UI_HEIGHT 18
#define RESPAWN_UI_WIDTH 36
#define RESPAWN_UI_HEIGHT 27
#define SCORE_PADDING 0.1f
#define DIGIT_2_OFFSET (SCORE_UI_WIDTH * 0.25f)
#define DIGIT_1_OFFSET (SCORE_UI_WIDTH )
#define DIGIT_0_OFFSET (((SCORE_UI_WIDTH * 2) - DIGIT_2_OFFSET))

class ScoreUI
{
public:
	ScoreUI();
	~ScoreUI();
	void init(GLuint* numTexes, bool isRespawnUI = false);

	void update(float score, Coord2D position);
	void render();
private:
	bool mIsRespawnUI;
	GLuint *mNumTexes;
	int unitsScore, tensScore, hundredsScore;
	Coord2D mPosition;
};

