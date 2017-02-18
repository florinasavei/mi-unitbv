/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tema1;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.io.Serializable;

public class Student implements Serializable {


    private static int idStudent = 1;
    int identifier;
    String nume;
    String prenume;
    String CNP;
    String telefon;
    int birthYear;
    int nrNote = 0;
    List<Nota> listaNote;

    public Student() {
        listaNote = new ArrayList<Nota>();
        if (this.identifier>1){
            idStudent=this.identifier;
        }
            this.identifier = idStudent;
            idStudent++;
    }


    public static Student IntroducereStudent() {

        Scanner input = new Scanner(System.in);
        Student student = new Student();

        System.out.println("Introduceti numele studentului: ");
        student.nume = input.nextLine();

        System.out.println("Introduceti prenumele studentului: ");
        student.prenume = input.nextLine();

        System.out.println("Introduceti CNP-ul studentului: ");
        student.CNP = input.nextLine();
        student.birthYear = Integer.parseInt(student.GetAnNastere());

        System.out.println("Introduceti numarul de telefon al studentului: ");
        student.telefon = input.nextLine();

        return student;
    }

    public void IntroducereNote() {

        Scanner input = new Scanner(System.in);

        System.out.println("Introduceti numarul de note pe care doriti sa le introduceti: ");
        int Notas = Integer.parseInt(input.nextLine());

        for (int i = 0; i < Notas; i++) {
            Nota Nota = new Nota();

            System.out.println("Introduceti materia:");
            Nota.materie = input.nextLine();

            System.out.println("Introduceti nota:");
            Nota.nota = Double.parseDouble(input.nextLine());

            System.out.println("Introduceti data:");
            Nota.data = input.nextLine();

            this.listaNote.add(Nota);
        }

        this.nrNote += Notas;
    }

    public String GetAnNastere() {
        String lastDigits = this.CNP.substring(1, 3);
        if (Integer.parseInt(lastDigits) > 18)
            return "19" + lastDigits;
        else
            return "20" + lastDigits;

    }

    public boolean HasVodafone() {
        if (this.telefon.substring(1, 3).equals("72") ||
                this.telefon.substring(1, 3).equals("73"))
            return true;

        return false;
    }

    public boolean IsBornChristmas() {
        if (this.CNP.substring(3, 7).equals("1224"))
            return true;

        return false;
    }

    public void CalculateMeanOver8(Student student){

        double sum = 0;
        int count =0;

        for (Nota n : student.listaNote) {

            if (n.nota > 8)
            {
                sum += n.nota;
                count++;
            }

        }
        double mean = sum/count;
        System.out.println("Media notelor peste 8 ale studentului "+student.nume+" este: "+mean);
    }

    public String afisareStudent() {

        String note = "";
        for (Nota d : listaNote) {
            note += "Materie: " + d.materie + " Nota: " + d.nota + " Data: " + d.data + "\n";
        }

        if (note.equals(""))
            note = "Nici o nota introdusa\n";

        return "Id student: "+ this.identifier + "\n" +
                "Nume & prenume: "+ this.nume +" " + this.prenume +"\n" +
                " CNP: " + this.CNP +"\n" +
                " Telefon: " + this.telefon +"\n\n" +
                "Note \n" +
                note +
                "_________________________________________________\n";
    }
}
