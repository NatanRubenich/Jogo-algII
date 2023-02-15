#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <errno.h>

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include<time.h>
#include<string.h>

// tamanho da janela
#define LARGURA 1380
#define ALTURA 720
#define tamanhox 32
#define tamanhoy 32
int inicio =0;
int vida=2;
int tempo = 60;
int currentTime=0;
int tempoAux =0;
int pontos = 0;
Mix_Music *musica;
bool iniciojogo = false;

int matriztela[22][43] = {
    {6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7},
    {5,0,0,0,3,3,3,3,0,3,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,3,3,3,0,0,3,3,3,0,3,0,3,5},
    {5,0,3,1,0,15,0,0,0,3,3,0,3,3,0,3,3,3,0,3,3,3,3,0,3,0,0,0,3,0,3,0,0,0,0,0,0,3,0,3,0,0,5},
    {5,0,3,3,3,3,3,0,3,3,3,0,0,0,0,3,3,3,0,3,0,0,3,0,3,3,0,0,3,0,3,3,3,3,0,3,0,0,0,0,0,0,5},
    {5,0,0,2,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,3,3,0,0,0,3,3,0,0,3,0,0,0,0,0,0,3,3,3,0,3,3,3,5},
    {5,0,3,3,3,3,0,3,3,3,0,0,0,3,0,0,0,0,0,0,3,0,3,0,3,3,0,0,3,3,3,0,3,3,3,3,3,3,0,0,0,3,5},
    {5,0,0,0,0,0,0,3,0,3,0,0,0,3,0,0,3,3,0,0,3,0,3,0,3,3,0,3,3,0,3,0,0,0,0,0,0,3,0,3,3,3,5},
    {5,0,3,3,0,3,0,3,0,3,0,3,0,3,3,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,0,5},
    {5,0,3,0,0,3,3,3,0,3,0,3,0,0,0,3,3,3,0,0,3,0,0,3,0,3,0,3,3,0,0,3,0,0,0,0,0,0,0,0,3,0,5},
    {5,0,3,3,0,3,0,3,0,3,0,0,0,3,0,0,0,3,0,0,3,0,0,3,0,3,0,3,0,0,0,3,3,3,3,0,0,0,3,3,3,0,5},
    {5,0,3,3,0,0,0,3,0,3,0,3,3,3,0,0,0,3,3,0,0,0,3,0,0,3,0,3,3,3,0,0,0,3,3,0,0,0,0,0,0,0,5},
    {5,0,3,0,0,3,0,3,0,3,0,3,3,3,0,0,3,3,0,3,0,0,3,3,0,3,0,3,3,3,0,3,0,3,3,0,0,3,3,0,3,3,5},
    {5,0,3,0,0,0,0,3,0,3,0,3,3,3,0,0,0,0,0,0,0,0,3,3,0,3,0,0,3,3,0,3,0,0,0,0,0,3,3,0,3,0,5},
    {5,3,3,3,3,3,3,3,0,3,0,0,0,0,0,3,3,3,0,3,0,0,0,0,3,3,0,0,3,3,0,0,0,0,0,3,0,0,3,3,3,0,5},
    {5,3,3,3,0,3,0,3,0,3,0,3,3,3,3,3,3,3,0,3,3,0,3,3,3,3,0,0,3,3,3,0,3,3,0,0,3,0,3,3,3,0,5},
    {5,3,3,0,0,0,0,3,0,3,0,3,3,0,0,0,0,3,0,3,0,0,0,0,0,3,0,0,0,0,0,0,3,3,0,0,3,3,3,0,0,0,5},
    {5,0,3,0,0,3,3,3,0,0,3,3,3,0,0,0,0,3,0,3,0,0,3,3,0,0,0,3,3,3,3,0,3,3,3,0,0,0,0,0,3,0,5},
    {5,0,3,0,0,3,3,0,0,0,0,0,0,0,3,3,0,3,0,3,0,0,3,3,3,0,0,0,0,0,0,0,3,3,3,3,3,0,3,3,0,0,5},
    {5,0,0,0,0,3,3,0,3,3,0,3,3,0,3,3,0,3,0,3,0,0,3,3,3,3,0,3,3,3,3,0,3,0,3,0,0,0,3,3,0,3,5},
    {5,0,0,3,0,0,0,0,3,0,0,0,0,0,3,3,0,3,0,0,0,0,3,3,0,0,0,3,3,0,0,0,3,0,3,3,3,3,3,0,0,3,5},
    {5,3,3,3,3,3,0,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,3,3,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,3,3,5},
    {8,20,18,4,2,21,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,19,17,9}};
int linhas = 22, colunas = 43;
int xt, yt;


