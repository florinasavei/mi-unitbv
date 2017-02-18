/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serializare;

import java.io.*;

public class Serialize {

    public static void SerializeObject(Object object, String fileName) {

        try {
            File yourFile = new File(fileName + ".ser");

            if (yourFile.exists()) {
                yourFile.delete();
            }

            yourFile.createNewFile(); // if file already exists will do nothing
            FileOutputStream fileOut = new FileOutputStream(yourFile, false);

            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(object);
            out.close();
            fileOut.close();
            System.out.printf("Serialized data is saved in " + fileName + ".ser\n");
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

}
