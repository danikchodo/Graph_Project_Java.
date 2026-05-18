package src;
import javax.swing.*;
import java.awt.*;

public class GraphPanel extends JPanel {
    private final Graph graph;
    
    private boolean showIds = true;
    private boolean showWeights = true;
    private double zoomFactor = 1.0;
    private int offsetX = 0;
    private int offsetY = 0;

    public GraphPanel(Graph graph) {
        this.graph = graph;
        setBackground(Color.WHITE);
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
//transformacja pola obejrzenia
        g2d.translate(getWidth() / 2.0 + offsetX, getHeight() / 2.0 + offsetY);
        g2d.scale(zoomFactor, zoomFactor);
        g2d.translate(-getWidth() / 2.0, -getHeight() / 2.0); 
