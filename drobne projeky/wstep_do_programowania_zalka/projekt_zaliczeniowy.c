#include <stdio.h>
#include <stdlib.h>

int ilosc_linii_pliku(char *);                          //tutaj liczymy ilosc linii w pliku czyli ilosc naszych danych pomiarowych
int ilosc_znakow_pliku_zamiana_przec_kropka(char *);    //to nam zlicza znaki w pliku i zamienia przecinki na kropki
double **sczytanie_wartosci(char *);                    //tablica danych wyglada tak ze x sa w 1 kolumnie a y w 2
void calkowanie(double** ,char *);                      //liczy pole pod wykresem
void rozniczkowanie(double** ,char *);                  //liczy roznice sasiednich y w punkcie
double **edycja_danych(double** ,char *);               //mozemy zmieniac poszczegolne punkty naszych danych pomiarowych i na nowo zapisac dane do pliku
double **nowe_wartosci(int);                            //podajemy wlasny zbior danych i tworzymy z niego wykres
double **realokowanie_zmniejszanie(double** ,char* ,int);   //zmniejszenie ilosci wczytanych czy juz edytowanych danych
double **realokowanie_powiekszanie(double** ,char* ,int);   //zwiekszenie ilosci danych i przypisanie nowym danym wartosci
double wykres(double** ,int , char *);                      //wyswietlenie wykresu z wczytanych czy edytowanych danych

int main(){
	char nazwa_pliku[20];
	char opcja_real;
	double **dane_pomiarowe;
	double **nowe_dane_pomiarowe;
	int ilosc_punktow,ilosc_nowych_punktow,ilosc_realokowanych_punktow;
	int i,opcja,a=0;

	printf("Witamy w programie.\nMenu programu:\n");
	printf("1. Wczytanie danych z pliku do programu.\n");
	printf("2. Calkowanie numeryczne danych pomiarowych.\n");
	printf("3. Rozniczkowanie numeryczne danych pomiarowych.\n");
	printf("4. Edycja danych pomiarowych i ich zapis do pliku z wybraniem separatora.\n");
	printf("5. Realokacja danych pomiarowych.\n");
	printf("6. Wyswietlenie danych w postaci wykresu google charts.\n");
	printf("7. Utworzenie wykresu z dowolnej ilosci danych podanych przez uzytkownika.\n");
	printf("8. Wyjscie z programu.\n");

    while(1){
        poczatek0:
        printf("Opcja programu: ");
        scanf("%d",&opcja);
        switch(opcja) {
            case 1: {
                printf("Podaj nazwe pliku, ktory chcesz wczytac: ");
                scanf("%s",&nazwa_pliku);
                ilosc_punktow = ilosc_linii_pliku(nazwa_pliku);
                dane_pomiarowe = sczytanie_wartosci(nazwa_pliku);
                a=1;
            }; break;
            case 2: {
                if (a==0){
                    printf("Tego nie da sie wykonac bez wczytania danych!\n");
                    goto poczatek0; }
                calkowanie(dane_pomiarowe,nazwa_pliku);
            }; break;
            case 3: {
                if (a==0){
                    printf("Tego nie da sie wykonac bez wczytania danych!\n");
                    goto poczatek0; }
                rozniczkowanie(dane_pomiarowe,nazwa_pliku);
            }; break;
            case 4: {
                 if (a==0){
                    printf("Tego nie da sie wykonac bez wczytania danych!\n");
                    goto poczatek0; }
                dane_pomiarowe=edycja_danych(dane_pomiarowe,nazwa_pliku);
            }; break;
            case 5: {
                if (a==0){
                    printf("Tego nie da sie wykonac bez wczytania danych!\n");
                    goto poczatek0; }
                poczatek5:
                printf("Chcesz powiekszyc(P) czy zmniejszyc(Z) ilosc danych pomiarowych?\n");
                scanf(" %c",&opcja_real);
                if (opcja_real=='Z'){
                    printf("O ile chcesz zmniejszyc ilosc danych pomiarowych?\n");
                    scanf("%d",&ilosc_realokowanych_punktow);
                    dane_pomiarowe=realokowanie_zmniejszanie(dane_pomiarowe,nazwa_pliku,ilosc_realokowanych_punktow);
                    ilosc_punktow=ilosc_punktow-ilosc_realokowanych_punktow; }
                if (opcja_real=='P'){
                    printf("O ile chcesz powiekszyc ilosc danych pomiarowych?\n");
                    scanf("%d",&ilosc_realokowanych_punktow);
                    dane_pomiarowe=realokowanie_powiekszanie(dane_pomiarowe,nazwa_pliku,ilosc_realokowanych_punktow);
                    ilosc_punktow=ilosc_punktow+ilosc_realokowanych_punktow; }
                if ((opcja_real!='Z')&&(opcja_real!='P')) {
                    printf("Podales zla opcje, nalezy podac P lub Z\n");
                    goto poczatek5;}
            }; break;
            case 6: {
                if (a==0){
                    printf("Tego nie da sie wykonac bez wczytania danych!\n");
                    goto poczatek0; }
                wykres(dane_pomiarowe,ilosc_punktow,"wykres.html");
                system("wykres.html");
            }; break;
            case 7: {
                printf("Ile danych pomiarowych chcesz podac?\n");
                scanf("%d",&ilosc_nowych_punktow);
                nowe_dane_pomiarowe=nowe_wartosci(ilosc_nowych_punktow);
                wykres(nowe_dane_pomiarowe,ilosc_nowych_punktow,"wykres.html");
                system("wykres.html");
            }; break;
            case 8: {
                for (i=0;i<ilosc_punktow;i++)
                    free(dane_pomiarowe[i]);
                free(dane_pomiarowe);

                for (i=0;i<ilosc_nowych_punktow;i++)
                    free(nowe_dane_pomiarowe[i]);
                free(nowe_dane_pomiarowe);
                exit(0);
            }; break;
            default: {
                printf("Nie ma takiej opcji!\n");
            }; break;
        }
    }
	return 0;
}

