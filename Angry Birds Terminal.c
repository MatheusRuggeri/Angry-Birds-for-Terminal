/********************************************************************/
/**                                                                **/
/**                   UNIVERSITY OF SAO PAULO                      **/
/**                                                                **/
/**   Joao Matheus Rugeri Murdiga                   7573941        **/
/**   Exercicio-Programa 3 - Angry Bixos                           **/
/**   Professor: Nina S. T. Hirata                                 **/
/**   Turma: 3                                                     **/
/**                                                                **/
/********************************************************************/

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * NESSE EP3:
 * NAO DEVO USAR AS FUNCOES DA BIBLIOTECA MATH.H
 * NAO DEVO USAR VETORES OU MATRIZES
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#include <stdio.h>

/* Constantes */
#define SIM 1
#define NAO 0
#define EPS 0.0001
#define MIN_VX 0.0001
#define PI 3.1415954
#define ARQ_ENTRADA "entrada.txt"

/* Grafico */
#define ESTI "E"
#define ALVO "A"
#define CRUZ "+"
#define H "-"
#define VERT "|"
#define BIXO "o"
#define NADA " "

/* ************************************************************
   PROTOTIPOS
 * ************************************************************
*/

/* ------------------------------------------------------------
   Funcoes obrigatorias que eu preciso implementar
   e utilizar no programa
*/

float Sen (float x, float eps);
float Cos (float x, float eps);
float Converte (float x);
void  AtualizaPosicaoEVelocidade(float *y, float *vely, float dt, float g);
int   Arredonda (float x);
void  ImprimaCondicaoInicial(int nLin, int nCol, float nUni, float yE, float yA, float hA);
int ImprimaSemDep (float yE, float vMax, float yA, float hA, float dist, int nBix, int nLin, int nCol, float nUni, float g, float ori, float des);
int ImprimaDepurado (float yE, float vMax, float yA, float hA, float dist, int nBix, int nLin, int nCol, float nUni, float g, float ori, float des);



/* ------------------------------------------------------------
   INCLUA AQUI OS PROTOTIPOS DE OUTRAS FUNCOES QUE DESEJAR IMPLEMENTAR
*/



/* *********************************************************************
 *
 A funcao LeiaParametros e' dada e voce deve utiliza-la em seu trabalho.
 *
 * *********************************************************************
*/
void LeiaParametros (float *yE, float *vMax,
                     float *yA, float *hA,
                     float *dist,
		     int *nBix,
                     int *nLin, int *nCol,
                     float *nUni,
		     float *g);

/* ************************************************************
  Funcao leia parametros: le os parametros do arquivo entrada.txt
*/
void LeiaParametros (float *yE, float *vMax,
                     float *yA, float *hA,
		     float *dist,
                     int *nBix,
                     int *nLin, int *nCol,
                     float *nUni,
		     float *g)
{
  FILE *arq;
  arq = fopen(ARQ_ENTRADA, "r");
  /* Estilingue */
  fscanf(arq, "%f %f", yE, vMax);
  /* Alvo */
  fscanf(arq, "%f %f", yA, hA);
  /* dist = xA - xE */
  fscanf(arq, "%f", dist);
  /* numero de bixos */
  fscanf(arq, "%d", nBix);
  /* numero de linhas do grafico */
  fscanf(arq, "%d", nLin);
  /* numero de colunas do grafico */
  fscanf(arq, "%d", nCol);
  /* unidade utilizada pelo grafico, ou numero (real) de unidades por linha */
  fscanf(arq, "%f", nUni);
  /* aceleracao da gravidade */
  fscanf(arq, "%f", g);

  fclose(arq);
  return;
}

/* *********************************************************************
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *       Coloque as suas funcoes a seguir
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *********************************************************************
*/

/* ************************************************************
   funcao Sen
*/

float Sen (float x, float eps)
{
    float aux = 0.0;
    float numerador, seno, adicionar, testador, prod_den;
    int den;

    x = Converte (x);

    testador = 1; /*Atribui valor superior ao EPS ao testador*/
    numerador = x;
    seno = x; /*Atribui x ao seno a fim de evitar a primeira conta (x/1!), pois o resultado já seria x*/
    den = 3; /*Inicia-se com 3 como dígito do denominador, pois o valor 1 já está atribuido a variável "seno"*/
    prod_den = 6; /*Já inicia-se com fatorial de 3 no produto dos denominadores*/


    while (testador >= eps || testador <= -eps){ /*Testa se o testador tem módulo inferior ou igual ao EPS*/
        numerador =  - ((numerador * x * x));
        adicionar = (numerador / (prod_den)); /*Calcula o valor a ser adicionado ao seno anterior*/
        den = den + 2;
        prod_den = prod_den * (den)* (den - 1); /*Faz o fatorial do denominador*/
        seno = seno + adicionar;
        testador = adicionar;
    }

    aux = seno;

    return aux;
}

