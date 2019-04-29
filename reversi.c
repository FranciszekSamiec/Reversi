#include <stdio.h>

char charTab[8]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

enum Ruch{
    PRAWIDLOWY=1,
    POWTORZ=2
};

//gobalna zmienna przechowuje informacje o jakości ruchu
enum Ruch czyPrawidlowy;

enum StanGry{
    KONIEC_GRY=1,
    KONTYNUUJ=2
};

//globalna zmienna przechowująca informację o zakońzceniu programu (dla EOF)
enum StanGry stan=KONTYNUUJ;

enum  Kierunek{
    NORTH=1,
    EAST=2,
    SOUTH=3,
    WEST=4,
    NORTH_EAST=5,
    SOUTH_EAST=6,
    SOUTH_WEST=7,
    NORTH_WEST=8
};

enum Gracz{
    UZYTKOWNIK=1,
    KOMPUTER=2
};

void inicjalizuj_tablice(char tab[][8]){
    for(int w=0; w<8; w++){
        for(int k=0; k<8; k++){
            tab[w][k]='-';
            tab[3][3]='B';
            tab[3][4]='C';
            tab[4][3]='C';
            tab[4][4]='B';
        }
    }
}

void wyswietl_tablice(char tab[][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printf("%c", tab[i][j]);
        }
        printf("%d\n", i+1);
    }
    for(char q='a'; q<'i'; q++){
        printf("%c", q);
    }
    printf("\n");
}

void przypisz_tablice(char tab1[][8], char tab2[][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            tab1[i][j]=tab2[i][j];
        }
    }
}

void modyfikuj(int* x, int* y, enum Kierunek direction, int* range, int incr){
    if(incr==1)
        *range=*range+1;
    else if(incr==0)
        *range=*range-1;
  
    switch(direction){
        case NORTH :
            (*y)--;
            break;
        case EAST :
            (*x)++;
            break;
        case SOUTH :
            (*y)++;
            break;
        case WEST :
            (*x)--;
            break;
        case NORTH_EAST :
            (*y)--;
            (*x)++;
            break;
        case NORTH_WEST :
            (*y)--;
            (*x)--;
            break;
        case SOUTH_WEST :
            (*y)++;
            (*x)--;
            break;
        case SOUTH_EAST :
            (*y)++;
            (*x)++;
            break;
        default:
            break;
    }
}

int roznica(char tab_wzorcowa[][8]){
    int wynik=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(tab_wzorcowa[i][j]=='C'){
                wynik++;
            }
            if(tab_wzorcowa[i][j]=='B'){
                wynik--;
            }
        }
    }
    return wynik;
}

void odwracanie(char tab[][8], int x, int y, enum Kierunek direction, int* zamiana, enum Gracz player, int* licznik){
    int startx=x; //kolumna
    int starty=y; //wiersz
    int exit=0;
    int range = 0;
    char moj_znak;
    char jego_znak;
    if(player==UZYTKOWNIK){
        moj_znak='C';
        jego_znak='B';
    }else{
        moj_znak='B';
        jego_znak='C';
    }
    while(tab[y][x]!='-' && exit==0 && x>=0 && x<8 && y>=0 && y<8){ 
        modyfikuj(&x, &y, direction, &range, 1);
        if(tab[y][x]==moj_znak){
            exit=1;
        }
    }
    if(exit==1){
        x=startx;
        y=starty;
        while(range!=0){
            modyfikuj(&x, &y, direction, &range, 0);
            if(tab[y][x]==jego_znak){
                tab[y][x]=moj_znak;
                *zamiana=1;
                (*licznik)++;
            }
        }
    }
}

