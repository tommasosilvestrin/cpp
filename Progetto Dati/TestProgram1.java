import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

//Class my entry
class MyEntry
{
    private Integer key;
    private String value;
    public int entry_size;

    public MyEntry (Integer key, String value)
    {
        this.key = key;
        this.value = value;
        this.entry_size = 1;
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
    private double alpha;                                                   // head probability of a coin toss
    private Random rand;
    private int h;                                                          // number of lists Si
    private int size;                                                       // number of entries in S0
    private MyEntry inf = new MyEntry(Integer.MAX_VALUE, "+inf");
    private MyEntry minf = new MyEntry(Integer.MIN_VALUE, "-inf");
    private MyEntry [] entries;                                             // array with all the entries

    public SkipListPQ (double alpha)
    {
        this.alpha = alpha;
        this.rand = new Random();
        this.h = 1;
        this.size = 0;
        this.entries = new MyEntry [] {minf, inf};
    }

    public int size ()
    {
        return size;
    }

    public MyEntry min ()
    {
        if (size == 0)
        {
            return entries[0];
        }
        return entries[1];
    }

    public int insert (int key, String value)
    {
        MyEntry new_entry = new MyEntry(key, value);
        MyEntry [] new_entries = new MyEntry [entries.length + 1];
        int i = 1;
        while (i < entries.length && entries[i].getKey() < new_entry.getKey())
        {
            i++;
        }
        for (int j = 0; j < i; j++)
        {
            new_entries[j] = entries[j];
        }
        new_entries[i] = new_entry;
        size++;
        for (int j = i + 1; j < new_entries.length; j++)
        {
            new_entries[j] = entries[j - 1];
        }
        entries = new_entries;
        entries[i].entry_size = generateEll(this.alpha, new_entry.getKey());
        if (entries[i].entry_size > h - 1)
        {
            h = entries[i].entry_size + 1;
        }
        
        return key;
    }

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
        MyEntry min_entry = entries[1];
        MyEntry [] new_entries = new MyEntry[entries.length - 1];
        new_entries[0] = entries[0];
        for (int i = 1; i < new_entries.length; i++)
        {
            new_entries[i] = entries[i + 1];
        }
        entries = new_entries;
        if (min_entry.entry_size == h - 1)
        {
            h = entries[1].entry_size + 1;
            for (int i = 2; i < entries.length - 1; i++)
            {
                if (entries[i].entry_size > entries[i - 1].entry_size)
                {
                    h = entries[i].entry_size;
                }
            }
        }
        return min_entry;
    }

    public void print()
    {
        for (int i = 1; i < entries.length - 1; i++)
        {
            System.out.print(entries[i].getKey() + " " + entries[i].getValue() + " " + (entries[i].entry_size + 1) + ", ");
        }
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