SDL_Window *janelaprincipal = NULL; // Nome da janela principal do jogo.
SDL_Surface *content = NULL;        // Área de trabalho da janela.
SDL_Renderer *visualizacao;         // Área de visualização da janela.

SDL_Surface *textSurface;
SDL_Texture *text;
SDL_Rect textRect;



//controle do teclado
typedef struct Teclas{
    bool esquerda;
    bool direita;
    bool prabaixo;
    bool pracima;
    bool espaco;
};


Teclas teclas;


void inicializaTeclas(){
    teclas.esquerda = false;
    teclas.direita  = false;
    teclas.prabaixo = false;
    teclas.pracima  = false;
    teclas.espaco   = false;
}


typedef struct Objeto{

    SDL_Rect area;               // Cria um retângulo area.x, area.y, area.w (largurra), area.h (altura).
    float velocidade = 0;        // Velocidade que o objeto se move.
    SDL_Texture* textura = NULL; // Textura da imagem.
    bool emmovimento = false;    // Para/reinicia movimento.
    bool visivel = true;         // Se o objeto é visivel ou não.
    float rigido = true;         // Se o objeto pode ou não der destruído.
    int vida = 3;
    char texto[10];
};


Objeto *fundo;
Objeto *personagem;
Objeto *rocha;
Objeto *arvore;
Objeto *fruta;
Objeto *morte;
Objeto *coracao;
Objeto *ampulheta;

Objeto *paredenortesul;
Objeto *paredeesquerdadireita;
Objeto *paredenorteesquerda;
Objeto *paredenortedireita;
Objeto *paredesulesquerda;
Objeto *paredesuldireita;
Objeto *logo_stranger;
Objeto *press_espaco;
Objeto *gameover;

Objeto *esquerda;
Objeto *direita;
Objeto *norte;
Objeto *sul;
Objeto *esquerdadireita;
Objeto *nortesul;

//Objeto *texto;
Objeto *texto_vida;
Objeto *texto_timer;
Objeto *texto_score;

//diretivas do jogo
bool fim = false; // Encerra o jogo com true.



// Nome do objeto, posicao x, posição y, largula e altura.
Objeto* carregaObjeto(const char *caminho_da_imagem, int largura, int altura){

    // Criação do objeto.
    Objeto *o;
    o = (Objeto*) malloc (sizeof (Objeto));

    // Atribuição de valores às variáveis do objeto.
    o->area.x = 0;
    o->area.y = 0;
    o->area.w = largura; // Largura do objeto.
    o->area.h = altura;  // Altura da nave.


    SDL_Surface* imagem = IMG_Load(caminho_da_imagem); // lê a imagem.
    if( imagem == NULL ){
        printf( "Erro ao carregar imagem %s\n", SDL_GetError());
    } else{
        o->textura = SDL_CreateTextureFromSurface(visualizacao, imagem); // Cria a textura.
        SDL_FreeSurface(imagem); // Apaga a imagem da tela.
    }
    return o;
}

Objeto* carregaTexto(const char *caminho_da_fonte, int largura, int altura,char texto[10]){

    // Criação do objeto.
    Objeto *o;
    o = (Objeto*) malloc (sizeof (Objeto));

    // Atribuição de valores às variáveis do objeto.
    o->area.x = 0;
    o->area.y = 0;
    o->area.w = largura; // Largura do objeto.
    o->area.h = altura;  // Altura da nave.


    SDL_Surface* objetoSurface;
    SDL_Color cor = {150,0,0}; // Cor do texto;
    strcpy(o->texto, texto);
    objetoSurface = TTF_RenderText_Solid(TTF_OpenFont(caminho_da_fonte, 32), o->texto, cor);
        if (objetoSurface == NULL){
            printf("Erro ao carregar o texto! %s", SDL_GetError());
        }else {
        o->textura = SDL_CreateTextureFromSurface(visualizacao,objetoSurface);
        SDL_FreeSurface(objetoSurface);
        }
    return o;
}

void desenha(Objeto *obj){
    SDL_RenderCopy(visualizacao,obj->textura,NULL, &obj->area);
}

void close(){

    SDL_FreeSurface(content);
    SDL_DestroyWindow(janelaprincipal);
    SDL_DestroyRenderer(visualizacao);
    IMG_Quit();
    delete(content);
    delete(rocha);
    delete(arvore);
    delete(fundo);
    delete(fruta);
    delete(morte);
    delete(coracao);
    delete(ampulheta);

    delete(paredenortesul);
    delete(paredeesquerdadireita);
    delete(paredenorteesquerda);
    delete(paredenortedireita);
    delete(paredesulesquerda);
    delete(paredesuldireita);
    delete(logo_stranger);
    delete(press_espaco);
    delete(gameover);

    delete(esquerda);
    delete(direita);
    delete(norte);
    delete(sul);
    delete(esquerdadireita);
    delete(nortesul);

    Mix_FreeMusic(musica);
    Mix_CloseAudio();

    SDL_Quit();
}

