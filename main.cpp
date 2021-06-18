#include "variables.h"
using namespace std;


int EggCorpBuyIntSelectedChoice, EggCorpSellIntSelectedChoice, OrangeLTDBuyIntSelectedChoice, OrangeLTDSellIntSelectedChoice;
int maxStocks;
float money = 1000;
long int randomInteger;
bool mouseButtonPressed, drawingNewsFeed;
	ifstream positiveNewsEvents("positive-news-events.txt");
	ifstream negativeNewsEvents("negative-news-events.txt");
	string newsEvent = 0;

void updateMoney();																																							//functions to load threads
void threadFunction();
void allegroFunction();
void drawNewsFeed();
string generateRandomEvents();

int BuyButtonHeight, BuyButtonWidth, BuyButtonX, BuyButtonY, MaxButtonHeight, MaxButtonWidth, MaxButtonX, MaxButtonY, minusButtonHeight, minusButtonWidth,
minusButtonX, minusButtonY, plusButtonHeight, plusButtonWidth, plusButtonX, plusButtonY, EggCorpMaxStocks, OrangeLTDMaxStocks;







stocks EggCorp("EggCorp", 50, 0.1, 10);
stocks OrangeLTD("OrangeLTD", 500, 10, 0);


int main() {
	threadFunction();
	return 0;
}



string generateRandomEvents() {
	vector <string> positiveEvents, negativeEvents;
	while (getline(positiveNewsEvents, newsEvent)) {
		positiveEvents.push_back(newsEvent);
	}
	while (getline(negativeNewsEvents, newsEvent)) {
		negativeEvents.push_back(newsEvent);
	}

	srand((unsigned) time(NULL));
	randomInteger = (rand() % 10) + 1;

		if (randomInteger <= 5) {
			int	randomInteger2 = rand() % 5;
			cout << "positive - randomInteger2: " << randomInteger2 << endl << endl;
			switch (randomInteger2) {

			case 0:
				
				newsEvent = positiveEvents[0];
				EggCorp.companyStockValue+= 10;
				EggCorp.incomePerStock+= 0.1;
				break;

			case 1:
				newsEvent = positiveEvents[1];
				OrangeLTD.companyStockValue+= 50;
				OrangeLTD.incomePerStock += 0.25;
				break;

			case 2:
				newsEvent = positiveEvents[2];
				EggCorp.companyStockValue+= 5;
				EggCorp.incomePerStock += 0.05;
				break;

			case 3:
				newsEvent = positiveEvents[3];
				OrangeLTD.companyStockValue+= 25;
				EggCorp.companyStockValue-= 5;
				break;

			case 4:
				newsEvent = positiveEvents[4];
				EggCorp.companyStockValue+= 20;
				EggCorp.incomePerStock+= 0.2;
				break;
			}

		}
		else if (randomInteger > 5) {
			int	randomInteger2 = rand() % 5;
			cout << "negative - randomInteger2: " << randomInteger2 << endl << endl;

			switch (randomInteger2) {

			case 0:
				newsEvent = negativeEvents[0];
				OrangeLTD.companyStockValue-= 20;
				OrangeLTD.incomePerStock-= 0.25;
				break;

			case 1:
				newsEvent = negativeEvents[1];
				EggCorp.companyStockValue-= 5;
				EggCorp.incomePerStock-= 0.05;
				break;

			case 2:
				newsEvent = negativeEvents[2];
				EggCorp.companyStockValue-= 10;
				EggCorp.incomePerStock-= 0.1;
				break;

			case 3:
				newsEvent = negativeEvents[3];
				OrangeLTD.companyStockValue-= 35;
				OrangeLTD.incomePerStock-= 0.35;
				break;

			case 4:
				newsEvent = negativeEvents[4];
				OrangeLTD.companyStockValue-= 10;
				OrangeLTD.incomePerStock-= 0.4;
				break;
			}
		}
	
	return newsEvent;
}

void stocks::bailout() {
	if (this->companyStockValue <= 0) {
		this->companyStockValue = 50;
		cout << this->companyName << " went bankrupt! Their stock value hit 0, and they have been bailed out by the government. Their stock value has been reset to: " << this->companyStockValue << endl;
	}

	else if (this->incomePerStock <= 0) {
		this->incomePerStock = 0.1;
		cout << this->companyName << " went bankrupt! Their income per stock hit 0 and they have been bailed out by the government. Their income per stock has been reset to: " << this->incomePerStock << endl;
	}
}

