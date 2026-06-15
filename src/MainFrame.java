package src;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class MainFrame extends JFrame {

    public MainFrame() {
      private Graph graph;
    private GraphPanel graphPanel;

    public MainFrame() {
        super("Vizualizer graphu");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1024, 768);
        setLocationRelativeTo(null);

        graph=new Graph();
        loadGraphEdges();

        graphPanel=new GraphPanel(graph);
        add(graphPanel, BorderLayout.CENTER);

        JPanel topPanel=new JPanel(new FlowLayout(FlowLayout.LEFT, 15, 10));
        topPanel.setBackground(new Color(240, 240, 240));

        JLabel lblChoose=new JLabel("Wlaczyc algorytm vizualizacji graphu:");
        lblChoose.setFont(new Font("Arial", Font.BOLD, 12));

        JButton btnFR=new JButton("Fruchterman-Reingold");
        JButton btnTutte=new JButton("Tutte");

        btnFR.addActionListener(e->runAndLoadAlgorithm("fr"));
        btnTutte.addActionListener(e->runAndLoadAlgorithm("tutte"));

        topPanel.add(lblChoose);
        topPanel.add(btnFR);
        topPanel.add(btnTutte);
        add(topPanel, BorderLayout.NORTH);

        setVisible(true);
    }


    private void runAndLoadAlgorithm(String algoFlag) {
        try {

            String cmd = "./grafy -i graf_testowy.txt -a " + algoFlag + " -o output.txt";
            Process process=Runtime.getRuntime().exec(cmd);
            int exitCode=process.waitFor();
            
            if (exitCode== 0) {
                loadCoordinates();
                graphPanel.resetView(); 
                repaint();              
            } else {
                JOptionPane.showMessageDialog(this, 
                    "blad dzialania programu" + exitCode, 
                    "blad", JOptionPane.ERROR_MESSAGE);
            }

        } catch (IOException | InterruptedException ex) {
            JOptionPane.showMessageDialog(this, 
                "nie udalo sie skompilowac programu", 
                "blad innicylizacji", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void loadGraphEdges() {
        File originalFile=new File(".txt");
        if (!originalFile.exists()) return;
        try (java.util.Scanner sc=new java.util.Scanner(originalFile)) {
            sc.useLocale(java.util.Locale.US);
            while (sc.hasNext()) {
                String token=sc.next();
                if (token.startsWith("args") {
        SwingUtilities.invokeLater(()->new MainFrame());
    }
}
