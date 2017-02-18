package serializare;

import java.io.*;
import java.util.Scanner;

public class Serializare {

    public static void ObiectSerializare(Object object, String numeFisier) {
                Scanner intrebare = new Scanner(System.in);

        try {
		            File fisierulMeu = new File(numeFisier + ".bin");
		
		            if (fisierulMeu.exists()) {
                                System.out.println("Exista deja un fisier cu acelasi nume, doriti sa il stergeti? (y/n)");
                                String stergere=intrebare.nextLine();
                                stergere =stergere.toLowerCase().substring(0,1);//va lua prima litera si o va converti in litera mica
                                if (stergere=="y"){
                                    fisierulMeu.delete();  //daca fisierul exista,se va sterge
                                }
		            }
		
		            fisierulMeu.createNewFile(); //Metoda createNewFile() din clasa File.java
		            FileOutputStream fileOut = new FileOutputStream(fisierulMeu, false);
		
		            ObjectOutputStream out = new ObjectOutputStream(fileOut);
		            out.writeObject(object);
		            out.close();
		            fileOut.close();
		            System.out.printf("Informatiile au fost salvae in fisierul " + numeFisier + ".bin\n");
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

}
