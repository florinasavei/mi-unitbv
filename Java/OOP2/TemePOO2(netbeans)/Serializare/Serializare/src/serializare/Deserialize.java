package serializare;

import java.io.*;

public class Deserialize {

    public static Object DeserializeObject(String fileName) {

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
            System.out.println("Object class not found");
            c.printStackTrace();
            return  null;
        }

        System.out.println("Deserialized...\n");
        return object;
    }

}
