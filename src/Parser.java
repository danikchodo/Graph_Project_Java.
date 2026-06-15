import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.Locale;

public interface Parser{
    void load(File file,Graph graph)throws IOException;
}

class TxtParser implements Parser {
    @Override
    public void load(File file, Graph graph) throws IOException {
        graph.getNodes().clear();
        graph.getEdges().clear();

        try (Scanner sc=new Scanner(file)) {
        sc.useLocale(Locale.US);
            if (!sc.hasNextInt()) 
                return;
            int numNodes=sc.nextInt();
            if (!sc.hasNextInt())
                return;
            int numEdges=sc.nextInt();

        for (int i = 0;i<numNodes;i++) {
                if (!sc.hasNextInt()) break;
                int id=sc.nextInt();
                
                if (!sc.hasNextDouble()) break;
                double x=sc.nextDouble();
                
                if (!sc.hasNextDouble()) break;
                double y=sc.nextDouble();
                
                graph.addNode(new Graph.Node(id,x,y));
            }

            for (int i=0;i<numEdges;i++) {
                if (!sc.hasNextInt()) break;
                int src=sc.nextInt();
                
                if (!sc.hasNextInt()) break;
                int dst=sc.nextInt();
                
                if (!sc.hasNextDouble()) break;
                double weight=sc.nextDouble();
                
                graph.addEdge(new Graph.Edge(src,dst,weight));
            }
        }
    }
}
