#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <ctime>
#include <glut.h>
#pragma comment (lib, "ws2_32.lib")


auto  current_time= std::chrono::high_resolution_clock::now();
std::string clientData;
bool newDataBool;
bool arrow;
std::string boxNumber;
bool allBoxes;
std::string testBox;

bool dot;
bool box1Mode;
bool box2Mode;
bool box4Mode;
bool box5Mode;


bool phaseOne; 
bool phaseTwo;
bool phaseThree;
bool mainPhase;

float freq1 = ((1.0 / 12.0) / 2.0) * 1000;
float freq2 = ((1.0 / 10.0) / 2.0) * 1000;
float freq4 = ((1.0 / 7.6) / 2.0) * 1000;
float freq5 = ((1.0 / 6.6) / 2.0) * 1000;

void square(float x1, float y1  , float x2, float y2, float x3, float y3,float x4, float y4) {
	glPushMatrix();
	glColor3f(0, 225, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x3, y3, 0.0);
	glVertex3f(x4, y4, 0.0);
	glEnd();
	glPopMatrix();
}

void triangle(int rotate, int Tx , int Ty) {
	glPushMatrix();
	glTranslated(Tx, Ty, 0);
	if (rotate == 1) {
	glRotated(180, 0, 0, rotate);

	}
	glColor3f(255, 255, 255);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);
	glVertex3f(25.0f, 25.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void point(float  size,int red , int green ,int blue,float xT, float yT) {
	glPushMatrix();
	glTranslated(xT, yT, 0);
	glColor3f(red, green, blue);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void print(int x, int y, char *string)
{

	glPushMatrix();
	glColor3f(255, 255, 255);
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glPopMatrix();
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (newDataBool) {
		std::cout << clientData;
		newDataBool = false;
		if (clientData.at(0) == 'a' ) {
			testBox = clientData.at(1);
			arrow = true;
			boxNumber = testBox;
			dot = true;
			std::cout << "Now the arrow should point at Box number: "<< testBox << "\n";


			phaseOne = false;
			phaseTwo = false;
			phaseThree = false;
			mainPhase = false;
		}
		else if (clientData.at(0) == 'g') {
			arrow = false;
			dot = false;
			allBoxes = true;


			phaseOne = false;
			phaseTwo = false;
			phaseThree = false;
			mainPhase = false;
		}
		else if (clientData.at(0) == 'p') {
			dot = false;
			arrow = false;
			allBoxes = false;


			phaseOne = false;
			phaseTwo = false;
			phaseThree = false;
			mainPhase = false;

		}
		//New interface 
		else if (clientData.at(0) == '1') {
			phaseOne = true;
			dot = false;
			arrow - false;
			allBoxes = false;

		}
		else if (clientData.at(0) == '2') {
			phaseTwo = true;
			dot = false;
			arrow - false;
			allBoxes = false;

		}
		else if (clientData.at(0) == '3') {
			phaseThree = true;
			dot = false;
			arrow - false;
			allBoxes = false;

		}
		else if (clientData.at(0) == '0') {
			mainPhase = true;
			dot = false;
			arrow - false;
			allBoxes = false;
		}




		else { // can add here to improve for letters

			allBoxes = true;
			arrow = false;
			std::cout << "all boxes" << "\n";

		}
	}


		if (dot) {
		
			point(10.0f, 255, 255, 255, 200, 800);
			point(10.0f, 255, 255, 255, 800, 800);
			point(10.0f, 255, 255, 255, 200, 200);
			point(10.0f, 255, 255, 255, 800, 200);
			/*
		point(50.0f, 0, 0, 0, 200, 800);
		point(50.0f, 0, 0, 0, 800, 800);
		point(50.0f, 255, 0, 255, 200, 200);
		point(50.0f, 0, 0, 255, 800, 200);



		/*
			point(10.0f, 255, 255, 255, 300, 800);
			point(10.0f, 255, 255, 255, 900, 800);
			point(10.0f, 255, 255, 255, 300, 200);
			point(10.0f, 255, 255, 255, 900, 200);
			*/
	}
	else {


			if (mainPhase) {
				print(175, 800, "Questions");
				print(775, 800, "Subjects");
				print(175, 200, "Verbs");
				print(775, 200, "Spell");
			}
			else if (phaseOne) {
				print(175, 800, "what");
				print(775, 800, "who");
				print(175, 200, "how");
				print(775, 200, "why");
			}
			else if (phaseTwo) {
				print(175, 800, "You");
				print(775, 800, "I");
				print(175, 200, "They");
				print(775, 200, "We");
			}
			else if (phaseThree) {
				print(175, 800, "Do");
				print(775, 800, "Drink");
				print(175, 200, "Eat");
				print(775, 200, "No");
			}
			else {
				point(10.0f, 255, 255, 255, 200, 800);
				point(10.0f, 255, 255, 255, 800, 800);
				point(10.0f, 255, 255, 255, 200, 200);
				point(10.0f, 255, 255, 255, 800, 200);
			}

		/*
		point(10.0f, 255, 255, 255, 100, 800);
		point(10.0f, 255, 255, 255, 700, 800);
		point(10.0f, 255, 255, 255, 100, 200);
		point(10.0f, 255, 255, 255, 700, 200);


		point(10.0f, 255, 255, 255, 300, 800);
		point(10.0f, 255, 255, 255, 900, 800);
		point(10.0f, 255, 255, 255, 300, 200);
		point(10.0f, 255, 255, 255, 900, 200);

		*/
		/*print( 175, 800, "Hello");
		print( 775, 800, "Yes");
		print( 175, 200, "No");
		print( 775, 200, "Bye");*/
	}
	

	
	

	if (arrow) {

		if (boxNumber == "1") {
			triangle(0, 175, 600);
			//print(112, 180, (char *)"focus On this Box");
		}		
		else if (boxNumber == "2") {
			triangle(0, 775, 600);
			//print(262, 180, (char *)"focus On this Box");
		}		
		else if (boxNumber == "4") {
			triangle(1, 225, 400);
			//print(90, 73, (char *)"focus On this Box");
		}		
		else if (boxNumber == "5") {
			triangle(1, 825, 400);
			//print(245, 73, (char *)"focus On this Box");
		}
	}
	else if(allBoxes){

		if (box1Mode) {
			square(50, 650, 350, 650, 350, 950, 50, 950);

			//square(50, 175, 100, 175, 100, 265, 50, 265);
			//point(10000.f, 0, 255, 0, 125, 250);
		}


		if (box2Mode) {
			square(650, 650, 950, 650, 950, 950, 650, 950);

			//square(175, 175, 225, 175, 225, 265, 175, 265);
			//point(10000.f, 0, 255, 0, 275, 250);

		}

		if (box4Mode) {
			square(50, 50, 350, 50, 350, 350, 50, 350);
			//point(10000.f, 0, 255, 0, 50, 75);
		}


		if (box5Mode) {
			square(650, 50, 950, 50, 950, 350, 650, 350);
			//square(350, 650, 350, 950, 650, 950, 650, 650);
			//square(175, 50, 225, 50, 225, 140, 175, 140);
			//point(10000.f, 0, 255, 0, 200, 75);
		}


	}




	glFlush();
}


void bar(int x)
{
	std::cout << "helloo";
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return;
	}
	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " <<
			ntohs(client.sin_port) << std::endl;
	}

	// Close listening socket
	closesocket(listening);

	// While loop: accept and echo message back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		// Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cerr << "Error in recv(). Quitting" << std::endl;
			break;
		}

		if (bytesReceived == 0)
		{
			std::cout << "Client disconnected " << std::endl;
			break;
		}

		//std::cout << std::string(buf, 0, bytesReceived) << std::endl;
		clientData = std::string(buf, 0, bytesReceived);
		newDataBool = true;

		// Echo message back to client
		//send(clientSocket, buf, bytesReceived + 1, 0);

	}

	// Close the socket
	closesocket(clientSocket);

	// Cleanup winsock
	WSACleanup();

	system("pause");
}
void boxOne(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	//auto elapsed = std::chrono::high_resolution_clock::now() - current_time;
	//long long microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
	//std::cout << (microseconds) << "\n";
	//current_time = std::chrono::high_resolution_clock::now();
	box1Mode = !box1Mode;
	glutPostRedisplay();						    // redraw 		 
	glutTimerFunc( freq1 , boxOne, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}
void boxTwo(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	box2Mode = !box2Mode;
	glutPostRedisplay();						    // redraw 		 
	glutTimerFunc(freq2, boxTwo, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}
void boxFour(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	box4Mode = !box4Mode;
	glutPostRedisplay();						    // redraw 		 
	glutTimerFunc(freq4, boxFour, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}
void boxFive(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	
	box5Mode = !box5Mode;
	glutPostRedisplay();						    // redraw 		 
	glutTimerFunc(freq5, boxFive, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}
void main(int argc, char** argr) {
	glutInit(&argc, argr);
	std::thread second(bar, 0);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	
	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	glutTimerFunc(0, boxOne, 0);
	glutTimerFunc(0, boxTwo, 0);
	glutTimerFunc(0, boxFour, 0);
	glutTimerFunc(0, boxFive, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000, 0.0, 1000);
	
	std::cout <<  ((1.0/12.0)/2)*1000;
	box1Mode = true;
	box2Mode = true;
	box4Mode = true;
	box5Mode = true;
	glutMainLoop();
}
