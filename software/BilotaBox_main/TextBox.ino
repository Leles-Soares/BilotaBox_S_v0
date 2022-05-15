/*
 * 
 */

void textbox(char *text, int linha, E_Alinhamento alinhamento, int tam, E_Colors cor, bool autoOfset, bool lineOn)
{
  tft.setRotation(2);
  //tft.drawRoundRect(posx, posy, 100, 100, 5, cor);
  char str[50];
  memset(str, 0, sizeof(str));
  int h, w, i, final_;
  tamanho_letra(&h, &w, tam);
  int lenText = strlen(text);
  int maxPLinha = (128 / w);
  int linhas = (lenText / maxPLinha) + 1;;
  int linha_inicio = linha;

  if (autoOfset)
    linha_inicio = linha - (linhas - 1);

  int l1 = (linha_inicio*h) - 3;
  int l2 = l1 + ((linhas)*h) + 3;
  tft.fillRect(0, l1, 128, (linhas*h) +3 , BL);
  
  if (lineOn)
  {
    tft.drawLine(0, l1, 128, l1, cor);
    tft.drawLine(0, l2, 128, l2, cor);    
  }
  
  for (i = 0; i < linhas; i++)
  {
    final_ = MIN_N(maxPLinha, lenText -(maxPLinha*i));
    strncpy(str, text + (maxPLinha*i), final_);
    alinharMensagem(cor, tam, str, alinhamento, (linha_inicio + i));
    memset(str, 0, sizeof(str));
  }
  










  /*
  
  sprintf(str, "%s = %d", "lenText", lenText);
  alinharMensagem(cor, tam, str, E, 2);
  Serial.print("lenText = ");Serial.println(lenText);
  delay(2000);

  sprintf(str, "%s = %d", "maxPLinha", maxPLinha);
  alinharMensagem(cor, tam, str, E, 3);
  Serial.print("maxPLinha = ");Serial.println(maxPLinha);
  delay(2000);
  
  sprintf(str, "%s = %d", "linhas", linhas);
  alinharMensagem(cor, tam, str, E, 4);
  Serial.print("linhas = ");Serial.println(linhas);
  delay(2000);

  */
  //tam 3 altura 24
  //tam 3 comprimento 18
  
  //tam 2 altura 18
  //tam 2 comprimento 12

  //tam 1 altura 11
  //tam 1 comprimento 6
  //max por linha = (128 / comprimento) 
  //linha = (len / max_por_lina) + 1;
  //if()
  //alinharMensagem(E_Colors cor, int tam, char *msg, E_Alinhamento alinhamento, int line)
}
