#include<iostream>
#include<glad/glad.h> // de lel opengl functions
#include<GLFW/glfw3.h>  // de lel window w el input
#include <cmath> // de lel math functions e7na 3awzenha a4an el sin wel cos lel circle
#include <vector> // including it aashan a2dar a3ml list el feha la3ba fel lines
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// el vertex shader: by2ol kol no2ta tro7 fen 3al shasha  doool GLSL LANGUAGE FOR GPU PRORGRAM // GPU PROGRAM IS SHADER 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform vec2 offset;\n"
"uniform vec2 scale;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x * scale.x + offset.x,\n"
"                      aPos.y * scale.y + offset.y,\n"
"                      0.0, 1.0);\n"
"}\0";

// el fragment shader: by2ol kol pixel gowa el shakl lono eh (orange)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0);\n"
"}\0";

GLuint TriangleVAO, RectangleVAO, TriangleVBO, RectangleVBO, CircleVAO, CircleVBO;

GLint offset, scale, colors;

int screen = 0;
int cutFrame = 0;
int wave = 1;                       // 1, 2 aw 3
int waveSize[3] = { 3, 5, 10 };     // kam enemy fe kol wave
int spawnedInWave = 0;              // tala3na kam enemy fel wave di
float spawnTimer = 0.0f;