/* ************************************************************
   funcao Cos
*/
float Cos (float x, float eps)
{
    float aux = 0.0;
    float cosseno, adicionar, testador, numerador, prod_den;
    int den;

    x = Converte (x);

    testador = 1; /*Atribui valor superior ao EPS ao testador*/
    numerador = 1;
    cosseno = 1;
    den = 2; /*Inicia-se com 2 como dígito do denominador*/
    prod_den = 2; /*Já inicia-se com fatorial de 2 no produto dos denominadores*/


    while (testador >= eps || testador <= -eps){ /*Testa se o testador tem módulo inferior ou igual ao EPS*/
        numerador =  - ((numerador * x * x));
        adicionar = (numerador / (prod_den));
        den = den + 2;
        prod_den = prod_den * (den)* (den - 1);
        cosseno = cosseno + adicionar;
        testador = adicionar;
    }

    if (cosseno <= 0) {cosseno = -cosseno;} /*Evita com que a função retorne o valor "-0" (zero com sinal negativo), como todo o cosseno do intervalo é positivo, não há problema matemático nessa ação*/

    aux = cosseno;



    return aux;
}


/* ************************************************************
  Funcao Converte
*/
float Converte (float x)
{
  float aux = 0.0;
  aux = (PI/2) * x;
  return aux;
}

/* ************************************************************
  Funcao Atualiza posicao e velocidade
*/
void AtualizaPosicaoEVelocidade(float *y, float *vely, float dt, float g)
{

  *y = *y + (*vely * dt) + (0.5 * g * dt * dt);
  *vely = *vely + g * dt;


  if (*y <= 0) {*y = 0;}


  return;
}

/* ************************************************************
  Funcao Arredonda
*/
int Arredonda (float f) {

    int aux = 0;
	aux = f;

    while (f>=1){f--;}   /*Reduz o valor de f até deixar de ter unidades inteiras*/
    if (f>= 0.5) {aux++;} /*Se o resto for maior que 0.5 adiciona um*/

  return aux;
}

/* ************************************************************
  Funcao Imprime Condicao Inicial
*/
void ImprimaCondicaoInicial(int nLin, int nCol, float nUni, float yE, float yA, float hA)
{
  int eixoy, eixox, contar, alt, passou = 0;
  eixoy = nLin; /*eixoy é equivalente ao nLin, entretanto, ao contrário do plano cartesiano, no EP o valor vai de nLin até zero*/
  eixox = nCol; /*Equivalente ao eixoy*/
  alt = Arredonda(hA/nUni) - 1; /*Define a altura do alvo*/
  printf ("\nCondicao Inicial:\n\n");

while (nLin >= 0){


    while (eixox >= 0){

                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--;} /*Estilingue coloca-se um E*/
                else
                    if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                    else
                        if (eixox%5 == 0 && eixoy%5 == 0) {printf("+"); eixox--;} /*Valor de nLin e nCol divisível por 5 é equivalente a um +*/
                        if (eixox%5 != 0 && eixoy%5 == 0 && eixox >= 0) {printf("-"); eixox--;}
        }

    nLin--; /*Altera localmente o nLin pois já foi impresso uma linha.*/
    printf ("\n");
    eixoy = nLin; /*Volta com as condições iniciais.*/
    eixox = nCol;


    for (contar = 4; contar > 0; contar--){
            while (eixoy >= 0 && eixox >= 0){
              passou = 1;
                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--;} /*Estilingue coloca-se um E*/
                else
                    if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                    else
                        if (eixoy%5 != 0 && eixox%5 != 0) {printf(" ");eixox--;}
                        else
                            if (eixoy%5 != 0 && eixox%5 == 0) {printf("|");eixox--;}

                    }
                    if (passou == 1){
                    printf ("\n");
                    nLin--;
                    eixoy = nLin;
                    eixox = nCol;
                    passou = 0;}
                }


} /*Finaliza quando nLin for menor que zero, ou seja, todas as linhas foram impressas.*/

  return;
}

