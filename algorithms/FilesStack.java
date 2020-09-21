import java.io.File;

public class FilesStack {
    private static void _listFiles(String path, int numTabs) {
        System.out.println(String.format("_listFiles, %s, %d", path, numTabs));
        File file = new File(path);
        String[] files = file.list();
        /*for (int i = 0; i < files.length; i++) {
            System.out.print(files[i] + " ");
        }
        System.out.println();*/
        
        for (String x : files) {
            for (int i = 0; i < numTabs; i++) {
                System.out.print("\t");
            }
            File xf = new File(x);
            System.out.println(xf.getAbsolutePath());
            if (xf.isDirectory()) {
                _listFiles(xf.getAbsolutePath(), numTabs + 1);
            }
        }
    }

    public static void listFiles(String path) {
        _listFiles(path, 0);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            String msg = String.format("Usage: %s path",
                FilesStack.class.getSimpleName());
            System.out.println(msg);
            System.exit(1);
        }
        listFiles(args[0]);
    }
}