void DrawingRectangles(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors

	glBindVertexArray(RectangleVAO);              // bind means select  the rectangle
	glUniform3f(colors, r, g, b);
	glUniform2f(scale, w, h);
	glUniform2f(offset, x, y);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

void DrawingCircle(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors

	glBindVertexArray(CircleVAO);              // bind means select  the circle 
	glUniform3f(colors, r, g, b);
	glUniform2f(scale, w, h);
	glUniform2f(offset, x, y);
	glDrawArrays(GL_TRIANGLES, 0, 24);

}

void DrawingTriangles(float x, float y, float w, float h, float r, float g, float b) { //  (x,y) dol el offsets , (w,h) dool el scaling factors , (r,g,b) dool lel colors

	glBindVertexArray(TriangleVAO);
	glUniform3f(colors, r, g, b);
	glUniform2f(scale, w, h);
	glUniform2f(offset, x, y);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Teta(float x, float y, float s) {   // s = size: 1 = normal, 0.5 = half
	DrawingRectangles(x - 0.056f * s, y - 0.023f * s, 0.017f * s, 0.256f * s, 0.42, 0.26, 0.15);   // el 3asaya (cane)
	DrawingRectangles(x - 0.006f * s, y - 0.05f * s, 0.119f * s, 0.031f * s, 0.42, 0.26, 0.15);   // cane piece
	DrawingRectangles(x, y, 0.073f * s, 0.108f * s, 0.29, 0.17, 0.37);                             // Body of teta
	DrawingCircle(x, y + 0.093f * s, 0.062f * s, 0.111f * s, 0.96, 0.96, 0.96);                    // el hijab
	DrawingCircle(x, y + 0.091f * s, 0.037f * s, 0.067f * s, 0.88, 0.71, 0.54);                    // we4 teta (face)
}

void Mama(float x, float y, float s) {   // melee
	DrawingTriangles(x, y, 0.1f * s, 0.203f * s, 0.48, 0.31, 0.63);                                // dress (purple)
	DrawingCircle(x, y + 0.149f * s, 0.062f * s, 0.111f * s, 0.95, 0.78, 0.29);                    // head / scarf (yellow)
	DrawingRectangles(x + 0.073f * s, y + 0.132f * s, 0.034f * s, 0.117f * s, 0.23, 0.44, 0.82);   // slipper
}

void Brother(float x, float y, float s) {
	DrawingRectangles(x, y - 0.096f * s, 0.058f * s, 0.069f * s, 0.14, 0.22, 0.36);                // pants
	DrawingRectangles(x, y, 0.069f * s, 0.122f * s, 0.16, 0.62, 0.56);                             // shirt
	DrawingCircle(x, y + 0.1f * s, 0.053f * s, 0.094f * s, 0.88, 0.71, 0.54);                      // head
	DrawingRectangles(x + 0.072f * s, y + 0.018f * s, 0.025f * s, 0.086f * s, 0.25, 0.64, 0.30);   // spray can (green)
}

void Namoosa(float x, float y) {
	DrawingRectangles(x - 0.064f, y, 0.047f, 0.008f, 0.17, 0.17, 0.17);
	DrawingCircle(x, y, 0.081f, 0.05f, 0.17, 0.17, 0.17); 
	DrawingCircle(x - 0.007f, y + 0.047f, 0.05f, 0.056f, 0.93, 0.93, 0.93); /


}

void SorSar(float x, float y) {
	DrawingCircle(x, y, 0.125f, 0.078f, 0.55, 0.17, 0.1); // body
	DrawingCircle(x - 0.07f, y, 0.034f, 0.061f, 0.35, 0.12, 0.06); // head

}
void Cat(float x, float y) {
	DrawingRectangles(x + 0.07f, y + 0.047f, 0.016f, 0.111f, 0.85f, 0.47f, 0.12f);
	DrawingCircle(x, y, 0.141f, 0.117f, 0.91f, 0.54f, 0.17f);
	DrawingTriangles(x - 0.11f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);
	DrawingTriangles(x - 0.07f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);
	DrawingCircle(x - 0.091f, y + 0.041f, 0.069f, 0.122f, 0.94f, 0.60f, 0.24f);
}
void Pot(float x, float y) {
	DrawingCircle(x - 0.11f, y + 0.08f, 0.03f, 0.053f, 0.40f, 0.42f, 0.45f);    
	DrawingCircle(x + 0.11f, y + 0.08f, 0.03f, 0.053f, 0.40f, 0.42f, 0.45f);    
	DrawingRectangles(x, y, 0.20f, 0.30f, 0.62f, 0.64f, 0.67f);                
	DrawingRectangles(x, y - 0.165f, 0.16f, 0.03f, 0.35f, 0.36f, 0.38f);         
	DrawingRectangles(x, y + 0.165f, 0.22f, 0.03f, 0.40f, 0.42f, 0.45f);        
	DrawingCircle(x, y + 0.195f, 0.025f, 0.044f, 0.25f, 0.25f, 0.28f);           
	DrawingCircle(x, y + 0.25f, 0.04f, 0.071f, 0.95f, 0.95f, 0.95f);             
}
void Window(float x, float y) {
	DrawingRectangles(x, y, 0.28f, 0.40f, 0.95f, 0.95f, 0.92f);         

	DrawingRectangles(x, y, 0.012f, 0.35f, 0.95f, 0.95f, 0.92f);       
	DrawingRectangles(x, y, 0.24f, 0.02f, 0.95f, 0.95f, 0.92f);        
	DrawingRectangles(x, y - 0.21f, 0.32f, 0.03f, 0.55f, 0.35f, 0.20f);  
}
void Clock(float x, float y) {
	DrawingCircle(x, y, 0.10f, 0.178f, 0.25f, 0.20f, 0.18f);            
	DrawingCircle(x, y, 0.085f, 0.151f, 0.98f, 0.97f, 0.93f);            
	DrawingRectangles(x, y + 0.03f, 0.006f, 0.06f, 0.25f, 0.20f, 0.18f);  
	DrawingRectangles(x + 0.02f, y, 0.04f, 0.008f, 0.25f, 0.20f, 0.18f); 
}
void Fridge(float x, float y) {
	DrawingRectangles(x, y, 0.20f, 0.62f, 0.92f, 0.93f, 0.95f);                   

	DrawingRectangles(x - 0.07f, y, 0.012f, 0.14f, 0.60f, 0.62f, 0.65f);          

}
void Door(float x, float y) {
	DrawingRectangles(x, y, 0.22f, 0.68f, 0.40f, 0.25f, 0.15f);                 
	DrawingRectangles(x, y - 0.01f, 0.19f, 0.65f, 0.60f, 0.40f, 0.25f);        
	DrawingCircle(x + 0.065f, y - 0.02f, 0.02f, 0.036f, 0.90f, 0.75f, 0.30f);  
}
void Shelf(float x, float y) {
	DrawingRectangles(x, y, 0.24f, 0.02f, 0.55f, 0.35f, 0.20f);                 
	DrawingRectangles(x - 0.09f, y - 0.03f, 0.015f, 0.04f, 0.45f, 0.28f, 0.16f);   
	DrawingRectangles(x + 0.09f, y - 0.03f, 0.015f, 0.04f, 0.45f, 0.28f, 0.16f); 
	DrawingRectangles(x - 0.06f, y + 0.05f, 0.05f, 0.08f, 0.85f, 0.35f, 0.25f);    
	DrawingRectangles(x + 0.05f, y + 0.045f, 0.04f, 0.07f, 0.95f, 0.80f, 0.35f);   
}

int mamaHealth = 5;
int brotherHealth = 5;
int tetaHealth = 7;
int namoosaHealth = 5;
int sorsarHealth = 5;
int catHealth = 7;

void HealthSquares(float x, float y, int health) {  // da el health bar el fo2 el characters 
	for (int i = 0; i < health; i++) {
		DrawingRectangles(x + i * 0.018f, y,
			0.014f, 0.025f,        // size of one square
			0.45f, 0.62f, 0.25f);  // green
	}
}

//yahya part

enum EnemyType
{
	EASY,     // namoosa: btedrab men fo2
	MEDIUM,   // sorsar: beyedrab men ta7t
	HARD      // cat: beyegry w beyedrab 2
};

typedef struct EnemyDescription {
	EnemyType type;
	int lane;
	float x;
	int health;
	float hitTimer;     // w2t el darb lama beyetkhane2 m3 player
	float shootTimer;   // w2t el darb men b3eed
} EnemyDescription;

std::vector<EnemyDescription> enemies;



typedef struct Bullet {
	int lane;
	float x;
	bool high;   // true = men fo2 (duck), false = men ta7t (jump)
} Bullet;

std::vector<Bullet> bullets;

typedef struct PlayerBullet {
	int lane;
	float x;
} PlayerBullet;

std::vector<PlayerBullet> playerBullets;   // el spray bta3 el Brother



typedef struct FloorCoin {
	int lane;
	float x;
} FloorCoin;

std::vector<FloorCoin> floorCoins;


bool lost = false;   // true lama enemy yewsal el home base
bool won = false;    // true lama el 3 waves y5lso
//yahya part





// Yassin's Starting Part 



enum PlayerType   // aashan a3rf akml based on type bta3o
{
	MELEE,
	RANGED,
	DEFENSE
};
// (el struct lazem yeb2a ba3d el enum 3ashan beyesta5dem PlayerType)
typedef struct PlayerDescription {
	PlayerType type;
	int lane;
	float x;
	int health;
	int state = 0;           // normal = 0 , jump = 1 , duck = 2
	float stateTime = 0.0f;  // beyhsb el w2t b3d el jump aw el duck
	float shootTimer = 0.0f;
} PlayerDescription;

std::vector<PlayerDescription> players;   // el list beta3et kol el players 

int coin = 30; // intially 30 as maktob fel description 
int prices[3] = { 10,40,60 }; // prices bta3 kol type

bool unlocked[3] = { true,false,false }; // array yeol eh unlocked w eh laa .
bool ElLinesSelected[3] = { false, false, false }; // array da lel selected lines anhy lines selected

int GebElLane(float mouseX, float mouseY)
{
	int lane = -1;   // -1 = mesh 3ala ay lane

	if (mouseX >= -0.75f && mouseX <= 1.0f) {

		if (mouseY <= 0.165f && mouseY > -0.225f) {
			lane = 0;   // Awel lane
		}
		else if (mouseY <= -0.225f && mouseY > -0.615f) {
			lane = 1;   // tani lane
		}
		else if (mouseY <= -0.615f && mouseY >= -1.0f) {
			lane = 2;   // talet lane
		}
	}

	return lane;
}
int GebElCard(float mouseX, float mouseY)
{
	int card = -1; // mesh aal card
	if (mouseY >= 0.703f && mouseY <= 0.937f) {

		if (mouseX >= -0.965f && mouseX <= -0.835f)
		{
			card = MELEE; //bteshra7 nafsha
		}
		else if (mouseX >= -0.815f && mouseX <= -0.685f)
		{
			card = RANGED;
		}
		else if (mouseX >= -0.665f && mouseX <= -0.535f) {
			card = DEFENSE;
		}

	}
	return card;
}

void ResetGame() {
	players.clear();
	enemies.clear();
	bullets.clear();
	playerBullets.clear();
	floorCoins.clear();
	coin = 30;
	wave = 1;
	spawnedInWave = 0;
	spawnTimer = 0.0f;
	lost = false;
	won = false;
	ElLinesSelected[0] = false;
	ElLinesSelected[1] = false;
	ElLinesSelected[2] = false;
}
void DosetElMouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double PixelelX;   // pixel el x
		double PixelelY;   // pixel el y
		glfwGetCursorPos(window, &PixelelX, &PixelelY);   // glfw bygeb el position fel window
		float mouseX = (float)((PixelelX / 1280.0f) * 2.0f - 1.0f);
		float mouseY = (float)(1.0f - (PixelelY / 720.0f) * 2.0f);

		if (screen == 0) {
			if (mouseX >= -0.2f && mouseX <= 0.2f && mouseY >= 0.02f && mouseY <= 0.18f)     // PLAY
				screen = 1;
			if (mouseX >= -0.2f && mouseX <= 0.2f && mouseY >= -0.23f && mouseY <= -0.07f)   // qUIt
				glfwSetWindowShouldClose(window, true);
			return;
		}

		if (screen == 1) return;

		if (screen == 3) {
			if (mouseX >= -0.32f && mouseX <= -0.02f && mouseY >= -0.18f && mouseY <= -0.02f) {   // PLAY
				screen = 2;
			}
			if (mouseX >= 0.02f && mouseX <= 0.32f && mouseY >= -0.18f && mouseY <= -0.02f) {     // rEPLAY
				ResetGame();
				screen = 2;
			}
			return;
		}

		int lane = GebElLane(mouseX, mouseY);
		if (lane != -1)
		{
			ElLinesSelected[lane] = !ElLinesSelected[lane];
		}

		int card = GebElCard(mouseX, mouseY);
		if (card != -1 && unlocked[card]) {   // lw dost 3ala lane msh card matshtresh ay haga
			for (int i = 0; i < 3; i++)
			{
				if (ElLinesSelected[i] && coin >= prices[card])
				{
					PlayerDescription p;
					p.type = (PlayerType)card;
					p.lane = i;
					p.x = -0.70f;
					if (card == DEFENSE) {
						p.health = 7;                                    // Teta
					}
					else {
						p.health = 5;                                    // Mama wel Brother
					}

					players.push_back(p);                                // save fel list el 3amlna fo2 bl include fo2 5ales 
					coin -= prices[card];                                // etfa3
					ElLinesSelected[i] = false;						// deselect the lane
				}
			}
		}
	}
}

