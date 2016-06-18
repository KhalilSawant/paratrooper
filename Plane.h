	class Plane {
	private:
		static const unsigned int PlaneHeight = 13;
		static const unsigned int PlaneLength = 30;

		static const unsigned int FlyHeightLeftPlane;
		static const unsigned int FlyHeightRightPlane;
		
		static const unsigned int PlaneStartOffMargin;
		static const unsigned int InterPlaneGap;
		
		static const unsigned int Advancement;
		
		static unsigned int planeBitMap[PlaneHeight][PlaneLength];

		static char* leftPlaneBufferedImage;
		static char* rightPlaneBufferedImage;
		
		static Plane* head;
		static Plane* tail;
		
		bool fromRight;
		int x,y;
		Plane* next;
		
		Plane(bool fromRight);
		void xorDraw();
		bool isHit();
		static void remove(Plane** tmpPl);
		
		void explode();
	public:
		static void initialize();
		static void create(bool fromRight);
		static void advance();
};
