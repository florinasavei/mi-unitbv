package AFN;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class AFN {
	public static boolean verificareCuvant(int n, String A, String cuvant) {
		for (int i = 0; i < cuvant.length(); i++)
			if (A.indexOf(cuvant.charAt(i)) < 0)
				return true;
		return false;
	}

	public static boolean verificareFinala(String[] stCurenta, String F) {
		for (int i = 0; i < stCurenta.length; i++)
			if (stCurenta[i] != null)
				if (F.indexOf(stCurenta[i]) >= 0)
					return true;
		return false;
	}

	public static String[] returneazaStare(int n, char a, String[] stCurenta1,
			String[] st1, String[] alf, String[] st2) {
		String[] s = new String[n];
		int k = 0;
		for (int j = 0; j < stCurenta1.length; j++)
			if (stCurenta1[j] != null)
				for (int i = 0; i < n; i++)
					if (st1[i].equals(stCurenta1[j]) == true
							&& alf[i].indexOf(a) >= 0) {
						if (s[0] == null)
							s[k++] = st2[i];
						else if (diferit(s, st2[i]))
							s[k++] = st2[i];
					}
		return s;

	}

	public static boolean diferit(String[] stCurenta, String stare) {
		for (int j = 0; j < stCurenta.length; j++)
			if (stCurenta[j] != null)
				if (stCurenta[j].equals(stare) == true)
					return false;
		return true;
	}

	public static boolean verificare(String[] st1, String[] alf, String[] st2,String F, String q0, String cuvant, int n) 
	{
		String cuv = cuvant;
		String[] stCurenta1 = new String[n];
		stCurenta1[0] = q0;
		String[] stCurenta2 = new String[n];
		for (int i = 0; i < cuvant.length(); i++) {
			try
			{
				stCurenta2 = returneazaStare(n, cuv.charAt(i), stCurenta1, st1,	alf, st2);
			} 
			catch (Exception e) 
			{
				System.out.println("ERROR: " + e.getMessage());
				return false;
			}
			if (i == cuvant.length() - 1 && verificareFinala(stCurenta2, F) == true)
				return true;
			stCurenta1 = stCurenta2;
			stCurenta2 = null;
		}
		return false;
	}

	public static void main(String args[]) throws FileNotFoundException {
		Scanner sc = new Scanner(new FileReader("afn"));
		String Q, A, F, q0;
		Q = sc.nextLine();
		A = sc.nextLine();
		q0 = sc.nextLine();
		F = sc.nextLine();
		int n = Integer.parseInt(sc.nextLine());
		
		String[] st1 = new String[n];
		String[] alf = new String[n];
		String[] st2 = new String[n];
		
		for (int i = 0; i < n; i++) 
		{
			st1[i] = sc.next();
			alf[i] = sc.next();
			st2[i] = sc.next();
		}

		System.out.println("Starile sunt urmatoarele: " + Q);
		System.out.println("Elementele alfabetului sunt: " + A);
		System.out.println("Introdu cuvantul de verificat:");
		Scanner sb = new Scanner(System.in);
		String cuv = sb.nextLine();
		if (verificareCuvant(n, A, cuv) == false)
			if (verificare(st1, alf, st2, F, q0, cuv, n) == true)
				System.out.println("Cuvantul e recunoscut de AFN!");
			else
				System.out.println("Cuvantul NU e recunoscut de AFN!");
	}

}

