class FieldC : public ObjectC
{
public:
	FieldC(float_t x, float_t y, uint32_t height, uint32_t width, uint32_t initColor);
    ~FieldC();
    void setColor(uint32_t color) {mFieldColor = color;};
    long getColor() {return mFieldColor;};
    void update(DWORD milliseconds);
    virtual void render();
    void setWidth(uint32_t width) {mWidth = width;};
    uint32_t getWidth() {return mWidth;};
    void setHeight(uint32_t height) {mHeight = height;};
    uint32_t getHeight() {return mHeight;};

	void moveUp();
private:
    uint32_t mFieldColor;
	uint32_t mHeight;
	uint32_t mWidth;
	bool8_t mEnabled;
};