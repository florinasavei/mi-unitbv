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
        boolean menu = true;
        Scanner scanner = new Scanner(System.in);

        if (!LoadUserListFromFile())
            listaUtilizatori = new ArrayList<Utilizator>();
        else
            PrintUserList();

        if (!LoadProductListFromFile())
            listaProduse = new ArrayList<Produs>();
        else
            PrintProductList();

        do {
            System.out.println("1 - Autentificare.");
            System.out.println("2 - Creare cont nou.");
            System.out.println("3 - Lista useri.");
            System.out.println("4 - Inchidere Aplicatie.");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    System.out.println("Username:");
                    String username = scanner.nextLine();

                    System.out.println("Password:");
                    String password = scanner.nextLine();

                    if (!Authentify(username, password))
                        System.out.println("Autentificare esuata.");

                    break;
                case 2:
                    System.out.println("Alegeti tipul de utilizator:");
                    System.out.println("========================\n");
                    System.out.println("1 - Vanzator.");
                    System.out.println("2 - Cumparator.");

                    int type = Integer.parseInt(scanner.nextLine());
                    Utilizator user;

                    if (type == 1)
                        user = new Vanzator();
                    else if (type == 2)
                        user = new Cumparator();
                    else {
                        System.out.println("Optiunea nu este valida.");
                        user = null;
                    }

                    if (user != null) {
                        listaUtilizatori.add(Utilizator.IntroducereUser(user));
                        RefreshUserList();
                    }
                    break;
                case 3:
                    PrintUserList();
                    break;
                case 4:
                    System.out.println("Aplicatia se va inchide.");
                    menu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.");
                    break;
            }
        }
        while (menu);

        SaveUserListToFile();
        SaveProductListToFile();

        scanner.close();
    }

    public static void RefreshUserList() {
        SaveUserListToFile();
        LoadUserListFromFile();
    }

    public static void SaveUserListToFile() {
        try {
            if (listaUtilizatori.size() != 0)
                Serialize.SerializeObject(listaUtilizatori, "users");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean LoadUserListFromFile() {

        try {

            Object deserialized = Deserialize.DeserializeObject("users");

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

    public static void RefreshProductList() {
        SaveProductListToFile();
        LoadProductListFromFile();
    }

    public static void SaveProductListToFile() {
        try {
            if (listaProduse.size() != 0)
                Serialize.SerializeObject(listaProduse, "products");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean LoadProductListFromFile() {

        try {

            Object deserialized = Deserialize.DeserializeObject("products");

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

    private static void PrintUserList() {
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

    private static void PrintProductList() {
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

    public static boolean IsUsernameValid(String username) {

        for (Utilizator d : listaUtilizatori)
            if (d.Username.equals(username))
                return false;

        return true;
    }

    public static boolean DoesProductExists(String name) {

        for (Produs p : listaProduse)
            if (p.Nume.toLowerCase().equals(name.toLowerCase()))
                return true;

        return false;
    }

    public static final Pattern VALID_EMAIL_ADDRESS_REGEX =
            Pattern.compile("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,6}$", Pattern.CASE_INSENSITIVE);

    public static boolean IsEmailValid(String emailStr) {
        Matcher matcher = VALID_EMAIL_ADDRESS_REGEX.matcher(emailStr);
        return matcher.find();
    }

    public static boolean Authentify(String username, String password) {

        boolean found = false;

        for (Utilizator d : listaUtilizatori) {
            if (d.Username.equals(username) &&
                    d.Password.equals(password)) {

                System.out.println("Autentificare cu succes.\n");
                found = true;

                if (d instanceof Vanzator)
                    VendorMenu(d);
                else if (d instanceof Cumparator)
                    BuyerMenu(d);
            }
        }

        if (found)
            return true;
        else
            return false;
    }

    public static void VendorMenu(Utilizator user) {

        boolean menu = true;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bine ai venit " + user.Nume + " " + user.Prenume + "!\n");

        do {
            System.out.println("1 - Adaugare produs.");
            System.out.println("2 - Vizualizare produse proprii.");
            System.out.println("3 - Schimbare parola.");
            System.out.println("4 - Deloghare.");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    System.out.println("Introduceti numele produslui: ");
                    String newProduct = scanner.nextLine();

                    if(DoesProductExists(newProduct))
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
                    RefreshProductList();
                    break;
                case 2:
                    Produs.ViewProductsByVendor(user.Username);
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

        boolean menu = true;
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
                        RefreshProductList();

                    break;
                case 5:
                    System.out.println("Vei fi deloghat.\n");
                    menu = false;
                    break;
                default:
                    System.out.println("Introduceti o optiune valida.\n");
                    break;
            }
        } while (menu);

    }
}

