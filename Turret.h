class Turret {
	  
	private:
		
		static const unsigned int PlatformHeight;
		static const unsigned int PlatformWidth;
		static const unsigned int BrickLayers;
		static const unsigned int BricksPerLayer;
		static const unsigned int BrickHeight;
		static const unsigned int BrickWidth;
		
		static const unsigned int MinAngle;
		static const unsigned int MaxAngle;
		static const unsigned int AngleIncrement;
		static const unsigned int Length;
		static const unsigned int Girth;

		unsigned int pivot_x, pivot_y;
		unsigned int angle;

		void drawPlatform();
		void draw();
		void erase();
		
	public:
		
		static const unsigned int LeftEdge;
		static const unsigned int RightEdge;
	
		Turret();
		unsigned int getAngle();
		void getTip(unsigned int& x, unsigned int& y);
		void moveRight();
		void moveLeft();

		void bigblast();
};
