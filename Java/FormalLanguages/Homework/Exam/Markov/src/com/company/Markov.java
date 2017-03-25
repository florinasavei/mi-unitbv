package com.company;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class Markov {

    public static void main(String[] args) throws FileNotFoundException {
        FileInputStream fis = new FileInputStream("reguli.txt");
        Scanner citireFisier = new Scanner(fis);
        Scanner citireCuvand = new Scanner(System.in);

        ArrayList<String> stanga = new ArrayList<String>();
        ArrayList<String> dreapta = new ArrayList<String>();
        String cuvant;

        System.out.print("Cuvantul: ");
        cuvant=citireCuvand.next();

        int nrReguli = Integer.parseInt(citireFisier.nextLine());
        System.out.print("Numarul de reguli este : ");
        System.out.println(nrReguli);

        System.out.print("Avem urmatoarele reguli : ");
        for (int i=0; i<nrReguli; i++)
        {
            stanga.add(citireFisier.next());
            dreapta.add(citireFisier.next());
            System.out.println( stanga.get(i) + " " + dreapta.get(i));
        }

        System.out.println();

        citireFisier.close();
        citireCuvand.close();


        for (int i=0; i<nrReguli; i++)
        {
            if (cuvant.indexOf(stanga.get(i)) != -1) //daca exista caracterul i din cuvant in membrul stang
            {
                cuvant = cuvant.replaceFirst(stanga.get(i), dreapta.get(i)); //inlocuim primul membrul din stanga cu corespondentul sau din dreapta
                cuvant = cuvant.replaceFirst("lambda", ""); //eliminam lamda
                i=-1; //resetam counter-ul
            }
        }

        System.out.print("Cuvantul generat este: " + cuvant);

    }

}

