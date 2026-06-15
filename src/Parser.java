package src;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.Locale;


public class Parser {
    public void load(File file, Graph graph) throws IOException {
        graph.getNodes().clear();

        try (Scanner sc=new Scanner(file)) {
        sc.useLocale(Locale.US);
        while (sc.hasNext()) {
                if (!sc.hasNextInt()) {
                    sc.next();
                    continue;
                }
                int id = sc.nextInt();
                
                if (!sc.hasNextDouble()) break;
                double x = sc.nextDouble();
                
                if (!sc.hasNextDouble()) break;
                double y = sc.nextDouble();
                
                graph.addNode(new Graph.Node(id, x, y));
            }
        }
    }
}
