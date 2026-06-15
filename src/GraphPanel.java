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

    private Point lastMousePosition;

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
    public void resetView() { this.zoomFactor=1.0;this.offsetX=0;this.offsetY = 0;repaint(); }
@Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);


        if (graph.getNodes().isEmpty()) {
            g2d.setColor(Color.LIGHT_GRAY);
            g2d.setFont(new Font("Arial",Font.PLAIN, 16));
            String msg="Kliknij algorytm, aby zaladowac.";
            int msgWidth=g2d.getFontMetrics().stringWidth(msg);
            g2d.drawString(msg,(getWidth()-msgWidth)/2, getHeight()/2);
            return;
        }

        double minX=Double.MAX_VALUE,maxX=-Double.MAX_VALUE;
        double minY=Double.MAX_VALUE,maxY=-Double.MAX_VALUE;
        for (Graph.Node node:graph.getNodes()) {
            if (node.x<minX) minX=node.x;
            if (node.x>maxX) maxX=node.x;
            if (node.y<minY) minY=node.y;
            if (node.y>maxY) maxY=node.y;
        }

        double graphWidth=maxX-minX;
        double graphHeight=maxY-minY;
        if (graphWidth==0)graphWidth=1;
        if (graphHeight==0)graphHeight=1;


        boolean autoScale=(maxX <= 10.0 && maxY <= 10.0);
        double scaleX=autoScale?(getWidth()*0.8)/graphWidth:1.0;
        double scaleY=autoScale?(getHeight()*0.8)/graphHeight:1.0;
        double currentScale=Math.min(scaleX, scaleY);

        g2d.translate(getWidth()/2.0+offsetX,getHeight()/2.0+offsetY);
        g2d.scale(zoomFactor,zoomFactor);
        g2d.translate(-getWidth()/2.0,-getHeight()/2.0); 

        java.util.Map<Integer,Graph.Node> nodeMap=new java.util.HashMap<>();
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
               
                int x1 = autoScale ? (int)((src.x-minX)*currentScale+getWidth()*0.1) : (int)src.x;
                int y1 = autoScale ? (int)((src.y-minY)*currentScale+getHeight()*0.1) : (int)src.y;
                int x2 = autoScale ? (int)((dst.x-minX)*currentScale+getWidth()*0.1) : (int)dst.x;
                int y2 = autoScale ? (int)((dst.y-minY)*currentScale+getHeight()*0.1) : (int)dst.y;

                g2d.drawLine(x1,y1,x2,y2);
               if (showWeights){
                    g2d.setColor(Color.BLUE);
                    int midX=(x1+x2)/2;
                    int midY=(y1+y2)/2;
                    g2d.drawString(String.format("%.1f",edge.weight),midX+5,midY-5);
                    g2d.setColor(Color.GRAY);
                }
            }
        }

        for (Graph.Node node:graph.getNodes()) {
            int nx=autoScale ?(int)((node.x-minX)*currentScale+getWidth()*0.1):(int)node.x;
            int ny=autoScale ?(int)((node.y-minY)*currentScale+getHeight()*0.1):(int)node.y;

            g2d.setColor(new Color(70, 130, 180));
            g2d.fillOval((int)nx-nodeRadius, (int)ny-nodeRadius,nodeRadius*2,nodeRadius*2);

   
            g2d.setColor(Color.DARK_GRAY);
            g2d.drawOval((int)nx-nodeRadius,(int)ny-nodeRadius,nodeRadius*2,nodeRadius*2);
            if (showIds){
                g2d.setColor(Color.WHITE);
                g2d.setFont(new Font("Arial", Font.BOLD, 12));
                String idStr=String.valueOf(node.id);
                
                FontMetrics fm = g2d.getFontMetrics();
                int textX=(int)nx-fm.stringWidth(idStr)/2;
                int textY=(int)ny+fm.getAscent()/2 - 2;
                g2d.drawString(idStr,textX,textY);
            }
        }
    } 
} 
