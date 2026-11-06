#include<iostream>
#include<glad/glad.h> // de lel opengl functions
#include<GLFW/glfw3.h>  // de lel window w el input
#include <cmath> // de lel math functions e7na 3awzenha a4an el sin wel cos lel circle
#include <vector> // including it aashan a2dar a3ml list el feha la3ba fel lines

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
"uniform float red;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(mix(color, vec3(1.0, 0.0, 0.0), red), 1.0);\n"
"}\0";

GLuint TriangleVAO, RectangleVAO, TriangleVBO, RectangleVBO, CircleVAO, CircleVBO;

GLint offset, scale, colors;
GLint makanelred;   // where "red" is inside the shader

// hn3ml function testahl 3lena bdl mn3ed kol 4ewaya hn3ml wa7d lel rectangle we wa7d lel circle we by5do inputes we bytl3o el shapes . bnendh 3lehom fel while loop


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
	DrawingRectangles(x - 0.064f, y, 0.047f, 0.008f, 0.17, 0.17, 0.17); // stinger
	DrawingCircle(x, y, 0.081f, 0.05f, 0.17, 0.17, 0.17); // body
	DrawingCircle(x - 0.007f, y + 0.047f, 0.05f, 0.056f, 0.93, 0.93, 0.93); // head


}

void SorSar(float x, float y) {
	DrawingCircle(x, y, 0.125f, 0.078f, 0.55, 0.17, 0.1); // body
	DrawingCircle(x - 0.07f, y, 0.034f, 0.061f, 0.35, 0.12, 0.06); // head

}
void Cat(float x, float y) {
	DrawingRectangles(x + 0.07f, y + 0.047f, 0.016f, 0.111f, 0.85f, 0.47f, 0.12f);   // tail (dark orange)
	DrawingCircle(x, y, 0.141f, 0.117f, 0.91f, 0.54f, 0.17f);                         // body (orange)
	DrawingTriangles(x - 0.11f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);       // left ear
	DrawingTriangles(x - 0.07f, y + 0.12f, 0.028f, 0.05f, 0.91f, 0.54f, 0.17f);       // right ear
	DrawingCircle(x - 0.091f, y + 0.041f, 0.069f, 0.122f, 0.94f, 0.60f, 0.24f);       // head (light orange)
}

int mamaHealth = 5;
int brotherHealth = 5;
int tetaHealth = 7;
int namoosaHealth = 5;
int sorsarHealth = 5;
int catHealth = 7;

void HealthSquares(float x, float y, int health) {  // da el health bar el fo2 el characters . 
	for (int i = 0; i < health; i++) {
		DrawingRectangles(x + i * 0.018f, y,
			0.014f, 0.025f,        // size of one square
			0.45f, 0.62f, 0.25f);  // green
	}
}



enum EnemyType
{
	EASY,     // namoosa: btedrab men fo2 ,fa 0 = namosa
	MEDIUM,   // sorsar: beyedrab men ta7t ,fa 1 = sorsar
	HARD      // cat: beyegry w beyedrab 2 ,fa 2 = cat
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

std::vector<PlayerDescription> players;   // el list beta3et kol el players (btebda2 empty)

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
void DosetElMouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double PixelelX;   // pixel el x
		double PixelelY;   // pixel el y
		glfwGetCursorPos(window, &PixelelX, &PixelelY);   // glfw bygeb el position fel window
		float mouseX = (float)((PixelelX / 1280.0f) * 2.0f - 1.0f);
		float mouseY = (float)(1.0f - (PixelelY / 720.0f) * 2.0f);

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
	for(int i = 0;i <players.size(); i++)
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

	int newState = 0;
	if (key == GLFW_KEY_W || key == GLFW_KEY_UP)   
		newState = 1;
	if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) 
		newState = 2;  
	if (newState == 0) 
		return;

	

	for (int i = 0; i < players.size(); i++) { // hena bnshof mn el players ely msh bey duck or jump
		if (players[i].type == DEFENSE) 
			continue;          
		if (!ElLinesSelected[players[i].lane]) 
			continue;   
		if (players[i].state != 0) 
			continue;              

		players[i].state = newState;
		players[i].stateTime = 0;
	}
}

