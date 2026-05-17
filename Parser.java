import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public interface Parser{
    void load(File file,Graph graph)throws IOException;
}

class TxtParser implements Parser {
    @Override
    public void load(File file, Graph graph) throws IOException {
        graph.getNodes().clear();
        graph.getEdges().clear();

        try (Scanner sc=new Scanner(file)) {
            if (!sc.hasNextInt()) 
                return;
            
            int numNodes=sc.nextInt();
            int numEdges=sc.nextInt();

            for (int i=0;i<numNodes;i++) {
                int id=sc.nextInt();
                double x=sc.nextDouble();
                double y=sc.nextDouble();
                graph.addNode(new Graph.Node(id,x,y));
            }

            for (int i=0;i<numEdges; i++) {
                int src=sc.nextInt();
                int dst=sc.nextInt();
                double weight=sc.nextDouble();
                graph.addEdge(new Graph.Edge(src,dst,weight));
            }
        }
    }
}
