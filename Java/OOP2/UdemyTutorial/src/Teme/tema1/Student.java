package Teme.tema1;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.io.Serializable;

public class Student implements Serializable {

    //<editor-fold desc="#properties">

    private static int id = 1;
    int identifier;
    String nume;
    String prenume;
    String CNP;
    String telefon;
    int birthYear;
    int nrNote = 0;
    List<Nota> listaNote;

    //</editor-fold>

    //<editor-fold desc="#constructors">

    public Student() {
        listaNote = new ArrayList<Nota>();
        this.identifier = id;
        id++;
    }

    //</editor-fold>

    public static Student IntroducereStudent() {

        Scanner reader = new Scanner(System.in);
        Student student = new Student();

        System.out.println("Introduceti numele studentului: ");
        student.nume = reader.nextLine();

        System.out.println("Introduceti prenumele studentului: ");
        student.prenume = reader.nextLine();

        System.out.println("Introduceti CNP-ul studentului: ");
        student.CNP = reader.nextLine();
        student.birthYear = Integer.parseInt(student.GetAnNastere());

        System.out.println("Introduceti numarul de telefon al studentului: ");
        student.telefon = reader.nextLine();

        return student;
    }

    public void IntroducereNote() {

        Scanner reader = new Scanner(System.in);

        System.out.println("Introduceti numarul de note pe care doriti sa le introduceti: ");
        int Notas = Integer.parseInt(reader.nextLine());

        for (int i = 0; i < Notas; i++) {
            Nota Nota = new Nota();

            System.out.println("Introduceti materia:");
            Nota.materie = reader.nextLine();

            System.out.println("Introduceti nota:");
            Nota.nota = Double.parseDouble(reader.nextLine());

            System.out.println("Introduceti data:");
            Nota.data = reader.nextLine();

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

    public String toString() {

        String note = "";
        for (Nota d : listaNote) {
            note += "Materie: " + d.materie + " Nota: " + d.nota + " Data: " + d.data + "\n";
        }

        if (note.equals(""))
            note = "Studentul nu are note.\n";

        return this.identifier + ". " +
                this.nume +
                " " +
                this.prenume +
                "\n" +
                " CNP: " +
                this.CNP +
                "\n" +
                " Telefon: " +
                this.telefon +
                "\n" +
                "== Note =================================\n" +
                note +
                "=========================================\n";
    }
}
