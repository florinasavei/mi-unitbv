/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package problema1;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.io.Serializable;
import static problema1.Main01.nrStudenti;

public class Student implements Serializable {


    public static int id = 1;
    int identificator=nrStudenti;
    String nume;
    String prenume;
    String CNP;
    String telefon;
    int birthYear;
    int nrNote = 0;
    List<Nota> listaNote;


    public Student() { //constructor
        listaNote = new ArrayList<Nota>();
        this.identificator++;
    }

    //</editor-fold>

    public static Student IntroducereStudent() {

        Scanner reader = new Scanner(System.in);
        Student student = new Student();

        System.out.println("Introduceti numele de familie al studentului: ");
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

        Scanner input = new Scanner(System.in);

        System.out.println("Introduceti numarul de note pe care doriti sa le introduceti: ");
        int note = Integer.parseInt(input.nextLine());

        for (int i = 0; i < note; i++) {
            Nota notaStudent = new Nota();

            System.out.println("Introduceti materia:");
            notaStudent.materie = input.nextLine();

            System.out.println("Introduceti nota:");
            notaStudent.nota = Double.parseDouble(input.nextLine());

            System.out.println("Introduceti data:");
            notaStudent.data = input.nextLine();

            this.listaNote.add(notaStudent);
        }

        this.nrNote += note;
    }

    public String GetAnNastere() {
        String lastDigits = this.CNP.substring(1, 3);
        if (Integer.parseInt(lastDigits) > 18)
            return "19" + lastDigits;
        else
            return "20" + lastDigits;

    }

    public boolean areVodafone() { 
        if (this.telefon.substring(1, 3).equals("72") ||
                this.telefon.substring(1, 3).equals("73"))
            return true;

        return false;
    }

    public boolean eNascutDeCraciun() {
        if (this.CNP.substring(3, 7).equals("1224"))
            return true;

        return false;
    }

    public void mediaNotelorPeste8(Student student){

        double sum = 0;
        int count =0;

        for (Nota n : student.listaNote) {

            if (n.nota > 8)
            {
                sum += n.nota;
                count++;
            }

        }
        double medie = sum/count;
        System.out.println("Media notelor peste 8 ale studentului "+student.nume+" este: "+medie);
    }

    public String afisareStudent() {

        String note = "";
        for (Nota d : listaNote) {
            note += "Materie: " + d.materie + " Nota: " + d.nota + " Data: " + d.data + "\n";
        }

        if (note.equals(""))
            note = "Studentul nu are note.\n";

        return this.identificator + ". " +
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
                "Note:\n" +
                note +
                "______________________________________________\n";
    }
    
   
}
