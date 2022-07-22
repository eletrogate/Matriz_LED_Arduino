/***********************************
 *     Incluindo a biblioteca      *
 ***********************************/
#include <MD_MAX72xx.h>

/***********************************
 *           Definicoes            *
 ***********************************/
#define  DELAYTIME  120  //Controla a velocidade em que o texto se desloca

#define TIPO_DO_HARDWARE MD_MAX72XX::GENERIC_HW  // Modelo da matriz de LED

#define MAX_MODULOS  1   // Quantidade de matriz de LED que o seu projeto possui

#define DATA_PIN  10  // Pino do DIN
#define CS_PIN    9   // Pino do CS
#define CLK_PIN   8   // Pino do CLK


/**********************************
 *     Criando o objeto matriz    *
 **********************************/
MD_MAX72XX matriz(TIPO_DO_HARDWARE, DATA_PIN, CLK_PIN, CS_PIN, MAX_MODULOS);


/**********************************
 *             Setup              *
 **********************************/
void setup() 
{
  matriz.begin();
  matriz.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);  //Controla a intensidade dos LEDs e MAX_INTENSITY é a intensidade maxima
}


/**********************************
 *         Loop principal         *
 **********************************/
void loop() // Loop principal
{
  escrever_texto("Eletrogate   ");  //Escreve na matriz o texto passado como parâmetro, que no caso é Eletrogate
}


/**********************************
 *     Funcao escrever_texto      *
 **********************************/
void escrever_texto(const char *p)  //Função que escreve o texto
{
  byte charWidth;
  byte cBuf[8];  

  matriz.clear();  //Desliga todos os LEDs da matriz

  while (*p != '\0')
  {
    charWidth = matriz.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (byte i = 0; i <= charWidth; i++)  
    {
      matriz.transform(MD_MAX72XX::TSL);  //TSL = desloca um pixel para a esquerda
      if (i < charWidth)
        matriz.setColumn(0, cBuf[i]);
      delay(DELAYTIME);
    }
  }
}