import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

//Class my entry
class MyEntry
{
    private Integer key;
    private String value;

    public MyEntry (Integer key, String value)
    {
        this.key = key;
        this.value = value;
    }
    public Integer getKey ()
    {
        return key;
    }
    public String getValue ()
    {
        return value;
    }
    @Override
    public String toString ()
    {
        return key + " " + value;
    }
}

//Class SkipListPQ
class SkipListPQ
{
    private double alpha;
    private Random rand;
    private MyEntry inf = new MyEntry(Integer.MAX_VALUE, "+inf");
    private MyEntry minf = new MyEntry(Integer.MIN_VALUE, "+inf");
    private MyEntry [][] skip_list;
    private int size;   // numero di entry compreso le sentinelle
    private int h;      // altezza della skip list

    public SkipListPQ (double alpha)
    {
        this.alpha = alpha;
        this.rand = new Random();
        this.skip_list[0][0] = minf;
        this.skip_list[0][1] = inf;
        this.skip_list[1][0] = minf;
        this.skip_list[1][1] = inf;
        this.size = 0;
        this.h = 2;
    }

    public int size ()
    {
        return size;
    }

    public MyEntry min ()
    {
    }

    public int insert (int key, String value)
    {
        int nodes_traversed = 0;
        int p = 0; // position in Si that contains the largest key <= k
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < size + 2; j++)
            {
                if (skip_list[i][j].getKey() < key && skip_list[i][j] != null)
                {
                    p++;
                }
            }
            p--;
        }

        return nodes_traversed;
    }
    /*
    key = 7     p = 2
    -inf                    +inf
    -inf        4           +inf
    -inf    2   4       8   +inf
    -inf    2   4   6   8   +inf
    
    */

    private int generateEll (double alpha_, int key)
    {
        int level = 0;
        if (alpha_ >= 0. && alpha_< 1)
        {
            while (rand.nextDouble() < alpha_)
            {
                level += 1;
            }
        }
        else
        {
            while (key != 0 && key % 2 == 0)
            {
                key = key / 2;
                level += 1;
            }
        }
        return level;
    }

    public MyEntry removeMin()
    {
    }

    public void print()
    {
    }
}

//TestProgram

public class TestProgram1
{
    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.out.println("Usage: java TestProgram <file_path>");
            return;
        }

        try (BufferedReader br = new BufferedReader(new FileReader(args[0])))
        {
            String[] firstLine = br.readLine().split(" ");
            int N = Integer.parseInt(firstLine[0]);
            double alpha = Double.parseDouble(firstLine[1]);
            System.out.println(N + " " + alpha);

            SkipListPQ skipList = new SkipListPQ(alpha);

            for (int i = 0; i < N; i++)
            {
                String[] line = br.readLine().split(" ");
                int operation = Integer.parseInt(line[0]);

                switch (operation)
                {
                    case 0:
                        MyEntry minEntry = skipList.min();
                        if (minEntry != null) {
                            System.out.println("\n" + minEntry);
                        }
                        break;
                    case 1:
                        @SuppressWarnings("unused") MyEntry removedEntry = skipList.removeMin();
                        break;
                    case 2:
                        int key = Integer.parseInt(line[1]);
                        String value = line[2];
                        skipList.insert(key, value);
                        break;
                    case 3:
                        skipList.print();
                        break;
                    default:
                        System.out.println("Invalid operation code");
                        return;
                }
            }
        } catch (IOException e)
        {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}