package src;

import java.util.ArrayList;
import java.util.List;

public class Graph {

    public static class Node {
        public int id;
        public double x, y;

        public Node(int id, double x, double y) {
            this.id=id;
            this.x=x;
            this.y=y;
        }
    }

    public static class Edge {
        public int source_id;
        public int dest_id;
        public double weight;

        public Edge(int source_id,int dest_id,double weight) {
            this.source_id=source_id;
            this.dest_id=dest_id;
            this.weight=weight;
        }
    }

    private List<Node>nodes=new ArrayList<>();
    private List<Edge>edges=new ArrayList<>();

    public void addNode(Node node) { nodes.add(node); }
    public void addEdge(Edge edge) { edges.add(edge); }

    public List<Node> getNodes() { return nodes; }
    public List<Edge> getEdges() { return edges; }
}