void ruch_komputera(char tab[][8], char tab_wzorcowa[][8]){
    int zamiana=0;
    int max_licznik=0;
    int w_optimal;
    int k_optimal;
    int licznik;
   
    przypisz_tablice(tab, tab_wzorcowa);
    for(int w=0; w<8; w++){
        for(int k=0; k<8; k++){
            if(tab[w][k]=='-')
            {
                licznik=0;
                tab[w][k]='B';
                for(enum Kierunek it_kierunek=NORTH ;it_kierunek<=NORTH_WEST; it_kierunek++){
                    odwracanie(tab, k, w, it_kierunek, &zamiana, KOMPUTER, &licznik);
                    if(licznik>max_licznik){
                        w_optimal=w;
                        k_optimal=k;
                        max_licznik=licznik;
                    }
                }
                przypisz_tablice(tab, tab_wzorcowa);
            }
        }
    }
    if(zamiana==1){
        tab_wzorcowa[w_optimal][k_optimal]='B';
      
        for(enum Kierunek it_kierunek=NORTH ;it_kierunek<=NORTH_WEST; it_kierunek++)
            odwracanie(tab_wzorcowa, k_optimal, w_optimal, it_kierunek, &zamiana, KOMPUTER, &licznik);
       
        printf("%c%d %d\n", charTab[k_optimal], w_optimal+1, roznica(tab_wzorcowa));
        wyswietl_tablice(tab_wzorcowa);
    }else{
        printf("= %d\n", roznica(tab_wzorcowa));
        wyswietl_tablice(tab_wzorcowa);
    }
}

enum StanGry ruch_gracza(char tab[][8], char tab_wzorcowa[][8]);
  
int main(){
    char tab_wzorcowa[8][8];
    char tab[8][8];

    inicjalizuj_tablice(tab);
    wyswietl_tablice(tab);
    przypisz_tablice(tab_wzorcowa, tab);
   
    while(stan==KONTYNUUJ){

        if(ruch_gracza(tab, tab_wzorcowa)==KONIEC_GRY){//warunek zakończenia gry dla EOF
            printf("\n");
            return 0;
        }
        if(czyPrawidlowy==POWTORZ){
            printf("%d\n", roznica(tab_wzorcowa));
            wyswietl_tablice(tab_wzorcowa);
        }
        else{
            ruch_komputera(tab, tab_wzorcowa);
        }
    }
    return 0;
}

//Zwraca 0 jeśli koniec pliku (kończymy gre). W innym przypadku zwraca 1 (kontynuujemy gre).
enum StanGry ruch_gracza(char tab[][8], char tab_wzorcowa[][8]){
    int zamiana=0;
    int x;  //kolumna
    int y;  //wiersz
    int licznik=0;
    int tempx;
    int tempy;
    int error=0;

    przypisz_tablice(tab, tab_wzorcowa);
    x = getchar() - 'a';
    if(x==EOF){
        stan=KONIEC_GRY;
    }

    if(x==-36){ //warunek dla oddania ruchhu kiedy przekażemy znak '='
        error=1;
        czyPrawidlowy=PRAWIDLOWY;

        int nl = getchar(); //nl - nowa linia (równy 10 kiedy enter)
        if(nl==EOF){
            stan=KONIEC_GRY;
            error=1;
        }
        else if(nl!=10){
            czyPrawidlowy=POWTORZ;
            if(nl==EOF){
                stan=KONIEC_GRY;
            }
            while(getchar()!=10){}
        }

        if(czyPrawidlowy==PRAWIDLOWY)
            printf("= ");
        else
            printf("? ");
    }
    else{
        y = getchar() - 47;
        int nl = getchar(); //nl - nowa linia (równy 10 kiedy enter)
        if(nl==EOF){
            stan=KONIEC_GRY;
            error=1;
        }
        else if(nl!=10){
            //int r=0;
            if(nl==EOF){
                stan=KONIEC_GRY;
                error=1;
            }
            while(getchar()!=10){}
        }

        if((x<0||x>7||y<2||y>9||tab[y-2][x]!='-'||nl!=10)&&(stan==KONTYNUUJ)){
            printf("? ");
            czyPrawidlowy=POWTORZ;
            error=1;
        }
        else{
            y-=2;
            tempx=x;
            tempy=y;
        }
    }
   
    if(error==0){
        tab[y][x]='C';
        for(enum Kierunek it_kierunek=NORTH ;it_kierunek<=NORTH_WEST; it_kierunek++){
            odwracanie(tab, x, y, it_kierunek, &zamiana, UZYTKOWNIK, &licznik);
        }
          
        if(zamiana==1){
            czyPrawidlowy=PRAWIDLOWY;
            przypisz_tablice(tab_wzorcowa, tab);
            printf("%c%d ", charTab[tempx], tempy+1);
        }else{
            tab[tempy][tempx]='-'; //jezeli ruch byl nie prawidłowy to trzeba usunac znak C z tablicy 
            czyPrawidlowy=POWTORZ;

            printf("? ");
        }
    }
    return stan;
}