//fix fix fix
float CenterKolLane[3] = { -0.03f, -0.42f, -0.81f };   // el y bta3 nos kol lane
void DrawLaneBorder(int lane, float r, float g, float b)
{
	float y = CenterKolLane[lane];   // nos el lane

	DrawingRectangles(0.125f, y + 0.189f, 1.75f, 0.012f, r, g, b);   // fo2 
	DrawingRectangles(0.125f, y - 0.189f, 1.75f, 0.012f, r, g, b);   // ta7t 
	DrawingRectangles(-0.7465f, y, 0.007f, 0.39f, r, g, b);   // shemal 
	DrawingRectangles(0.9965f, y, 0.007f, 0.39f, r, g, b);   // ymen 
}
const char* letterNames = "YOULSEGdJbPArqIt";  // leh el letters de bec dool kol eli hn7tgom fel menues eli homa :YOU lose, good job , play,quit, Replay

//  dol 8 segments 7ashan el letters eli fel menue wel pop ups a4an nktbhom
bool letterSegments[16][7] = {
	//  a      b      c      d      e      f      g
	{ false, true,  true,  true,  false, true,  true },  // 0  Y
	{ true,  true,  true,  true,  true,  true,  false },  // 1  O
	{ false, true,  true,  true,  true,  true,  false },  // 2  U
	{ false, false, false, true,  true,  true,  false },  // 3  L
	{ true,  false, true,  true,  false, true,  true },  // 4  S
	{ true,  false, false, true,  true,  true,  true },  // 5  E
	{ true,  false, true,  true,  true,  true,  false },  // 6  G
	{ false, true,  true,  true,  true,  false, true },  // 7  d
	{ false, true,  true,  true,  true,  false, false },  // 8  J
	{ false, false, true,  true,  true,  true,  true },  // 9  b
	{ true,  true,  false, false, true,  true,  true },  // 10 P
	{ true,  true,  true,  false, true,  true,  true },  // 11 A
	{ false, false, false, false, true,  false, true },  // 12 r
	{ true,  true,  true,  false, false, true,  true },  // 13 q
	{ false, true,  true,  false, false, false, false },  // 14 I
	{ false, false, false, true,  true,  true,  true }   // 15 t
};
void DrawLetter(char letter, float cx, float cy, float s, float r, float g, float b)
{

	int row = -1;
	for (int i = 0; i < 16; i++) {
		if (letterNames[i] == letter) row = i;   //  hena it look at this char in here YOULSEGdJbPArqIt"
	}
	if (row == -1) return;


	if (letterSegments[row][0]) DrawingRectangles(cx, cy + 0.06f * s, 0.04f * s, 0.012f * s, r, g, b);              
	if (letterSegments[row][6]) DrawingRectangles(cx, cy, 0.04f * s, 0.012f * s, r, g, b);                            
	if (letterSegments[row][3]) DrawingRectangles(cx, cy - 0.06f * s, 0.04f * s, 0.012f * s, r, g, b);               
	if (letterSegments[row][5]) DrawingRectangles(cx - 0.02f * s, cy + 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);  
	if (letterSegments[row][1]) DrawingRectangles(cx + 0.02f * s, cy + 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);   
	if (letterSegments[row][4]) DrawingRectangles(cx - 0.02f * s, cy - 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);  
	if (letterSegments[row][2]) DrawingRectangles(cx + 0.02f * s, cy - 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);  
}


