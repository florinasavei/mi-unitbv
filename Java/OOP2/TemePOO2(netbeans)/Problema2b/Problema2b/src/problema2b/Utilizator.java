package problema2b;


import java.io.Serializable;
import java.util.Scanner;

public class Utilizator implements Serializable {

    public String Nume, Prenume, Email, Username, Password;

    public static Utilizator IntroducereUser(Utilizator user) {

        Scanner reader = new Scanner(System.in);
        boolean correct = false;

        System.out.println("Introduceti numele userului: ");
        user.Nume = reader.nextLine();

        System.out.println("Introduceti prenumele userului: ");
        user.Prenume = reader.nextLine();

        do {

            System.out.println("Introduceti adresa de email: ");
            String email = reader.nextLine();

            if (Main02b.IsEmailValid(email))
            {
                user.Email = email;
                correct= true;
            }
            else
                System.out.println("Email-ul nu este valid.");

        }while (!correct);

        correct = false;

        do {

            System.out.println("Introduceti username-ul: ");
            String username = reader.nextLine();

            if (Main02b.IsUsernameValid(username))
            {
                user.Username = username;
                correct= true;
            }
            else
                System.out.println("Username-ul exista deja. Introduceti unul diferit.");

        } while (!correct);

        correct = false;

        System.out.println("Introduceti password-ul: ");
        user.Password = reader.nextLine();


        do {
            System.out.println("Reintroduceti password-ul: ");
            String confirmPassoword = reader.nextLine();

            if (!confirmPassoword.equals(user.Password))
                System.out.println("Parolele nu sunt identice.");
            else
                correct = true;

        } while (!correct);

        return user;
    }

    public static String ChangePassword()
    {
        Scanner reader = new Scanner(System.in);
        boolean correct = false;

        System.out.println("Introduceti noul password: ");
        String password = reader.nextLine();

        do {
            System.out.println("Confirma password: ");
            String confirmPassoword = reader.nextLine();

            if (!confirmPassoword.equals(password))
                System.out.println("Parolele nu sunt identice.");
            else
            {
                correct = true;
            }

        } while (!correct);

        return password;
    }
}
