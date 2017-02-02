#include <stdio.h>
#include <string.h>

#define STARE	99
#define SIMBOL	20

int N_simbol;	/* numar de simboluri */
int N_stare;	/* numar total de stari */
char *N_streFinala;	/* numar stari finale */
int Tabel_AFD[STARE][SIMBOL];

char NumeStare[STARE][STARE + 1];	/* tabelul stare-nume */

int N_iesireAFN_STARE;	/* numarul de stari finale minimizate */
int iesireAFN[STARE][SIMBOL];
char finale_noi[STARE + 1];


void print_tabel_AFD(
	int tab[][SIMBOL],	/* tabel AFD */
	int nSTARE,	/* numar de stari */
	int nSIMBOL,	/* numar simboluri intrare */
	char *finale)
{
	int i, j;

	puts("\n tabelul AFN:");

	printf("     | ");
	for (i = 0; i < nSIMBOL; i++) printf("  %c  ", '0' + i);

	printf("\n-----+--");
	for (i = 0; i < nSIMBOL; i++) printf("-----");
	printf("\n");

	for (i = 0; i < nSTARE; i++) {
		printf("  %c  | ", 'A' + i);	/* stare */
		for (j = 0; j < nSIMBOL; j++)
			printf("  %c  ", tab[i][j]);	/* urmatoarea stare */
		printf("\n");
	}
	printf("Stare finala = %s\n", finale);
}

/*
Initialize NFA table.
*/
void citeste_tabel_AFN()
{

	Tabel_AFD[0][0] = 'B'; Tabel_AFD[0][1] = 'C';
	Tabel_AFD[1][0] = 'E'; Tabel_AFD[1][1] = 'F';
	Tabel_AFD[2][0] = 'A'; Tabel_AFD[2][1] = 'A';
	Tabel_AFD[3][0] = 'F'; Tabel_AFD[3][1] = 'E';
	Tabel_AFD[4][0] = 'D'; Tabel_AFD[4][1] = 'F';
	Tabel_AFD[5][0] = 'D'; Tabel_AFD[5][1] = 'E';

	N_streFinala = "EF";
	N_stare = 6;
	N_simbol = 2;
}

void citeste_starea_urmatoare(char *stare_urmatoare, char *stare_curenta,
	int AFD[STARE][SIMBOL], int symbol)
{
	int i, ch;

	for (i = 0; i < strlen(stare_curenta); i++)
		*stare_urmatoare++ = AFD[stare_curenta[i] - 'A'][symbol];
	*stare_urmatoare = '\0';
}


char index_clasa_echivalenta(char ch, char stnt[][STARE + 1], int n)
{
	int i;

	for (i = 0; i < n; i++)
	if (strchr(stnt[i], ch)) return i + '0';
	return -1;	/* urmatoarea stare nu e definita */
}

char este_in_starea_urmatoare(char *s)
{
	char clasa_echivalenta;	/* prima clasa de echivalenta */

	while (*s == '@') s++;
	clasa_echivalenta = *s++;	/* indexul clasei de echivalenta */

	while (*s) {
		if (*s != '@' && *s != clasa_echivalenta) return 0;
		s++;
	}

	return clasa_echivalenta;	/* urmatoarea stare */
}

int state_index(char *state, char stnt[][STARE + 1], int n, int *pn,
	int curent)	
{
	int i;
	char state_flags[STARE + 1];	

	if (!*state) return -1;	/* nu exista starea urmatoare */

	for (i = 0; i < strlen(state); i++)
		state_flags[i] = index_clasa_echivalenta(state[i], stnt, n);
	state_flags[i] = '\0';

	printf("   %d:[%s]\t--> [%s] (%s)\n",
		curent, stnt[curent], state, state_flags);

	if (i = este_in_starea_urmatoare(state_flags))
		return i - '0';	
	else {
		strcpy(stnt[*pn], state_flags);
		return (*pn)++;
	}
}


int init_clasa_echivalenta(char NumeStare[][STARE + 1], int n, char *finale)
{
	int i, j;

	if (strlen(finale) == n) {	/* toate starile sunt finale */
		strcpy(NumeStare[0], finale);
		return 1;
	}

	strcpy(NumeStare[1], finale);
	for (i = j = 0; i < n; i++) {
		if (i == *finale - 'A') {
			finale++;
		}
		else NumeStare[0][j++] = i + 'A';
	}
	NumeStare[0][j] = '\0';

	return 2;
}


