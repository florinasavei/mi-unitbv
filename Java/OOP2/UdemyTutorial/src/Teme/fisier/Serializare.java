 package Teme.fisier;

import java.io.*;

public class Serializare {

    public static void ObiectSerializare(Object object, String fileName) {

        try {
		            File yourFile = new File(fileName + ".ser");
		
		            if (yourFile.exists()) {
		                yourFile.delete();
		            }
		
		            yourFile.createNewFile(); // daca fisierul deja exista nu se intampla nimic
		            FileOutputStream fileOut = new FileOutputStream(yourFile, false);
		
		            ObjectOutputStream out = new ObjectOutputStream(fileOut);
		            out.writeObject(object);
		            out.close();
		            fileOut.close();
		            System.out.printf("Datele salvate in " + fileName + ".ser\n");
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

}
