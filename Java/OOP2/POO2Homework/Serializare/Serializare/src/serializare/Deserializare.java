package serializare;

import java.io.*;

public class Deserializare {

    public static Object obiectDeserializat(String fileName) {

        Object object;

        try {

            File yourFile = new File(fileName + ".bin");
            if (!yourFile.exists()) {
                return null;
            }

            try (FileInputStream fileIn = new FileInputStream(fileName + ".bin")) {
                ObjectInputStream in = new ObjectInputStream(fileIn);
                object = in.readObject();
                in.close();
            }

        } catch (IOException i) {
            i.printStackTrace();
            return null;
        } catch (ClassNotFoundException c) {
            c.printStackTrace();
            return  null;
        }

        System.out.println("Deserializare...\n");
        return object;
    }

}
