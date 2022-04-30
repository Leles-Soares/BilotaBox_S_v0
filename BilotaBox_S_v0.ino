#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <string.h>

// These pins will also work for the 1.8" TFT shield

//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0  
#define TFT_MISO 0 
#define TFT_LED 33 

//controle

#define K_ENTER 26 //Enter do joystik
#define K_Y     35 //Y do joystik -> analogico
#define K_X     32 //X do joystik -> analogico
int range_alfa  = 27;


#define MAX_ANALOG 4095
#define MIN_ANALOG 0

#define MIN_N(a,b) (a < b ? a : b)
typedef enum
{
  R  = ST77XX_RED,
  G  = ST77XX_GREEN, 
  BU = ST77XX_BLUE, 
  Y  = ST77XX_YELLOW, 
  W  = ST77XX_WHITE, 
  BL = ST77XX_BLACK, 
}E_Colors;

typedef enum
{
  E,
  C, 
  D,
}E_Alinhamento;
/*
typedef struct
{
  int h;
  int w;
}S_letra;

S_letra myletra;*/
//esp32 LoRa
/*
#define TFT_DC 17 //A0
#define TFT_CS 21 //CS
#define TFT_MOSI 2 //SDA
#define TFT_CLK 23 //SCK
#define TFT_RST 0  
#define TFT_MISO 0 
*/

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

float p = 3.1415926;

boolean alinharMensagem(E_Colors cor, int tam, char *msg, E_Alinhamento alinhamento, int line);
void menu(char *msg);
void controle(int x, int y, boolean squad);
void sorteio(void);

void jogo(int qtAcerto, int minino, int maximo, char *msg);
void colocaZero(char *msg, int numero);
void apostaMega();




int posicao_alfabeto = 0;
int cursor_alfa(int y, int Delay);
char escrita(int pos_alfa);
char escrita_rederizada(int line, int c_size, E_Alinhamento alinhamento, bool show_text);

void jogo_da_forca();

void limpaTela()
{
  tft.fillScreen(ST77XX_BLACK);
  delay(200);
}

void textbox(char *text, int linha, E_Alinhamento alinhamento, int tam, E_Colors cor, bool autoOfset, bool lineOn);
char escrita_rederizada2(int line, int c_size, E_Alinhamento alinhamento, bool show_text, int conjunto);

void setup() 
{
  Serial.begin(9600);
  Serial.print("Hello! ST77xx TFT Test");
  pinMode(TFT_LED, OUTPUT);
  pinMode(K_ENTER, INPUT_PULLUP);
  digitalWrite(TFT_LED, 1);

  //ledcSetup(0, 5000, 8);
  //ledcAttachPin(TFT_LED, 0);
  
  //pinMode(TFT_LED, OUTPUT);
  //digitalWrite(TFT_LED,1);
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(2);
  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 0.96" 180x60 TFT
  //tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  // Use this initializer (uncomment) if you're using a 1.54" 240x240 TFT
  //tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels



  //menu("- Menu -");

 tft.fillScreen(ST77XX_BLACK);
 randomSeed(analogRead(32));
  
}

char str[22];
char str2[10];
void loop() {



  escrita_rederizada2(5, 2, C, true, 1);
  limpaTela();

  escrita_rederizada2(5, 2, C, true, 2);
  limpaTela();

  escrita_rederizada2(5, 2, C, true, 3);
  limpaTela();
  
  textbox("lalala babybabydo biruleibe do birujuice alo marciano", 1, C, 1, W, false, true);
  esperaBotao();
  textbox("lalala babybabydo biruleibe do birujuice alo marciano", 1, C, 1, BL, false, true);
  



//------------------------------------------------------- jogo da forca - [início]
  tft.setRotation(2);
  jogo_da_forca();
  tft.fillScreen(ST77XX_BLACK);
//------------------------------------------------------- jogo da forca - [fim]


//------------------------------------------------------- escrita - [início]
  Serial.println(escrita_rederizada(7, 2, C, false));
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(escrita_rederizada(8, 2, C, true));
  tft.fillScreen(ST77XX_BLACK);
//------------------------------------------------------- escrita - [fim]


//------------------------------------------------------- mouse - [início]
  tft.setRotation(2);
  do
  {tft.setRotation(2);
    controle(map(analogRead(K_X), 0, 4095, 128, 0), map(analogRead(K_Y), 4095, 0, 0, 160), digitalRead(K_ENTER));
  }
  while(digitalRead(K_ENTER));
  delay(1000);
//------------------------------------------------------- mouse - [fim]


//------------------------------------------------------- megasena - [início]
  //sorteio();
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
  apostaMega();
  delay(2000);
  esperaBotao();
  tft.fillScreen(ST77XX_BLACK);
//------------------------------------------------------- megasena - [fim]

}