int ilosc_linii_pliku(char *nazwa_pliku) {
    FILE *plik;
    int L=0;
    char znak;

    plik=fopen(nazwa_pliku,"r");
     if (plik == NULL){
        printf("Nie udalo sie otworzyc pliku. ");
        return 0; }
    else {
    while(!feof(plik)) {
        znak=fgetc(plik);
        if (znak=='\n') L++; }
    rewind(plik);
    fclose(plik); }
    return L;

}

int ilosc_znakow_pliku_zamiana_przec_kropka(char *nazwa_pliku) {
    FILE *plik;
    int Z=0,P=0;
    int i;
    char znak;
    char *tab;

    plik=fopen(nazwa_pliku,"r");
    if (plik == NULL){
        printf("Nie udalo sie otworzyc pliku. \n");
        return 0; }
    else {
    rewind(plik);
    while(!feof(plik)) {
		 znak=fgetc(plik);
            Z++; }
    tab=(char*)malloc(Z*sizeof(char));
    rewind(plik);
	for (i=0;i<Z;i++){
        fscanf(plik,"%c",&tab[i]);
        if (tab[i]==',') tab[i]='.'; }
    fclose(plik); }

    plik=fopen("kropki.txt","w");
    for (i=0;i<Z;i++)
        fprintf(plik,"%c",tab[i]);
    fclose(plik);

    free(tab);
    return Z;
}

double **sczytanie_wartosci(char *nazwa_pliku) {
	FILE *plik;
	int i,Z,L;
	double **tab2;


	L = ilosc_linii_pliku(nazwa_pliku);
    Z = ilosc_znakow_pliku_zamiana_przec_kropka(nazwa_pliku);

	plik=fopen("kropki.txt","r");

    rewind(plik);
	tab2 = (double**)malloc(L*sizeof(double*));
        for (i=0;i<L;i++)
            tab2[i]=(double*)malloc(2*sizeof(double));
        for (i=0;i<L;i++)
            fscanf(plik,"%lf;%lf",&tab2[i][0],&tab2[i][1]);

    fclose(plik);

	return tab2;
}

void calkowanie(double **tab, char *nazwa_pliku) {
    int i,L;
    double suma=0,a,b;

    L = ilosc_linii_pliku(nazwa_pliku);
    for (i=1;i<L;i++) {
        a=tab[i][0]-tab[i-1][0];
        b=tab[i][1]-tab[i-1][1];
        suma=suma+a*b; }
        printf("Suma pola pod wykresem wynosi: %lf\n",suma);
}

void rozniczkowanie(double **tab, char *nazwa_pliku) {
    int i,p,L;
    double *rozniczka;

    L = ilosc_linii_pliku(nazwa_pliku);
    rozniczka=(double*)malloc(L*sizeof(double));
    for (i=1;i<L;i++)
        rozniczka[i]=tab[i][1]-tab[i-1][1];

    printf("W jakim punkcie pokazac wartosc rozniczki? (1-%d)\n",L);
    printf("Jesli chcesz przerwac pokazywanie rozniczki wcisnij 0\n");
    poczatek4:
    while(1){
        printf("Punkt: ");
        scanf("%d",&p);
        if (p==0) break;
        if ((p>L)||(p<0)) {
            printf("Podales punkt ktory nie nalezy do zakresu, jeszcze raz podaj punkt\n");
            goto poczatek4; }
        printf("Wartosc rozniczki w punkcie %d wynosi: %lf\n",p,rozniczka[p-1]); }
    free(rozniczka);
}

