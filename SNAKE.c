#include<stdio.h>
#include<stdlib.h> // Para fun��o srand() e system()
#include<windows.h> // Para fun��o SetConsoleCursorPosition()
#include<conio.h> // Para fun��o getch() e kbhit()
#include<time.h> // Para fun��o rand()

// Vari�veis Globais
int c[300][2], pontos=1, cx=2, cy=2;
int comida[2], velo=150;

// FUN��ES
void gotoxy(int x, int y){ // Fun��o 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenha(){ // Desenha a cobrinha
    int i;
    for(i=0; i<pontos; i++){
        gotoxy(c[i][0],c[i][1]);
        printf("%c",219);
    }
}

void atualiza(){ // Atualiza a posi��o da cobrinha
    int i;
    gotoxy(c[pontos][0],c[pontos][1]);
    printf(" ");
    for(i=pontos; i>=0; i--){
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}

int analiza(){ // V� se a cobrinha enconstou em seu pr�prio corpo
    int i, retorno=0;
    for(i=1; i<pontos; i++){
        if(cx==c[i][0] && cy==c[i][1]){
            retorno=1;
        }
    }
    return retorno;
}

void geraComida(){ // Gera comida em local aleat�rio
    gotoxy(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 48) +1;
    comida[1] = (rand() % 18) +1;
    gotoxy(comida[0],comida[1]);
    printf("%c",4);
}

int main(){
    int i, gameover=0;
    int tecla;

    for(i=0; i<50; i++){ // Linha superior
        gotoxy(i,0);
        printf("%c",219);
        Sleep(5); // Pausa execu��o por 5 milissegun.
    }
    
    for(i=0; i<20; i++){ // Coluna da direita
        gotoxy(50,i);
        printf("%c",219);
        Sleep(5); // Pausa execu��o por 5 milissegun.
    }
    
    for(i=50; i>=0; i--){ // Linha inferior
        gotoxy(i,20);
        printf("%c",219);
        Sleep(05); // Pausa execu��o por 5 milissegun.
    }
    
    for(i=20; i>0; i--){ //Coluna da esquerda
        gotoxy(0,i);
        printf("%c",219);
        Sleep(5); // Pausa execu��o por 5 milissegun.
    }
    
    geraComida(); // Gera a primeira comida
    desenha(); // Desenha a cobra
    tecla='d'; // A dire��o � para a direita
    
    while(gameover==0){ // Enquanto o usu�rio n�o perder
        gotoxy(52,2); 
        printf("Pontos: %d\t",pontos);
        gotoxy(52,4); 
        printf("Velocidade: %.2f caracteres\n",1000/velo);
        c[0][0]=cx;
        c[0][1]=cy;
        
        if(kbhit()) // Se alguma tecla for apertada, o valor vai para a vari�vel 'tecla'
            tecla=getch(); 

        if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // Se a cabe�a da cobra estiver na parede superior 0 jogo acaba
        }   
		                 
        if(tecla=='a' || tecla=='A' || tecla==75){
            cx--;
            if(cx==0) break; // Se a cabe�a da cobra estiver na parede da esquerda o Jogo acaba
        }
		 
        if(tecla=='s' || tecla=='S' || tecla==80){
            cy++;
            if(cy==20) break; // Se a cabe�a da cobra estiver na parede de baixo o jogo acaba
        }
        
        if(tecla=='d' || tecla=='D' || tecla==77){
            cx++;
            if(cx>=50) break; // Se a a cabe�a da cobra estiver na parede da direida o jogo acaba
        }

        if(cx==comida[0] && cy==comida[1]){ // Se a cobra comer a comida
            pontos++;
            if(velo>50) velo-=10; // Velocidade em milissegun. abaixa
            geraComida();
        }
        gameover=analiza();
        atualiza(); 
        desenha(); 
        gotoxy(50,20);
        Sleep(velo);
    }
    system("cls"); // Quando o usu�rio perder, limpa a tela e exibe uma mensagem final
    printf("Voce perdeu! Fez %d pontos.\n",pontos);
    printf("Desenvolvido por Kelvin Guimaraes. \nIdeia de Daniel Oliveira. \n");
    system("pause");
}
