import java.io.*;
import java.util.regex.*; //Pattern, Matcher si PatternSyntaxException

public class AnalizorLexical{
	static int stareInit=0; //starea initiala
	static int stare=0; //starea curenta
	
	public static void main(String[] args){
		try{
			//citirea se face din fisier
			BufferedReader br=new BufferedReader(new FileReader("sursa.txt"));
			//afisarea rezultatului se face in fisier
			BufferedWriter bw=new BufferedWriter(new FileWriter("FisierRezultat2.txt"));
			//fiecare linie citita apare ca un string
			String linie;
			while ((linie=br.readLine())!=null){
				System.out.println(linie);
				//apelez procedura care desparte linia in tokeni
				//si scrie in fisier tipul unitatilor lexicale
				nextToken(linie,bw);
			}
			br.close();
			bw.close();
		}catch(Exception ex){}
	}
	
	public static boolean getToken(String s){
		// return true daca string este cuv cheie
		
		boolean cuvCheie=false;
		try{
			BufferedReader cuvant=new BufferedReader(new FileReader("CuvinteCheie.txt"));
			String linie;
			//se citeste cate o linie din fis CuvinteCheie.txt
			while ((linie=cuvant.readLine())!=null){
				//verific daca stringurile sunt egale
				if (s.compareTo(linie)==0)
					cuvCheie=true;
			}
			cuvant.close();	
		}catch(Exception exc){}
		return cuvCheie;
	}
	
	public static boolean isLetter(String s){
		//return true daca s este litera
		
		//reprezentare compilatã a unei expresiei regulate
		Pattern pattern=Pattern.compile("[a-zA-Z]");
		//motor care interpreteazã patternul si realizeazã operatiile
		//de potrivire pe un string de intrare
		Matcher matcher=pattern.matcher(s);
		//se apeleazã pentru a realiza o potrivire rapidã
		boolean este=matcher.matches();
		return este;
	}
	
	public static boolean isDigit(String s){
		Pattern pattern=Pattern.compile("[0-9]");
		Matcher matcher=pattern.matcher(s);
		boolean este=matcher.matches();
		return este;
	}
	
	public static int fail(){
		if (stareInit==0)
			stareInit=9;
		else
			if (stareInit==9)
				stareInit=12;
			else
				if (stareInit==12)
					stareInit=0;
		return stareInit;
	}

	public static void nextToken(String linie,BufferedWriter sw){
		//se desparte linia in tokeni
		
		int i=0; //linia
		int inceput=0;
		String c;
		try{
			while (i<=linie.length()){
				if(i==linie.length()){
					String cuvant=linie.substring(inceput, i);
					if (getToken(cuvant)){
						sw.write("Cuvant cheie: "+linie.substring(inceput, i));
						sw.newLine();
					}
					else{
						//daca nu este cuvant, este identificator
						if (isLetter(cuvant)){
							sw.write("Identificator: "+linie.substring(inceput, i));
							sw.newLine();
						}
						else
							sw.write(linie.substring(inceput,i));
					}
					sw.newLine();
					return;
				}
				switch(stare) //starile diagramei de tranzitie
				{
				case 0:
				{
					c=linie.substring(i, i+1)+"";
					if ((c.equals(" "))||(c.equals("\\t"))||(c.equals("\\n")))
					{	
						stare=0;
						inceput=i+1;
						i++;
					}
					else
						if (c.equals("<")){
							stare=1;
							inceput=i+1;
							i++;
						}
						else{
							if (c.equals("=")){
								stare=5;
								inceput=i+1;
								i++;
							}
							else{
								if (c.equals(">")){
									stare=6;
									inceput=i+1;
									i++;
								}
								else
									stare=fail();
							}
						}
					break;
				}
				case 1:
				{
					c=linie.substring(i,i+1);
					if (c.equals("="))	
						stare=2;
					else 
						if (c.equals(">")) 
							stare=3;
						else 
							stare=4;
					break;
				}
				case 2:
				{
					sw.write("Operator relational: <=");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 3:
				{
					sw.write("Operator relational: <>");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 4:
				{
					sw.write("Operator relational: <");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 5:
				{
					sw.write("Operator relational: =");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 6:
				{
					c=linie.substring(i,i+1)+"";
					if (c.equals("="))
						stare=7;
					else
						stare=8;		
					break;
				}
				case 7:
				{
					sw.write("Operator relational: >=");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 8:
				{
					sw.write("Operator relational: >");
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 9:
				{
					c=linie.substring(i,i+1)+"";
					if (isLetter(c))
					{
						stare=10;
						i++;
					}
					else						
						stare=fail();
					break;
				}
				case 10:
				{
					c=linie.substring(i,i+1)+"";
					if (isLetter(c))
					{
						stare=10;
						i++;
					}
					else						
						if (isDigit(c))
						{	
							stare=10;
							i++;
						}
						else
							stare=11;	
					break;
				}
				case 11:
				{
					if(getToken(linie.substring(inceput,i))) 
						 sw.write("Cuvant cheie: "+linie.substring(inceput,i));
					else   
						sw.write("Identificator: "+linie.substring(inceput,i));
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 12:
				{
					c=linie.substring(i,i+1)+"";
					if (isDigit(c))
					{
						stare=13;
						i++;
					}
					else
						stare=fail();
					break;
				}
				case 13:
				{
					c=linie.substring(i,i+1)+"";
					if (isDigit(c))
					{
						stare=13;
						i++;
					}
					else
						if (c.equals("."))
						{
							stare=14;				
							i++;
						}
						else
							if (c.equals("E"))
							{
								stare=16;
								i++;
							}
							else
								stare=27;
					break;
				}
				case 14:
				{
					c=linie.substring(i,i+1)+"";
				 	if (isDigit(c))
					{
				 		stare=15;
				 		i++;
					}
					else
						stare=fail();
					break;
				}
				case 15:
				{
					c=linie.substring(i,i+1)+"";
					if (isDigit(c))
					{
						stare=15;
						i++;
					}
					else
						if (c.equals("E"))
						{
							stare=16;
							i++;
						}
						else 
							stare=24;
					break;
				}
				case 16:
				{
					c=linie.substring(i,i+1)+"";
					if (c.equals("+"))
					{
						stare=17;
						i++;
					}
					else		
						if (c.equals("-"))
						{
							stare=17;
							i++;
						}
						else
							if (isDigit(c))
							{
								stare=18;
								i++;
							}	
							else
								stare=fail();
					break;
				}
				case 17:
				{
					c=linie.substring(i,i+1)+"";
					if (isDigit(c))
					{
						stare=18;
						i++;
					}
					else		
						stare=fail();
					break;
				}
				case 18:
				{
					c=linie.substring(i,i+1)+"";
					if (isDigit(c))
					{
						stare=18;
						i++;
					}
					else																	
						stare=19;
					break;
				}
				case 19:
				{
					sw.write("Numar: "+linie.substring(inceput,i));
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				case 24:
				{
					sw.write("Numar: "+linie.substring(inceput,i));
					sw.newLine();
					sw.newLine();
					stare=0;
					break;
				}
				default:
				{
					sw.write("Numar: "+linie.substring(inceput,i));
					sw.newLine();
					sw.newLine();
					stare=0;
				}
				}
			}
		}catch(Exception exc){System.out.println(exc.getMessage());}
	}
	
}