double **edycja_danych(double **tab,char *nazwa_pliku) {
    FILE *plik;
    int i,p,L,Z=0;
    double x,y;
    char opcja,znak;
    char nowy_plik[20];
    char *tab_znakow;

    L = ilosc_linii_pliku(nazwa_pliku);

    printf("Jaki punkt z danych pomiarowych chcesz edytowac? Zakres 1-%d\n",L);
    printf("Jesli chcesz przerwac edycje danych wcisnij 0\n");
    poczatek1:
    while(1){
        printf("Punkt: ");
        scanf("%d",&p);
        if (p==0) break;
        if ((p>L)||(p<0)) {
            printf("Podales punkt ktory nie nalezy do zakresu, jeszcze raz podaj punkt\n");
            goto poczatek1; }
        printf("Wartosc tego punktu wynosi: x=%lf y=%lf\n",tab[p-1][0],tab[p-1][1]);
        printf("Podaj nowe wartosci tego punktu oddzielone spacja: ");
        scanf("%lf %lf",&x,&y);
        tab[p-1][0]=x;
        tab[p-1][1]=y; }

    printf("Jak chcesz nazwac utworzony wyedytowany plik? (Liczba znakow do 20)\n");
    scanf("%s",&nowy_plik);
    printf("Wyedytowane dane chcesz zapisac z przecinkiem(P) czy z kropka(K)\n");
    poczatek2:
    scanf(" %c",&opcja);
    if (opcja=='K') {
        plik=fopen(nowy_plik,"w");
            for (i=0;i<L;i++)
        fprintf(plik,"%lf;%lf\n",tab[i][0],tab[i][1]);
        fclose(plik);
        printf("Plik o nazwie %s zostal utworzony!\n",nowy_plik);
    }
    if (opcja=='P') {
        plik=fopen(nowy_plik,"w");
        for (i=0;i<L;i++)
            fprintf(plik,"%lf;%lf\n",tab[i][0],tab[i][1]);
        fclose(plik);

        plik=fopen(nowy_plik,"r");
        while(!feof(plik)) {
            znak=fgetc(plik);
                Z++; }
        tab_znakow=(char*)malloc(Z*sizeof(char));
        rewind(plik);
        for (i=0;i<Z;i++){
            fscanf(plik,"%c",&tab_znakow[i]);
        if (tab_znakow[i]=='.') tab_znakow[i]=','; }
        fclose(plik);

        plik=fopen(nowy_plik,"w");
            for (i=0;i<Z;i++)
        fprintf(plik,"%c",tab_znakow[i]);
        fclose(plik);
        free(tab_znakow);
        printf("Plik o nazwie %s zostal utworzony!\n",nowy_plik);
    }
    if ((opcja!='K')&&(opcja!='P')) {
        printf("Podales zla opcje, nalezy podac P lub K\n");
        goto poczatek2;
    }
    return tab;
}

double **nowe_wartosci(int liczba_nowych_danych) {
    int i,j,p,L;
    double **tab;
    double t;
    char opcja;

    L=liczba_nowych_danych;
    tab=(double**)malloc(L*sizeof(double*));
        for (i=0;i<L;i++)
            tab[i]=(double*)malloc(2*sizeof(double));

    /*printf("Ktory punkt danych chcesz podac? (Zakres 1-%d)\n",L);
    printf("Jesli chcesz przerwac podawanie danych wcisnij 0\n");
    poczatek3:
    while(1){
        printf("Punkt: ");
        scanf("%d",&p);
        if (p==0) break;
        if ((p>L)||(p<0)) {
            printf("Podales punkt ktory nie nalezy do zakresu, jeszcze raz podaj punkt\n");
            goto poczatek3; }
        printf("Podaj x i y punktu %d oddzielajac wartosci spacja: ",p);
        scanf("%lf %lf",&tab[p-1][0],&tab[p-1][1]); } */

    printf("Nastapi podanie danych! (Zakres 1-%d)\n",L);
    for (i=0;i<L;i++) {
        printf("Podaj x i y punktu %d oddzielajac wartosci spacja: ",i+1);
        scanf("%lf %lf",&tab[i][0],&tab[i][1]); }

    printf("Czy chcesz przesortowac dane pomiarowe? tak-rosnaco(R), tak-malejaco(M), nie(N)\n");
    poczatek7:
    printf("Podaj opcje: ");
    scanf(" %c",&opcja);
    switch(opcja){
            case 'R': {
                for (j=0;j<L;j++){
                for (i=0;i<L-1;i++){
                    if (tab[i][1]>tab[i+1][1]){
                        t=tab[i][1];
                        tab[i][1]=tab[i+1][1];
                        tab[i+1][1]=t; }}}
                printf("Posortowales tablice rosnaco!\n");
            }; break;
            case 'M': {
                for (j=0;j<L;j++){
                for (i=0;i<L-1;i++){
                    if (tab[i][1]<tab[i+1][1]){
                        t=tab[i][1];
                        tab[i][1]=tab[i+1][1];
                        tab[i+1][1]=t; }}}
                printf("Posortowales tablice malejaco!\n");
            }; break;
            case 'N': {
                printf("Nie posortowales tablicy!\n");
            }; break;
            default : {
                printf("Nie ma takiej opcji!\n");
                goto poczatek7;
            }; break;

    }

    return tab;
    }

