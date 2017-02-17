/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tema1;


/**
 * 
 * 								 1 POO 2
 *						Invatamant la Distanta

 *		Sa se realizeze o aplicatie in Java care sa permita citirea de la tastatura a unei liste de studenti.
 *
 *		Pentru fiecare student se vor citi urmatoarele informatii:
 *				Nume
 *				Prenume
 *				CNP
 *				Nr Telefon
 *				Numarul de note
 *				Lista de note
 *
 *		Pentru fiecare nota se va citi:
 *				Materia
 *				Nota
 *				Data
 * 
 *		Cerinte:
 *			Sa se sorteze studentii dupa anul nasterii
 *			Sa se afiseze studentii care au numar de Vodafone
 *			Sa se afiseze studentii nascuti de Craciun
 *			Sa se afiseze studentii care au peste 5 la materia POO2
 *			Sa se afiseze studentii care au restante, impreuna cu lista restantelor
 *			Media notelor peste 8 ale studentului X, al carui nume este introdus de la tastatura.
 *			Daca pentru vre-una dintre cerinte nu avem rezultat (Ex: nu exista nici un student nascut de Craciun), atunci se va semnala acest lucru printr-un mesaj.
 *
 * 		TODO: Stergerea unui student sau a unei note
 * 
 * @author Asavei Florin
 *
 */


import serializare.*;

import java.util.*;

public class Main1 {

    public static void main(String[] args) {
        boolean meniu = true;
        Scanner scanner = new Scanner(System.in);
        List<Student> listaStudenti = new ArrayList<Student>();

        Object Deserializat = Deserializare.ObiectDeserializare("studenti");

        if (Deserializat != null) {
            listaStudenti = (List<Student>) Deserializat;
            PrintStudentList(listaStudenti);
        } else {
            System.out.println("Nu exista nicio inregistrare.\n");
        }
        System.out.println("___________________________________________________\n");
        do {

            System.out.println("Alegeti o optiune:");
            System.out.println("1 : Introduceti un student.");
            System.out.println("2 : Introduceti note pentru un student.");
            System.out.println("3 : Sortarea studenti dupa anul de nastere(varsta crescatoare).");
            System.out.println("4 : Afisarea studentilor cu numar de Vodafone.");
            System.out.println("5 : Afisarea studentilor nascuti de Craciun.");
            System.out.println("6 : Afisarea studentilor care au peste 5 la materia POO2.");
            System.out.println("7 : Afisarea studentilor care au restante, impreuna cu lista restantelor.");
            System.out.println("8 : Afisarea mediei notelor pentru studentul introdus.");
            System.out.println("9 : Printare lista curenta studenti.");
            System.out.println("10 : Inchide si salveaza.");

            int optiune = Integer.parseInt(scanner.nextLine());

            switch (optiune) {
                case 1:
                    listaStudenti.add(IntroducereStudent());
                    break;
                case 2:
                    System.out.println("Introduceti ID-ul studentului apoi introdu notele:");
                    int id = Integer.parseInt(scanner.nextLine());
                    boolean found = false;
                    for (Student d : listaStudenti) {
                        if (d.identifier == id) {
                            d.IntroducereNote();
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                        System.out.println("Studentul cu respectivul id nu exista.\n");

                    break;
                case 3:  //sortare dupa anul nasterii
                    List<Student> listaStudentiCopy = listaStudenti;
                    Collections.sort(listaStudentiCopy, new Comparator<Student>() {
                        @Override
                        public int compare(Student s1, Student s2) {
                            return s1.birthYear < s2.birthYear ? 1
                                    : s1.birthYear > s2.birthYear ? -1
                                    : 0;
                        }
                    });

                    PrintStudentList(listaStudentiCopy);
                    break;
                case 4:
                    boolean foundVodafone = false;
                    for (Student d : listaStudenti) {
                        if (d.HasVodafone()) {
                            System.out.println(d.nume + " " + d.prenume + " are Vodafone.");
                            foundVodafone = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundVodafone)
                        System.out.println("Nu exista studenti cu Vodafone.\n");
                    break;
                case 5:
                    boolean foundChristmas = false;
                    for (Student d : listaStudenti) {
                        if (d.IsBornChristmas()) {
                            System.out.println(d.nume + " " + d.prenume + " este nascut de Craciun.");
                            foundChristmas = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundChristmas)
                        System.out.println("Nu exista studenti nascuti de Craciun.\n");

                    break;
                case 6:
                    boolean foundPOOOver5 = false;
                    for (Student d : listaStudenti) {
                        for (Nota n : d.listaNote) {

                            if (n.materie.equals("POO2") &&
                                    n.nota > 5)
                                System.out.println(d.nume + " " + d.prenume + " are nota peste 5 la POO2 pe data de " + n.data);
                            foundPOOOver5 = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundPOOOver5)
                        System.out.println("Nu exista studenti care au peste 5 la materia POO2.\n");
                    break;
                case 7:
                    boolean foundFailed = false;
                    for (Student d : listaStudenti) {

                        List<Nota> listFailed = new ArrayList<Nota>();

                        for (Nota n : d.listaNote) {
                            if (n.nota < 5) {
                                listFailed.add(n);
                                foundFailed = true;
                            }
                        }

                        if (foundFailed) {
                            System.out.println("\n\nStudentul " + d.nume + " " + d.prenume + " are restante.");
                            System.out.println("________________________________");
                            for (Nota f : listFailed) {
                                System.out.println("Materia: " + f.materie + " - " + "Nota: " + f.nota + ".");
                            }
                        }

                    }

                    System.out.print("\n");

                    if (!foundFailed)
                        System.out.println("Nu exista studenti care au peste 5 la materia POO2.\n");
                    break;
                case 8:
                    System.out.println("Introduceti studentul pentru care vreti sa calculati media notelor peste 8:");
                    String studentName = scanner.nextLine();

                    boolean foundStudent = false;
                    for (Student d : listaStudenti) {
                        if (d.nume.equals(studentName)) {
                            d.CalculateMeanOver8(d);
                            foundStudent = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundStudent)
                        System.out.println("Nu exista student cu acest nume.\n");

                    break;
                case 9:
                    PrintStudentList(listaStudenti);
                    break;
                case 10:
                    System.out.println("Aplicatia se va inchide.");
                    meniu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.");
                    break;

            }
        } while (meniu);

        if (listaStudenti.size() != 0)
            Serializare.ObiectSerializare(listaStudenti, "studenti");

        scanner.close();
    }

    private static Student IntroducereStudent() {

        Student student = Student.IntroducereStudent();

        System.out.println("Ati introdus urmatorul student: ");
        System.out.println(student.toString());
        System.out.println("___________________________________________\n");

        return student;
    }

    private static void PrintStudentList(List<Student> list) {
        for (Student d : list) {
            System.out.println(d.toString());
        }
    }
}
