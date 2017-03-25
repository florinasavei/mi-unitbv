#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
typedef char sir[1024];

struct productii{
	char arc;
	int iesire;
	productii *urmator;
};

productii **v; // arcele sub forma tabelara
int *sf; // multimea cu finale
sir s;
int n_finale;
int incercari = 20;
int cautare(int qi, char arc, int nivel, int nivel2){
	if (nivel2>incercari)return -1;
	int i, qf = 0; productii *v2;
	int ok = 0;
	if (nivel == strlen(s) - 1){
		v2 = v[qi];
		while (v2 != NULL){
			if (arc == v2->arc){
				qf = v2->iesire; ok = 1;
				for (i = 0; i<n_finale; i++)if (sf[i] == qf)return 1;
			}
			v2 = v2->urmator;
		}
		if (ok)return 0;
	}
	else{
		v2 = v[qi];
		while (v2 != NULL){
			if (arc == v2->arc){
				qf = v2->iesire;
				i = cautare(qf, s[nivel + 1], nivel + 1, nivel2 + 1);
				if (i>0)return 1; if (i == 0)ok = 1;
			}
			else if (v2->arc == '_'){
				qf = v2->iesire;
				i = cautare(qf, s[nivel], nivel, nivel2 + 1);
				if (i>0)return 1; if (i == 0)ok = 1;
			}
			v2 = v2->urmator;
		}
		if (ok)return 0;
	}
	return -1;
}


int main(int argc, char* argv[]){
	char *sg; // sigma
	int si; // starea initiala
	int n_stari, n_sigma, n_arce, i;
	ifstream f("AF_intrare.txt"), f2("AF_cuvant.txt");
	f2 >> s;
	f >> n_stari; v = new productii*[n_stari];
	for (i = 0; i<n_stari; i++)v[i] = NULL;
	f >> n_sigma; sg = new char[n_sigma];

	for (i = 0; i<n_sigma; i++)f >> sg[i];
	f >> n_arce;
	productii *v2; int qi, qf; char cc; // PENTRU A AJUTA LA CITIRE
	for (i = 0; i<n_arce; i++){
		f >> qi;
		if (v[qi] != NULL){
			v2 = v[qi]; while (v2->urmator != NULL)v2 = v2->urmator;
			v2->urmator = new productii; v2 = v2->urmator;
		}
		else{
			v[qi] = new productii; v2 = v[qi];
		}
		f >> cc;
		f >> qf;
		v2->arc = cc; v2->iesire = qf; v2->urmator = NULL;
	}
	f >> si;
	f >> n_finale; sf = new int[n_finale];
	for (i = 0; i<n_finale; i++)f >> sf[i];
	f.close(); f2.close();
	int ok = cautare(si, s[0], 0, 0);
	if (ok<0){
		cout << "Cuvantul BLOCHEAZA" << endl;
	}
	else if (ok == 0){
		cout << "NU ESTE ACCEPTAT" << endl;
	}
	else{
		cout << "ACCEPTAT" << endl;
	}

	//getchar();

	return 0;
}