/* ************************************************************
   MINHAS FUNCOES
   Escreva a seguir outras funcoes que desejar
*/
int ImprimaSemDep (float yE, float vMax, float yA, float hA, float dist, int nBix, int nLin, int nCol, float nUni, float g, float ori, float des)
{
  float pontYE = yE, pontVELY= 0, VelX = 0;
  float Tempo = 0, dt = 0;
  int eixoy, eixox, contar, alt, passou = 0, contagem = 1, ganhou = 0, altualvo;

  eixoy = nLin; /*eixoy é equivalente ao nLin, entretanto, ao contrário do plano cartesiano, no EP o valor vai de nLin até zero*/
  eixox = nCol; /*Equivalente ao eixoy*/
  alt = Arredonda(hA/nUni) - 1; /*Define a altura do alvo*/
  altualvo = hA - nUni; /*Para testar a vitória, pega-se a altura do alvo e subtrai o quando vale um deles (a base)*/

  VelX = vMax * des * Cos (ori, EPS);
        if (VelX <= MIN_VX) {VelX = MIN_VX;}
  Tempo = dist / VelX;
  dt = Tempo/nCol;

AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g); /*Calcula a primeira posição*/


  printf("\nGrafico do lancamento com deslocamento/orientacao = [ %.4f, %.4f]\n", des, ori);

while (nLin >= 0){

    while (eixox >= 0){

        pontYE = yE; pontVELY= 0; /*Define a variavel pontYE como inicialmente o ponto yE*/
        pontVELY = vMax * des * Sen (ori, EPS); /*Calcula a velocidade inicial no eixo Y*/
        contagem = 0; /*Auxiliar para impressão do gráfico*/

                while (contagem <= nCol){
                    if(Arredonda(pontYE/nUni) == eixoy && eixox == nCol - contagem && contagem <= nCol && eixox != nCol) /*Verifica se algum ponto da equação deve ser impresso no gráfico*/
                    {
                        printf("o");
                         if(((pontYE) >= (yA)  && eixox == 0) && ((pontYE) <= (yA + hA) && eixox == 0)){ganhou = 1;} /*Verifica se o alvo foi acertado*/
                        eixox--;
                        }
                      AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g);
                      contagem++;

                    }

                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--;} /*Estilingue coloca-se um E*/
                else
                        if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                        else
                            if (eixox%5 == 0 && eixoy%5 == 0) {printf("+"); eixox--;} /*Valor de nLin e nCol divisível por 5 é equivalente a um +*/
                            else
                                if (eixox%5 != 0 && eixoy%5 == 0 && eixox >= 0) {printf("-"); eixox--;}
        }


    nLin--; /*Altera localmente o nLin pois já foi impresso uma linha.*/
    printf ("\n");
    eixoy = nLin; /*Volta com as condições iniciais.*/
    eixox = nCol;


    for (contar = 4; contar > 0; contar--){
            while (eixoy >= 0 && eixox >= 0){

        VelX = vMax * des * Cos (ori, EPS);
            if (VelX <= MIN_VX) {VelX = MIN_VX;}
        Tempo = dist / VelX;
        dt = Tempo/nCol;


        pontYE = yE;
        pontVELY = vMax * des * Sen (ori, EPS);
            contagem = 0;

              passou = 1;

                while (contagem <= nCol){
                    if(Arredonda(pontYE/nUni) == eixoy && eixox == nCol - contagem && contagem <= nCol && eixox != nCol)
                    {
                        printf("o");
                        if(((pontYE) >= (yA)  && eixox == 0) && ((pontYE) <= (yA + hA) && eixox == 0)){ganhou = 1;} /*Verifica se o alvo foi acertado*/
                        eixox--;
                    }
                        AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g);
                      contagem++;

                    }

                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--;} /*Estilingue coloca-se um E*/
                else
                    if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                    else
                        if (eixoy%5 != 0 && eixox%5 != 0) {printf(" ");eixox--;}
                        else
                            if (eixoy%5 != 0 && eixox%5 == 0) {printf("|");eixox--;}

                    }
                    if (passou == 1){
                    printf ("\n");
                    nLin--;
                    eixoy = nLin;
                    eixox = nCol;
                    passou = 0;}
                }


} /*Finaliza quando nLin for menor que zero, ou seja, todas as linhas foram impressas.*/

return ganhou;
}


