import java.io.*;
import java.util.*;
import java.math.*;

public class f {
    public static void main(String args[]) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        int target = Integer.parseInt(st.nextToken());
        long s = 0;
        long v[] = new long[n];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            v[i] = Long.parseLong(st.nextToken());
            s += v[i];
        }

        BigInteger ans = BigInteger.valueOf(Long.MAX_VALUE);
        long cur_h = 0, sv = 0;
        for (int i = 0; i < n; i++) {
            if (cur_h >= target) {
                ans = BigInteger.valueOf(i);
                break;
            }
            BigInteger l = BigInteger.valueOf(0);
            BigInteger r = BigInteger.valueOf((long)2e9);
            while (l.compareTo(r) < 0) {
                BigInteger k = l.add(r).divide(BigInteger.valueOf(2));
                BigInteger aux = k.multiply(BigInteger.valueOf(n)).add(BigInteger.valueOf(i));
                BigInteger h = aux.multiply(aux.add(BigInteger.valueOf(1))).divide(BigInteger.valueOf(2));
                h = h.add(k.multiply(BigInteger.valueOf(s)).add(BigInteger.valueOf(sv)));
                if (h.compareTo(BigInteger.valueOf(target)) >= 0) r = k;
                else l = k.add(BigInteger.ONE);
            }
            BigInteger got = l.multiply(BigInteger.valueOf(n)).add(BigInteger.valueOf(i));
            if (got.compareTo(ans) < 0) ans = got;
            cur_h += v[i] + i + 1;
            sv += v[i];
        }
        out.println(ans);
        out.close();
    }
}
