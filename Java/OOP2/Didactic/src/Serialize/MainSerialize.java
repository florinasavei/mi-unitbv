package Serialize;

import java.io.*;

public class MainSerialize {

	public static void main(String[] args) {
		Person arthur=new Person();
		
		arthur.name = "Arthur Dent";
		arthur.age=44;
		
		String fileName="data.bin";
		
		try {
			ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(fileName));
			os.writeObject(arthur); //write object
			os.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace(); 
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("Done writting!");
		
		try {
			ObjectInputStream is = new ObjectInputStream(new FileInputStream(fileName));
			Person p = (Person) is.readObject(); //read object
			System.out.println("Read name="+p.name+ "\nage=" + p.age);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
}
