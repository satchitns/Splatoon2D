class StateManagerC
{
public:
	static StateManagerC	*CreateInstance();
	static StateManagerC	*GetInstance() {return sInstance;};
	~StateManagerC(){};
	enum 
	{
		NO_BALLS_FILLED,
		HALF_BALLS_FILLED,
		ALL_BALLS_FILLED
	};
	int32_t		getState();
	void		setState(int32_t stateToSet);
	void		shutdown();
private:
	static StateManagerC *sInstance;
	StateManagerC(){};
	int32_t		mCurrentState;
};