void DrawWord(const char* word, float x, float y, float s, float r, float g, float b)
{
	for (int i = 0; word[i] != '\0'; i++) {                     
		DrawLetter(word[i], x + i * 0.055f * s, y, s, r, g, b);  
	}
}


// which of the 7 bars are ON for each digit 0-9
// order of the columns:   a(top)  b(top-right)  c(bottom-right)  d(bottom)  e(bottom-left)  f(top-left)  g(middle)
bool digitSegments[10][7] = {
	//  a      b      c      d      e      f      g
	{ true,  true,  true,  true,  true,  true,  false },   // 0
	{ false, true,  true,  false, false, false, false },   // 1
	{ true,  true,  false, true,  true,  false, true },   // 2
	{ true,  true,  true,  true,  false, false, true },   // 3
	{ false, true,  true,  false, false, true,  true },   // 4
	{ true,  false, true,  true,  false, true,  true },   // 5
	{ true,  false, true,  true,  true,  true,  true },   // 6
	{ true,  true,  true,  false, false, false, false },   // 7
	{ true,  true,  true,  true,  true,  true,  true },   // 8
	{ true,  true,  true,  true,  false, true,  true }    // 9
};

// draws one digit (0-9) with its centre at (cx, cy), s = size (1 = normal)
void DrawDigit(int digit, float cx, float cy, float s, float r, float g, float b)
{
	// horizontal bars
	if (digitSegments[digit][0]) DrawingRectangles(cx, cy + 0.06f * s, 0.04f * s, 0.012f * s, r, g, b);   // a: top
	if (digitSegments[digit][6]) DrawingRectangles(cx, cy, 0.04f * s, 0.012f * s, r, g, b);   // g: middle
	if (digitSegments[digit][3]) DrawingRectangles(cx, cy - 0.06f * s, 0.04f * s, 0.012f * s, r, g, b);   // d: bottom

	// vertical bars
	if (digitSegments[digit][5]) DrawingRectangles(cx - 0.02f * s, cy + 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);   // f: upper left
	if (digitSegments[digit][1]) DrawingRectangles(cx + 0.02f * s, cy + 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);   // b: upper right
	if (digitSegments[digit][4]) DrawingRectangles(cx - 0.02f * s, cy - 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);   // e: lower left
	if (digitSegments[digit][2]) DrawingRectangles(cx + 0.02f * s, cy - 0.03f * s, 0.007f * s, 0.06f * s, r, g, b);   // c: lower right
}

// draws a whole number (0 to 999), starting at x and going right, s = size
void DrawNumber(int number, float x, float y, float s, float r, float g, float b)
{
	int hundreds = number / 100;
	int tens = (number / 10) % 10;
	int ones = number % 10;

	float gap = 0.055f * s;              // smaller digits -> smaller gap

	if (number >= 100) {
		DrawDigit(hundreds, x, y, s, r, g, b);   // pass the size along
		x = x + gap;
	}
	if (number >= 10) {
		DrawDigit(tens, x, y, s, r, g, b);
		x = x + gap;
	}
	DrawDigit(ones, x, y, s, r, g, b);
}

//fix fix fix
void RasmetElCard()
{
	DrawingRectangles(-0.90f, 0.82f, 0.13f, 0.234f, 0.45f, 0.30f, 0.18f);
	DrawingRectangles(-0.90f, 0.82f, 0.117f, 0.215f, 0.98f, 0.94f, 0.85f);
	Mama(-0.90f, 0.835f, 0.39f);
	DrawNumber(prices[MELEE], -0.913f, 0.735f, 0.4f, 0.93f, 0.45f, 0.15f);
	DrawingRectangles(-0.75f, 0.82f, 0.13f, 0.234f, 0.45f, 0.30f, 0.18f);
	DrawingRectangles(-0.75f, 0.82f, 0.117f, 0.215f, 0.98f, 0.94f, 0.85f);
	Brother(-0.75f, 0.835f, 0.45f);
	DrawNumber(prices[RANGED], -0.763f, 0.735f, 0.4f, 0.93f, 0.45f, 0.15f);
	DrawingRectangles(-0.60f, 0.82f, 0.13f, 0.234f, 0.45f, 0.30f, 0.18f);
	DrawingRectangles(-0.60f, 0.82f, 0.117f, 0.215f, 0.98f, 0.94f, 0.85f);
	Teta(-0.60f, 0.835f, 0.45f);
	DrawNumber(prices[DEFENSE], -0.613f, 0.735f, 0.4f, 0.93f, 0.45f, 0.15f);
}
float JumpDuckOffset(int state, float time) { // beyshb how high el jump we how lower el duck
	if (state == 1)
		return 0.15f * sin(3.14159f * time / 0.6f);
	if (state == 2)
		return -0.06f;
	return 0;
}
void RasmElBoughtPlayer(PlayerDescription p)			// betersem player wa7ed: el character + el health bar beta3o
{
	float up = JumpDuckOffset(p.state, p.stateTime);   //  ad eh el player yetla3 aw yenzel
	float y = CenterKolLane[p.lane] - 0.04f + up;

	if (p.type == MELEE)
		Mama(p.x, y, 0.75f);

	else if (p.type == RANGED)
		Brother(p.x, y, 0.75f);

	else
		Teta(p.x, y, 0.75f);

	float barY = CenterKolLane[p.lane] + 0.165f + up;  // Yahya: el health bar yetla3 m3ah
	float startX = p.x - (p.health - 1) * 0.009f;

	for (int i = 0; i < p.health; i++)
	{
		DrawingRectangles(startX + i * 0.018f, barY, 0.015f, 0.027f, 0.85f, 0.15f, 0.15f);
	}
}



