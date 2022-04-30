int palavraSecreta(char *str)
{
  int id = random(0,30);

  char palavras[40][20]
  {
    "Amarelo", 
    "Amiga", 
    "Amor",
    "Ave",
    "Branco", 
    "Cama",
    "Caneca",
    "Celular",
    "Clube",
    "Copo", 
    "Doce",
    "Elefante",
    "Escola",
    "Estojo",
    "Faca",
    "Foto",
    "Garfo",
    "Geleia",
    "Girafa",
    "Janela",
    "Limonada",
    "Meia",
    "Noite",
    "Odeovo",
    "Pai",
    "Parque",
    "Passarinho",
    "Peixe",
    "Pijama",
    "Rato",
    "Umbigo",
  };

  //Serial.println("Palavra sorteada");
  //Serial.println(palavras[id]);
  //Serial.println(palavras[id]);
  sprintf(str, palavras[id]);

  return id;
}

void dicas(char *str, int id)
{
  char _dicas[40][30]
  {
    "cor", 
    "pessoa do peito", 
    "sentimento",
    "aminal",
    "cor", 
    "quarto",
    "recipiente",
    "muito caro",
    "gente paia",
    "recipiente", 
    "diabetes",
    "animal",
    "bom, mas ruim tbm",
    "recipiente",
    "cozinha",
    "nude",
    "cozinha",
    "comida",
    "animal",
    "buraco",
    "comida",
    "pano",
    "dark",
    "duvido",
    "caraio de familia",
    "lugar com gente correndo",
    "dinossauro",
    "jamais devia criar pernas",
    "pano",
    "isturti liru",
    "tapar com esparadrapo kkkkk",
  };

  sprintf(str, _dicas[id]);
}
void mostraPalavra(char *strSecreta, char *str2Chutes, char *strFormatada)
{
  int i = 0;
  int j = 0;
  char strOculta[20] = {0};
  if (strlen(str2Chutes)  == 0)
  {
    memset(strOculta, '_', strlen(strSecreta));
    //Serial.print("limpou");Serial.println(j);
  }
  /*else
  {
    for (i = 0; i < strlen(str1); i++)
    {
      if ( tolower(str1[i]) == tolower(str2[j]))
        strOculta[i] = str1[i];
      else
        strOculta[i] = '_';
    }
  }*/
  else
  {
    for (i = 0; i < strlen(strSecreta); i++)
    {
      
      for (j = 0; j < strlen(str2Chutes); j++) 
      {
        //Serial.print("I ");Serial.print(i); Serial.print(" J ");Serial.println(j);
        //Serial.print("comparando ");Serial.print(tolower(strSecreta[i]));
        //Serial.print(" com ");Serial.println(tolower(str2Chutes[j]));
        if ( tolower(strSecreta[i]) == tolower(str2Chutes[j]))
        {
          //Serial.println("é igual");
          strOculta[i] = strSecreta[i];
          break;
        }
        else
        {
          //Serial.println("diferente");
          strOculta[i] = '_';
        }
        //Serial.print("strOculta = "); Serial.println(strOculta);
      }
    //Serial.println("_________________________\n");
    }
  }

  //Serial.println("Palavra formatada");
  //Serial.println(strOculta);
  sprintf(strFormatada, strOculta);
}

bool verificaLetra(char letra, char *string)
{
  int j = 0;
  int count = 0;
  bool result = false;
  
  for (j = 0; j < strlen(string); j++) 
  {
    if ( tolower(letra) == tolower(string[j]))
    {
     count++;
    }
  }
  if (count) result = true;

  return result;
}

void jogo_da_forca()
{
  char secreto[20] = {0};
  char _dicas[30] = {0};
  char chutes[20] = {0};
  char strGame[20] = {0};
  char corretos[20] = {0};
  int erros = 0;
  bool acertou = false;
  
  dicas(_dicas,palavraSecreta(secreto));
  mostraPalavra(secreto, chutes, strGame);
  
  char str00[10] = {"|------"};
  char str01[10] = {"|/"};
  char str02[10] = {"|"};
  char str03[10] = {"|"};
  char str04[10] = {"|"};
  char str05[10] = {"|"};

  /*
  char str00[10] = {"|------"};
  char str01[10] = {"|/    O"};
  char str02[10] = {"|   \\_|_/"};
  char str03[10] = {"|     | "};
  char str04[10] = {"|    / \\"};
  char str05[10] = {"|"};
    */
  alinharMensagem(W, 2, str00, E, 0);
  alinharMensagem(W, 2, str01, E, 1);
  alinharMensagem(W, 2, str02, E, 2);
  alinharMensagem(W, 2, str03, E, 3);
  alinharMensagem(W, 2, str04, E, 4);
  alinharMensagem(W, 2, str05, E, 5);
  alinharMensagem(W, 2, strGame, C, 7);

  textbox(_dicas, 10, C, 1, G, true, true);
  int tentativas = 0;
  
  //while()
  
  
  //delay(5000);
  do
  {
    chutes[tentativas] = escrita_rederizada(8, 2, C, false);
    alinharMensagem(BL, 2, strGame, C, 7);
    mostraPalavra(secreto, chutes, strGame);
    alinharMensagem(W, 2, strGame, C, 7);
    
    if (!(verificaLetra(chutes[tentativas], secreto)))
    {
      erros++;
      switch(erros)
      {
        case 1:
          alinharMensagem(BL, 2,"|/    O", E, 1);
          alinharMensagem(W, 2, "|/    O", E, 1);      
        break;
        case 2:
          alinharMensagem(BL, 2,"|     |  ", E, 2);
          alinharMensagem(W, 2, "|     |  ", E, 2);      
          alinharMensagem(BL, 2,"|     |  ", E, 3);
          alinharMensagem(W, 2, "|     |  ", E, 3);      
        break;
        case 3:
          alinharMensagem(BL, 2,"|   \\_|", E, 2);
          alinharMensagem(W, 2, "|   \\_|", E, 2);        
        break;
        case 4:
          alinharMensagem(BL, 2,"|   \\_|_/", E, 2);
          alinharMensagem(W, 2, "|   \\_|_/", E, 2);        
        break;//char str04[10] = {"|    / \\"};
        case 5:
          alinharMensagem(BL, 2,"|    / ", E, 4);
          alinharMensagem(W, 2, "|    /", E, 4);        
        break;
        case 6:
          alinharMensagem(BL, 2,"|    / \\", E, 4);
          alinharMensagem(W, 2, "|    / \\", E, 4);        
        break;
      }
    }

    tentativas++;

    acertou = strcmp(strGame, secreto) ? false : true;

    delay(200);
  }
  while(erros < 6 && !acertou);

  
  delay(100);
  if(acertou)
  {
    tft.setRotation(2);    
    textbox("Parabens", 4, C, 2, G, false, false);
    textbox("     ,", 3, C, 2, G, false, false);
    delay(500);

  }

  else
  {
    tft.setRotation(2);
    textbox("Perdeu", 4, C, 2, Y, false, false);
  }
  delay(5000);
 
}





/*
|------
|/    O
|   
|   
|   
|

|------
|/    O
|  
|   
|   
|

|------
|/    O
|   |
|     |
|     
|

|------
|/    O
|  .|
|   ´ |
|    
|


|------
|/    O
|   |.
|     | ` 
|    
|

|------
|/    O
|  .|.
|   ´ | ` 
|    
|


|------
|/    O
|  .|.
|   ´ | ` 
|    / 
|

|------
|/    O
|    .|.
|   ´ | ` 
|    / \
|

*/
