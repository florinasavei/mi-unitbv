package com.company;

import java.io.*;
import java.util.*;
public class AFD2 {

    public int[][] Transition = new int[20][20];
    public int nr_litere_alfabet, nr_stari;
    public ArrayList < Character > alfabet;
    public Set < Integer > stari_finale;

    public void construieste_AFD() throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("introduceti numarul de litere ale alfabetului");
        nr_litere_alfabet = Integer.parseInt(br.readLine());

        System.out.println("introduceti numarul de stari ale AFD-ului");
        nr_stari = Integer.parseInt(br.readLine());


        System.out.println("introduceti alfabetul");
        String alphabets = br.readLine();

        alfabet = new ArrayList < Character > ();
        for (int i = 0; i < alphabets.length(); i++)
        {
            alfabet.add(alphabets.charAt(i));

        }

        for (int s = 0; s < nr_stari; s++) {
            System.out.println("tranzitiile pentru starea " +s);
            for (int r = 0; r < nr_litere_alfabet; r++) {
                int int1 = Integer.parseInt(br.readLine());
                Transition[s][r] = int1;
            }
        }

        stari_finale = new HashSet < Integer > ();
        System.out.println("introduceti starea/starile finala/e\n");
        System.out.println("tastati -1 cand ati terminat");

        int int2 = Integer.parseInt(br.readLine());

        while (int2 != -1) {
            stari_finale.add(int2);
            int2 = Integer.parseInt(br.readLine());
        }
        System.out.println("starea finala este: "+stari_finale);
        Test_AFD();
    }

    public void Test_AFD() throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int state;
        System.out.println("introduceti starea initiala");
        state = Integer.parseInt(br.readLine());

        System.out.println("introduceti cuvantul pe care doriti sa il verificati, cu # la sfarsit:\n");
        String cuvant = br.readLine();
        int index = 0;

        while (cuvant.charAt(index) != '#')
        {
            char char1 = cuvant.charAt(index);
            int index1 = alfabet.indexOf(char1);
            state = Transition[state][index1];
            index++;
        }

        if (stari_finale.contains(state))
            System.out.print("cuvantul este acceptat de AFD");
        else
            System.out.println("cuvantul nu este acceptat de AFD");
    }

    public static void main(String args[]) throws Exception {
        AFD2 afd = new AFD2();
        afd.construieste_AFD();
    }
}