bool EnemyOdamPlayer(PlayerDescription player)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].lane != player.lane)
			continue;                                  // msh fe nafs el lane -> skip

		float masafa = enemies[i].x - player.x;        // positive = el enemy 3ala ymeen el player
		if (masafa >= 0 && masafa < 0.15f)
			return true;                               // fe enemy odamo -> o2af
	}
	return false;                                      // mafeesh 7ad odamo -> emshy
}
void MovementElplayers()
{

	if (lost || won)
		return;
	for (int i = 0;i < players.size(); i++)
	{
		if (players[i].type != DEFENSE && players[i].x < 0.93f && !EnemyOdamPlayer(players[i]))
		{
			players[i].x += 0.0015f;
		}
	}
}

bool HalEnemeyOdamy(PlayerDescription player)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].lane != player.lane)
			continue;
		if (enemies[i].x > player.x)
			return true;
	}
	return false;
}

void BrotherYedrab()   // el Brother beyedrab men b3eed kol 1.5 seconds
{
	if (lost || won)
		return;

	for (int i = 0; i < players.size(); i++) {
		if (players[i].type != RANGED)
			continue;                              // el Brother bas
		if (!HalEnemeyOdamy(players[i]))
			continue;                              // mafeesh enemy odamo -> mayedrabsh

		players[i].shootTimer = players[i].shootTimer + 0.016f;
		if (players[i].shootTimer >= 1.5f) {
			PlayerBullet b;
			b.lane = players[i].lane;
			b.x = players[i].x + 0.05f;            // men 3and el spray can
			playerBullets.push_back(b);
			players[i].shootTimer = 0;
		}
	}
}
void MoveBrotherBullets()
{
	if (lost || won)
		return;

	for (int i = playerBullets.size() - 1; i >= 0; i--) {
		playerBullets[i].x = playerBullets[i].x + 0.01f;   // el spray beyemshy ymeen

		bool etshalet = false;

		for (int e = 0; e < enemies.size(); e++) {
			if (enemies[e].lane != playerBullets[i].lane) continue;

			float masafa = enemies[e].x - playerBullets[i].x;
			if (masafa < 0) masafa = -masafa;

			if (masafa < 0.05f) {
				enemies[e].health = enemies[e].health - 1;   // el enemy etdarab
				etshalet = true;
				break;
			}
		}

		if (playerBullets[i].x > 1.0f) etshalet = true;      // 5arget mel lane

		if (etshalet) playerBullets.erase(playerBullets.begin() + i);
	}
}

void RasmBrotherBullets()
{
	for (int i = 0; i < playerBullets.size(); i++) {
		float y = CenterKolLane[playerBullets[i].lane] - 0.03f;   // 3ala 3elw el spray can
		DrawingCircle(playerBullets[i].x, y, 0.025f, 0.044f, 0.25f, 0.64f, 0.30f);   // green spray
	}
}




// Yassin's Ending part!


//Yahya's starting his part 




void KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;

	if (key == GLFW_KEY_ESCAPE) {
		if (screen == 2) screen = 3;
		else if (screen == 3) screen = 2;
		return;
	}
	if (screen != 2) return;

	int newState = 0;
	if (key == GLFW_KEY_W || key == GLFW_KEY_UP)
		newState = 1;// jump
	if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
		newState = 2;   // duck
	if (newState == 0)
		return;

	for (int i = 0; i < players.size(); i++) { // hena bnshof mn el players ely msh bey duck or jump
		if (players[i].type == DEFENSE)
			continue;          // Teta mabetjumpsh
		if (!ElLinesSelected[players[i].lane])
			continue;   // el lane msh selected
		if (players[i].state != 0)
			continue;              // already jumping/ducking

		players[i].state = newState;
		players[i].stateTime = 0;
	}
}

void UpdateJumpDuck(int& state, float& time)   // el jump/duck by5las ba3d 0.6 seconds
{
	if (state == 0)
		return;
	time = time + 0.016f;
	if (time >= 0.6f) {
		state = 0;
		time = 0;
	}
}


void YahyaPlayers()   // update el jump + ersem el players b-function Yassin
{
	for (int i = 0; i < players.size(); i++) {
		if (!lost && !won)
			UpdateJumpDuck(players[i].state, players[i].stateTime);   // el jump/duck by5las ba3d 0.6 s

		RasmElBoughtPlayer(players[i]);   // Yassin's function (heya elly bt-add el jump offset)
	}
}







void SpawnEnemy()
{
	EnemyDescription enemy;

	if (wave == 1)
		enemy.type = EASY;                                // wave 1: namoosa bas
	if (wave == 2)
		enemy.type = (EnemyType)(spawnedInWave % 2);      // wave 2: namoosa w sorsar
	if (wave == 3)
		enemy.type = (EnemyType)(spawnedInWave % 3);      // wave 3: el talata

	enemy.lane = rand() % 3;      // rand betnzl 3 enemies f random lane
	enemy.x = 1.0f;               // men el right edge
	enemy.hitTimer = 0;
	enemy.shootTimer = 0;

	if (enemy.type == HARD)
		enemy.health = 7; //lw wave hard el enemies el health bt3hm beyb3a 7 bdl 5
	else
		enemy.health = 5;

	enemies.push_back(enemy);
	spawnedInWave = spawnedInWave + 1;
}