int citeste_AFN_optimizat(char stnt[][STARE + 1], int n,
	int AFD[][SIMBOL], int n_sym, int newAFD[][SIMBOL])
{
	int n2 = n;		
	int i, j;
	char urmaroarea[STARE + 1];

	for (i = 0; i < n; i++) {	
		for (j = 0; j < n_sym; j++) {
			citeste_starea_urmatoare(urmaroarea, stnt[i], AFD, j);
			newAFD[i][j] = state_index(urmaroarea, stnt, n, &n2, i) + 'A';
		}
	}

	return n2;
}


void chr_append(char *s, char ch)
{
	int n = strlen(s);

	*(s + n) = ch;
	*(s + n + 1) = '\0';
}

void sort(char stnt[][STARE + 1], int n)
{
	int i, j;
	char temp[STARE + 1];

	for (i = 0; i < n - 1; i++)
	for (j = i + 1; j < n; j++)
	if (stnt[i][0] > stnt[j][0]) {
		strcpy(temp, stnt[i]);
		strcpy(stnt[i], stnt[j]);
		strcpy(stnt[j], temp);
	}
}

int split_clasa_echivalenta(char stnt[][STARE + 1],
	int i1,	
	int i2,	
	int n,	
	int n_AFD)	
{
	char *old = stnt[i1], *vec = stnt[i2];
	int i, n2, flag = 0;
	char newSTARE[STARE][STARE + 1];	

	for (i = 0; i < STARE; i++) newSTARE[i][0] = '\0';

	for (i = 0; vec[i]; i++)
		chr_append(newSTARE[vec[i] - '0'], old[i]);

	for (i = 0, n2 = n; i < n_AFD; i++) {
		if (newSTARE[i][0]) {
			if (!flag) {	
				strcpy(stnt[i1], newSTARE[i]);
				flag = 1;	
			}
			else	
				strcpy(stnt[n2++], newSTARE[i]);
		}
	}

	sort(stnt, n2);	

	return n2;	
}


int set_new_clasa_echivalenta(char stnt[][STARE + 1], int n,
	int newAFD[][SIMBOL], int n_sym, int n_AFD)
{
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n_sym; j++) {
			k = newAFD[i][j] - 'A';
			if (k >= n)	
				return split_clasa_echivalenta(stnt, i, k, n, n_AFD);
		}
	}

	return n;
}

void print_clasa_echivalentaes(char stnt[][STARE + 1], int n)
{
	int i;

	printf("\nPosibila clasa de echivalenta ==>");
	for (i = 0; i < n; i++)
		printf(" %d:[%s]", i, stnt[i]);
	printf("\n");
}


int optimize_AFD(
	int AFD[][SIMBOL],	/* tabelul AFD */
	int n_AFD,	/* numar stari AFD */
	int n_sym,	/* numar sumboluri intrare AFD */
	char *finale,	/* numar stari finale AFD */
	char stnt[][STARE + 1],	
	int newAFD[][SIMBOL])	/* tabel AFD minimizat */
{
	char urmaroarea[STARE + 1];
	int n;	
	int n2;	

	n = init_clasa_echivalenta(stnt, n_AFD, finale);

	while (1) {
		print_clasa_echivalentaes(stnt, n);
		n2 = citeste_AFN_optimizat(stnt, n, AFD, n_sym, newAFD);
		if (n != n2)
			n = set_new_clasa_echivalenta(stnt, n, newAFD, n_sym, n_AFD);
		else break;
	}

	return n;	
}

/*
Check if 't' is a subset of 's'.
*/
int este_substring(char *s, char *t)
{
	int i;

	for (i = 0; *t; i++)
	if (!strchr(s, *t++)) return 0;
	return 1;
}


void get_finale_noi(
	char *finale_noi,	
	char *finale_vechi,	
	char stnt[][STARE + 1],	
	int n)	
{
	int i;

	for (i = 0; i < n; i++)
	if (este_substring(finale_vechi, stnt[i])) *finale_noi++ = i + 'A';
	*finale_noi++ = '\0';
}

void main()
{
	citeste_tabel_AFN();
	print_tabel_AFD(Tabel_AFD, N_stare, N_simbol, N_streFinala);

	N_iesireAFN_STARE = optimize_AFD(Tabel_AFD, N_stare,
		N_simbol, N_streFinala, NumeStare, iesireAFN);
	get_finale_noi(finale_noi, N_streFinala, NumeStare, N_iesireAFN_STARE);

	print_tabel_AFD(iesireAFN, N_iesireAFN_STARE, N_simbol, finale_noi);
	getchar();
}