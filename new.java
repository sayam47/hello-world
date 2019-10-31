import java.util.*;
import java.lang.*;
class CHFINGS{
    public static void main(String args[]){
        Scanner scan = new Scanner(System.in);
        int test = scan.nextInt();
        while(test-->0){
            long num = scan.nextLong();
            long k = scan.nextLong();
            long result = solution(num,k);
            System.out.println(result);
        }
    }
    public static long solution(long num,long k){
        long mod = 1000000007;
        long  a = k;
        long d = num-1;
        long r = (a-2)%(d);
        long second = (1 + (a-2)/d)%mod;
        long first = (a + r)%mod;
        return (first*second/2)%mod;
    }
}
