package serializare;


import java.io.*;

public class Deserializare {

    public static Object ObiectDeserializare(String numeFisier) {

        Object object;

        try {

            File fisierulMeu = new File(numeFisier + ".bin");
            if (!fisierulMeu.exists()) {
                return null;
            }

            FileInputStream fileIn = new FileInputStream(numeFisier + ".bin");
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