double **realokowanie_zmniejszanie(double **tab,char *nazwa_pliku,int zmiana_danych) {
    int i,L,d;

    d=zmiana_danych;
    L=ilosc_linii_pliku(nazwa_pliku);

        tab=(double**)realloc(tab,(L-d)*sizeof(double*));

    return tab;
}

double **realokowanie_powiekszanie(double **tab,char *nazwa_pliku,int zmiana_danych) {
    int i,L,d;

    d=zmiana_danych;
    L=ilosc_linii_pliku(nazwa_pliku);

        tab=(double**)realloc(tab,(L+d)*sizeof(double*));
            for (i=L;i<L+d;i++)
                tab[i]=(double*)malloc(2*sizeof(double));
        for (i=L;i<L+d;i++){
            printf("Podaj dane x i y oddzielone spacja punktu %d :",i+1);
            scanf("%lf %lf",&tab[i][0],&tab[i][1]);}

    return tab;
}

double wykres(double** tablica,int ilosc_punktow, char *nazwa) {
	FILE *Wsk_do_pliku;
	int i,d,maks=0;
	char tytul_wykresu[50],kolor[20];
	double temp;

	printf("Podaj tytul wykresu, ktory chcesz umiescic na stronie: ");
	scanf("%s",&tytul_wykresu);
	printf("Podaj kolor wykresu: ");
	scanf("%s",&kolor);

    temp=tablica[0][1];
	for (i=0;i<ilosc_punktow-1;i++){
        if (tablica[i+1][1]>temp) {
            temp=tablica[i+1][1];
            maks=i+1; }
	}

	Wsk_do_pliku = fopen(nazwa,"w");

	fprintf(Wsk_do_pliku,"<html>\n");
	fprintf(Wsk_do_pliku,"<head>\n");
	fprintf(Wsk_do_pliku,"<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(Wsk_do_pliku,"<script type=\"text/javascript\">\n");
	fprintf(Wsk_do_pliku,"google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(Wsk_do_pliku,"google.setOnLoadCallback(drawChart);\n");
	fprintf(Wsk_do_pliku,"function drawChart() {\n");
	fprintf(Wsk_do_pliku,"var data = google.visualization.arrayToDataTable([\n");
	fprintf(Wsk_do_pliku,"['i', 'dane z tablicy'],\n");

	//
	for(i=0;i<ilosc_punktow;i++){
		fprintf(Wsk_do_pliku,"[%lf, %lf],\n",tablica[i][0],tablica[i][1]);   //przekazanie danych na wykres
	}

	//

	fprintf(Wsk_do_pliku,"]);\n");

	fprintf(Wsk_do_pliku,"var options = {\n");
	fprintf(Wsk_do_pliku,"title: 'rozklad Gaussa'\n");
	fprintf(Wsk_do_pliku,"};\n");
	fprintf(Wsk_do_pliku,"var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(Wsk_do_pliku,"chart.draw(data, {\n");
	fprintf(Wsk_do_pliku,"colors: ['%s']\n",kolor);
	fprintf(Wsk_do_pliku,"}\n");
	fprintf(Wsk_do_pliku,");\n");
	fprintf(Wsk_do_pliku,"}\n");
	fprintf(Wsk_do_pliku,"</script>\n");
	fprintf(Wsk_do_pliku,"</head>\n");
	fprintf(Wsk_do_pliku,"<body>\n");
	fprintf(Wsk_do_pliku, "Tytul wykresu: %s <br \>\n",tytul_wykresu);
	fprintf(Wsk_do_pliku, "%d lini(danych pomiarowych) w pliku <br \>\n",ilosc_punktow);
	fprintf(Wsk_do_pliku, "Maksimum wystepuje w punkcie %d i wynosi x=%lf oraz y=%lf\n",maks+1,tablica[maks][0],tablica[maks][1]);
	fprintf(Wsk_do_pliku,"<div id=\"chart_div\" style=\"width: 900px; height: 500px;\"></div>\n");
	fprintf(Wsk_do_pliku,"</body>\n");
	fprintf(Wsk_do_pliku,"</html>\n");

	fclose(Wsk_do_pliku);
	return 0;
}
