#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <chrono>
#include <thread>

// We are going to use the SFML Library
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window.hpp>


using namespace std;
#define PI 3.1415926
#define MOVEMEMORY 30
#define TWOPI 2*PI
#define EIGHTPI 8*PI
#define X0 400
#define Y0 400
#define GRAVITATIONALK 0.5
unsigned long long cntvalues = 0, cntrep = 0;
double r1=200, r2=100;
double pastx2, pasty2, x2, y2,x1,y1forval;
double vectorx2[100],vectory2[100];
double vectorx1[100], vectory1[100];
float m1 = 10;
float m2 = 10;
double a1 = PI/2;
double a2 = 0;
double a1_v = 0;
double a2_v = 0;
double a1_a = 0;
double a2_a = 0;
int window1, graphx1,graphy1,graphx2,graphy2;
sf::RenderWindow* MainWindow;

std::vector<sf::RenderWindow*> MyVectorofWindows;
void showvalues();
void ResetValuesForPendulumsLocation();
void DrawPendulumsInTheirLocations(sf::RenderWindow* wind); // Function Prototypes

void DrawInMainWindowAtStart(sf::RenderWindow* wind) {
	//setupw1();
	sf::CircleShape Circle{ 5, 100 };
	Circle.setPosition(400 - 20, 400 - 20);
	wind->draw(Circle);


	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = sf::Vector2f(0, 400);
	line[1].position = sf::Vector2f(800, 400);
	wind->draw(line);

	sf::VertexArray line2(sf::LinesStrip, 2);
	line2[0].position = sf::Vector2f(400, 0);
	line2[1].position = sf::Vector2f(400, 800);
	wind->draw(line2);



	x1 = r1 * sin(a1) + X0;
	y1forval = r1 * cos(a1) + Y0;
	x2 = r2 * sin(a2) + x1;
	y2 = r2 * cos(a2) + y1forval;
	cntvalues++;
	vectorx2[cntvalues] = x2;
	vectory2[cntvalues] = y2;
	vectorx1[cntvalues] = x1;
	vectory1[cntvalues] = y1forval;

}

void drawlinesforpendulumssfml(sf::RenderWindow* wind) {
	sf::CircleShape Circle{ 5, 100 };
	Circle.setPosition(400 - 5, 400 - 5);
	wind->draw(Circle);

	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = sf::Vector2f(0, 400);
	line[1].position = sf::Vector2f(800, 400);
	wind->draw(line);

	sf::VertexArray line2(sf::LinesStrip, 2);
	line2[0].position = sf::Vector2f(400, 0);
	line2[1].position = sf::Vector2f(400, 800);
	wind->draw(line2);

	if (cntvalues >= MOVEMEMORY) {
		for (unsigned int i = 1; i <= MOVEMEMORY; i++) {
			vectorx2[i] = vectorx2[i + 1];
			vectory2[i] = vectory2[i + 1];
		
			vectorx1[i] = vectorx1[i + 1];
			vectory1[i] = vectory1[i + 1];
			
		}
		cntvalues--;
	}
	for (unsigned int i = 2; i <= cntvalues; i++) {

		
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = sf::Vector2f(vectorx2[i - 1], vectory2[i - 1]);
		line[1].position = sf::Vector2f(vectorx2[i], vectory2[i]);
		wind->draw(line);


		sf::VertexArray line2(sf::LinesStrip, 2);
		line2[0].position = sf::Vector2f(vectorx1[i - 1], vectory1[i - 1]);
		line2[1].position = sf::Vector2f(vectorx1[i], vectory1[i]);
		wind->draw(line2);
		

	}


}

void SpawnMainWindow() {
	MainWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "DoublePendulumEmulation");

	while (MainWindow->isOpen())
	{

		sf::Event event;
		while (MainWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainWindow->close();
		}

		MainWindow->clear(sf::Color::Red);

		drawlinesforpendulumssfml(MainWindow);
		ResetValuesForPendulumsLocation();
		DrawPendulumsInTheirLocations(MainWindow);

		// Draw secondary windows -> This reduces FPS on main window

		showvalues();

		using namespace std::this_thread;     // sleep_for, sleep_until
		using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
		using std::chrono::system_clock;

		sleep_for(100ms);


		MainWindow->display();
	}
}

