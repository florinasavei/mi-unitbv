
package serializare;

import java.io.*;
import java.util.Scanner;

public class Serializare {
static Scanner raspunsStergere = new Scanner(System.in);
static String seSterge;
 
    public static void obiectSerializat(Object object, String fileName) {

        try {
            File yourFile = new File(fileName + ".bin");

            if (yourFile.exists()) {
                stergereFisier(yourFile);
            }

            yourFile.createNewFile(); // if file already exists will do nothing
            FileOutputStream fileOut = new FileOutputStream(yourFile, false);

            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(object);
            out.close();
            fileOut.close();
            System.out.printf("Datele au fost salvate in fisierul " + fileName + ".bin\n");
        } catch (IOException i) {
            i.printStackTrace();
        }
    }
    
    private static void stergereFisier(File yourFile){
        System.out.println("Fisierul "+yourFile+" exista deja, doriti sa il stergeti? Y/N");
        seSterge=raspunsStergere.nextLine();
        if(seSterge=="Y"){
             yourFile.delete();
            System.out.println("Fisierul " + yourFile + ".bin a fost sters\n");
        }
    }

}