char *my_itoa(int n, char *str, size_t str_size, unsigned short base){
	static const char symbols[36]={
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
		'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	unsigned abs_n;
	unsigned quot, rem;
	char rev_str[CHAR_BIT*sizeof(int)];
	int rev_str_len=0;

	if(base<2 || base>sizeof symbols){  // Base inválida?
		errno=EINVAL;
		return NULL;
	}

	if(str_size<2){  // String de saída pequena demais?
		errno=ERANGE;
		return NULL;
	}

	if(n<0){  // Trata número negativo
		abs_n=(unsigned)-n;
		*str++='-';
		str_size--;
	}
	else
		abs_n=n;

	do {
		quot=abs_n/base;
		rem=abs_n-quot*base;
		rev_str[rev_str_len++]=symbols[rem];  // Seleciona o algarismo correspondente ao resto.
		if(rev_str_len>str_size-1){  // String de saída pequena demais?
			errno=ERANGE;
			return NULL;
		}
		abs_n=quot;
	} while(quot>0);

	do
		*str++=rev_str[--rev_str_len];  // Copia dígitos da string reversa para a ordem natural na saída.
	while(rev_str_len>0);

	*str='\0';  // Coloca o byte nulo terminador da string de saída.

	return str;
}

void display(){

    SDL_RenderClear(visualizacao);
    desenha(fundo);
    desenha(arvore);
    desenha(rocha);
    desenha(personagem);
    desenha(fruta);
    desenha(coracao);
    desenha(ampulheta);

    desenha(paredenortesul);
    desenha(paredeesquerdadireita);
    desenha(paredenorteesquerda);
    desenha(paredenortedireita);
    desenha(paredesulesquerda);
    desenha(paredesuldireita);
    desenha(logo_stranger);
    desenha(press_espaco);
    desenha(gameover);

    desenha(esquerda);
    desenha(direita);
    desenha(norte);
    desenha(sul);
    desenha(esquerdadireita);
    desenha(nortesul);


    SDL_RenderPresent(visualizacao);
}

void posiciona(Objeto *obj, int x, int y){

    obj->area.x=x;
    obj->area.y=y;
}

void posiciona_fruta(Objeto *obj, int x, int y){

    obj->area.x=(rand() % 43);
    obj->area.y=(rand() % 22);
}

void displaytela_fruta(){
   srand(time(NULL)); // Puxar do relogio
        do{
            xt = (rand() % 43);
            yt = (rand() % 22);
            if(matriztela[yt][xt]==0){ // Fruta.
                 posiciona(fruta, xt*tamanhox, yt*tamanhoy);
            }
        }while((matriztela[yt][xt])!=0);
        printf("xt: %d  yt: %d", xt,yt);
        matriztela[yt][xt] = 2;
}

bool colisao(){
    int linhaA = ceil(personagem->area.y / tamanhoy);
    int colunaA = ceil(personagem->area.x / tamanhox);
    int linhaB = ceil((personagem->area.y+personagem->area.h-2) / tamanhoy);
    int colunaB = ceil((personagem->area.x) / tamanhox);
    int linhaC = ceil((personagem->area.y) / tamanhoy);
    int colunaC = ceil((personagem->area.x + personagem->area.w-2) / tamanhox);
    int linhaD = ceil((personagem->area.y+personagem->area.h-2) / tamanhoy);
    int colunaD = ceil((personagem->area.x + personagem->area.w-2) / tamanhox);

    printf("\n x:%d y:%d, A l:%d c:%d, B l:%d c:%d, C l:%d c:%d, D l:%d c:%d",
            personagem->area.x, personagem->area.y,linhaA, colunaA, linhaB, colunaB, linhaC, colunaC, linhaD, colunaD);
     if(matriztela[linhaA][colunaA] == 3 ||
        matriztela[linhaB][colunaB] == 3 ||
        matriztela[linhaC][colunaC] == 3 ||
        matriztela[linhaD][colunaD] == 3 )
        return true;
     if(matriztela[linhaA][colunaA] == 4 ||
        matriztela[linhaB][colunaB] == 4 ||
        matriztela[linhaC][colunaC] == 4 ||
        matriztela[linhaD][colunaD] == 4 )
        return true;
     if(matriztela[linhaA][colunaA] == 5 ||
        matriztela[linhaB][colunaB] == 5 ||
        matriztela[linhaC][colunaC] == 5 ||
        matriztela[linhaD][colunaD] == 5 )
        return true;
     if(matriztela[linhaA][colunaA] == 6 ||
        matriztela[linhaB][colunaB] == 6 ||
        matriztela[linhaC][colunaC] == 6 ||
        matriztela[linhaD][colunaD] == 6 )
        return true;
     if(matriztela[linhaA][colunaA] == 7 ||
        matriztela[linhaB][colunaB] == 7 ||
        matriztela[linhaC][colunaC] == 7 ||
        matriztela[linhaD][colunaD] == 7 )
        return true;
     if(matriztela[linhaA][colunaA] == 8 ||
        matriztela[linhaB][colunaB] == 8 ||
        matriztela[linhaC][colunaC] == 8 ||
        matriztela[linhaD][colunaD] == 8 )
        return true;
     if(matriztela[linhaA][colunaA] == 9 ||
        matriztela[linhaB][colunaB] == 9 ||
        matriztela[linhaC][colunaC] == 9 ||
        matriztela[linhaD][colunaD] == 9 )
        return true;
     if(matriztela[linhaA][colunaA] == 10 ||
        matriztela[linhaB][colunaB] == 10 ||
        matriztela[linhaC][colunaC] == 10 ||
        matriztela[linhaD][colunaD] == 10 )
        return true;
     if(matriztela[linhaA][colunaA] == 11 ||
        matriztela[linhaB][colunaB] == 11 ||
        matriztela[linhaC][colunaC] == 11 ||
        matriztela[linhaD][colunaD] == 11 )
        return true;
     if(matriztela[linhaA][colunaA] == 12 ||
        matriztela[linhaB][colunaB] == 12 ||
        matriztela[linhaC][colunaC] == 12 ||
        matriztela[linhaD][colunaD] == 12 )
        return true;
     if(matriztela[linhaA][colunaA] == 12 ||
        matriztela[linhaB][colunaB] == 13 ||
        matriztela[linhaC][colunaC] == 13 ||
        matriztela[linhaD][colunaD] == 13 )
        return true;
     if(matriztela[linhaA][colunaA] == 14 ||
        matriztela[linhaB][colunaB] == 14 ||
        matriztela[linhaC][colunaC] == 14 ||
        matriztela[linhaD][colunaD] == 14 )
        return true;
        if(matriztela[linhaA][colunaA] == 19 ||
        matriztela[linhaB][colunaB] == 19 ||
        matriztela[linhaC][colunaC] == 19 ||
        matriztela[linhaD][colunaD] == 19 )
        return true;
     if(matriztela[linhaA][colunaA] == 15 ||
        matriztela[linhaB][colunaB] == 15 ||
        matriztela[linhaC][colunaC] == 15 ||
        matriztela[linhaD][colunaD] == 15 ){ // demogorgon
        //vida -= 1;
        printf("colidiu");
            if (matriztela[linhaA][colunaA] == 15){
                    matriztela[linhaA][colunaA] = 16;
                    posiciona(fruta, linhaA*tamanhox, colunaA*tamanhoy);
                    desenha(fruta);}
            if (matriztela[linhaB][colunaB] == 15){
                    matriztela[linhaB][colunaB] = 16;
                    posiciona(fruta, linhaB*tamanhox, colunaB*tamanhoy);
                    desenha(fruta);}
            if (matriztela[linhaC][colunaC] == 15){
                    matriztela[linhaC][colunaC] = 16;
                    posiciona(fruta, linhaC*tamanhox, colunaC*tamanhoy);
                    desenha(fruta);}
            else if (matriztela[linhaD][colunaD] == 15){
                    matriztela[linhaD][colunaD] = 16;
                    posiciona(fruta, linhaD*tamanhox, colunaD*tamanhoy);
                    desenha(fruta);}
        return true;
        }
        if(matriztela[linhaA][colunaA] == 20 ||
        matriztela[linhaB][colunaB] == 20 ||
        matriztela[linhaC][colunaC] == 20 ||
        matriztela[linhaD][colunaD] == 20 )
        return true;
     if(matriztela[linhaA][colunaA] == 2 ||
        matriztela[linhaB][colunaB] == 2 ||
        matriztela[linhaC][colunaC] == 2 ||
        matriztela[linhaD][colunaD] == 2) {
                    inicio = currentTime;
        printf ("  Colidiu !!!!!!!! Erro %s",SDL_GetError());
            if (matriztela[linhaA][colunaA] == 2)
                    matriztela[linhaA][colunaA] = 0;
            if (matriztela[linhaB][colunaB] == 2)
                    matriztela[linhaB][colunaB] = 0;
            if (matriztela[linhaC][colunaC] == 2)
                    matriztela[linhaC][colunaC] = 0;
            else if (matriztela[linhaD][colunaD] == 2)
                    matriztela[linhaD][colunaD] = 0;
            displaytela_fruta();
            pontos += 1;
    }
    return false;
}

void movimenta(Objeto *obj){

    if(teclas.direita) {
        obj->area.x+=obj->velocidade;
        if(colisao()){
            obj->area.x-=obj->velocidade;
        }

    }
    if(teclas.esquerda){
        obj->area.x-=obj->velocidade;
        if(colisao()){
            obj->area.x+=obj->velocidade;
        }
    }
    if(teclas.prabaixo){
        obj->area.y+=obj->velocidade;
        if(colisao()){
            obj->area.y-=obj->velocidade;
        }
    }
    if(teclas.pracima) {
        obj->area.y-=obj->velocidade;;;;;
        if(colisao()){
            obj->area.y+=obj->velocidade;
        }
    }
}

void velocidade(Objeto *obj, float v){

    obj->velocidade=v;
}

void atualizaTexto_score(){       // Vida
    if(my_itoa(pontos,texto_score->texto,sizeof texto_score->texto,10) != NULL) {
        SDL_Surface* objSurface;
        SDL_Color cor = {150,0,0};
        objSurface = TTF_RenderText_Solid(TTF_OpenFont("fontes\\Calculator.ttf",36),texto_score->texto,cor);
        //criar a textura atraves do content e o obj surface
        texto_score->textura = SDL_CreateTextureFromSurface(visualizacao, objSurface);
        SDL_FreeSurface(objSurface);
    }else{
        printf("\nErro ao converter texto Score!!!");
    }
}

void atualizaTexto_vida(){       // Vida
    if(my_itoa(vida,texto_vida->texto,sizeof texto_vida->texto,10) != NULL) {
        SDL_Surface* objSurface;
        SDL_Color cor = {150,0,0};
        objSurface = TTF_RenderText_Solid(TTF_OpenFont("fontes\\Calculator.ttf",36),texto_vida->texto,cor);
        //criar a textura atraves do content e o obj surface
        texto_vida->textura = SDL_CreateTextureFromSurface(visualizacao, objSurface);
        SDL_FreeSurface(objSurface);
    }else{
        printf("\nErro ao converter texto vida!!!");
    }
}

void atualizaTexto(int milissegundos){       // temporizador
    int segundos = milissegundos / 1000;

    char textoAux[10];
    if(my_itoa(segundos,textoAux,sizeof textoAux,10) != NULL) {
        strcpy(texto_timer->texto,textoAux);
    }else {
        printf("\nErro ao converter texto (atualizaTextoTime).");
    }
    SDL_Surface* objSurface;
    SDL_Color cor = {150,0,0};
    objSurface = TTF_RenderText_Solid(TTF_OpenFont("fontes\\Calculator.ttf",36),texto_timer->texto,cor);
    //criar a textura atraves do content e o obj surface
    texto_timer->textura = SDL_CreateTextureFromSurface(visualizacao, objSurface);
    SDL_FreeSurface(objSurface);
}

void verifica(){
        int segundos=0;
        currentTime = SDL_GetTicks();
        segundos = (currentTime - inicio) / 1000;
        if(segundos > 18){
            inicio = currentTime;
            vida -= 1;
           // _sleep(1100);
            matriztela[1][1] = 1;
            personagem->area.x=32;
            personagem->area.y=32;
        return;
    }
}

bool init(){

    bool success = true;
if( TTF_Init() < 0 )
    {
        printf( "Erro ao carregar a SDL: %s\n", SDL_GetError() );
        success = false;
    }

    // Inicializa a SDL

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Erro ao carregar a SDL: %s\n", SDL_GetError() );
        success = false;
    }
    else{

        // Cria a janela principal
        janelaprincipal = SDL_CreateWindow( " Stranger Things! ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   LARGURA, ALTURA, SDL_WINDOW_SHOWN );
        if( janelaprincipal == NULL ){

            printf( "Erro na criação da janela: %s\n", SDL_GetError() );
            success = false;
        } else{
            visualizacao = SDL_CreateRenderer(janelaprincipal, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
        // Carrega os objetos de cena.
        fundo      = carregaObjeto("imagens\\fundo.jpg",LARGURA,ALTURA);
        personagem = carregaObjeto("imagens\\esquimo.png",32, 32);
        rocha      = carregaObjeto("imagens\\rochaquadrada3.png",32, 32);
        arvore     = carregaObjeto("imagens\\arvore.png",32, 32);
        fruta      = carregaObjeto("imagens\\waffles.png",32,32);
        morte      = carregaObjeto("imagens\\morte_demo.png",32,32);
        coracao      = carregaObjeto("imagens\\coracao.png",32,32);
        ampulheta      = carregaObjeto("imagens\\ampulheta.png",32,32);

        paredenortesul        = carregaObjeto("imagens\\paredenortesul.png",32,32);
        paredeesquerdadireita = carregaObjeto("imagens\\paredeesquerdadireita.png",32,32);
        paredenorteesquerda   = carregaObjeto("imagens\\paredenorteesquerda.png",32,32);
        paredenortedireita    = carregaObjeto("imagens\\paredenortedireita.png",32,32);
        paredesulesquerda     = carregaObjeto("imagens\\paredesulesquerda.png",32,32);
        paredesuldireita      = carregaObjeto("imagens\\paredesuldireita.png",32,32);
        logo_stranger         = carregaObjeto("imagens\\stranger_things.png",576,278);
        press_espaco          = carregaObjeto("imagens\\pressione_espaco.png",520,120);
        gameover              = carregaObjeto("imagens\\gameover.jpg",720,520);

        esquerda        = carregaObjeto("imagens\\esquerda.png",32,32);
        direita         = carregaObjeto("imagens\\direita.png",32,32);
        norte           = carregaObjeto("imagens\\norte.png",32,32);
        sul             = carregaObjeto("imagens\\sul.png",32,32);
        esquerdadireita = carregaObjeto("imagens\\esquerdadireita.png",32,32);
        nortesul        = carregaObjeto("imagens\\demogorgon.png",32,32);

        texto_timer           = carregaTexto("fontes\\Calculator.ttf",35,35," ");
        texto_vida            = carregaTexto("fontes\\Calculator.ttf",35,35," ");
        texto_score           = carregaTexto("fontes\\Calculator.ttf",35,35," ");
        // posiciona os objetos de cena
        // posiciona(personagem, 10, ALTURA-personagem->area.h-5);
        // posiciona(rocha, 350, 250);
        // posiciona(arvore, 300, 150);
        // define a velocidade de movimentação dos objetos
        velocidade(personagem, 2);
    }
    return success;
}

void displaytela(){

    SDL_RenderClear(visualizacao);
    //desenha(fundo);

    for(yt=0; yt<linhas; yt++){
        for(xt=0; xt<colunas; xt++){

            if(matriztela[yt][xt]==1){ // Personagem.
                if(iniciojogo==false){
                    posiciona(personagem, xt*tamanhox, yt*tamanhoy);
                    desenha(personagem);
                }
            }
            if(matriztela[yt][xt]==3){ // Rígido.
                posiciona(rocha, xt*tamanhox, yt*tamanhoy);
                desenha(rocha);
            }

            if(matriztela[yt][xt]   ==4){
                posiciona(paredenortesul, xt*tamanhox, yt*tamanhoy);
                desenha(paredenortesul);
            }
            if(matriztela[yt][xt]==5){
                posiciona(paredeesquerdadireita, xt*tamanhox, yt*tamanhoy);
                desenha(paredeesquerdadireita);
            }
            if(matriztela[yt][xt]==6){
                posiciona(paredenorteesquerda, xt*tamanhox, yt*tamanhoy);
                desenha(paredenorteesquerda);
            }
            if(matriztela[yt][xt]==7){
                posiciona(paredenortedireita, xt*tamanhox, yt*tamanhoy);
                desenha(paredenortedireita);
            }
            if(matriztela[yt][xt]==8){
                posiciona(paredesulesquerda, xt*tamanhox, yt*tamanhoy);
                desenha(paredesulesquerda);
            }
            if(matriztela[yt][xt]==9){
                posiciona(paredesuldireita, xt*tamanhox, yt*tamanhoy);
                desenha(paredesuldireita);
            }
            if(matriztela[yt][xt]==10){
                posiciona(esquerda, xt*tamanhox, yt*tamanhoy);
                desenha(esquerda);
            }
            if(matriztela[yt][xt]==11){
                posiciona(direita, xt*tamanhox, yt*tamanhoy);
                desenha(direita);
            }
            if(matriztela[yt][xt]==12){
                posiciona(norte, xt*tamanhox, yt*tamanhoy);
                desenha(norte);
            }
            if(matriztela[yt][xt]==13){
                posiciona(sul, xt*tamanhox, yt*tamanhoy);
                desenha(sul);
            }
            if(matriztela[yt][xt]==14){
                posiciona(esquerdadireita, xt*tamanhox, yt*tamanhoy);
                desenha(esquerdadireita);
            }
            if(matriztela[yt][xt]==15){ //demogorgon
                posiciona(nortesul, xt*tamanhox, yt*tamanhoy);
                desenha(nortesul);
            }
            if(matriztela[yt][xt]==16){ //morte_demogorgon
                posiciona(morte, xt*tamanhox, yt*tamanhoy);
                desenha(morte);
            }
            if(matriztela[yt][xt]==17){ //Texto
                posiciona(texto_timer, xt*tamanhox, yt*tamanhoy);
                desenha(texto_timer);
            }
            if(matriztela[yt][xt]==18){ //Texto_vida
                posiciona(texto_vida, xt*tamanhox, yt*tamanhoy);
                desenha(texto_vida);
            }
            if(matriztela[yt][xt]==19){ //ampulheta
                posiciona(ampulheta, xt*tamanhox, yt*tamanhoy);
                desenha(ampulheta);
            }
            if(matriztela[yt][xt]==20){ //coração
                posiciona(coracao, xt*tamanhox, yt*tamanhoy);
                desenha(coracao);
            }
            if(matriztela[yt][xt]==21){ //texto_score
                posiciona(texto_score, xt*tamanhox, yt*tamanhoy);
                desenha(texto_score);
            }
            else if(matriztela[yt][xt]==2){
                posiciona(fruta, xt*tamanhox, yt*tamanhoy);
                desenha(fruta);
            }

        }
    }
    desenha(personagem);
    SDL_RenderPresent(visualizacao);
}

int cont = 0;

void fimJogo(){
    SDL_RenderClear(visualizacao);
    texto_vida= carregaTexto("fontes\\Calculator.ttf",180,90,"Seu Score");
    posiciona(texto_vida,(LARGURA/2)-200,(ALTURA/2)+80);
    posiciona(gameover,320,10);
    posiciona(texto_score,(LARGURA/2)-10,(ALTURA/2)+123);
    desenha(gameover);
    desenha(texto_score);
    desenha(texto_vida);
    SDL_RenderPresent(visualizacao);
    Sleep(5000);
    close();
    exit(0);
}

void tela_inicio(){
    char caminho[150];
    teclas.espaco = false;
    inicializaTeclas();
    SDL_Event evento;
    int verif = 0;
    do{
    for(int i=0; i<44; i++){
        SDL_RenderClear(visualizacao);
        if(i==0){
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-0.png",LARGURA,ALTURA);
            press_espaco = carregaObjeto("imagens\\pressione_espaco.png",520,120);}
        else if(i==1)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-1.png",LARGURA,ALTURA);
        else if(i==2)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-2.png",LARGURA,ALTURA);
        else if(i==3)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-3.png",LARGURA,ALTURA);
        else if(i==4)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-4.png",LARGURA,ALTURA);
        else if(i==5)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-5.png",LARGURA,ALTURA);
        else if(i==6)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-6.png",LARGURA,ALTURA);
        else if(i==7)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-7.png",LARGURA,ALTURA);
        else if(i==8)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-8.png",LARGURA,ALTURA);
        else if(i==9)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-9.png",LARGURA,ALTURA);
        else if(i==10)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-10.png",LARGURA,ALTURA);
        else if(i==11){
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-11.png",LARGURA,ALTURA);
            press_espaco = carregaObjeto("imagens\\nada.png",520,120);}
        else if(i==12)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-12.png",LARGURA,ALTURA);
        else if(i==13)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-13.png",LARGURA,ALTURA);
        else if(i==14)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-14.png",LARGURA,ALTURA);
        else if(i==15)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-15.png",LARGURA,ALTURA);
        else if(i==16)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-16.png",LARGURA,ALTURA);
        else if(i==17)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-17.png",LARGURA,ALTURA);
        else if(i==18)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-18.png",LARGURA,ALTURA);
        else if(i==19)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-19.png",LARGURA,ALTURA);
        else if(i==20)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-20.png",LARGURA,ALTURA);
        else if(i==21)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-21.png",LARGURA,ALTURA);
        else if(i==22){
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-22.png",LARGURA,ALTURA);
            press_espaco = carregaObjeto("imagens\\pressione_espaco.png",520,120);}
        else if(i==23)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-23.png",LARGURA,ALTURA);
        else if(i==24)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-24.png",LARGURA,ALTURA);
        else if(i==25)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-25.png",LARGURA,ALTURA);
        else if(i==26)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-26.png",LARGURA,ALTURA);
        else if(i==27)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-27.png",LARGURA,ALTURA);
        else if(i==28)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-28.png",LARGURA,ALTURA);
        else if(i==29)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-29.png",LARGURA,ALTURA);
        else if(i==30)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-30.png",LARGURA,ALTURA);
        else if(i==31)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-31.png",LARGURA,ALTURA);
        else if(i==32)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-32.png",LARGURA,ALTURA);
        else if(i==33){
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-33.png",LARGURA,ALTURA);
            press_espaco = carregaObjeto("imagens\\nada.png",520,120);}
        else if(i==34)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-34.png",LARGURA,ALTURA);
        else if(i==35)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-35.png",LARGURA,ALTURA);
        else if(i==36)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-36.png",LARGURA,ALTURA);
        else if(i==37)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-37.png",LARGURA,ALTURA);
        else if(i==38)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-38.png",LARGURA,ALTURA);
        else if(i==39)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-39.png",LARGURA,ALTURA);
        else if(i==40)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-40.png",LARGURA,ALTURA);
        else if(i==41)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-41.png",LARGURA,ALTURA);
        else if(i==42)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-42.png",LARGURA,ALTURA);
        else if(i==43)
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-43.png",LARGURA,ALTURA);
        else if(i==44){
            fundo = carregaObjeto("imagens\\telainicio\\tumblr_obsz6kZi6j1ucbcfgo1_500-44.png",LARGURA,ALTURA);
            i=0;
        }

        while(SDL_PollEvent(&evento)){
                switch(evento.type){
                    case SDL_QUIT :
                        fim = true;
                        break;
                    case SDL_KEYDOWN: // tecla pressionada
                        if (evento.key.keysym.sym == SDLK_SPACE){
                            teclas.espaco = true;
                            verif = 1;
                            i =44;
                            printf("true\n %d",verif);
                        }
                        if (evento.key.keysym.sym == SDLK_ESCAPE)
                            fim = true;
                            verif = 1;
                            i =44;
                            printf("true\n \n%d", verif);
                        break;
            }
            }
        posiciona(logo_stranger,400,10);
        posiciona(press_espaco,457,300);
        desenha(fundo);
        desenha(logo_stranger);
        desenha(press_espaco);
        SDL_RenderPresent(visualizacao);
        Sleep(50);
    }
    }while(verif != 1);
}


int main( int argc, char* args[] ){

int frequencia = 22050;
Uint16 formato = AUDIO_S16SYS;
int canais = 2;
int buffer = 4096;

Mix_OpenAudio(frequencia, formato, canais, buffer);
musica = Mix_LoadMUS("tema.mp3");
Mix_PlayMusic(musica, -1);

for(yt=0; yt<linhas; yt++){
    for( xt=0; xt<colunas; xt++)
        printf("%d ", matriztela[yt][xt]);
    printf("\n");
}

    inicializaTeclas();
    //Eventos
    SDL_Event evento;

    //Inicializa a SDL
    if( !init() )
    {
        printf( "Falha na inicialização!\n" );
    }
    else
    {
        tela_inicio();
        while(!fim){
            while( SDL_PollEvent( &evento ))
            {
                switch(evento.type){
                    case SDL_QUIT :
                        fim = true;
                        break;

                    case SDL_KEYDOWN: // tecla pressionada

                        if(evento.key.keysym.sym == SDLK_LEFT)
                            teclas.esquerda = true;
                        if (evento.key.keysym.sym == SDLK_RIGHT)
                            teclas.direita = true;
                        if(evento.key.keysym.sym == SDLK_DOWN)
                            teclas.prabaixo = true;
                        if (evento.key.keysym.sym == SDLK_UP)
                            teclas.pracima = true;
                        if (evento.key.keysym.sym == SDLK_SPACE){
                            iniciojogo = true;
                            teclas.espaco = true;
                        }
                        if (evento.key.keysym.sym == SDLK_ESCAPE)
                            fim = true;
                        break;

                    case SDL_KEYUP: // Tecla solta.
                        if(evento.key.keysym.sym == SDLK_LEFT)
                            teclas.esquerda = false;
                        if (evento.key.keysym.sym == SDLK_RIGHT)
                            teclas.direita = false;
                        if(evento.key.keysym.sym == SDLK_DOWN)
                            teclas.prabaixo = false;
                        if (evento.key.keysym.sym == SDLK_UP)
                            teclas.pracima = false;
                        if (evento.key.keysym.sym == SDLK_SPACE)
                            teclas.espaco = false;
                        break;
                }
            }

            if(iniciojogo){
                if(cont == 0){
                    inicio = SDL_GetTicks();
                    cont++;
                }
                movimenta(personagem);
                //printf("\nPersonagem x:%d y:%d",personagem->area.x,personagem->area.y);
                //display();
                atualizaTexto(currentTime - inicio);
               // printf("currentTime: %d\n",currentTime);
                atualizaTexto_vida();
                atualizaTexto_score();
                verifica();
                if(vida <= 0){
                    fimJogo();
                }
            }
            displaytela();
        }
    }

    close();
    return 0;
}
