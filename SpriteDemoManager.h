struct VertexFormatPos3Tex2
{   // Custom vertex format for position+normal
	float tu , tv ;             ///< texture coordinates	
	float px , py , pz ;        ///< untransformed (world-space) position
};

	class SpriteDemoManagerC
{
public:
	static SpriteDemoManagerC	*CreateInstance();
	static SpriteDemoManagerC	*GetInstance() {return sInstance;};
	~SpriteDemoManagerC(){};

	void		init(int width, int height);
	void		updateSprites(DWORD milliseconds);
	void		renderSprites();
	void		shutdown();

	int			getWidth() {return mWidth;}
	int			getHeight() {return mHeight;}


	void	setMood(int x, int y, int mood);
	void	setID(int x, int y, int id);
	void	setPosition(int x, int y, float xPosition, float yPosition);
	float	getXPosition(int x, int y);
	float	getYPosition(int x, int y);
	int		getMood(int x, int y);
	int		getSpriteID(int x, int y);

private:
	static SpriteDemoManagerC *sInstance;
	SpriteDemoManagerC(){};
	void randomizeSprites();

	GLuint mSpriteTextureMap;
	int mWidth;
	int mHeight;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;

	int *mMoodArray;
	float *mPosArrayX, *mPosArrayY;
	int *mSpriteIDArray;
	VertexFormatPos3Tex2 *mVertexArray;
};

#define MOOD_UPDATE_DELTA_TIME 100