// Merkins William
// Chpt2 PA

import java.util.Scanner;

public class reverseString {

    // Recursive method to reverse a string
    public static String reverseString(String str) {
        // Base case: if the string is empty or has only one character
        if (str == null || str.length() <= 1) {
            return str;
        }

        // Move the first character to the end and recurse with the remaining substring
        return reverseString(str.substring(1)) + str.charAt(0);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Prompt user for input
        System.out.print("Enter the string to be reversed: ");
        String inputStr = scanner.nextLine();

        // Limit input to 20 characters
        if (inputStr.length() > 20) {
            inputStr = inputStr.substring(0, 20);
        }

        // Reverse the string using recursion
        String reversedStr = reverseString(inputStr);

        // Print the reversed string
        System.out.println("Reversed: " + reversedStr);

        scanner.close();
    }
}