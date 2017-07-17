
import java.io.*;
import java.util.*;
import java.awt.geom.*;

/**
 * Solution to Knights
 * 
 * With numbers as large as 10^9, we've got to pursue an O(logn) solution.
 * That means we've got to divide and conquer - chop the corridor in half,
 * figure each half, put them together somehow. Rinse & repeat.
 * 
 * The problem is that the knights can attack across boundaries, 
 * so the separation isn't clean. We'll handle this by using a bitmap to 
 * represent 2 columns of the corridor, and computing, not a single value,
 * but a matrix of values, where result[i][j] is the number of ways
 * to put knights in a stretch of the corridor of size n, which starts
 * with bitmap i and ends with bitmap j.
 * 
 * We'll represent 2 columns of the corridor with a bitmap, like this:
 * 
 *  67
 *  45
 *  23
 *  01
 *  
 *  That way, if the corridor is only one cell wide, we'll use bits 0 and 1.
 *  Two wide, we'll use 0-3. Three wide is 0-5 and 4 wide is 0-7. 
 * 
 * @author vanb
 */
public class knights
{
    public Scanner sc;
    public PrintStream ps;
    
    /** The mod value, so we can generate huge numbers. */
    public static final long MOD = 1000000009L; 
    
    /** 
     * This is a list of bitmaps which will attack themselves.
     * Look at the bitmap in the comments above. If there's a knight
     * at 0 and a knight at 5, they'll attack each other. Also 1-4, 2-7 and 3-6.
     */
    public static final int self[] = 
    { 
        (1<<0)|(1<<5), 
        (1<<1)|(1<<4), 
        (1<<2)|(1<<7), 
        (1<<3)|(1<<6) 
    };
    
    /**
     * This is a list of bitmaps which will attack each other if two of our
     * 2-column bitmaps are placed side-by-side. For example, a knight at 0
     * on the left bitmap will attack a knight at 2 on the right bitmap (and vice versa).
     * LLRR
     * 6767
     * 4545
     * 2323
     * 0101
     */
    public static final int attacks[][] = 
    { 
        {1<<0, 1<<2}, 
        {1<<2, 1<<4}, 
        {1<<4, 1<<6}, 
        {1<<1, 1<<3}, 
        {1<<3, 1<<5}, 
        {1<<5, 1<<7},
        {1<<2, 1<<0}, 
        {1<<4, 1<<2}, 
        {1<<6, 1<<4}, 
        {1<<3, 1<<1}, 
        {1<<5, 1<<3}, 
        {1<<7, 1<<5},
        {1<<1, 1<<4},
        {1<<3, 1<<6},
        {1<<5, 1<<0},
        {1<<7, 1<<2}
    };

    /** Dimensions of the corridor */
    public int n, m;
    
    /** 
     * A boolean array: compatible[i][j] is true iff bitmap i can
     * be placed immediately to the left of bitmap j without them attacking each other.
     */
    public boolean compatible[][];
    
    /** 
     * valid[i] is true iff bitmap i doesn't attack itself
     */
    public boolean valid[];
    
    /** This is the number of bitmaps. */
    public int nmaps;

    /** Memoization to remember results we've already computed. */
    public HashMap<Integer,long[][]> memo = new HashMap<Integer,long[][]>();
    
    /**
     * Compute the number of ways to arrange knights in a corridor m long.
     * Instead of computing one number, it computes a 2d array of numbers.
     * ways[i][j] is the number of ways to arrange knights in a corridor
     * of length m, starting with bitmap i and ending with bitmap j
     * 
     * @param m Length of corridor
     * @return The described matrix
     */
    public long[][] ways( int m )
    {
        long result[][] = memo.get( m );
     
        // If we've already computed this, don't do it again.
        if( result==null )
        {
            result = new long[nmaps][nmaps];
            // We'll chop the corridor in half.
            // Actually, we'll take the two halves PLUS ONE.
            // We'll assume that they overlap by 2 in the middle.
            // So, we'll be looking at first halves that start with bitmap i and end with k.
            // and second halves that start with k and end with j.
            
            // Get the results for the first half +1
            long m1[][] = ways( m/2+1 );
            
            // Get the results for the second half +1
            long m2[][] = ways( m-m/2+1 );
            
            // Put'em together by matrix multiplication
            for( int i=0; i<nmaps; i++ ) if( valid[i] )
            for( int j=0; j<nmaps; j++ ) if( valid[j] ) 
            {
                 result[i][j] = 0;
                 for( int k=0; k<nmaps; k++ ) if( valid[k] ) 
                 {
                     result[i][j] += m1[i][k] * m2[k][j] % MOD;
                     result[i][j] %= MOD;
                 }
            }
            
            // Remember this result!
            memo.put( m, result );
        }

        return result;
    }
           
