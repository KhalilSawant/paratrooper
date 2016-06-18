class Paratrooper {
	private:
		static const unsigned int SoldierHeight = 20;
		static const unsigned int SoldierWidth = 10;
		static const unsigned int TrooperHeight = 36;
		static const unsigned int TrooperWidth = 16;

		static const unsigned int OffTurretMargin;
		static const unsigned int Advancement;
	
		static unsigned int soldierBitMap[SoldierHeight][SoldierWidth];
		static unsigned int trooperBitMap[TrooperHeight][TrooperWidth];

		static char* soldierBufferedImage;
		static char* trooperBufferedImage;
		
		static Paratrooper* head;
		static Paratrooper* tail;

		int x, y;
		Paratrooper* next;
		Paratrooper(int x0, int y0);
		void xorDraw();
		bool isHit();
		static void remove(Paratrooper** tmpPara);
	public:
		static void initialize();
		static void create(int x0, int y0);
		static void advance();
};
