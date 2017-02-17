package Teme.fisier;

import java.io.*;

public class Deserializare {

    public static Object ObiectDeserializare(String fileName) {

        Object object;

        try {

            File yourFile = new File(fileName + ".ser");
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
            System.out.println("Object class not found");
            c.printStackTrace();
            return  null;
        }

        System.out.println("Deserializared...\n");
        return object;
    }

}