void ResetValuesForPendulumsLocation() {
	double num1 = -GRAVITATIONALK * (2 * m1 * m2) * sin(a1);
	double num2 = m2 * GRAVITATIONALK * sin(a1 - 2 * a2);
	double num3 = 2 * sin(a1 - a2) * m2 * (a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2));
	double den1 = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
	///
	a1_a = (num1 - num2 - num3) / den1;
	///
	double nnum1 = 2 * sin(a1 - a2) * (a1_v * a1_v * r1 * (m1 + m2) + GRAVITATIONALK * (m1 + m2) * cos(a1) + a2_v * a2_v * r2 * m2 * cos(a1 - a2));
	double dden1 = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
	a2_a = (nnum1 / dden1);
	a1 += a1_v;
	a2 += a2_v;
	a1_v += a1_a;
	a2_v += a2_a;
	x1 = r1 * sin(a1) + X0;
	y1forval = r1 * cos(a1) + Y0;
	x2 = r2 * sin(a2) + x1;
	y2 = r2 * cos(a2) + y1forval;
	cntvalues++;
	vectorx2[cntvalues] = x2;
	vectory2[cntvalues] = y2;
	vectorx1[cntvalues] = x1;
	vectory1[cntvalues] = y1forval;
}

void DrawPendulumsInTheirLocations(sf::RenderWindow* wind) {

	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = sf::Vector2f(X0,Y0);
	line[1].position = sf::Vector2f(x1, y1forval);
	wind->draw(line);

	sf::VertexArray line2(sf::LinesStrip, 2);
	line2[0].position = sf::Vector2f(x1, y1forval);
	line2[1].position = sf::Vector2f(x2, y2);
	wind->draw(line2);


	sf::CircleShape Circle{ m2, 100 };
	Circle.setPosition(x2-m2, y2-m2);
    Circle.setFillColor(sf::Color::Yellow);
	wind->draw(Circle);

	sf::CircleShape Circle2{ m1, 100 };
	Circle2.setPosition(x1 - m1, y1forval - m1);
    Circle2.setFillColor(sf::Color::Blue);
	wind->draw(Circle2);
}

void showvalues() {
	std::cout << "_________REPORT NO" << " " << cntrep << "_________";
	std::cout << "CURRENT X1: " << x1 << endl;
	std::cout << "CURRENT Y1: " << y1forval << endl;
	std::cout << "CURRENT X2: " << x2 << endl;
	std::cout << "CURRENT Y2: " << y2 << endl;
	std::cout << "ANGLE TETHA1 (VARIABLE): " << a1 << endl;
	std::cout << "ANGLE TETHA2 (VARIABLE): " << a2 << endl;
	std::cout << "ANGLE TETHA1 (VALUE IN DEGREES - CUMULATED): " << a1 * 180 / PI << endl;
	std::cout << "ANGLE TETHA2 (VALUE IN DEGREES - CUMULATED): " << a2 * 180 / PI << endl;
}

void StartAThreadForAWindow(sf::RenderWindow* wind) {
	while (wind->isOpen())
	{

		sf::Event event;
		while (wind->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wind->close();
		}

		wind->clear(sf::Color::Black);


		wind->display();
	}
}
int main() {
	cntrep++;
	// There are 5 windows in total that we need to show
	//MyVectorofWindows.push_back(new sf::RenderWindow(sf::VideoMode(300, 300), "Graph For X1 Coordinate"));
	//MyVectorofWindows.push_back(new sf::RenderWindow(sf::VideoMode(300, 300), "Graph For X2 Coordinate"));
	//MyVectorofWindows.push_back(new sf::RenderWindow(sf::VideoMode(300, 300), "Graph For Y1 Coordinate"));
	//MyVectorofWindows.push_back(new sf::RenderWindow(sf::VideoMode(300, 300), "Graph For Y2 Coordinate"));


	//sf::Thread* th1 = new sf::Thread(StartAThreadForAWindow, MyVectorofWindows.at(0));
	//sf::Thread* th2 = new sf::Thread(StartAThreadForAWindow, MyVectorofWindows.at(1));
	//sf::Thread* th3 = new sf::Thread(StartAThreadForAWindow, MyVectorofWindows.at(2));
	//sf::Thread* th4 = new sf::Thread(StartAThreadForAWindow, MyVectorofWindows.at(3));
	//th1->launch();
	//th2->launch();
	//th3->launch();
	//th4->launch();


	x1 = r1 * sin(a1)+X0;
	y1forval = r1 * cos(a1)+Y0;
	x2 = r2 * sin(a2)+x1;
	y2 = r2 * cos(a2)+ y1forval;
	cntvalues++;
	vectorx2[cntvalues] = x2;
	vectory2[cntvalues] = y2;
	vectorx1[cntvalues] = x1;
	vectory1[cntvalues] = y1forval;

	// We need to do this in the main Window at start
	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	///
	pastx2 = x2;
	pasty2 = y2;

	SpawnMainWindow();

	std::cin.get();
	return 0;
}