void w2tJumpDuck(int& state, float& time)   // el jump/duck by5las ba3d 0.6 seconds
{
	if (state == 0) 
		return;
	time = time + 0.016f;
	if (time >= 0.6f) {
		state = 0;
		time = 0;
	}
}


void zbttjumpduckplayer()   // update el jump + ersem el players b3d el zbta
{
	for (int i = 0; i < players.size(); i++) {
		if (!lost && !won)
			w2tJumpDuck(players[i].state, players[i].stateTime);   

		RasmElBoughtPlayer(players[i]);   
	}
}


int wave = 1;                       
int waveSize[3] = { 3, 5, 10 };    
int spawnedInWave = 0;             
float spawnTimer = 0.0f;

void bnzlenemy()
{
	EnemyDescription enemy;

	if (wave == 1) 
		enemy.type = EASY;                               
	if (wave == 2) 
		enemy.type = (EnemyType)(spawnedInWave % 2);      // wave 2: namoosa w sorsar bet3rf ezay b enk spawedinwave % 2 hatetl3 0 1 0 1 we hakaza 0 = namosa 1 = sorsar
	if (wave == 3) 
		enemy.type = (EnemyType)(spawnedInWave % 3);      

	enemy.lane = rand() % 3;     
	enemy.x = 1.0f;              
	enemy.hitTimer = 0;
	enemy.shootTimer = 0;

	if (enemy.type == HARD) 
		enemy.health = 7; 
	else                
		enemy.health = 5;

	enemies.push_back(enemy);
	spawnedInWave = spawnedInWave + 1;
}

void UpdateWaves() // lesa fe enemies fel wave di fa spawn enemies kol 2 seconds
{
	
	if (spawnedInWave < waveSize[wave - 1]) {
		spawnTimer = spawnTimer + 0.016f;
		if (spawnTimer >= 2.0f) {
			bnzlenemy();
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
		float masafa = enemy.x - players[i].x; 
		if (masafa >= 0 && masafa < 0.15f) 
			return i; 
	}
	return -1;
}

void ethrkwdrb()   // el enemies btemshy aw btedra
{
	for (int i = 0; i < enemies.size(); i++) {

		float speed = 0.001f;
		int damage = 1;
		if (enemies[i].type == HARD) {
			speed = 0.003f;
			damage = 2;
		}

		int player = PlayerOdamEnemy(enemies[i]);   

		if (player == -1) {
			enemies[i].x = enemies[i].x - speed;
			continue;
		}

		enemies[i].hitTimer = enemies[i].hitTimer + 0.016f;
		if (enemies[i].hitTimer < 1.0f)
			continue;
		enemies[i].hitTimer = 0;

		if (players[player].type != DEFENSE)
			enemies[i].health = enemies[i].health - 1;

		if (enemies[i].health > 0)
			players[player].health = players[player].health - damage;
	}
}
void Enemiesbttrb()   
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].type == HARD)
			continue;   

		if (PlayerOdamEnemy(enemies[i]) != -1)
			continue; 
		enemies[i].shootTimer = enemies[i].shootTimer + 0.016f;

		if (enemies[i].shootTimer >= 5.0f) {
			Bullet b;
			b.lane = enemies[i].lane;
			b.x = enemies[i].x;
			b.high = (enemies[i].type == EASY);   
			bullets.push_back(b);
			enemies[i].shootTimer = 0;
		}
	}
}

void threkelBullets()
{

	for (int i = bullets.size() - 1; i >= 0; i--) {
		bullets[i].x = bullets[i].x - 0.0050f;   // 

		bool etshalet = false;

		for (int p = 0; p < players.size(); p++) {
			if (players[p].lane != bullets[i].lane) 
				continue;
			if (bullets[i].x - players[p].x > 0.05f) 
				continue;    
			if (players[p].x - bullets[i].x > 0.05f) 
				continue;    

			// dodge: duck lel high, jump lel low (Teta mabt-dodge-sh)
			if (bullets[i].high && players[p].state == 2) 
				continue;
			if (!bullets[i].high && players[p].state == 1) 
				continue;

			players[p].health = players[p].health - 1;   
			etshalet = true;
			break;
		}

		if (bullets[i].x < -0.75f) etshalet = true;      

		if (etshalet) bullets.erase(bullets.begin() + i);
	}
}