int ImprimaDepurado (float yE, float vMax, float yA, float hA, float dist, int nBix, int nLin, int nCol, float nUni, float g, float ori, float des)
{
  float pontYE = yE, pontVELY= 0, VelX = 0;
  float Tempo = 0, dt = 0, y1 = -1, y2 = -1;
  int eixoy, eixox, contar, alt, passou = 0, contagem = 1, ganhou = 0, altualvo, cortou = 0;

  eixoy = nLin; /*eixoy é equivalente ao nLin, entretanto, ao contrário do plano cartesiano, no EP o valor vai de nLin até zero*/
  eixox = nCol; /*Equivalente ao eixoy*/
  alt = Arredonda(hA/nUni) - 1; /*Define a altura do alvo*/
  altualvo = hA - nUni; /*Para testar a vitória, pega-se a altura do alvo e subtrai o quando vale um deles (a base)*/

  VelX = vMax * des * Cos (ori, EPS);
        if (VelX <= MIN_VX) {VelX = MIN_VX;}
  Tempo = dist / VelX;
  dt = Tempo/nCol;

AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g); /*Calcula a primeira posição*/


        printf ("\nGrafico do lancamento com deslocamento/orientacao = [ %.4f, %.4f]\n", des, ori);
        printf ("\nCondicoes iniciais desse lancamento:");
        printf ("\nAng (rad)   = %9.4f", Converte(ori) );
        printf ("\tCos  = %9.4f", Cos (ori, EPS));
        printf ("\t\tSin  = %9.4f\n", Sen (ori, EPS));
        printf ("Velocidade  = %9.4f", vMax * des);
        printf ("\tVelX = %9.4f", vMax * des * Cos (ori, EPS));
        printf ("\t\tVelY = %9.4f\n", vMax * des * Sen (ori, EPS));
        printf ("Tempo Total = %9.4f", dist / VelX);
        printf ("\tIncremento Temporal = %9.4f  entre colunas\n", dt);




  while (eixox >= 0){printf(" "); eixox--;}
  printf ("     lin  nInters\ty1\ty2\n");

  eixox = nCol;

while (nLin >= 0){

        cortou = 0; /*Verifica quantas vezes bixo cortou a linha*/
        y1 = -1; y2 = -1;

    while (eixox >= 0){

        pontYE = yE; pontVELY= 0; /*Define a variavel pontYE como inicialmente o ponto yE*/
        pontVELY = vMax * des * Sen (ori, EPS); /*Calcula a velocidade inicial no eixo Y*/
        contagem = 0; /*Auxiliar para impressão do gráfico*/

                while (contagem <= nCol){
                    if(Arredonda(pontYE/nUni) == eixoy && eixox == nCol - contagem && contagem <= nCol && eixox != nCol) /*Verifica se algum ponto da equação deve ser impresso no gráfico*/
                    {
                        printf("o");  cortou++;
                        if (y1 == -1 && Arredonda(yE/nUni) != eixoy) {y1 = pontYE;}
                            else
                                if (y2 == -1)   {y2 = pontYE;}
                        if(((pontYE) >= (yA)  && eixox == 0) && ((pontYE) <= (yA + hA) && eixox == 0)){ganhou = 1;} /*Verifica se o alvo foi acertado*/
                        eixox--;
                        }
                        AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g);
                      contagem++;
                    }

                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--; y1 =yE; cortou++;/*Segundo o exemplo, no lançamento E conta como se o bixo estivesse passado por aqui*/} /*Estilingue coloca-se um E*/
                else
                        if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                        else
                            if (eixox%5 == 0 && eixoy%5 == 0) {printf("+"); eixox--;} /*Valor de nLin e nCol divisível por 5 é equivalente a um +*/
                            else
                                if (eixox%5 != 0 && eixoy%5 == 0 && eixox >= 0) {printf("-"); eixox--;}

        }
        printf ("     %2d     %2d\t%9.4f%9.4f", nLin, cortou, y1, y2);

        nLin--; /*Altera localmente o nLin pois já foi impresso uma linha.*/
        printf ("\n");
        eixoy = nLin; /*Volta com as condições iniciais.*/
        eixox = nCol;


    for (contar = 4; contar > 0; contar--){

        cortou = 0;
        y1 = -1; y2 = -1;

      while (eixoy >= 0 && eixox >= 0){

        VelX = vMax * des * Cos (ori, EPS);
            if (VelX <= MIN_VX) {VelX = MIN_VX;}
        Tempo = dist / VelX;
        dt = Tempo/nCol;


        pontYE = yE;
        pontVELY = vMax * des * Sen (ori, EPS);
            contagem = 0;
            passou = 1;

                while (contagem <= nCol){
                    if(Arredonda(pontYE/nUni) == eixoy && eixox == nCol - contagem && contagem <= nCol && eixox != nCol)
                    {
                        printf("o"); cortou++;

                        if (y1 == -1 && Arredonda(yE/nUni) != eixoy) {y1 = pontYE;}
                            else
                                if (y2 == -1)   {y2 = pontYE;}

                         if(((pontYE) >= (yA)  && eixox == 0) && ((pontYE) <= (yA + hA) && eixox == 0)){ganhou = 1;} /*Verifica se o alvo foi acertado*/
                    eixox--;
                    }
                        AtualizaPosicaoEVelocidade(&pontYE, &pontVELY, dt, g);
                      contagem++;
                    }

                if (Arredonda(yE/nUni) == eixoy && eixox == nCol){printf("E"); eixox--; y1 = yE; cortou++;} /*Estilingue coloca-se um E*/
                else
                    if ((Arredonda(yA/nUni) + alt >= eixoy && Arredonda(yA/nUni) <= eixoy) && eixox ==0){printf("A"); eixox--;} /*Se for o Alvo, ou faz parte dele, A*/
                    else
                        if (eixoy%5 != 0 && eixox%5 != 0 && eixox != -1 /*o -1 evita erros de impressão caso o último valor impresso na linha seja um bixo*/) {printf(" ");eixox--;}
                        else
                            if (eixoy%5 != 0 && eixox%5 == 0) {printf("|");eixox--;}

                    }
                            if (nLin > 0) {printf ("     %2d     %2d\t%9.4f%9.4f", nLin, cortou, y1, y2);
}

                    if (passou == 1){
                    printf ("\n");
                    nLin--;
                    eixoy = nLin;
                    eixox = nCol;
                    passou = 0;}
                }

} /*Finaliza quando nLin for menor que zero, ou seja, todas as linhas foram impressas.*/


