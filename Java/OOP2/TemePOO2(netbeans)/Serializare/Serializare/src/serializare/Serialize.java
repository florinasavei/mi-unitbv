
package serializare;

import java.io.*;

public class Serialize {

    public static void SerializeObject(Object object, String fileName) {

        try {
            File yourFile = new File(fileName + ".bin");

            if (yourFile.exists()) {
                yourFile.delete();
                System.out.println("Fisierul " + fileName + ".bin a fost sters\n");
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

}
