class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1600;
	static const uint32_t mScreenHeight = 900;
	static const uint32_t mBitsPerPixel = 32;
	static const int32_t mViewingVolumeXMax = 569;
	static const int32_t mViewingVolumeXMin = -569;
	static const int32_t mViewingVolumeYMax = 320;
	static const int32_t mViewingVolumeYMin = -320;
	static const int32_t mViewingVolumeZMax = 100;
	static const int32_t mViewingVolumeZMin = -100;

	bool mGameOver;
	bool mIsInMainMenu;

private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	CGame(){};
};