package src;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;
import java.util.Map;

    public class GraphPanel extends JPanel {
    private final Graph graph;
    
    private boolean showIds = true;
    private boolean showWeights = true;
    private double zoomFactor = 1.0;
    private int offsetX = 0;
    private int offsetY = 0;

    private Point

    public GraphPanel(Graph graph) {
        this.graph = graph;
        setBackground(Color.WHITE);

        addMouseListener(new MouseAdapter(){
            @Override 
            public void mousePressed(MouseEvent e){
                lastMousePosition=e.getPoint();
            }
        });
        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (lastMousePosition!=null) {
                    int deltaX=e.getX()-lastMousePosition.x;
                    int deltaY=e.getY()-lastMousePosition.y;
                    offsetX+=deltaX;
                    offsetY+=deltaY;
                    lastMousePosition=e.getPoint();
                    repaint();
            }
        });
        addMouseWheelListener(new MouseWheelListener(){
            @Override
            public void mouseWheelMoved(MouseWheelEvent e){
                if (e.getWheelRotation() < 0) {
                    changeZoom(1.1); 
                }else{
                    changeZoom(0.9); 
                }
            }
        });
    }
//zmiana stanu paneli
    public void setShowIds(boolean showIds) { this.showIds = showIds; repaint(); }
    public void setShowWeights(boolean showWeights) { this.showWeights = showWeights; repaint(); }
    public void changeZoom(double factor) { this.zoomFactor *= factor; repaint(); }
    public void resetView() { this.zoomFactor = 1.0; this.offsetX = 0; this.offsetY = 0; repaint(); }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.translate(getWidth()/2.0+offsetX, getHeight() / 2.0 + offsetY);
        g2d.scale(zoomFactor, zoomFactor);
        g2d.translate(-getWidth()/2.0,-getHeight()/ 2.0); 


        java.util.Map<Integer, Graph.Node> nodeMap = new java.util.HashMap<>();
        for (Graph.Node node:graph.getNodes()) {
            nodeMap.put(node.id, node);
        }

        int nodeRadius=15; 

        g2d.setColor(Color.GRAY);
        g2d.setStroke(new BasicStroke(2)); 
        for (Graph.Edge edge:graph.getEdges()) {
            Graph.Node src=nodeMap.get(edge.source_id);
            Graph.Node dst=nodeMap.get(edge.dest_id);

            if (src != null && dst != null) {
                g2d.drawLine((int)src.x,(int)src.y,(int)dst.x,(int)dst.y);

                if (showWeights) {
                    g2d.setColor(Color.BLUE);
                    int midX=(int) ((src.x + dst.x)/2);
                    int midY=(int) ((src.y + dst.y)/2);
                    g2d.drawString(String.format("%.1f",edge.weight),midX + 5,midY - 5);
                    g2d.setColor(Color.GRAY); 
                }
            }
        }

        for (Graph.Node node:graph.getNodes()) {
            g2d.setColor(new Color(70, 130, 180));
            g2d.fillOval((int)node.x-nodeRadius, (int)node.y-nodeRadius,nodeRadius*2,nodeRadius* 2);

   
            g2d.setColor(Color.DARK_GRAY);
            g2d.drawOval((int)node.x-nodeRadius,(int)node.y-nodeRadius,nodeRadius*2,nodeRadius * 2);
            if (showIds){
                g2d.setColor(Color.WHITE);
                g2d.setFont(new Font("Arial", Font.BOLD, 12));
                String idStr=String.valueOf(node.id);
                
                FontMetrics fm = g2d.getFontMetrics();
                int textX=(int)node.x-fm.stringWidth(idStr)/2;
                int textY=(int)node.y+fm.getAscent()/2 - 2;
                g2d.drawString(idStr,textX,textY);
            }
        }
    } 
} 
