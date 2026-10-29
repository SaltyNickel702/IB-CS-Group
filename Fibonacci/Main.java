public class Main {
    public static void main(String[] args) {
        System.out.println(IsInSequence(35));
    }

    public static int FibIterative(int index) {
        if (index <= 1) {
            return index;
        }
        
        int prev2 = 0;
        int prev1 = 1;
        int current = 0;
        
        for (int i = 2; i <= index; i++) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return current;
    }
    

    public static int FibRecursive(int index) {
        if (index <= 1) {
            return index;
        }
        return FibRecursive(index - 1) + FibRecursive(index - 2);
    }

    public static boolean IsInSequence(int number) {
        if (number < 0) {
            return false;
        } else if (number == 0 || number == 1) {
            return true;
        } else {
            return IsInSequence(number, 1, 1);
        }
    }

    public static boolean IsInSequence(int number, int a, int b) {
        if (number == a + b) {
            return true;
        } else if (number < a) {
            return false;
        } else {
            return IsInSequence(number, a + b, a);
        }
    }
}