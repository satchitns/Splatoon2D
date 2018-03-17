class BallManagerC
{
public:
	static BallManagerC	*CreateInstance();
	static BallManagerC	*GetInstance() {return sInstance;};
	~BallManagerC(){};

	int32_t	getNumBalls() {return NUM_BALLS;};
	void	init();
	void	shutdown();
	void	updateBalls(DWORD milliseconds);
	BallC *	getBallPtr(int32_t index);
	void	renderBalls();
private:
	BallC **ballPtrs;
	static BallManagerC *sInstance;
	static const int32_t NUM_BALLS = 30;
	BallManagerC(){};
};