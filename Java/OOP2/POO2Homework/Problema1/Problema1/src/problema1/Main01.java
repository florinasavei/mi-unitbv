/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package problema1;


import java.util.*;
import serializare.*;


public class Main01 {
public static int nrStudenti=0;
public static int nrStudentiAfisati=0;
    public static void main(String[] args) {
        
        boolean afisareMeniu = true;
        Scanner scanner = new Scanner(System.in);
        List<Student> listaStudenti = new ArrayList<Student>(); //vector cu obiecte de tip Student

        Object deserializat = Deserializare.obiectDeserializat("studenti");
        
        if (deserializat != null) {
            listaStudenti = (List<Student>) deserializat;
            afisareListaStudenti(listaStudenti);
        } else {
            System.out.println("Nu exista nicio inregistrare.\n");
        }
        
         nrStudenti=listaStudenti.size();
               
        do {
            
            Meniu meniu = new Meniu();
            meniu.AfisareMeniu();

            char optiuneMeniu = scanner.next().charAt(0);

            switch (optiuneMeniu) {
                case '1': //intodcure student
                    listaStudenti.add(InsertStudent());
                    break;
                case '2': //introducere note
                    System.out.println("Introduceti id-ul studentului pentru care vreti sa introduceti note:");
                    int idCitit = Integer.parseInt(scanner.nextLine());
                    boolean found = false;
                    for (Student stud : listaStudenti) {
                        if (stud.identificator == idCitit) {
                            stud.IntroducereNote();
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                        System.out.println("Nu exista nici un student cu id-ul "+idCitit+"\n");

                    break;
                case '3': //sortare dupa anul nasterii descrescator (varsta crescatoare)
                    List<Student> listaStudentiCopy = listaStudenti;
                    Collections.sort(listaStudentiCopy, new Comparator<Student>() {
                        @Override
                        public int compare(Student s1, Student s2) {
                            return s1.birthYear < s2.birthYear ? 1
                                    : s1.birthYear > s2.birthYear ? -1
                                    : 0;
                        }
                    });

                    afisareListaStudenti(listaStudentiCopy);
                    break;
                case '4':  //Are numat de vodafone(incepe cu *73)
                    boolean foundVodafone = false;
                    for (Student d : listaStudenti) {
                        if (d.areVodafone()) {
                            System.out.println(d.nume + " " + d.prenume + " are Vodafone.");
                            foundVodafone = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundVodafone)
                        System.out.println("Nu exista studenti cu Vodafone.\n");
                    break;
                case 5:  //Afisare studenti nascuti de caraciuni
                    boolean nascutDeCraciun = false;
                    for (Student d : listaStudenti) {
                        if (d.eNascutDeCraciun()) {
                            System.out.println(d.nume + " " + d.prenume + " este nascut de Craciun.");
                            nascutDeCraciun = true;
                        }
                    }

                    System.out.print("\n");

                    if (!nascutDeCraciun)
                        System.out.println("Nu exista studenti nascuti de Craciun.\n");

                    break;
                case '6': //afisare studenti care au peste 5 la POO2
                    boolean aPromovatPOO2 = false;
                    for (Student stud : listaStudenti) {
                        for (Nota n : stud.listaNote) {

                            if (n.materie.equals("POO2") && n.nota > 5)
                                System.out.println(stud.nume + " " + stud.prenume + " are nota peste 5 la POO2 pe data de " + n.data);
                            aPromovatPOO2 = true;
                        }
                    }

                    System.out.print("\n");

                    if (!aPromovatPOO2)
                        System.out.println("Nu exista studenti care au peste 5 la materia POO2.\n");
                    break;
                case '7': //aisare restantieri
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
                            System.out.println("______________________________________________");
                            for (Nota f : listFailed) {
                                System.out.println("Materia: " + f.materie + " - " + "Nota: " + f.nota + ".");
                            }
                        }

                    }

                    System.out.print("\n");

                    if (!foundFailed)
                        System.out.println("Nici un student nu are peste 5 la POO2.\n");
                    break;
                case '8': //afisare medie note peste 8
                    System.out.println("Introduceti  numel de familie al studentului pt care vreti sa calculati media notelor peste 8:");
                    String studentName = scanner.nextLine();

                    boolean foundStudent = false;
                    for (Student d : listaStudenti) {
                        if (d.nume.equals(studentName)) {
                            d.mediaNotelorPeste8(d);
                            foundStudent = true;
                        }
                    }

                    System.out.print("\n");

                    if (!foundStudent)
                        System.out.println("Nu exista student cu acest nume.\n");

                    break;
                case '9': //afisare lista studenti
                    afisareListaStudenti(listaStudenti);
                    break;
                case 'x': //iesire din program
                    System.out.println("Aplicatia se va inchide.");
                    afisareMeniu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.");
                    break;

            }
        } while (afisareMeniu);

        if (listaStudenti.size() != 0)
            Serializare.obiectSerializat(listaStudenti, "studenti");
           
        scanner.close();
    }

    private static Student InsertStudent() {
        
        
        Student student = Student.IntroducereStudent();
        nrStudenti++;
        System.out.println("______________________________________________\n");
        System.out.println("Ati introdus urmatorul student: ");
        System.out.println(student.afisareStudent());
        System.out.println("______________________________________________\n");
        
        return student;
    }

    private static void afisareListaStudenti(List<Student> listaStudenti) {
        for (Student stud : listaStudenti) {
            System.out.println(stud.afisareStudent());
            nrStudentiAfisati++;
        }
        System.out.println("\nAu fost afisati "+nrStudentiAfisati+" studenti \n" );
    }
}
