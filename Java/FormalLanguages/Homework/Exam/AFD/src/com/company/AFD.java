package com.company;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class AFD
{

    public static boolean verificareCuvant(int n,String A,String cuvant)
    {
        for(int i=0;i<cuvant.length();i++)
            if(A.indexOf(cuvant.charAt(i))<0)
                return true;
        return false;
    }

    public static boolean verificareFinala(String st2,String F)
    {
        if(F.indexOf(st2)<0)
            return false;
        return true;
    }

    public static String returneazaStare(int n,char a,String stare,String[] st1,String[] alf,String[] st2)
    {
        for(int i=0;i<n;i++)
            if( st1[i].equals(stare)==true && alf[i].indexOf(a)>=0)
                return st2[i];
        throw new RuntimeException("Cuvantul nu e recunoscut de automat!");
    }

    public static boolean verificare(String[] st1,String[] alf,String[] st2,String F,String q0,String cuvant,int n)
    {
        String cuv=cuvant;
        String stCurenta=q0;
        for(int i=0;i<cuvant.length();i++)
        {
            try{
                stCurenta=returneazaStare(n,cuv.charAt(i),stCurenta,st1,alf,st2);
            }
            catch(Exception e)
            {
                //return false;
                System.out.println("ERROR: "+e.getMessage());
                return false;
            }

            if( i==cuvant.length()-1 && verificareFinala(stCurenta,F)==true)
                //if(verificareFinala(stCurenta,F)==true )
                return true;
        }
        return false;
    }

    public static void main(String args[]) throws FileNotFoundException
    {
        Scanner sc = new Scanner(new FileReader("AFD.txt"));
        String Q,A,F,q0;
        Q=sc.nextLine();
        A=sc.nextLine();
        q0=sc.nextLine();
        F=sc.nextLine();
        int n=sc.nextInt();

        String[] st1=new String[n];
        String[] alf=new String[n];
        String[] st2=new String[n];

        for(int i=0;i<n;i++)
        {
            st1[i]=sc.next();
            alf[i]=sc.next();
            st2[i]=sc.next();
        }

        System.out.println("Starile sunt urmatoarele: "+Q);
        System.out.println("Elementele alfabetului sunt: "+A);
        System.out.println("Introdu cuvantul de verificat:");
        Scanner sb = new Scanner(System.in);
        String cuv = sb.nextLine();
        if (verificareCuvant(n, A, cuv) == false)
            if (verificare(st1, alf, st2, F, q0, cuv, n) == true)
                System.out.println("Cuvantul e recunoscut de AFD!");
            else
                System.out.println("Cuvantul NU e recunoscut de AFD!");

    }
}

