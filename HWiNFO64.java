import java.io.IOException;

public class HWiNFO64 {

    public static boolean isHWiNFORunning() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec(System.getenv("windir") + "\\system32\\" + "tasklist.exe");
        String tasksList = new String(process.getInputStream().readAllBytes());
        return tasksList.contains("HWiNFO64.EXE");
    }

    public static void openHWiNFO() throws IOException {
        if (!isHWiNFORunning()) {
            Runtime.getRuntime().exec("C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE");
            System.out.println("HWiNFO64.EXE is opened.");
        } else {
            System.out.println("HWiNFO64.EXE is already running.");
        }
    }

    public static void killHWiNFO() throws IOException {
        if (isHWiNFORunning()) {
            Runtime.getRuntime().exec("taskkill /F /IM HWiNFO64.EXE");
            System.out.println("HWiNFO64.EXE process terminated.");
        } else {
            System.out.println("HWiNFO64.EXE process is not running.");
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        // First, kill the HWiNFO64 process if it's running
        killHWiNFO();

        // Add a small delay (in milliseconds)
        try {
            Thread.sleep(1000);  // You can adjust the duration as needed
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Then, open the HWiNFO64 process
        openHWiNFO();
    }
}
