public class App {
    public static void main(String[] args) throws Exception {
        int x= 1; int n=1000000;
        long start, stop;

        start = System.nanoTime();
        System.out.println(powi(x,n));
        stop = System.nanoTime();
        System.out.println(stop - start);

        start = System.nanoTime();
        System.out.println(powr(x,n));
        stop = System.nanoTime();
        System.out.println(stop - start);

        start = System.nanoTime();
        System.out.println(powl(x,n));
        stop = System.nanoTime();
        System.out.println(stop - start);
    }

    public static int powr(int x, int n){
        if(n == 0){
            return 1;
        }else if(n%2 == 0){
            return powr(x*x, n/2);
        }
        return powr(x*x, n/2) * x;
    }

    public static int powl(int x, int n){
        if(n == 0){
            return 1;
        }
        return powr(x, n) * x;
    }

    public static int powi(int x, int n) {
        int prod = 1;
        while(n--> 0 ){
            prod*=x;
        }
        return prod;
    }
}
