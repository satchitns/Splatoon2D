class BallC : public ObjectC
{
public:
    BallC();
	BallC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY,int id);
    ~BallC();
	void setBallColor(long color) {mBallColor = color;};
    long getBallColor() {return mBallColor;};
    void update(DWORD milliseconds);
    virtual void render();
	void DoCollisions();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
    void setRadius(float radius) {mCollInfo.param1 = radius;mRadius = radius;};
	void setRandomColor();
	void reduceVelocity(float_t factor);
	void moveUp();
private:
	void CollideField();

	long mBallColor;
    bool mEnabled;
    float mRadius;
	bool mAtRest;
};