boolean alinharMensagem(E_Colors cor, int tam, char *msg, E_Alinhamento alinhamento, int line)
{
  //tam 3 altura 24
  //tam 3 comprimento 18
  
  //tam 2 altura 18
  //tam 2 comprimento 12

  //tam 1 altura 11
  //tam 1 comprimento 6
  int sizeLine = 10;
  int sizeColun = 10;
  int alinhar  = 0;

  
  tamanho_letra(&sizeLine, &sizeColun, tam);
  
    switch(alinhamento)
  {
    case E:  
      break;
    case C:
    alinhar = (128 - (strlen(msg)*sizeColun))/2;
      break;
    case D:
    alinhar = (128 - (strlen(msg)*sizeColun));
      break;
    default:break;
  }

  
  
  tft.setTextWrap(false);
  //tft.fillScreen(BL);
  tft.setCursor(alinhar, sizeLine *line);
  tft.setTextColor(cor);
  tft.setTextSize(tam);
  tft.println(msg);
}

void controle(int x, int y, boolean squad)
{
  int color, radomic;
  Serial.print("( ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println(")");

  radomic = random(0, 255);
  if(radomic < 50)
    color = W;
  else if(radomic >= 50 && radomic < 100 )
    color = BU;
  else if(radomic >= 100 && radomic < 150 )
    color = Y;
  else if(radomic >= 150 && radomic < 200 )
    color = G;
  else if(radomic >= 200 && radomic < 255 )
    color = R;


  
  //tft.drawPixel(x, y, color);


  tft.fillRect(x-5, y-5 , 10, 10, Y);
  
  delay(10);
  if(squad == 1)
    tft.fillRect(x-5, y-5 , 10, 10, BL);
}

void menu(char *msg)
{ 
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRoundRect(0, 30, 128, 115, 5, W);
  alinharMensagem(W, 2, msg, C, 0);
  for(int x = 0; x<6; x++)
  {

    alinharMensagem(W, 2, "XXXXXXXXX", C, 2);
    alinharMensagem(W, 2, "XXXXXXXXX", C, 3);
    alinharMensagem(W, 2, "XXXXXXXXX", C, 4);
    alinharMensagem(W, 2, "XXXXXXXXX", C, 5);
    alinharMensagem(W, 2, "XXXXXXXXX", C, 6);
    alinharMensagem(W, 2, "XXXXXXXXX", C, 7);

    tft.fillRect(5, (x*18)+(34) , 118, 18, W);
    alinharMensagem(BL, 2, "XXXXXXXXX", C, x+2);
    delay(1000);
    tft.fillRect(5, (x*18)+(34) , 118, 18, BL);
  }
}

void tamanho_letra(int* sizeLine, int* sizeColun, int tam)
{
  switch(tam)
  {
    case 1:
    *sizeLine = 11;
    *sizeColun = 6;
      break;
    case 2:
    *sizeLine = 18;
    *sizeColun = 12;
      break;
    case 3:
    *sizeLine = 25;
    *sizeColun = 18;
      break;
    default:break;
  }
}

void esperaBotao()
{
  do{} while((digitalRead(K_ENTER)));
}
