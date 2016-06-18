class Bullet {

	private:

		static const unsigned int SideMargin;
		static const unsigned int UpMargin;
		static const unsigned int Advancement;

		int x, y;
		int x_Advancement;
		int y_Advancement;
		Bullet* next;

		Bullet(int x0, int y0, unsigned int angle);
		void draw();
		void erase();
	
		static Bullet* head;
		static Bullet* tail;

	public:

		static void create(int x0, int y0, unsigned int angle);
		static void advance();
};