void UpdateWaves()
{
	// lesa fe enemies fel wave di fa spawn enemies kol 2 seconds
	if (spawnedInWave < waveSize[wave - 1]) {
		spawnTimer = spawnTimer + 0.016f;
		if (spawnTimer >= 2.0f) {
			SpawnEnemy();
			spawnTimer = 0;
		}
		return;
	}

	// el wave 5lst kolaha w mafeesh enemies fa nd5ol 3la el wave elly ba3daha lw de a5r wave ely heya 3 ent akda ksbt 
	if (enemies.size() == 0) {
		if (wave == 3) {
			won = true;
			std::cout << "Alf mabrook enta ksbt" << std::endl;
		}
		else {
			wave = wave + 1;
			spawnedInWave = 0;
			spawnTimer = 0;
			std::cout << "matfrhsh lesa fe wave tanya" << wave << std::endl;
		}
	}
}

int PlayerOdamEnemy(EnemyDescription enemy) // anhy player wa2ef 2odam el enemy da fe nafs el lane? -1 da lw mafesh enemy odam el player 

{
	for (int i = 0; i < players.size(); i++) {
		if (players[i].lane != enemy.lane)
			continue;
		float masafa = enemy.x - players[i].x; // lw rg3t positive value yeb2a el player 3ala el shemal
		if (masafa >= 0 && masafa < 0.15f)
			return i; // betrg3 player number
	}
	return -1;
}

void MoveAndFight()
{
	for (int i = 0; i < enemies.size(); i++) {
		int player = PlayerOdamEnemy(enemies[i]);

		if (player == -1) {
			// mafeesh player fa el enemy hyemshy shemal
			if (enemies[i].type == HARD)
				enemies[i].x = enemies[i].x - 0.003f;   // 0.003f de sor3t el cat 
			else
				enemies[i].x = enemies[i].x - 0.00100f; // 0.0015f de sor3t el sorsar wel namosa
		}
		else {

			enemies[i].hitTimer = enemies[i].hitTimer + 0.016f; // fe player wa2f w hayebd2 yerdrb el enemy ba3d kol second
			if (enemies[i].hitTimer >= 1.0f) {
				if (players[player].type != DEFENSE)
					enemies[i].health = enemies[i].health - 1;   //  el player beyedrab el awel. lw el player msh Teta el enemy beya5od damage by 1 we Teta defense player fa msh bet attack

				if (enemies[i].health > 0) {   //  el enemy beyedrab bas lw lesa 3ayesh ba3d darbet el player
					if (enemies[i].type == HARD)
						players[player].health = players[player].health - 2; // 3alashan enemy hard fa el player bey5od damage by 2
					else
						players[player].health = players[player].health - 1; // el player bey5od damage by 1 3ady
				}

				enemies[i].hitTimer = 0;
			}
		}
	}
}
void EnemiesShoot()   // namoosa wel sorsar beyedrabo men b3eed kol 2 seconds
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].type == HARD)
			continue;   // el cat mabtedrabsh men b3eed
		if (PlayerOdamEnemy(enemies[i]) != -1) continue; // lama el namosa tewsl lel player tebtl t shoot 
		enemies[i].shootTimer = enemies[i].shootTimer + 0.016f;
		if (enemies[i].shootTimer >= 5.0f) {
			Bullet b;
			b.lane = enemies[i].lane;
			b.x = enemies[i].x;
			b.high = (enemies[i].type == EASY);   // namoosa fo2, sorsar ta7t
			bullets.push_back(b);
			enemies[i].shootTimer = 0;
		}
	}
}

void MoveBullets()
{

	for (int i = bullets.size() - 1; i >= 0; i--) {
		bullets[i].x = bullets[i].x - 0.0050f;   // el darba betemshy shemal

		bool etshalet = false;

		for (int p = 0; p < players.size(); p++) {
			if (players[p].lane != bullets[i].lane)
				continue;
			if (bullets[i].x - players[p].x > 0.05f)
				continue;    // lesa mawseltsh
			if (players[p].x - bullets[i].x > 0.05f)
				continue;    // 3adet 5alas

			// dodge: duck lel high, jump lel low (Teta mabt-dodge-sh)
			if (bullets[i].high && players[p].state == 2)
				continue;
			if (!bullets[i].high && players[p].state == 1)
				continue;

			players[p].health = players[p].health - 1;   // etdarab
			etshalet = true;
			break;
		}

		if (bullets[i].x < -0.75f) etshalet = true;      // 5arget mel lane

		if (etshalet) bullets.erase(bullets.begin() + i);
	}
}


void RemoveDead()
{
	// enemies mayteen -> coin 3al ard
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i].health <= 0) {
			FloorCoin c;
			c.lane = enemies[i].lane;
			c.x = enemies[i].x;
			floorCoins.push_back(c);

			enemies.erase(enemies.begin() + i);
		}
	}

	// players mayteen (w el jumpInfo bta3hom m3ahom)

	for (int i = players.size() - 1; i >= 0; i--) {
		if (players[i].health <= 0) {
			players.erase(players.begin() + i);
		}
	}
}

void PickUpCoins()   // player lamas coin -> +10
{
	for (int i = floorCoins.size() - 1; i >= 0; i--) {
		for (int p = 0; p < players.size(); p++) {
			if (players[p].lane != floorCoins[i].lane) continue;
			float masafa = floorCoins[i].x - players[p].x;
			if (masafa < 0) masafa = -masafa;

			if (masafa < 0.2f) {
				coin = coin + 30;
				floorCoins.erase(floorCoins.begin() + i);
				break;
			}
		}
	}
}

void CheckLose()
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].x <= -0.75f) {
			lost = true;
			std::cout << "enta 5srt m3lsh" << std::endl;
		}
	}
}

void UpdateEnemies()   // kol el enemy logic kol frame
{
	if (lost || won)
		return;   // el game 5eles -> kol 7aga wa2fa

	UpdateWaves();
	MoveAndFight();
	EnemiesShoot();
	MoveBullets();
	RemoveDead();
	CheckLose();
}



