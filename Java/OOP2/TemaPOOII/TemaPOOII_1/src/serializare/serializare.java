/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serializare;

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
