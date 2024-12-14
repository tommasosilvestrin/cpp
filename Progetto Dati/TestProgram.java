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
    private double alpha;
    private Random rand;
    private List<List<MyEntry>> skip_list;
    private int size;

    public SkipListPQ (double alpha)
    {
        this.alpha = alpha;
        this.rand = new Random();
        this.size = 0;
        this.skip_list = new ArrayList<>();
        skip_list.add(new ArrayList<>());
    }

    public int size ()
    {
        return size;
    }

    public MyEntry min ()
    {
        if (size == 0)
        {
            return null;
        }
        List<MyEntry> bottom_list = skip_list.get(0);
        return bottom_list.get(0);
    }

    public int insert (int key, String value)
    {
        MyEntry new_entry = new MyEntry(key, value);
        int traversed_nodes = 0;

        level_exists(0);
        List<MyEntry> bottom_list = skip_list.get(0);
        int p = SkipSearch(bottom_list, key);
        traversed_nodes += (p + 1);
        
        
        if (p >= bottom_list.size() || !bottom_list.get(p).getKey().equals(key))
        {
            bottom_list.add(p, new_entry);
        }

        int entry_height = generateEll(alpha, key);
        for (int i = 0; i <= entry_height; i++)
        {
            level_exists(i);
            List<MyEntry> current_level = skip_list.get(i);
            p = SkipSearch(current_level, key);
            traversed_nodes += (p + 1);
            
            if (p >= current_level.size() || !current_level.get(p).getKey().equals(key))
            {
                current_level.add(p, new_entry);
            }
        }

        size++;
        return traversed_nodes;
    }

    private void level_exists (int level)
    {
        while (skip_list.size() <= level)
        {
            List <MyEntry> new_level = new ArrayList<>();
            new_level.add(new MyEntry(Integer.MIN_VALUE, "-inf"));
            new_level.add(new MyEntry(Integer.MAX_VALUE, "+inf"));
            skip_list.add(new_level);
        }
    }

    private int SkipSearch (List<MyEntry> list, int key)
    {
        int p = 0;
        while (p < list.size() && list.get(p).getKey() < key)
        {
            p++;
        }
        return p;
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
        if (size == 0)
        {
            return null;
        }

        MyEntry min_entry = min();
        if (min_entry != null)
        {
            for (int i = 0; i < skip_list.size(); i++)
            {
                skip_list.get(i).remove(min_entry);
                if (skip_list.get(i).isEmpty() && i > 0)
                {
                    skip_list.remove(i);
                }
            }
            size--;
        }

        return min_entry;
    }

    public void print()
    {
        List<MyEntry> bottom_list = skip_list.get(0);
        StringBuilder s = new StringBuilder();
        for (MyEntry entry : bottom_list)
        {
            int h = 0;
            for (int i = 0; i < skip_list.size(); i++)
            {
                if (i < skip_list.size() && skip_list.get(i).size() > 0 && skip_list.get(i).contains(entry))
                {
                    h++;
                }
            }
            s.append(entry.getKey()).append(" ").append(entry.getValue()).append(" ").append(h).append(", ");
        }
        s.deleteCharAt(s.length() - 1);
        s.deleteCharAt(s.length() - 1);
        System.out.println(s);
    }
}

//TestProgram

public class TestProgram
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

            SkipListPQ skip_list = new SkipListPQ(alpha);
            int total_inserts = 0;
            int total_traversed = 0;

            for (int i = 0; i < N; i++)
            {
                String[] line = br.readLine().split(" ");
                int operation = Integer.parseInt(line[0]);

                switch (operation)
                {
                    case 0:
                        MyEntry min_entry = skip_list.min();
                        if (min_entry != null) {
                            System.out.println(min_entry);
                        }
                        break;
                    case 1:
                        @SuppressWarnings("unused") MyEntry removedEntry = skip_list.removeMin();
                        break;
                    case 2:
                        int key = Integer.parseInt(line[1]);
                        String value = line[2];
                        int node_traversed = skip_list.insert(key, value);
                        total_traversed += node_traversed;
                        total_inserts++;
                        break;
                    case 3:
                        skip_list.print();
                        break;
                    default:
                        System.out.println("Invalid operation code");
                        return;
                }
            }

            double average_traversed_node = (double) total_traversed / total_inserts;
            System.out.println(alpha + " " + skip_list.size() + " " + total_inserts + " " + average_traversed_node);
        } catch (IOException e)
        {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}