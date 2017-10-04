/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground      
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * (3) 2K resistor:
 * ends to (2)+5V and (1)ground
 * other end to LCD VOO pin (pin 3)

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

boolean isBottom = true;
char topLine[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char bottomLine[16] =  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
int score = 0;

void setup() {
  pinMode(13,INPUT);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0);
  lcd.print("Star Cruiser");
  lcd.setCursor(0,1);
  lcd.print("By Joey");
  delay(1500);
}

void loop() {
  lcd.clear();
  readAndPrintPlayer();
  nextLine();
  printTopandBottomLines();
  endOfGame();
  score++;
  delay(500);
}

// runs end of game script
void endOfGame(void){
  if(endGame() == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You Lost");
    lcd.setCursor(0,1);
    lcd.print("Score: ");
    lcd.print(score);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Click to play");
    lcd.setCursor(0,1);
    lcd.print("again");
    score = 0;
    clearLines();
    while(digitalRead(13) == true);
  }
}

// Sets the top and bottom lines to all spaces
void clearLines(void){
  for(int i = 0; i < 16; i ++){
    bottomLine[i] = ' ';
    topLine[i] = ' ';
  }
}

// moves the start over and generates another
void nextLine(void){
   for(int i = 0; i < 15; i++){
      topLine[i] = topLine[i+1];
   }
   for(int i = 0; i < 15; i++){
      bottomLine[i] = bottomLine[i+1];
   }
   if(random(0,10)>6){
      topLine[15] = '*';
   }
   else{
      topLine[15] = ' ';
   }
   if(topLine[15] == '*'){
      bottomLine[15] = ' ';
   }
   else if(random(0,10) > 5){
      bottomLine[15] = '*';
   }
   else{
      bottomLine[15] = ' ';
   }
}

// checks to see if the the player chashed into a star
boolean endGame(void){
  if((isBottom == true && bottomLine[0] == '*') || (isBottom == false && topLine[0] == '*')){
     return true;
  }
  else{
     return false;
  }
}

//Prints the stars 
void printTopandBottomLines(void){
  lcd.setCursor(1,1);//colum 1 row 1
  for(int i = 1; i < 16; i++){
    lcd.print(bottomLine[i]);
  }
  lcd.setCursor(1,0); // colum 1 row 0
  for(int i = 1; i < 16; i++){
    lcd.print(topLine[i]);
  }
}

// Read the input and prints the player
void readAndPrintPlayer(void){
  if(analogRead(0)<200){
    isBottom = true;
  }
  else if(analogRead(0)>600){
    isBottom = false;
  }
  if(isBottom == true){
    lcd.setCursor(0,1);
    lcd.print('@');
  }
  else{
    lcd.setCursor(0,0);
    lcd.print('@');
  }
}

