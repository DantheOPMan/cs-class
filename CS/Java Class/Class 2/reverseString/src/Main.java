public class Main {
    public static void main(String[] args){

    }
    public static String reverseString(String t){
        if(t.length()<=1){
            return t;
        }
        return reverseString(t.substring(1) + t.charAt(0));
    }
    public static String reverseString2(String t){

        if(t.length() <=1){
            return t;
        }

        return t.charAt(t.length()-1) + reverseString2(t.substring(0, t.length()-1));
    }
}
