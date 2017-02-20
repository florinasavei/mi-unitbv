package problema2b;


import java.util.Scanner;

import serializare.*;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main02b {

    static List<Utilizator> listaUtilizatori;
    static List<Produs> listaProduse;

    public static void main(String[] args) {
        boolean afisareMeniu = true;
        Scanner scanner = new Scanner(System.in);

        if (!incarcaListaUtilizatoriDinFisier())
            listaUtilizatori = new ArrayList<Utilizator>();
        else
            afisareListaUtilizatori();

        if (!incarcaListaProduseDinFisier())
            listaProduse = new ArrayList<Produs>();
        else
            afisareListaProduse(); 

        do {
          
            Meniu meniuPrincipal = new Meniu();
            meniuPrincipal.afisareMeniuPrincipal();

            int optiune = Integer.parseInt(scanner.nextLine());

            switch (optiune) {
                case 1:
                    System.out.println("Username:");
                    String username = scanner.nextLine();

                    System.out.println("Parola:");
                    String password = scanner.nextLine();

                    if (!Autentificare(username, password))
                        System.out.println("Autentificare esuata.");

                    break;
                case 2:
                    System.out.println("Alegeti tipul de utilizator:");
                    System.out.println("1 - Vanzator.");
                    System.out.println("2 - Cumparator.");

                    int tipUtilizator = Integer.parseInt(scanner.nextLine());
                    Utilizator user;

                    if (tipUtilizator == 1)
                        user = new Vanzator();
                    else if (tipUtilizator == 2)
                        user = new Cumparator();
                    else {
                        System.out.println("Optiunea nu este valida.");
                        user = null;
                    }

                    if (user != null) {
                        listaUtilizatori.add(Utilizator.IntroducereUser(user));
                        reincarcaListaUtilizatori();
                    }
                    break;
                case 3:
                    afisareListaUtilizatori();
                    break;
                case 4:
                    System.out.println("Aplicatia se va inchide.");
                    afisareMeniu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.");
                    break;
            }
        }
        while (afisareMeniu);

        salveazaListaUtilizatoriInFisier();
        salveazaListaProuseinFisier();

        scanner.close();
    }

    public static void reincarcaListaUtilizatori() {
        salveazaListaUtilizatoriInFisier();
        incarcaListaUtilizatoriDinFisier();
    }

    public static void salveazaListaUtilizatoriInFisier() {
        try {
            if (listaUtilizatori.size() != 0)
                Serializare.obiectSerializat(listaUtilizatori, "utilizatori");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean incarcaListaUtilizatoriDinFisier() {

        try {

            Object deserialized = Deserializare.obiectDeserializat("utilizatori");

            if (deserialized != null) {
                listaUtilizatori = (List<Utilizator>) deserialized;
            } else {
                System.out.println("Nu exista niciun user.\n");
                return false;
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        return true;
    }

    public static void reincarvaListaProduse() {
        salveazaListaProuseinFisier();
        incarcaListaProduseDinFisier();
    }

    public static void salveazaListaProuseinFisier() {
        try {
            if (listaProduse.size() != 0)
                Serializare.obiectSerializat(listaProduse, "produse");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean incarcaListaProduseDinFisier() {

        try {

            Object deserialized = Deserializare.obiectDeserializat("produse");

            if (deserialized != null) {
                listaProduse = (List<Produs>) deserialized;
            } else {
                System.out.println("Nu exista niciun produs.\n");
                return false;
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        return true;
    }

    private static void afisareListaUtilizatori() {
        System.out.println("LISTA USERI:");
        String leftAlignFormat = "| %-15s | %-15s | %-16s | %-15s | %-20s |%n";

        System.out.format("+-----------------+-----------------+------------------+-----------------+----------------------+%n");
        System.out.format("| Nume            | Prenume         | Username         | Tip User        | Email                |%n");
        System.out.format("+-----------------+-----------------+------------------+-----------------+----------------------+%n");
        for (Utilizator d : listaUtilizatori) {
            if(d instanceof Cumparator)
            System.out.format(leftAlignFormat, d.Nume, d.Prenume, d.Username, "Cumparator", d.Email);
            if(d instanceof Vanzator)
                System.out.format(leftAlignFormat, d.Nume, d.Prenume, d.Username, "Vanzator", d.Email);
        }
        System.out.format("+-----------------+-----------------+------------------+-----------------+----------------------+%n");

        System.out.println("\n");
    }

    private static void afisareListaProduse() {
        System.out.println("LISTA DE PRODUSE:");
        String leftAlignFormat = "| %-2d | %-15s | %-16s | %-14.2f | %-13d |%n";

        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        System.out.format("| Id     | Nume            | Vanzator         | Pret           | Cantitate     |%n");
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        for (Produs p : listaProduse) {
            System.out.format(leftAlignFormat, p.getId(), p.Nume, p.getVendor(),p.Pret, p.Cantitate);
        }
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");

        System.out.println("\n");
    }

    private static void PrintAvailableProductList() {
        System.out.println("Lista de Produse:");
        System.out.println("=================================================================================");
        String leftAlignFormat = "| %-2d | %-15s | %-16s | %-14.2f | %-13d |%n";

        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        System.out.format("| Id     | Nume            | Vanzator         | Pret           | Cantitate     |%n");
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        for (Produs p : listaProduse) {
            if (p.Cantitate > 0)
                System.out.format(leftAlignFormat, p.getId(), p.Nume, p.getVendor(), p.Pret, p.Cantitate);
        }
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");

        System.out.println("\n");
    }

    public static boolean validareUsername(String username) {

        for (Utilizator d : listaUtilizatori)
            if (d.Username.equals(username))
                return false;

        return true;
    }

    public static boolean validareProdus(String name) {

        for (Produs p : listaProduse)
            if (p.Nume.toLowerCase().equals(name.toLowerCase()))
                return true;

        return false;
    }

    public static final Pattern VALID_EMAIL_ADDRESS_REGEX =
            Pattern.compile("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,6}$", Pattern.CASE_INSENSITIVE);

    public static boolean validareEmail(String emailStr) {
        Matcher matcher = VALID_EMAIL_ADDRESS_REGEX.matcher(emailStr);
        return matcher.find();
    }

    public static boolean Autentificare(String username, String password) {

        boolean found = false;

        for (Utilizator d : listaUtilizatori) {
            if (d.Username.equals(username) &&
                    d.Password.equals(password)) {

                System.out.println("Autentificare cu succes.\n");
                found = true;

                if (d instanceof Vanzator)
                    meniuVanzator(d);
                else if (d instanceof Cumparator)
                    BuyerMenu(d);
            }
        }

        if (found)
            return true;
        else
            return false;
    }

    public static void meniuVanzator(Utilizator user) {

        boolean menu = true;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bine ai venit " + user.Nume + " " + user.Prenume + "!\n");

        do {
            
            Meniu meniuVanzator=new Meniu();
            meniuVanzator.afisareMeniuVanzator();

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    System.out.println("Introduceti numele produslui: ");
                    String newProduct = scanner.nextLine();

                    if(validareProdus(newProduct))
                    {
                        System.out.println("Produsul exista deja, adaugati o cantitate la cel deja existent: ");
                        for (Produs p : listaProduse) {
                            if (p.Nume.toLowerCase().equals(newProduct.toLowerCase()))
                            {
                                p.Cantitate += Integer.parseInt(scanner.nextLine());
                            }
                        }
                    }
                    else
                    {
                    listaProduse.add(Produs.InsertProduct(user.Username, newProduct));
                    }
                    reincarvaListaProduse();
                    break;
                case 2:
                    Produs.afisareProduseVanzator(user.Username);
                    break;
                case 3:
                    for (Utilizator u : listaUtilizatori) {
                        if (u.Username.equals(user.Username))
                            u.Password = Utilizator.ChangePassword();
                    }
                    break;
                case 4:
                    System.out.println("Vei fi deloghat.\n");
                    menu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.\n");
                    break;
            }
        } while (menu);

    }

    public static void BuyerMenu(Utilizator user) {

        boolean meniuCumparare = true;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bine ai venit " + user.Nume + " " + user.Prenume + "!\n");

        do {
            System.out.println("1 - Vizualizare produse.");
            System.out.println("2 - Cautare produs dupa cod.");
            System.out.println("3 - Cautare produs dupa denumire.");
            System.out.println("4 - Cumparare produs.");
            System.out.println("5 - Deloghare.");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    PrintAvailableProductList();
                    break;
                case 2:
                    System.out.println("Introduceti codul produsului cautat.");
                    int productCode = Integer.parseInt(scanner.nextLine());
                    Produs.GetProductById(productCode);
                    break;
                case 3:
                    System.out.println("Introduceti numele produsului cautat.");
                    String productName = scanner.nextLine();
                    Produs.GetProductByName(productName);
                    break;
                case 4:
                    System.out.println("Introduceti codul produsului pe care doriti sa il cumparati.");
                    int buyCode = Integer.parseInt(scanner.nextLine());

                    System.out.println("Introduceti cantitatea dorita.");
                    int buyQuantity = Integer.parseInt(scanner.nextLine());

                    if (Produs.BuyProduct(buyCode, buyQuantity))
                        reincarvaListaProduse();

                    break;
                case 5:
                    System.out.println("Vei fi deloghat.\n");
                    meniuCumparare = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.\n");
                    break;
            }
        } while (meniuCumparare);

    }
}