void updateMoney() {
	while (true) {
		EggCorp.update(); OrangeLTD.update();																															//thread to update money every second
		Sleep(1000);
	}
}

void threadFunction() {																																					//function to load the threads
	thread t1(updateMoney);
	thread t2(allegroFunction);
	thread t3(drawNewsFeed);

	t1.join();
	t2.join();
	t3.join();
}

void drawNewsFeed() {
	while (true) {
		Sleep(10000);
		newsEvent = generateRandomEvents();
		drawingNewsFeed = true;
		Sleep(10000);
		drawingNewsFeed = false;
	}
}



void allegroFunction() {
	al_init();
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;

	ALLEGRO_BITMAP* BuyButton = NULL;
	ALLEGRO_BITMAP* SellButton = NULL;
	ALLEGRO_BITMAP* OrangeLTDBuyButton = NULL;
	ALLEGRO_BITMAP* OrangeLTDSellButton = NULL;
	ALLEGRO_BITMAP* MaxButton = NULL;
	ALLEGRO_BITMAP* PlusButton = NULL;
	ALLEGRO_BITMAP* NumberBox = NULL;
	ALLEGRO_BITMAP* MinusButton = NULL;
	ALLEGRO_BITMAP* NewsLogo = NULL;

	display = al_create_display(720, 360);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* font = al_load_ttf_font("cambria.ttf", 24, 0);
	ALLEGRO_FONT* smaller_font = al_load_ttf_font("cambria.ttf", 12, 0);

	al_install_keyboard();
	al_install_mouse();


	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());

	al_init_image_addon();
	al_init_primitives_addon();

	MinusButton = al_load_bitmap("minus.jpg");
	NumberBox = al_load_bitmap("numberbox.jpg");
	PlusButton = al_load_bitmap("plus.jpg");
	MaxButton = al_load_bitmap("maximage.jpg");
	BuyButton = al_load_bitmap("buyimage.jpg");
	SellButton = al_load_bitmap("sellimage.jpg");
	OrangeLTDBuyButton = al_load_bitmap("buyimage.jpg");
	OrangeLTDSellButton = al_load_bitmap("sellimage.jpg");
	NewsLogo = al_load_bitmap("newslogo.jpg");

	assert(NewsLogo != NULL);

	float posX = 0, posY = 0;
	bool isRunning = true;
	al_start_timer(timer);
	while (isRunning == true) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			isRunning = false;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			posX = event.mouse.x;
			posY = event.mouse.y;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (event.mouse.button & 1) {
				mouseButtonPressed = true;
			}
			else {
				mouseButtonPressed = false;
			}
		}

		//all mouse & keyboard events should be created above here



		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			string str = to_string(EggCorp.companyStockValue);
			const char* EggCorpstockValue = str.c_str();

			string str2 = to_string(EggCorp.numberOfStocks);
			const char* EggCorpnumberOfStocks = str2.c_str();
			
			string str3 = to_string(EggCorp.incomePerStock);
			const char* EggCorpincomePerStock = str3.c_str();

			string str4 = to_string(OrangeLTD.companyStockValue);
			const char* OrangeLTDstockValue = str4.c_str();

			string str5 = to_string(OrangeLTD.numberOfStocks);
			const char* OrangeLTDnumberOfStocks = str5.c_str();

			string str6 = to_string(OrangeLTD.incomePerStock);
			const char* OrangeLTDincomePerStock = str6.c_str();

			string moneyString = to_string(money);
			const char* moneyChar = moneyString.c_str();

			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Market Day! The stock prices are: ");
			al_draw_text(smaller_font, al_map_rgb(255, 255, 255), 375, 5, 0, "Your current money is: ");
			al_draw_text(smaller_font, al_map_rgb(255, 255, 255), 500, 5, 0, moneyChar);
			al_draw_text(smaller_font, al_map_rgb(255, 255, 255), 0, 25, 0, "Company Name                 Stock Price                 No# Owned                 Income per Stock ");
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 60, 0, "EggCorp");
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 112, 0, "OrangeLTD");
			al_draw_line(0, 52, 720, 52, al_map_rgb(255, 255, 255), 3);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 60, 0, EggCorpstockValue);																				//text outputs of company names and values
			al_draw_textf(font, al_map_rgb(255, 255, 255), 250, 60, 0, EggCorpnumberOfStocks);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 60, 0, EggCorpincomePerStock);
			al_draw_line(0, 105, 720, 105, al_map_rgb(255, 255, 255), 2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 112, 0, OrangeLTDstockValue);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 250, 112, 0, OrangeLTDnumberOfStocks);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 112, 0, OrangeLTDincomePerStock);

			string stringSelectedChoice1 = to_string(EggCorpBuyIntSelectedChoice);
			const char* selectedChoice1 = stringSelectedChoice1.c_str();


			if (drawingNewsFeed == true) {
				al_draw_filled_rectangle(0, 310, 720, 360, al_map_rgb(150, 0, 0));
				al_draw_bitmap(NewsLogo, 0, 310, 0);
				cNewsEvent = newsEvent.c_str();
				al_draw_multiline_text(smaller_font, al_map_rgb(255, 255, 255), 80, 320, 720, 15, 0, cNewsEvent);
			}


			al_draw_bitmap(BuyButton, 460, 60, 0);	
			al_draw_bitmap(SellButton, 460, 80, 0);
			al_draw_bitmap(PlusButton, 505, 60, 0);
			al_draw_bitmap(NumberBox, 530, 60, 0);
			al_draw_bitmap(MaxButton, 600, 60, 0);

			string stringEggCorpMaxStocks = to_string(EggCorpMaxStocks);
			const char* cEggCorpEggCorpMaxStocks = stringEggCorpMaxStocks.c_str();

			al_draw_textf(smaller_font, al_map_rgb(0, 0, 0), 532, 60, 0, selectedChoice1);
			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 640, 60, 0, "Max: ");
			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 668, 60, 0, cEggCorpEggCorpMaxStocks);
			al_draw_bitmap(MinusButton, 575, 60, 0);

			string stringSelectedChoice2 = to_string(EggCorpSellIntSelectedChoice);
			const char* selectedChoice2 = stringSelectedChoice2.c_str();

			al_draw_bitmap(OrangeLTDBuyButton, 460, 110, 0);
			al_draw_bitmap(OrangeLTDSellButton, 460, 130, 0);

			al_draw_bitmap(PlusButton, 505, 110, 0);
			al_draw_bitmap(NumberBox, 530, 110, 0);
			al_draw_bitmap(MaxButton, 600, 110, 0);
			al_draw_bitmap(MinusButton, 575, 110, 0);

			al_draw_bitmap(PlusButton, 505, 130, 0);
			al_draw_bitmap(NumberBox, 530, 130, 0);
			al_draw_bitmap(MaxButton, 600, 130, 0);
			al_draw_bitmap(MinusButton, 575, 130, 0);


			al_draw_bitmap(PlusButton, 505, 80, 0);
			al_draw_bitmap(NumberBox, 530, 80, 0);
			al_draw_bitmap(MaxButton, 600, 80, 0);
			al_draw_bitmap(MinusButton, 575, 80, 0);
			
			string sMaxSell = to_string(EggCorp.numberOfStocks);
			const char* cMaxSell = sMaxSell.c_str();

			al_draw_textf(smaller_font, al_map_rgb(0, 0, 0), 532, 80, 0, selectedChoice2);

			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 640, 80, 0, "Max: ");
			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 668, 80, 0, cMaxSell);

			string stringSelectedChoice3 = to_string(OrangeLTDBuyIntSelectedChoice);
			const char* selectedChoice3 = stringSelectedChoice3.c_str();

			string OrangeLTDSellMax = to_string(OrangeLTDMaxStocks);
			const char* OrangeLTDMaxBuy = OrangeLTDSellMax.c_str();

			al_draw_textf(smaller_font, al_map_rgb(0, 0, 0), 532, 110, 0, selectedChoice3);

			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 640, 110, 0, "Max: ");
			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 668, 110, 0, OrangeLTDMaxBuy);

			string stringSelectedChoice4 = to_string(OrangeLTDSellIntSelectedChoice);
			const char* selectedChoice4 = stringSelectedChoice4.c_str();

			al_draw_textf(smaller_font, al_map_rgb(0, 0, 0), 532, 130, 0, selectedChoice4);

			string sOrangeLTDMaxSell = to_string(OrangeLTD.numberOfStocks);
			const char* OrangeLTDMaxSell = sOrangeLTDMaxSell.c_str();

			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 640, 130, 0, "Max: ");
			al_draw_textf(smaller_font, al_map_rgb(255, 255, 255), 668, 130, 0, OrangeLTDMaxSell);
		}




		int plusButtonWidth = al_get_bitmap_width(PlusButton);
		int plusButtonHeight = al_get_bitmap_height(PlusButton);

		int rect_x2, rect_y2;

		plusButtonX = 505;
		plusButtonY = 60;

		rect_x2 = plusButtonX + al_get_bitmap_width(PlusButton);
		rect_y2 = plusButtonY + al_get_bitmap_height(PlusButton);

		if (
			(posX <= rect_x2 &&
				posX >= plusButtonX) &&
				(posY <= rect_y2 &&
					posY >= plusButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpBuyIntSelectedChoice++;
		}
		EggCorpMaxStocks = money / EggCorp.companyStockValue;
		if (EggCorpBuyIntSelectedChoice > EggCorpMaxStocks) {
			EggCorpBuyIntSelectedChoice--;
		}


		minusButtonWidth = al_get_bitmap_width(MinusButton);
		minusButtonHeight = al_get_bitmap_height(MinusButton);

		minusButtonX = 575;
		minusButtonY = 60;

		rect_x2 = minusButtonX + al_get_bitmap_width(MinusButton);
		rect_y2 = minusButtonY + al_get_bitmap_height(MinusButton);

		if (
			(posX <= rect_x2 &&
				posX >= minusButtonX) &&
				(posY <= rect_y2 &&
					posY >= minusButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpBuyIntSelectedChoice--;
		}
		if (EggCorpBuyIntSelectedChoice < 0) {
			EggCorpBuyIntSelectedChoice++;
		}

		BuyButtonWidth = al_get_bitmap_width(BuyButton);
		BuyButtonHeight = al_get_bitmap_height(BuyButton);

		BuyButtonX = 460;
		BuyButtonY = 60;

		rect_x2 = BuyButtonX + al_get_bitmap_width(BuyButton);
		rect_y2 = BuyButtonY + al_get_bitmap_height(BuyButton);


		if (
			(posX <= rect_x2 &&
				posX >= BuyButtonX) &&
				(posY <= rect_y2 &&
					posY >= BuyButtonY &&
					mouseButtonPressed == true)
			) {

			EggCorp.numberOfStocks += EggCorpBuyIntSelectedChoice;
			money -= (EggCorpBuyIntSelectedChoice * EggCorp.companyStockValue);
			EggCorpBuyIntSelectedChoice = 0;
		}

		MaxButtonHeight = al_get_bitmap_width(MaxButton);
		MaxButtonWidth = al_get_bitmap_height(MaxButton);

		MaxButtonX = 600;
		MaxButtonY = 60;

		rect_x2 = MaxButtonX + al_get_bitmap_width(MaxButton);
		rect_y2 = MaxButtonY + al_get_bitmap_height(MaxButton);

		if (
			(posX <= rect_x2 &&
				posX >= MaxButtonX) &&
				(posY <= rect_y2 &&
					posY >= MaxButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpBuyIntSelectedChoice = EggCorpMaxStocks;
		}






		plusButtonWidth = al_get_bitmap_width(PlusButton);
		plusButtonHeight = al_get_bitmap_height(PlusButton);


		plusButtonX = 505;
		plusButtonY = 80;

		rect_x2 = plusButtonX + al_get_bitmap_width(PlusButton);
		rect_y2 = plusButtonY + al_get_bitmap_height(PlusButton);

		if (
			(posX <= rect_x2 &&
				posX >= plusButtonX) &&
				(posY <= rect_y2 &&
					posY >= plusButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpSellIntSelectedChoice++;
		}
		if (EggCorpSellIntSelectedChoice > EggCorp.numberOfStocks) {
			EggCorpSellIntSelectedChoice--;
		}


		minusButtonWidth = al_get_bitmap_width(MinusButton);
		minusButtonHeight = al_get_bitmap_height(MinusButton);

		minusButtonX = 575;
		minusButtonY = 80;

		rect_x2 = minusButtonX + al_get_bitmap_width(MinusButton);
		rect_y2 = minusButtonY + al_get_bitmap_height(MinusButton);

		if (
			(posX <= rect_x2 &&
				posX >= minusButtonX) &&
				(posY <= rect_y2 &&
					posY >= minusButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpSellIntSelectedChoice--;
		}
		if (EggCorpSellIntSelectedChoice < 0) {
			EggCorpSellIntSelectedChoice++;
		}

		BuyButtonWidth = al_get_bitmap_width(BuyButton);
		BuyButtonHeight = al_get_bitmap_height(BuyButton);

		BuyButtonX = 460;
		BuyButtonY = 80;

		rect_x2 = BuyButtonX + al_get_bitmap_width(BuyButton);
		rect_y2 = BuyButtonY + al_get_bitmap_height(BuyButton);


		if (
			(posX <= rect_x2 &&
				posX >= BuyButtonX) &&
				(posY <= rect_y2 &&
					posY >= BuyButtonY &&
					mouseButtonPressed == true)
			) {

			EggCorp.numberOfStocks -= EggCorpSellIntSelectedChoice;
			money += (EggCorpSellIntSelectedChoice * EggCorp.companyStockValue);
			EggCorpSellIntSelectedChoice = 0;
		}

		MaxButtonHeight = al_get_bitmap_width(MaxButton);
		MaxButtonWidth = al_get_bitmap_height(MaxButton);

		MaxButtonX = 600;
		MaxButtonY = 80;

		rect_x2 = MaxButtonX + al_get_bitmap_width(MaxButton);
		rect_y2 = MaxButtonY + al_get_bitmap_height(MaxButton);

		if (
			(posX <= rect_x2 &&
				posX >= MaxButtonX) &&
				(posY <= rect_y2 &&
					posY >= MaxButtonY &&
					mouseButtonPressed == true)
			) {
			EggCorpSellIntSelectedChoice = EggCorp.numberOfStocks;
		}
















		plusButtonWidth = al_get_bitmap_width(PlusButton);
		plusButtonHeight = al_get_bitmap_height(PlusButton);


		plusButtonX = 505;
		plusButtonY = 110;

		rect_x2 = plusButtonX + al_get_bitmap_width(PlusButton);
		rect_y2 = plusButtonY + al_get_bitmap_height(PlusButton);

		if (
			(posX <= rect_x2 &&
				posX >= plusButtonX) &&
				(posY <= rect_y2 &&
					posY >= plusButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDBuyIntSelectedChoice++;
		}
		OrangeLTDMaxStocks = money / OrangeLTD.companyStockValue;
		if (OrangeLTDBuyIntSelectedChoice > OrangeLTDMaxStocks) {
			OrangeLTDBuyIntSelectedChoice--;
		}


		minusButtonWidth = al_get_bitmap_width(MinusButton);
		minusButtonHeight = al_get_bitmap_height(MinusButton);

		minusButtonX = 575;
		minusButtonY = 110;

		rect_x2 = minusButtonX + al_get_bitmap_width(MinusButton);
		rect_y2 = minusButtonY + al_get_bitmap_height(MinusButton);

		if (
			(posX <= rect_x2 &&
				posX >= minusButtonX) &&
				(posY <= rect_y2 &&
					posY >= minusButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDBuyIntSelectedChoice--;
		}
		if (OrangeLTDBuyIntSelectedChoice < 0) {
			OrangeLTDBuyIntSelectedChoice++;
		}

		BuyButtonWidth = al_get_bitmap_width(BuyButton);
		BuyButtonHeight = al_get_bitmap_height(BuyButton);

		BuyButtonX = 460;
		BuyButtonY = 110;

		rect_x2 = BuyButtonX + al_get_bitmap_width(BuyButton);
		rect_y2 = BuyButtonY + al_get_bitmap_height(BuyButton);


		if (
			(posX <= rect_x2 &&
				posX >= BuyButtonX) &&
				(posY <= rect_y2 &&
					posY >= BuyButtonY &&
					mouseButtonPressed == true)
			) {

			OrangeLTD.numberOfStocks += OrangeLTDBuyIntSelectedChoice;
			money -= (OrangeLTDBuyIntSelectedChoice * OrangeLTD.companyStockValue);
			OrangeLTDBuyIntSelectedChoice = 0;
		}

		MaxButtonHeight = al_get_bitmap_width(MaxButton);
		MaxButtonWidth = al_get_bitmap_height(MaxButton);

		MaxButtonX = 600;
		MaxButtonY = 110;

		rect_x2 = MaxButtonX + al_get_bitmap_width(MaxButton);
		rect_y2 = MaxButtonY + al_get_bitmap_height(MaxButton);

		if (
			(posX <= rect_x2 &&
				posX >= MaxButtonX) &&
				(posY <= rect_y2 &&
					posY >= MaxButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDBuyIntSelectedChoice = OrangeLTDMaxStocks;
		}






		plusButtonWidth = al_get_bitmap_width(PlusButton);
		plusButtonHeight = al_get_bitmap_height(PlusButton);


		plusButtonX = 505;
		plusButtonY = 130;

		rect_x2 = plusButtonX + al_get_bitmap_width(PlusButton);
		rect_y2 = plusButtonY + al_get_bitmap_height(PlusButton);

		if (
			(posX <= rect_x2 &&
				posX >= plusButtonX) &&
				(posY <= rect_y2 &&
					posY >= plusButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDSellIntSelectedChoice++;
		}
		if (OrangeLTDSellIntSelectedChoice > OrangeLTD.numberOfStocks) {
			OrangeLTDSellIntSelectedChoice--;
		}


		minusButtonWidth = al_get_bitmap_width(MinusButton);
		minusButtonHeight = al_get_bitmap_height(MinusButton);

		minusButtonX = 575;
		minusButtonY = 130;

		rect_x2 = minusButtonX + al_get_bitmap_width(MinusButton);
		rect_y2 = minusButtonY + al_get_bitmap_height(MinusButton);

		if (
			(posX <= rect_x2 &&
				posX >= minusButtonX) &&
				(posY <= rect_y2 &&
					posY >= minusButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDSellIntSelectedChoice--;
		}
		if (OrangeLTDSellIntSelectedChoice < 0) {
			OrangeLTDSellIntSelectedChoice++;
		}

		BuyButtonWidth = al_get_bitmap_width(BuyButton);
		BuyButtonHeight = al_get_bitmap_height(BuyButton);

		BuyButtonX = 460;
		BuyButtonY = 130;

		rect_x2 = BuyButtonX + al_get_bitmap_width(BuyButton);
		rect_y2 = BuyButtonY + al_get_bitmap_height(BuyButton);


		if (
			(posX <= rect_x2 &&
				posX >= BuyButtonX) &&
				(posY <= rect_y2 &&
					posY >= BuyButtonY &&
					mouseButtonPressed == true)
			) {

			OrangeLTD.numberOfStocks -= OrangeLTDSellIntSelectedChoice;
			money += (OrangeLTDSellIntSelectedChoice * OrangeLTD.companyStockValue);
			OrangeLTDSellIntSelectedChoice = 0;
		}

		MaxButtonHeight = al_get_bitmap_width(MaxButton);
		MaxButtonWidth = al_get_bitmap_height(MaxButton);

		MaxButtonX = 600;
		MaxButtonY = 130;

		rect_x2 = MaxButtonX + al_get_bitmap_width(MaxButton);
		rect_y2 = MaxButtonY + al_get_bitmap_height(MaxButton);

		if (
			(posX <= rect_x2 &&
				posX >= MaxButtonX) &&
				(posY <= rect_y2 &&
					posY >= MaxButtonY &&
					mouseButtonPressed == true)
			) {
			OrangeLTDSellIntSelectedChoice = OrangeLTD.numberOfStocks;
		}



		mouseButtonPressed = false;
		al_flip_display();
	}
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_bitmap(BuyButton);
	al_destroy_bitmap(SellButton);
	al_destroy_font(font);

}