    /**
     * Driver.
     * @throws Exception
     */
    public void doit() throws Exception
    {
        sc = new Scanner( System.in );
        ps = System.out;

        int t = sc.nextInt();
        while (t-- > 0) {
                               
            n = sc.nextInt();
            m = sc.nextInt();
        
            // here's the total number of bitmaps
            nmaps = 1<<(n<<1);
        
            // See which bitmaps are valid
            valid = new boolean[nmaps];
            Arrays.fill( valid, true );
            for( int i=0; i<nmaps; i++ ) for( int j=0; j<self.length; j++ )
                                         {
                                             // The self[] array holds bad bitmaps.
                                             // if i has both bits of any of those bitmaps,
                                             // then i isn't valid.
                                             valid[i] &= ((i&self[j])!=self[j]);
                                         }
        
            // See which pairs of bitmaps are compatible
            compatible = new boolean[nmaps][nmaps];
            for( int i=0; i<nmaps; i++ ) for( int j=0; j<nmaps; j++ )
                                         {
                                             // To be compatible, both i and j have to be valid!
                                             compatible[i][j] = valid[i] && valid[j];
            
                                             // Look to see of there's any cases where a knight in i
                                             // attacks a knight in j
                                             for( int k=0; k<attacks.length; k++ )
                                             {
                                                 compatible[i][j] &= ((i&attacks[k][0])==0) || ((j&attacks[k][1])==0);
                                             }
                                         }

            // This is the matrix for m==3
            long threes[][] = new long[nmaps][nmaps];
        
            // This is the matrix for m==4
            long fours[][] = new long[nmaps][nmaps];
        
            // Binary 01010101
            int map = 0x55;
            for( int i=0; i<nmaps; i++ ) for( int j=0; j<nmaps; j++ )
                                         {
                                             // if i and j can be put next to each other, then there's 1 way.
                                             // Otherwise, 0.
                                             fours[i][j] = compatible[i][j] ? 1L : 0L;
            
                                             // Threes are a little tricky.
                                             // The odd bits of i have to match the even bits of j,
                                             // and i has to be compatible with the odd bits of j.
                                             //
                                             // ii jj
                                             // 67=67
                                             // 45=45
                                             // 23=23
                                             // 01=01
                                             threes[i][j] = ((i>>1)&map)==(j&map) && compatible[i][(j>>1)&map] ? 1L : 0L;
                                         }
        
            // Put 3s and 4s in the memoization hash
            memo.put( 3, threes );
            memo.put( 4, fours );
        
            long answer = 0L;
        
            if( m==1 )
            {
                // m==1 is a special case. No knights can attack each other,
                // so it's just 2^n
                answer = 1<<n;
            }
            else if( m==2 )
            {
                // m==2 is a special case. It's just the number of valid bitmaps.
                for( int i=0; i<nmaps; i++ ) if( valid[i] ) ++answer;
            }
            else
            {
                // Get the result matrix
                long result[][] = ways( m );
            
                // Add up all of the cases
                for( int i=0; i<nmaps; i++ ) if( valid[i] ) 
                                                 for( int j=0; j<nmaps; j++ ) if( valid[j] )
                                                                              {
                                                                                  answer += result[i][j];
                                                                                  answer %= MOD;
                                                                              }
            }
        
            ps.println( answer );
        }
    }
    
    /**
     * @param args
     */
    public static void main( String[] args ) throws Exception
    {        
        new knights().doit();
    }   
}
