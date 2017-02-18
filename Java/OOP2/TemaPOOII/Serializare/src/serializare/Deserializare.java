package serializare;


import java.io.*;

public class Deserializare {

    public static Object ObiectDeserializare(String fileName) {

        Object object;

        try {

            File yourFile = new File(fileName + ".bin");
            if (!yourFile.exists()) {
                return null;
            }

            FileInputStream fileIn = new FileInputStream(fileName + ".ser");
            ObjectInputStream in = new ObjectInputStream(fileIn);
            object = in.readObject();
            in.close();
            fileIn.close();

        } catch (IOException i) {
            i.printStackTrace();
            return null;
        } catch (ClassNotFoundException c) {
            System.out.println("Clasa obiectului nu exista");
            c.printStackTrace();
            return  null;
        }

        System.out.println("Deserializare...\n");
        return object;
    }

}
