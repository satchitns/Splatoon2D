class FieldManagerC
{
public:
	static FieldManagerC	*CreateInstance();
	static FieldManagerC	*GetInstance() {return sInstance;};
	~FieldManagerC(){};

	FieldC* getFieldPtr();
	void init();
	void renderField();
	void shutdown();
private:
	static FieldManagerC *sInstance;
	FieldManagerC(){};
	
	FieldC *mFieldPtr;
};