/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package problema2b;


import java.io.Serializable;
import java.util.Random;
import java.util.Scanner;

public class Produs implements Serializable {
    private int identifier;
    private String Username;
    int Cantitate;
    String Nume;
    double Pret;

    Integer getId() {
        return identifier;
    }

    String getVendor() {
        return Username;
    }

    private void setVendor(String x) {
        this.Username = x;
    }

    public Produs() {
        Random ran = new Random();
        this.identifier = 100000 + ran.nextInt(900000);
    }

    public static Produs InsertProduct(String username, String name) {

        Scanner reader = new Scanner(System.in);
        boolean correct = false;

        Produs product = new Produs();
        product.setVendor(username);

        product.Nume = name;

        System.out.println("Introduceti pretul: ");
        product.Pret = Double.parseDouble(reader.nextLine());

        System.out.println("Introduceti cantitatea: ");
        product.Cantitate = Integer.parseInt(reader.nextLine());

        return product;
    }

    public static void afisareProduseVanzator(String username) {
        System.out.println("LISTA DE PRODUSE PENTRU " + username + ":");
        String leftAlignFormat = "| %-2d | %-15s | %-14.2f | %-13d |%n";

        System.out.format("+--------+-----------------+----------------+---------------+%n");
        System.out.format("| Id     | Nume            | Pret           | Cantitate     |%n");
        System.out.format("+--------+-----------------+----------------+---------------+%n");
        for (Produs p : Main02b.listaProduse) {
            if (p.Username.equals(username))
                System.out.format(leftAlignFormat, p.getId(), p.Nume, p.Pret, p.Cantitate);
        }
        System.out.format("+---------+----------------+----------------+---------------+%n");

        System.out.println("\n");
    }

    public static void GetProductById(int id) {

        System.out.println("LISTA DE PRODUSE CU CODUL: " + id + ":");
        String leftAlignFormat = "| %-2d | %-15s | %-16s | %-14.2f | %-13d |%n";

        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        System.out.format("| Id     | Nume            | Vanzator         | Pret           | Cantitate     |%n");
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        for (Produs p : Main02b.listaProduse) {
            if (p.getId().equals(id))
                System.out.format(leftAlignFormat, p.getId(), p.Nume, p.Username, p.Pret, p.Cantitate);
        }
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");

        System.out.println("\n");
    }

    public static void GetProductByName(String name) {

        System.out.println("LISTA DE PRODUSE CU NUMELE: " + name + ":");
        String leftAlignFormat = "| %-2d | %-15s | %-16s | %-14.2f | %-13d |%n";

        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        System.out.format("| Id     | Nume            | Vanzator         | Pret           | Cantitate     |%n");
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");
        for (Produs p : Main02b.listaProduse) {
            if (p.Nume.toLowerCase().contains(name.toLowerCase()))
                System.out.format(leftAlignFormat, p.getId(), p.Nume, p.Username, p.Pret, p.Cantitate);
        }
        System.out.format("+--------+-----------------+------------------+----------------+---------------+%n");

        System.out.println("\n");

    }

    public static boolean BuyProduct(int id, int quantity) {
        boolean bought = false;

        for (Produs p : Main02b.listaProduse) {
            if (p.getId().equals(id)) {
                if (quantity <= p.Cantitate) {
                    p.Cantitate -= quantity;
                    System.out.println("Achizitie efectuata cu succes.\n");
                    double total = quantity * p.Pret;
                    System.out.println("Totalul este: " + total + " RON.\n");
                    bought = true;
                } else
                    System.out.format("Stocul este insuficient pentru cantitatea introdusa sau codul introdus este incorect.\n");
            }
        }

        if (bought)
            return true;
        else
            return false;
    }
}