return ganhou;
}


/*
\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\

    P R O G R A M A    P R I N C I P A L

/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
 */

int main ()
{
  int modoDepuracao;

  float yE, vMax;
  float yA, hA;
  float dist;
  int nBix, nLin, nCol;
  float nUni, g;
  float ori, des;

  int NumeroBixos = 1, Acabou = 0;

  float pontYE = yE, pontVELY= 0, VelX = 0;
  float Tempo = 0, dt = 0;


  printf ("Voce deseja ligar o modo de depuracao?\n");
  printf ("Digite 1 (sim) ou 0 (nao): ");
  scanf("%d", &modoDepuracao);

  LeiaParametros( &yE, &vMax,
		  &yA, &hA,
		  &dist,
		  &nBix,
		  &nLin, &nCol,
		  &nUni,
		  &g );




  if (modoDepuracao == SIM) {
    printf ("\n\nModo de depuracao ligado!\n");
    printf ("Dados de entrada:\n");
    printf ("yE   = %9.4f  vMax = %9.4f \n", yE, vMax);
    printf ("yA   = %9.4f  hA   = %9.4f\n",  yA, hA);
    printf ("dist = %9.4f\n",  dist);
    printf ("nBix = %4d\n", nBix);
    printf ("nLin = %4d       nCol = %4d\n", nLin, nCol);
    printf ("nUni = %9.4f\n", nUni);
    printf ("g    = %9.4f\n", g);
    printf ("\n");
  }

  printf ("\nPara fazer um lancamento, digite um deslocamento (no intervalo [0,1])\n");
  printf ("e uma orientacao (no intervalo [-1, 1])\n");


  /* imprima grafico inicial */
  ImprimaCondicaoInicial(nLin, nCol, nUni, yE, yA, hA);
  /* Coloque o seu programa para jogar Angry Bixos a seguir...  */




while (Acabou == NAO){
    if (NumeroBixos < nBix + 1){
      printf ("\n====> Faca o lancamento %d / %d :\n", NumeroBixos, nBix);
        scanf("%f", &des);
        scanf("%f", &ori);

      VelX = vMax * des * Cos (ori, EPS);
            if (VelX <= MIN_VX) {VelX = MIN_VX;}
      Tempo = dist / VelX;
      dt = Tempo/nCol;
      pontYE = yE;
      pontVELY = 0;
      pontVELY = vMax * des * Sen (ori, EPS);


if (modoDepuracao == SIM) {

        if (ImprimaDepurado (yE, vMax, yA, hA, dist, nBix, nLin, nCol, nUni, g, ori, des) == 1) {printf("Voce ganhou!\nParabens, voce acertou um bixo em um veterano.\n"); Acabou = SIM;}
        else {printf("Infelizmente o veterano nao foi acertado nessa rodada.\n\n");}
        NumeroBixos++;
}


else{
        if (ImprimaSemDep (yE, vMax, yA, hA, dist, nBix, nLin, nCol, nUni, g, ori, des) == 1) {printf("Voce ganhou!\nParabens, voce acertou um bixo em um veterano.\n"); Acabou = SIM;}
        else {printf("Infelizmente o veterano nao foi acertado nessa rodada.\n\n");}
        NumeroBixos++;

}


    }

    else {Acabou = SIM; printf("\nO jogo acabou, voce nao conseguiu acertar o veterano.\n\n");}
}
  return 0;
}
