#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int ROWS = 16, COLS = 8, CELL_SIZE = 8, SW_PIN = 13;
int board[ROWS][COLS] = {0}, score = 0, gameState = 0; 

int shapes[7][4][4] = {
  {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}, {{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
  {{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}}, {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
  {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}, {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
  {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}}
};

struct Piece { int x, y; int shape[4][4]; };
Piece currentPiece;
unsigned long lastFallTime = 0;
int fallSpeed = 500;

bool isValid(int newX, int newY, int shape[4][4]) {
  for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(shape[i][j]) {
    int bX = newX + j, bY = newY + i;
    if(bX < 0 || bX >= COLS || bY >= ROWS || (bY >= 0 && board[bY][bX])) return false;
  }
  return true;
}

void rotatePiece() {
  int temp[4][4];
  for(int i=0; i<4; i++) for(int j=0; j<4; j++) temp[j][3-i] = currentPiece.shape[i][j];
  if(isValid(currentPiece.x, currentPiece.y, temp)) {
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) currentPiece.shape[i][j] = temp[i][j];
  }
}

void clearLines() {
  for(int i = ROWS - 1; i >= 0; i--) {
    bool full = true;
    for(int j = 0; j < COLS; j++) if(!board[i][j]) full = false;
    if(full) {
      score++;
      for(int k = i; k > 0; k--) for(int j = 0; j < COLS; j++) board[k][j] = board[k-1][j];
      for(int j = 0; j < COLS; j++) board[0][j] = 0;
      i++;
    }
  }
}

void spawnNewPiece() {
  currentPiece.x = 2; currentPiece.y = 0;
  int type = random(7);
  for(int i=0; i<4; i++) for(int j=0; j<4; j++) currentPiece.shape[i][j] = shapes[type][i][j];
  if(!isValid(currentPiece.x, currentPiece.y, currentPiece.shape)) gameState = 1; 
}

void setup() {
  pinMode(SW_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(1);
  randomSeed(analogRead(34));
  spawnNewPiece();
}

void loop() {
  if (gameState == 0) {
    int xVal = analogRead(34);
    if (xVal > 3500 && isValid(currentPiece.x + 1, currentPiece.y, currentPiece.shape)) { currentPiece.x++; delay(150); }
    if (xVal < 500 && isValid(currentPiece.x - 1, currentPiece.y, currentPiece.shape)) { currentPiece.x--; delay(150); }
    if (digitalRead(SW_PIN) == LOW) { rotatePiece(); delay(200); }

    if (millis() - lastFallTime > fallSpeed) {
      if (isValid(currentPiece.x, currentPiece.y + 1, currentPiece.shape)) currentPiece.y++;
      else {
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(currentPiece.shape[i][j]) board[currentPiece.y+i][currentPiece.x+j] = 1;
        clearLines();
        spawnNewPiece();
      }
      lastFallTime = millis();
    }
  }

  display.clearDisplay();
  if (gameState == 0) {
    display.setTextSize(1); display.setTextColor(WHITE);
    display.setCursor(70, 0); display.print("S:"); display.print(score);
    for(int i=0; i<ROWS; i++) for(int j=0; j<COLS; j++) if(board[i][j]) display.drawRect(j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(currentPiece.shape[i][j]) display.fillRect((currentPiece.x+j)*CELL_SIZE, (currentPiece.y+i)*CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
  } else {
    display.setTextSize(2); display.setCursor(10, 40); display.print("GAME OVER");
  }
  display.display();
}