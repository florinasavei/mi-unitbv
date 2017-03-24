package MyPackage;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class Markov {

	public static void main(String[] args) throws FileNotFoundException {
		FileInputStream fis = new FileInputStream("reguli_ex1.txt");
		Scanner cit_fis = new Scanner(fis);
		Scanner cit_cons = new Scanner(System.in);
		
		ArrayList<String> st = new ArrayList<String>();
		ArrayList<String> dr = new ArrayList<String>();
		//int reguli;
		String cuvant;
		
		System.out.print("Cuvantul: ");
		 cuvant=cit_cons.next();
		
		int reguli = Integer.parseInt(cit_fis.nextLine());
		System.out.print("Regulile sunt : ");
		System.out.println(reguli);
		
		for (int i=0; i<reguli; i++)
		{
			st.add(cit_fis.next());
			dr.add(cit_fis.next());
			System.out.println( st.get(i) + " " + dr.get(i));
		}
		
		System.out.println();
		
		cit_fis.close();
		cit_cons.close();
		
		
		for (int i=0; i<reguli; i++)
		{
			if (cuvant.indexOf(st.get(i)) != -1) 
			{
				cuvant = cuvant.replaceFirst(st.get(i), dr.get(i));
				cuvant = cuvant.replaceFirst("lambda", "");
				i=-1; 
			}
		}
		
		System.out.print("Rezultatul final este: " + cuvant);
		
	}

}