void RasmElEnemy(EnemyDescription enemy)
{
	float y = CenterKolLane[enemy.lane];

	if (enemy.type == EASY)
		Namoosa(enemy.x, y + 0.08f);   // fo2 lane 1
	else if (enemy.type == MEDIUM)
		SorSar(enemy.x, y - 0.10f);    // ta7t lane 2
	else
		Cat(enemy.x, y - 0.06f); // lane 3

	// health (dark red)
	float barY = CenterKolLane[enemy.lane] + 0.165f;
	float startX = enemy.x - (enemy.health - 1) * 0.009f;
	for (int i = 0; i < enemy.health; i++) {
		DrawingRectangles(startX + i * 0.018f, barY, 0.015f, 0.027f, 0.45f, 0.10f, 0.10f);
	}
}

void DrawEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		RasmElEnemy(enemies[i]);
	}

	for (int i = 0; i < bullets.size(); i++) {
		float y = CenterKolLane[bullets[i].lane];
		if (bullets[i].high)
			DrawingCircle(bullets[i].x, y + 0.08f, 0.02f, 0.035f, 0.17f, 0.17f, 0.17f);       // namoosa: dark circle fo2
		else
			DrawingRectangles(bullets[i].x, y - 0.13f, 0.02f, 0.035f, 0.90f, 0.80f, 0.55f);  // sorsar: beige square ta7t
	}


}
void DrawMainMenu() {
	DrawingRectangles(0.0f, 0.1f, 0.4f, 0.16f, 0.48f, 0.31f, 0.63f);
	DrawWord("PLAY", -0.1f, 0.1f, 1.2f, 1.0f, 1.0f, 1.0f);
	DrawingRectangles(0.0f, -0.15f, 0.4f, 0.16f, 0.45f, 0.30f, 0.18f);
	DrawWord("qUIt", -0.1f, -0.15f, 1.2f, 1.0f, 1.0f, 1.0f);
}

void DrawPauseMenu() {
	DrawingRectangles(0.0f, 0.0f, 1.0f, 0.8f, 0.15f, 0.12f, 0.10f);
	DrawWord("PAUSEd", -0.21f, 0.25f, 1.5f, 1.0f, 1.0f, 1.0f);

	DrawingRectangles(-0.17f, -0.1f, 0.3f, 0.16f, 0.48f, 0.31f, 0.63f);
	DrawWord("PLAY", -0.236f, -0.1f, 0.8f, 1.0f, 1.0f, 1.0f);

	DrawingRectangles(0.17f, -0.1f, 0.3f, 0.16f, 0.45f, 0.30f, 0.18f);
	DrawWord("rEPLAY", 0.06f, -0.1f, 0.8f, 1.0f, 1.0f, 1.0f);
}

void DrawCutscene() {
	Window(-0.30f, 0.55f);
	Clock(0.0f, 0.72f);
	Shelf(0.0f, 0.40f);
	Fridge(0.30f, 0.48f);
	Door(0.60f, 0.51f);
	DrawingRectangles(0.0f, -0.6f, 2.0f, 0.8f, 0.79f, 0.51f, 0.31f);   // floor
	Pot(-0.5f, -0.35f);

	Mama(-0.25f, -0.35f, 1.4f);

	float mx = 1.1f - cutFrame * 0.003f;
	if (mx < 0.3f) mx = 0.3f;
	Namoosa(mx, -0.05f);

	if (cutFrame == 0)   PlaySoundA("voices/cut_01_mama.wav", NULL, SND_FILENAME | SND_ASYNC);
	if (cutFrame == 420) PlaySoundA("voices/cut_02_mosquito.wav", NULL, SND_FILENAME | SND_ASYNC);

	cutFrame = cutFrame + 1;
	if (cutFrame >= 720) screen = 2;
}















//Yahya's ending his part



