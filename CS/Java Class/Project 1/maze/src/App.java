import java.io.File;
import java.util.Scanner;
// Daniel Yankovich CS114 H02
// Prof. Kapleau
// 02/07/2022
public class App {
    public static void main(String[] args) throws Exception {
        try{
            File  in = new File("maze.dat");
            Scanner scan = new Scanner(in);
            int rows, columns;
            int startRow =0, startColumn= 0;
            if(scan.hasNextLine()){
                String dimensions = scan.nextLine();
                rows = Integer.parseInt(dimensions.substring(0, dimensions.indexOf(" ")));
                columns = Integer.parseInt(dimensions.substring(dimensions.indexOf(" ")+1, dimensions.length()));
                maze = new char[rows][columns];
            }
            int row = 0;
            while(scan.hasNextLine()){
                String nextLine = scan.nextLine();
                for(int i = 0; i<nextLine.length(); i++){
                    maze[row][i] = nextLine.charAt(i);
                    if(nextLine.charAt(i) == '+'){
                        startRow = row;
                        startColumn = i;
                    }
                }
                row++;
            }
            scan.close();
            if(solve(startRow,startColumn)){
                outputMaze();
            }else{
                System.out.println("Maze is unsolvable.");
            }
        }catch (Exception e) {
            System.err.println("An error happened");
            e.printStackTrace();
        }
        
    }
    private static char[][] maze;
    public static boolean solve(int currentRow, int currentColumn){
        if(maze[currentRow][currentColumn] == '-'){
            return true;
        }
        if(maze[currentRow][currentColumn] == 'X'){
            return false;
        }
        if(maze[currentRow][currentColumn] == '+' && 0 !=currentColumn){
            return false;
        }
        maze[currentRow][currentColumn] = '+';
        if(solve(currentRow, currentColumn+1)){
            return true;
        }
        if(solve(currentRow, currentColumn-1)){ 
            return true;
        }
        if(solve(currentRow+1, currentColumn)){
            return true;
        }
        if(solve(currentRow-1, currentColumn)){
            return true;
        }
        maze[currentRow][currentColumn] = '.';
        return false;
    }
    private static void outputMaze(){
        for(int i =0; i < maze.length; i++){
            for(int x= 0; x < maze[0].length; x++){
                System.out.print(maze[i][x]);
            }
            System.out.println();
        }
    }
}
