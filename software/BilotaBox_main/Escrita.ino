

int cursor_alfa(int y, int Delay)
{
  //Serial.println(y);
  int result = 0;

  if(y <= MIN_ANALOG)
  {
    delay(100);
    result = -1;
  } 
  else if (y >= MAX_ANALOG)
  {
    delay(100);
    result = 1;
  }
    
  delay(Delay);
  return result;
}
//posicao_alfabeto = posicao_alfabeto + cursor_alfa(analogRead(K_Y));
char escrita(int pos_alfa)
{
  range_alfa = 27;
  char alfabeto[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  char letra = alfabeto[pos_alfa];
  return letra;
}

char escrita_numerica(int nemSelect)
{

  range_alfa = 11;
  char alfabeto[27] = {"0123456789"};
  char letra = alfabeto[nemSelect];
  return letra;
  /*
  range_alfa = 11;
  int numeros[11] = {"0123456789"};
  int numero = numeros[nemSelect];
  return letra;*/
}

char escrita_alfanum(int nemSelect)
{

  range_alfa = 37;
  char alfabeto[37] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
  char letra = alfabeto[nemSelect];
  return letra;
}


char escrita_rederizada2(int line, int c_size, E_Alinhamento alinhamento, bool show_text, int conjunto)
{
  char result = 0;
  char str2[10];
  memset(str, 0, sizeof(str));
  memset(str2, 0, sizeof(str2));
  //criar if
  if (1 == conjunto)
    str[0] = escrita(posicao_alfabeto);
  if (2 == conjunto)
    str[0] = escrita_numerica(posicao_alfabeto);
  if (3 == conjunto)
    str[0] = escrita_alfanum(posicao_alfabeto);
  int conta_mudancas = 0;
  int ultima_posicao = posicao_alfabeto;
  int passo;
  
  alinharMensagem(W, c_size, str, C, line);
  do
  {
    alinharMensagem(BL, c_size, "+   +", alinhamento, line);
    alinharMensagem(BL, c_size, "-   -", alinhamento, line);
    passo = cursor_alfa(analogRead(K_Y), 50);
    posicao_alfabeto = posicao_alfabeto + passo;

    
    
    if (posicao_alfabeto < 0)
      posicao_alfabeto = range_alfa-2;
    else if (posicao_alfabeto > range_alfa-2)
      posicao_alfabeto = 0;
    
    if(ultima_posicao != posicao_alfabeto)
    {
      conta_mudancas++;
      alinharMensagem(BL, c_size, str, alinhamento, line);
        //criar if
      if (1 == conjunto)
        str[0] = escrita(posicao_alfabeto);
      if (2 == conjunto)
        str[0] = escrita_numerica(posicao_alfabeto);
      if (3 == conjunto)
        str[0] = escrita_alfanum(posicao_alfabeto);
      //str[0] = escrita(posicao_alfabeto);
      
      alinharMensagem(W, c_size, str, alinhamento, line);
      delay(10);
      ultima_posicao = posicao_alfabeto;

      if(passo > 0)
      alinharMensagem(G, c_size, "+   +", alinhamento, line);
       else
      alinharMensagem(R, c_size, "-   -", alinhamento, line);      
      delay(50);
    }

    if (!digitalRead(K_ENTER))
    {
      if (show_text)
      {
        alinharMensagem(BL, c_size, str2, C, line-1); 
        if (strlen(str2) < 9)
        {
          strcat(str2, str);  
        }
        else
        {
          memset(str2, 0, sizeof(str2));
        }
          
        alinharMensagem(G, c_size, str2, C, line-1);
        delay(200);
      }
      else
      {
        if (1 == conjunto || 3 == conjunto)
        {
          str[0] = escrita(posicao_alfabeto);
          if (conta_mudancas == 0) str[0] = 'A';
        }
        else if (2 == conjunto)
        {
          str[0] = escrita_numerica(posicao_alfabeto);
          if (conta_mudancas == 0) str[0] = '0';
        }

    
         
        //if (conta_mudancas == 0) str[0] = 'A';
        result = str[0];
        break;
      }

    }
    result = str[0];
  }
  while((strlen(str2) < 9) );
  
  
  return result;
}







// ANTIGO

char escrita_rederizada(int line, int c_size, E_Alinhamento alinhamento, bool show_text)
{
  char result = 0;
  char str2[10];
  memset(str, 0, sizeof(str));
  memset(str2, 0, sizeof(str2));
  //criar if
  str[0] = escrita(posicao_alfabeto);
  int conta_mudancas = 0;
  int ultima_posicao = posicao_alfabeto;
  int passo;
  
  alinharMensagem(W, c_size, str, C, line);
  do
  {
    alinharMensagem(BL, c_size, "+   +", alinhamento, line);
    alinharMensagem(BL, c_size, "-   -", alinhamento, line);
    passo = cursor_alfa(analogRead(K_Y), 50);
    posicao_alfabeto = posicao_alfabeto + passo;

    
    
    if (posicao_alfabeto < 0)
      posicao_alfabeto = range_alfa-2;
    else if (posicao_alfabeto > range_alfa-2)
      posicao_alfabeto = 0;
    
    if(ultima_posicao != posicao_alfabeto)
    {
      conta_mudancas++;
      alinharMensagem(BL, c_size, str, alinhamento, line);
      //criar if
      str[0] = escrita(posicao_alfabeto);
      
      alinharMensagem(W, c_size, str, alinhamento, line);
      delay(10);
      ultima_posicao = posicao_alfabeto;

      if(passo > 0)
      alinharMensagem(G, c_size, "+   +", alinhamento, line);
       else
      alinharMensagem(R, c_size, "-   -", alinhamento, line);      
      delay(50);
    }

    if (!digitalRead(K_ENTER))
    {
      if (show_text)
      {
        alinharMensagem(BL, c_size, str2, C, line-1); 
        if (strlen(str2) < 9)
        {
          strcat(str2, str);  
        }
        else
        {
          memset(str2, 0, sizeof(str2));
        }
          
        alinharMensagem(G, c_size, str2, C, line-1);
        delay(200);
      }
      else
      {
        if (conta_mudancas == 0) str[0] = 'A';
        result = str[0];
        break;
      }

    }
    result = str[0];
  }
  while((strlen(str2) < 9) );
  
  
  return result;
}