int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Shib-Shib Defense", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);     // loop runs at the screen's speed (about 60 per second) 3ala 7sb el pc bt3k 
	gladLoadGL();
	glViewport(0, 0, 1280, 720);

	// el 3 no2at bto3 el triangle: (x, y, z)
	GLfloat TriangleVertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	GLfloat RectangleVertices[] =  // hena da 2 trinagles a4an n3ml rectangle el mfrod 6 vertices bs fe 2 points by3mlo overlapping 3ala b3d
	{
		-0.5f, -0.5f, 0.0f, // ta7t 3al 4emal
		 0.5f, -0.5f, 0.0f, // ta7t 3al ymen
		 0.5f,  0.5f, 0.0f, // fo2 3al ymen
		-0.5f,  0.5f, 0.0f // fo2 3al 4emal
	};
	GLfloat CircleVertices[] =   // 8 triangles x 3 points = 24 points  el radius is 0.5, el center (0, 0, 0) 3al shasha a4an ageb el x le kol slice b3ml el cos w el y b3ml el sin, w el z = 0.0f 3al shasha

	{
		0.0f, 0.0f, 0.0f,    0.5f,    0.0f,   0.0f,    0.354f,  0.354f, 0.0f,   // 1: C, A, B   c here is the center thats why it repeats in every triangle
		0.0f, 0.0f, 0.0f,    0.354f,  0.354f, 0.0f,    0.0f,    0.5f,   0.0f,   // 2: C, B, D
		0.0f, 0.0f, 0.0f,    0.0f,    0.5f,   0.0f,   -0.354f,  0.354f, 0.0f,   // 3: C, D, E
		0.0f, 0.0f, 0.0f,   -0.354f,  0.354f, 0.0f,   -0.5f,    0.0f,   0.0f,   // 4: C, E, F
		0.0f, 0.0f, 0.0f,   -0.5f,    0.0f,   0.0f,   -0.354f, -0.354f, 0.0f,   // 5: C, F, G
		0.0f, 0.0f, 0.0f,   -0.354f, -0.354f, 0.0f,    0.0f,   -0.5f,   0.0f,   // 6: C, G, H
		0.0f, 0.0f, 0.0f,    0.0f,   -0.5f,   0.0f,    0.354f, -0.354f, 0.0f,   // 7: C, H, I
		0.0f, 0.0f, 0.0f,    0.354f, -0.354f, 0.0f,    0.5f,    0.0f,   0.0f    // 8: C, I, A
	};

	// 1) vertex shader: e3mel wa7ed fady, edilo el text, e3melo compile  1 to 3 dol same for everyshape they are just to create the shader program for the gpu (graphic pipline)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 2) nafs el kalam lel fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 3) n7ot el etnen f program wa7ed w nerbothom ba3d
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// da hena a4an ne move el objects 
	offset = glGetUniformLocation(shaderProgram, "offset");
	scale = glGetUniformLocation(shaderProgram, "scale");
	colors = glGetUniformLocation(shaderProgram, "color");
	// el program ma3ah nos5a, fa mesh me7tagenhom
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 4) VBO = sandoo2 f memory el graphics card fih el no2at
	//    VAO = wara2a bt2ol ezay ne2ra el sandoo2
	// 
	//GLuint TriangleVAO, RectangleVAO, TriangleVBO, RectangleVBO , CircleVAO, CircleVBO;
	glGenVertexArrays(1, &TriangleVAO);
	glGenVertexArrays(1, &RectangleVAO);
	glGenVertexArrays(1, &CircleVAO);
	glGenBuffers(1, &TriangleVBO);
	glGenBuffers(1, &RectangleVBO);
	glGenBuffers(1, &CircleVBO);

	//circle 

	glBindVertexArray(CircleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, CircleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CircleVertices), CircleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// triangle
	glBindVertexArray(TriangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices), TriangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// rectangle
	glBindVertexArray(RectangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, RectangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RectangleVertices), RectangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);






	glfwSetMouseButtonCallback(window, DosetElMouse);   // "GLFW, on every click, call MouseClick"
	glfwSetKeyCallback(window, KeyPress);




	// Yahya's starting his part
	srand((unsigned)time(0));
	glfwSetKeyCallback(window, KeyPress);
	// Yahya's ending his part


	int counter = 60;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.95f, 0.89f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); // 3alashan ne use el program elly 3mlnah bta3 el shader el GLSL eli fo2

		if (screen == 0) {
			DrawMainMenu();
		}
		else if (screen == 1) {
			DrawCutscene();
		}
		else {
			Pot(-0.875, -0.42);
			Window(-0.30f, 0.55f);
			Clock(0.0f, 0.72f);
			Fridge(0.30f, 0.48f);
			Door(0.60f, 0.51f);
			Shelf(0.0f, 0.40f);

			// lanes
			DrawingRectangles(0.125f, -0.03f, 1.75f, 0.39f, 0.79f, 0.51f, 0.31f);   // lane 1
			DrawingRectangles(0.125f, -0.42f, 1.75f, 0.39f, 0.78f, 0.56f, 0.40f);   // lane 2
			DrawingRectangles(0.125f, -0.81f, 1.75f, 0.39f, 0.79f, 0.51f, 0.31f);   // lane 3

			// Yassin's Starting Part
			double PixelelX;
			double PixelelY;
			glfwGetCursorPos(window, &PixelelX, &PixelelY);
			float mouseX = (float)((PixelelX / 1280.0f) * 2.0f - 1.0f);
			float mouseY = (float)(1.0f - (PixelelY / 720.0f) * 2.0f);
			int ElcursorFeen = GebElLane(mouseX, mouseY);

			for (int i = 0; i < 3; i++) {
				if (ElLinesSelected[i] == true) {          // da aashan y highlight el line el ya hy hover aaleh ya hy select it
					DrawLaneBorder(i, 1.0f, 0.92f, 0.45f);
				}
				else if (i == ElcursorFeen) {
					DrawLaneBorder(i, 1.0f, 0.92f, 0.45f);
				}
			}
			for (int i = 0; i < 3; i++) {          // i = 0 MELEE, 1 RANGED, 2 DEFENSE
				if (coin >= prices[i])             // 3andy floos kfaya lel type da?
				{
					unlocked[i] = true;
				}
				else
				{
					unlocked[i] = false;           // no  -> lock it again (re-lock)
				}
			}

			DrawingCircle(0.80f, 0.875f, 0.05f, 0.089f, 0.88f, 0.65f, 0.15f);   // coin icon
			DrawNumber(coin, 0.86f, 0.875f, 1.0f, 0.93f, 0.45f, 0.15f);   // size 1 = normal

			RasmetElCard();
			if (screen == 2) {
				MovementElplayers();
				BrotherYedrab();
				MoveBrotherBullets();
			}
			RasmBrotherBullets();
			// Yassin's Ending Part

			// Yahya's starting his part
			YahyaPlayers();
			if (screen == 2) {
				UpdateEnemies();
			}
			DrawEnemies();
			// Yahya's ending his part

			if (lost) {
				DrawingRectangles(0.0f, 0.0f, 1.0f, 0.8f, 0.2f, 0.1f, 0.1f);
				DrawWord("YOU LOSE", -0.29f, 0.2f, 1.5f, 1.0f, 1.0f, 1.0f);
			}
			if (won) {
				DrawingRectangles(0.0f, 0.0f, 1.0f, 0.8f, 0.15f, 0.35f, 0.20f);
				DrawWord("GOOd JOb", -0.29f, 0.2f, 1.5f, 1.0f, 1.0f, 1.0f);
			}

			if (screen == 3) {
				DrawPauseMenu();
			}
		}

		glfwSwapBuffers(window);
	}

	// 6) emsa7 kol 7aga 3amalnaha
	glDeleteVertexArrays(1, &TriangleVAO);
	glDeleteVertexArrays(1, &RectangleVAO);
	glDeleteVertexArrays(1, &CircleVAO);


	glDeleteBuffers(1, &TriangleVBO);
	glDeleteBuffers(1, &RectangleVBO);
	glDeleteBuffers(1, &CircleVBO);



	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}