void sheelelDead()
{
	
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i].health <= 0) {
			FloorCoin coin;
			coin.lane = enemies[i].lane;
			coin.x = enemies[i].x;
			floorCoins.push_back(coin);

			enemies.erase(enemies.begin() + i);
		}
	}
	
	for (int i = players.size() - 1; i >= 0; i--) {
		if (players[i].health <= 0) {
			players.erase(players.begin() + i);
		}
	}
}

void PickUpCoins()   
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

void Checklw5srt()
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].x <= -0.75f) {
			lost = true;
			std::cout << "enta 5srt m3lsh" << std::endl;
		}
	}
}

void UpdateEnemies()   
{
	if (lost || won) 
		return;   // el game 5eles -> kol 7aga wa2fa

	UpdateWaves();
	ethrkwdrb();
	Enemiesbttrb();
	threkelBullets();
	sheelelDead();
	PickUpCoins();
	Checklw5srt();
}



void RasmEnemywahed(EnemyDescription enemy)
{
	float y = CenterKolLane[enemy.lane];

	glUniform1f(makanelred, (5 - enemy.health) * 0.15f);   //  kol ma ya5od damage b 0.15 el dm y2l we yeb2a ahmar aktar


	if (enemy.type == EASY)        
		Namoosa(enemy.x, y + 0.08f);   // fo2 fe lane 1
	else if (enemy.type == MEDIUM) 
		SorSar(enemy.x, y - 0.10f);    // ta7t fe lane 2
	else                       
		Cat(enemy.x, y - 0.06f); //fe lane 3

	glUniform1f(makanelred, 0.0f);                       


	float barY = CenterKolLane[enemy.lane] + 0.165f;
	float startX = enemy.x - (enemy.health - 1) * 0.009f;
	for (int i = 0; i < enemy.health; i++) {
		DrawingRectangles(startX + i * 0.018f, barY, 0.015f, 0.027f, 0.45f, 0.10f, 0.10f);
	}
}

void Rasmkolhaga()
{
	for (int i = 0; i < enemies.size(); i++) {
		RasmEnemywahed(enemies[i]);
	}

	for (int i = 0; i < bullets.size(); i++) {
		float y = CenterKolLane[bullets[i].lane];
		if (bullets[i].high) 
			DrawingCircle(bullets[i].x, y + 0.08f, 0.02f, 0.035f, 0.17f, 0.17f, 0.17f);      
		else                 
			DrawingRectangles(bullets[i].x, y - 0.13f, 0.02f, 0.035f, 0.90f, 0.80f, 0.55f);  
	}

	for (int i = 0; i < floorCoins.size(); i++) {   // ersem kol coin 3al ard
		float coinX = floorCoins[i].x;
		float coinY = CenterKolLane[floorCoins[i].lane] - 0.12f;
		DrawingCircle(coinX, coinY, 0.035f, 0.062f, 0.88f, 0.65f, 0.15f);   
	}

	
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
	makanelred = glGetUniformLocation(shaderProgram, "red");
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
	srand((unsigned)time(0)); // bet hepl rand ely fo2 t spawn random enemy fe random lanes 3ashan rand ely fo2 heya fixed fa hatnzl fel lan x msln same enemies
	glfwSetKeyCallback(window, KeyPress);
	// Yahya's ending his part


	int counter = 60;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.95f, 0.89f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram); // 3alashan ne use el program elly 3mlnah bta3 el shader el GLSL eli fo2

		// 5) ersem: esta5dem el program, el no2at, w ersem 3 no2at

		//static shapes first here is the lanes which are made of rectangles hn3ml 3 lanes 




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

		//for (int i = 0; i < players.size(); i++) {  //byresem kol player bought
			//RasmElBoughtPlayer(players[i]);
		//}

		DrawingCircle(0.80f, 0.875f, 0.05f, 0.089f, 0.88f, 0.65f, 0.15f);   // coin icon
		DrawNumber(coin, 0.86f, 0.875f, 1.0f, 0.93f, 0.45f, 0.15f);   // size 1 = normal              

		RasmetElCard();
		MovementElplayers();
		BrotherYedrab();
		MoveBrotherBullets();
		RasmBrotherBullets();
		// Yassin's Ending Part


		



		// Yahya's starting his part
		zbttjumpduckplayer();
		UpdateEnemies();
		Rasmkolhaga();
		// Yahya's ending his part














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